#include <ArduinoJson.h>
#include "WiFi.h"
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <Preferences.h>
#include "website.h"

// const char* networkName = "Automathaus";
// const char* password = "AutomatPass2023";
Preferences preferences;

const char* ssid_ap = "AutomathausNodeTest";
const char* password_ap = "0123456789";

WebServer server(80);

void setup() {
  Serial.begin(115200);
  preferences.begin("credentials", false);
  // char* networkSSID = "Automathaus";
  // char* password = "AutomatPass2023";

  WiFi.setHostname("AutomathausNode");
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  String networkSSID = preferences.getString("netssid", "");
  String password = preferences.getString("password", "");
  
  Serial.println(networkSSID);
  Serial.println(password);
  startSTAmode(networkSSID.c_str(), password.c_str());
  

  server.enableCORS();
  server.on("/", []() {
    server.send(200, "text/html", index_html);
  });

  server.on("/networks", []() {
    server.send(200, "application/json", scanWIFI());
  });

  server.on("/submit", HTTP_OPTIONS, [](){
    server.send(200); // Respond with HTTP 200 OK for preflight
  });

  server.on("/submit", HTTP_POST, handlePost);
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
  delay(2);
}

void startSTAmode(const char SSID[], const char password[]){
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


void startAPmode(){
  Serial.println("Starting configuration Access point");
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid_ap, password_ap);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
}


String scanWIFI(){
  String output = "";
  int n = WiFi.scanNetworks();
  Serial.println("Scan done");

  DynamicJsonDocument  doc(400);
  JsonArray networks = doc.createNestedArray("networks");

  if (n == 0) {
    Serial.println("no networks found");
  } else {
    for (int i = 0; i < n; ++i) {
      networks.add(WiFi.SSID(i));
    }

    WiFi.scanDelete();
  }

  serializeJsonPretty(doc,output);
  return output;
}








void handlePost() {
  StaticJsonDocument<100> doc;
  preferences.clear();

  if (server.hasArg("plain"))
  {
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
    ESP.restart();
  }
  else
  {
    server.send(400, "text/plain", "Bad Request");
  }
}



void handleNotFound() {
  server.send(404, "text/plain", "Not found 404");   
}