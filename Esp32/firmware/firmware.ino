#include <ArduinoJson.h>
#include <ESPmDNS.h>
#include <HTTPClient.h>
#include <Preferences.h>
#include <Update.h>
#include <WebServer.h>
#include <WiFiClient.h>

#include "FS.h"
#include "SPIFFS.h"
#include "WiFi.h"
#include "index.h"
#include "reset.h"


// =================================> Variabless and objects declarations <================================
Preferences preferences;
WebServer server(80);


bool resetMode = false;
const char* ssid_ap = "AutomathausNodeTest";
const char* password_ap = "0123456789";

const int firmwareVersion = 1;


// =================================> Setup() <================================
void setup() {
    Serial.begin(115200);
    preferences.begin("credentials", false);

    // Wifi stuff
    WiFi.setHostname("AutomathausNode");
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);

    // Pref. retival and usage
    String networkSSID = preferences.getString("netssid", "");
    String password = preferences.getString("password", "");

    // debug
    Serial.println(networkSSID);
    Serial.println(password);

    // Tries to connect to network
    startSTAmode(networkSSID.c_str(), password.c_str());

    server.enableCORS();  // CORS



    // Setting up the handlers

    // root
    server.on("/", []() {
        if (!resetMode) {
            server.send(200, "text/html", index_html);
        } else {
            server.send(200, "text/html", reset_html);
        }
    });

    // Get the networks
    server.on("/networks", []() { 
		server.send(200, "application/json", scanWIFI()); 
	});

    // handles the reset password form
    server.on("/submit", HTTP_OPTIONS, []() {
        server.send(200);  // Respond with HTTP 200 OK for preflight
    });

    server.on("/submit", HTTP_POST, handlePost);
    server.onNotFound(handleNotFound);

    // Starts http server
    server.begin();
    Serial.println("HTTP server started");
}



// Main loop
void loop() {
    server.handleClient();
    delay(2);
}

// Utility function, reboots the Esp32 and outputs the reason to the serial port.
static void rebootEspWithReason(String reason) {
    Serial.println(reason);
    delay(1000);
    ESP.restart();
}


// =================================> WiFi connection and credential reset <================================

// Starts the device in Station mode.
void startSTAmode(const char SSID[], const char password[]) {
    int timeout = 0;
    WiFi.mode(WIFI_STA);
    WiFi.begin(SSID, password);
    Serial.println("");

    // Wait for connection
    while (WiFi.status() != WL_CONNECTED && timeout < 10) {
        delay(500);
        Serial.print(".");
        timeout++;
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.print("Connected to ");
        Serial.println(SSID);
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
        resetMode = false;

        if (MDNS.begin("esp32")) {
            Serial.println("MDNS responder started");
        }

        preferences.end();
    } else {
        Serial.println("Connection failed.");
        WiFi.disconnect();
        startAPmode();
    }
}

// Starts the device in Access point mode for password reset.
void startAPmode() {
    Serial.println("Starting configuration Access point");
    resetMode = true;

    WiFi.mode(WIFI_AP);
    WiFi.softAP(ssid_ap, password_ap);
    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);
}

// Scans the wifi networks in the area and returns a Json string.
String scanWIFI() {
    String output = "";
    int n = WiFi.scanNetworks();
    Serial.println("Scan done");

    DynamicJsonDocument doc(400);
    JsonArray networks = doc.createNestedArray("networks");

    if (n == 0) {
        Serial.println("no networks found");
    } else {
        for (int i = 0; i < n; ++i) {
            networks.add(WiFi.SSID(i));
        }

        WiFi.scanDelete();
    }

    serializeJsonPretty(doc, output);
    return output;
}

