#include <ArduinoJson.h>
#include <WiFiClient.h>

#include "index.h"
#include "reset.h"

#define JSON_NAME "firmwareUpdate.json"

// Check if the code is being compiled for ESP32
#ifdef ESP32
    #define BOARD_NAME "ESP32" // Define a board name
    #include <WiFi.h>
    #include <HTTPClient.h>
    #include <WebServer.h>
    #include <ESPmDNS.h>
    #include <Preferences.h>

    WebServer server(80);
#endif

// Check if the code is being compiled for ESP8266
#ifdef ESP8266
    #define BOARD_NAME "ESP8266" // Define a board name
    #include <ESP8266WiFi.h>
    #include <ESP8266WebServer.h>
    #include <ESP8266HTTPClient.h>
    #include <ESP8266httpUpdate.h>
    #include <ESP8266mDNS.h>
    #include <Preferences.h>

    ESP8266WebServer server(80);
#endif


// =================================> Variables and objects declarations <================================
#define HOSTNAME "AutomathausNode"
#define AP_PASSWORD "0123456789"

Preferences preferences;

const String firmwareFolderUrl = "https://raw.githubusercontent.com/Lorenx03/AutomathausFirmware/main/" + String(BOARD_NAME) + "/";
String firmwareFilename = "firmware.bin";
const int firmwareVersion = 0;


// =================================> Setup() <================================
void setup() {
    // if (SPIFFS.begin()){
    //     Serial.println("Reading the filesystem...");
    // }else{
    //     Serial.println("Problems reading the filesystem");
    // }

    Serial.begin(115200);
    preferences.begin("credentials", false);

    // Wifi stuff
    WiFi.setHostname(HOSTNAME);
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);

    // Pref. retival and usage
    String networkSSID = preferences.getString("netssid", "");
    String password = preferences.getString("password", "");

    // debug
    Serial.println("");
    Serial.println(networkSSID);
    Serial.println(password);

    // Tries to connect to network
    if (tryConnect(networkSSID.c_str(), password.c_str())) {
        Serial.println("Connection failed.");
        startResetMode();
    }
    
    //server.enableCORS();  // CORS
    Serial.println("FIRMWARE VER: " + String(firmwareVersion));


    // Setting up the handlers

    // root
    server.on("/", []() {
        switch (WiFi.getMode()) {
            case WIFI_STA:
                server.send(200, "text/html", index_html);
            break;

            case WIFI_AP:
                server.send(200, "text/html", reset_html);
            break;
            
            default:
                server.send(200, "text/html", "Error");
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




// Timer variables
unsigned long previousMillis = 0;
//const long interval = 60000;
const long interval = 10000;

// Main loop
void loop() {
    server.handleClient();

    if (WiFi.getMode() == WIFI_STA) {
        unsigned long currentMillis = millis();
        if (currentMillis - previousMillis >= interval) {
            previousMillis = currentMillis;
            
            //OTA_UpdateRoutine();
        }
    }
    
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
bool tryConnect(const char SSID[], const char password[]) {
    int timeout = 0;
    WiFi.mode(WIFI_STA);
    WiFi.begin(SSID, password);
    Serial.println("");

    // Wait for connection
    while (WiFi.status() != WL_CONNECTED && timeout < 30) {
        delay(500);
        Serial.print(".");
        timeout++;
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.print("Connected to ");
        Serial.println(SSID);
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
        preferences.end();

        if (MDNS.begin(HOSTNAME)) {
            Serial.println("MDNS responder started");
        }

        return false;
    } else {
        WiFi.disconnect();
        return true;
    }
}

// Starts the device in Access point mode for password reset.
void startResetMode() {
    randomSeed(millis());
    String randomStr = "";
    for (int i = 0; i < 5; i++) {
        int randomNumber = random(0, 10); // Generate a random number between 0 and 9
        randomStr += String(randomNumber);
    }

    Serial.println("Starting configuration Access point");
    WiFi.mode(WIFI_AP);
    WiFi.softAP(HOSTNAME + randomStr, AP_PASSWORD);
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
    Serial.println("----> Checking for updates <----");
        if (checkForUpdates()) {
            
        }
}


bool checkForUpdates() {
    bool out = false;
    int jsonFirmwareVer = 0;
    
    HTTPClient http;
    http.begin(firmwareFolderUrl + JSON_NAME);
    int httpCode = http.GET();

    String payload = http.getString();
    //Serial.println(payload);

    StaticJsonDocument<100> json;
    deserializeJson(json, payload);

    if (httpCode == HTTP_CODE_OK) {
        jsonFirmwareVer = json["versionCode"].as<int>();
        firmwareFilename = json["fileName"].as<String>();

        Serial.print("Version: ");
        Serial.print(firmwareFilename);
        Serial.print("\tCode: ");
        Serial.println(jsonFirmwareVer);

        http.end();
        
        if (jsonFirmwareVer > firmwareVersion) {
            Serial.println("Firmware update available");
            out = true;
        } else {
            Serial.println("You have the latest version");
            out = false;
        }
    }

    return out;
}