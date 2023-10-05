#ifndef OTA_SPIFFS_h
#define OTA_SPIFFS_h

#include <WiFiClient.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include "FS.h"
#include <HTTPClient.h>
#include <WebServer.h>
#include <Preferences.h>
#include <Update.h>
#include "SPIFFS.h"

void OTA_UpdateRoutine();
bool checkForUpdates();
bool downloadFirmware(String firmwareUrl);
void performUpdate(Stream &updateSource, size_t updateSize);
void updateFromFS(fs::FS &fs);

#endif