// Handle the reset password post request and writes to internal memory, then
// restarts the system.
void handlePost() {
    StaticJsonDocument<100> doc;
    preferences.clear();

    if (server.hasArg("plain")) {
        String message = server.arg("plain");
        Serial.println("Received data: " + message);
        server.send(200, "text/plain", "{\"message\":\"Changed credentials\"}");
        DeserializationError error = deserializeJson(doc, message);

        if (error) {
            Serial.print("deserializeJson() failed: ");
            Serial.println(error.c_str());
            return;
        }

        const char* netSSID = doc["SSID"];
        const char* password = doc["password"];

        preferences.putString("netssid", netSSID);
        preferences.putString("password", password);

        Serial.println(netSSID);
        Serial.println(password);
        delay(200);

        preferences.end();

        Serial.println("Restarting in 3 seconds...");
        delay(3000);

        // Restart ESP
        rebootEspWithReason("Rebooting to apply the configuration settings...");
    } else {
        server.send(400, "text/plain", "Bad Request");
    }
}

// Here to make CORS work.
void handleNotFound() { server.send(404, "text/plain", "Not found 404"); }







// =================================> OTA Updates <================================

void OTA_UpdateRoutine(){
	
}

// bool checkFirmware() {
//     HTTPClient http;
//     http.begin(baseUrl + checkFile);
//     int httpCode = http.GET();
//     bool stat = false;
//     String payload = http.getString();
//     Serial.println(payload);
//     StaticJsonDocument<100> json;
//     deserializeJson(json, payload);

//     if (httpCode == HTTP_CODE_OK) {
//         fwVersion = json["versionCode"].as<int>();
//         fwName = json["fileName"].as<String>();
//         fwUrl = baseUrl + fwName;
//         if (fwVersion > currentVersion) {
//             Serial.println("Firmware update available");
//             stat = true;
//         } else {
//             Serial.println("You have the latest version");
//         }
//         Serial.print("Version: ");
//         Serial.print(fwName);
//         Serial.print("\tCode: ");
//         Serial.println(fwVersion);
//     }
//     http.end();

//     return stat;
// }


bool downloadFirmware(String firmwareUrl) {
    HTTPClient http;
    bool success = false;

    File f = SPIFFS.open("/update.bin", "w");
    if (f) {
        http.begin(firmwareUrl);
        int httpCode = http.GET();
        if (httpCode > 0) {
            if (httpCode == HTTP_CODE_OK) {
                Serial.println("Downloading...");
                http.writeToStream(&f);
                success = true;
            }
        } else {
            Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }
        f.close();
    } else {
        Serial.println("failed to open /update.bin");
    }
    http.end();

    return success;
}


void performUpdate(Stream &updateSource, size_t updateSize) {
    if (Update.begin(updateSize)) {
        size_t written = Update.writeStream(updateSource);
        if (written == updateSize) {
            Serial.println("Written : " + String(written) + " successfully");
        } else {
            Serial.println("Written only : " + String(written) + "/" + String(updateSize) + ". Retry?");
        }

        if (Update.end()) {
            Serial.println("OTA done!");

            if (Update.isFinished()) {
                Serial.println("Update successfully completed. Rebooting...");
            } else {
                Serial.println("Update not finished? Something went wrong!");
            }

        } else {
            Serial.println("Error Occurred. Error #: " + String(Update.getError()));
        }

    } else {
        Serial.println("Not enough space to begin OTA");
    }
}



void updateFromFS(fs::FS &fs) {
    File updateBin = fs.open("/update.bin");
    if (updateBin) {
        if (updateBin.isDirectory()) {
            Serial.println("Error, update.bin is not a file");
            updateBin.close();
            return;
        }

        size_t updateSize = updateBin.size();

        if (updateSize > 0) {
            Serial.println("Trying to start update");
            performUpdate(updateBin, updateSize);
        } else {
            Serial.println("Error, file is empty");
        }

        updateBin.close();

        // when finished remove the binary from spiffs to indicate end of the process
        Serial.println("Removing update file");
        fs.remove("/update.bin");

        rebootEspWithReason("Rebooting to complete OTA update");
    } else {
        Serial.println("Could not load update.bin from spiffs root");
    }
}