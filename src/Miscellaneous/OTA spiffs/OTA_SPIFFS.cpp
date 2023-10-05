#include "OTA_SPIFFS.h"
#define JSON_NAME "firmwareUpdate.json"

const String firmwareFolderUrl = "https://raw.githubusercontent.com/Lorenx03/AutomathausFirmware/main/Esp32/";
String firmwareFilename = "firmware.bin";
const int firmwareVersion = 0;

void OTA_UpdateRoutine(){
    Serial.println("----> Checking for updates <----");
        if (checkForUpdates()) {
            if (SPIFFS.exists("/update.bin")) {
                SPIFFS.remove("/update.bin");
                Serial.println("Removed existing update file");
            }
            if (downloadFirmware(firmwareFolderUrl + firmwareFilename)) {
                Serial.println("Download complete");
                updateFromFS(SPIFFS);
            } else {
                Serial.println("Download failed");
            }
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


bool downloadFirmware(String firmwareUrl) {
    HTTPClient http;
    bool success = false;

    File f = SPIFFS.open("/update.bin", FILE_WRITE);
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

        ESP.restart();
    } else {
        Serial.println("Could not load update.bin from spiffs root");
    }
}