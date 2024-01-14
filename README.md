# GPS-based-Toll-Deduction

## Creating local server
### Hardware Used
- ESP32 Module
- NEO 6M GPS Module
 
 #### Connection Layout:
- Neo-6M GPS Module (common pin configurations)
- VCC → 5V or 3.3V (based on module specs)
- GND → Ground
- TX → RXPin (16 in this case)
- RX → TXPin (17 in this case)
- ESP32 Board

Connect the required pins for communication and power to the GPS module:
Use the HardwareSerial ports for communication (Serial2 in this case for RX and TX).
Connect GND and VCC (5V or 3.3V, based on module requirements) to the appropriate pins on the ESP32.
#### Physical Wiring:
 - Neo-6M GPS Module to ESP32:
 - VCC of GPS module to 5V or 3.3V pin on the ESP32.
 - GND of GPS module to GND pin on the ESP32.
 - TX of GPS module to RXPin (16) of the ESP32.
 - RX of GPS module to TXPin (17) of the ESP32.

 #### Functioning
 This code is an Arduino sketch written for an ESP32 microcontroller. It combines the functionality of reading GPS coordinates from a Neo-6M GPS module and serving those coordinates through a simple web server 
 using the ESP32's built-in Wi-Fi capabilities. Here's an explanation of the main components and functionalities:

 #### Libraries Used:
 - TinyGPS++: A library for parsing NMEA data from a GPS module, in this case, the Neo-6M GPS module.
 - HardwareSerial: Used for serial communication with the GPS module (SerialGPS) and for debugging through the Arduino IDE (Serial).
 - WiFi and WiFiClient: Enable the ESP32 to connect to a Wi-Fi network.
 - WebServer: A library for setting up a web server on the ESP32.
 - ArduinoJson: Used for creating and parsing JSON data.
 #### Global Variables:
 - RXPin, TXPin, SerialGPS: Define the pins for serial communication with the GPS module.
 - gps: An instance of the TinyGPS++ library for handling GPS data.
 - ssid, password: Wi-Fi network credentials.
 - server: An instance of the WebServer class for handling HTTP requests.
 #### Setup Function:
 - Serial.begin(115200): Initialize the serial communication for debugging purposes.
 - SerialGPS.begin(9600, SERIAL_8N1, RXPin, TXPin): Initialize the serial communication for the GPS module. The GPS module is connected to pins RXPin and TXPin.
 - WiFi.begin(ssid, password): Connect to the specified Wi-Fi network.
 - while (WiFi.status() != WL_CONNECTED): Wait until the ESP32 is connected to the Wi-Fi network.
 - server.on("/location", handleLocation): Define an HTTP endpoint ("/location") that triggers the handleLocation function when accessed.
 - server.begin(): Start the web server.
 #### Loop Function:
 - while (SerialGPS.available() > 0): Read data from the GPS module when available.
 - if (gps.encode(SerialGPS.read())): Parse the NMEA data from the GPS module using the TinyGPS++ library.
 - if (gps.location.isUpdated()): If the GPS location is updated, print the latitude and longitude to the Serial monitor.
 - server.handleClient(): Handle incoming client requests (e.g., HTTP requests for the "/location" endpoint).
 - handleLocation Function:
 - DynamicJsonDocument jsonDoc(256): Create a dynamic JSON document with a buffer size of 256 bytes.
- JsonObject root = jsonDoc.to<JsonObject>(): Create a JSON object.
 - root["latitude"] = gps.location.lat(): Store the latitude in the JSON object.
 - root["longitude"] = gps.location.lng(): Store the longitude in the JSON object.
 - serializeJson(jsonDoc, response): Serialize the JSON document into a String.
 - server.send(200, "application/json", response): Send an HTTP response with a status code of 200 (OK), indicating success, and the JSON data.

In summary, this code reads GPS coordinates from a Neo-6M GPS module, connects to Wi-Fi, sets up a web server, and serves the GPS coordinates in JSON format when the "/location" endpoint is accessed. The coordinates are continuously updated in the loop function.





