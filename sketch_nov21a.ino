#include <TinyGPS++.h>
#include <HardwareSerial.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ArduinoJson.h>

const int RXPin = 16; // Define the RX pin connected to GPS module
const int TXPin = 17; // Define the TX pin connected to GPS module
HardwareSerial SerialGPS(2); // Create a hardware serial port for GPS

TinyGPSPlus gps; // Create a TinyGPS++ object

const char* ssid = "Ansh"; // Enter your WiFi SSID
const char* password = "12345678"; // Enter your WiFi Password

WebServer server(80); // Create a web server on port 80

void setup() {
  Serial.begin(115200);
  SerialGPS.begin(9600, SERIAL_8N1, RXPin, TXPin); // Initialize GPS serial port

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP()); // Print the IP address
  server.on("/location", handleLocation); // Endpoint for getting location data
  server.begin();
}

void loop() {
  while (SerialGPS.available() > 0) {
    if (gps.encode(SerialGPS.read())) {
      if (gps.location.isUpdated()) {
        Serial.print("Latitude: ");
        Serial.println(gps.location.lat(), 6);
        Serial.print("Longitude: ");
        Serial.println(gps.location.lng(), 6);
      }
    }
  }
  server.handleClient(); // Handle client requests
}

void handleLocation() {
  DynamicJsonDocument jsonDoc(256);
  JsonObject root = jsonDoc.to<JsonObject>();

  root["latitude"] = gps.location.lat();
  root["longitude"] = gps.location.lng();

  String response;
  serializeJson(jsonDoc, response);

  server.send(200, "application/json", response);
}