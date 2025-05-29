#ifndef COMM_H
#define COMM_H

// #include <WiFiUdp.h>
// #include <TelnetSpy.h>
#include <WiFi.h>
#include <Wire.h>

// ====================================
// WiFI Settings

// const char * ssidHome = "Matern";       // your network SSID (name)
// const char * passHome = "yourwelcome";  // your network password

const char * ssidHome = "MPEGuest";       // your network SSID (name)
const char * passHome = "wirelessmpe";  // your network password

int WiFiRetryCount = 0;
int WiFiretryMax = 20;

// ====================================
// Terminal Settings

// TelnetSpy telnet;

// bool sysflag_terminalActive = false;

// void telnetConnected() {
//   Serial.println(F("Telnet connection established."));
//   bitSet(sysFlags, sysflag_terminalActive);
// }

// void telnetDisconnected() {
//   Serial.println(F("Telnet connection closed."));
//   bitClear(sysFlags, sysflag_terminalActive);
// }

// void disconnectClientWrapper() {
//   telnet.disconnectClient();
//   bitClear(sysFlags, sysflag_terminalActive);
// }

// ====================================
// UDP Settings

// WiFiUDP displayUDP;

// #define MAX_IP_ADDRESSES 5

// IPAddress remoteIPs[MAX_IP_ADDRESSES] = {
//     IPAddress(192, 168, 1, 221),
//     IPAddress(192, 168, 1, 222),
//     IPAddress(192, 168, 1, 223),
//     IPAddress(192, 168, 1, 224),
//     IPAddress(192, 168, 1, 225)
// };
// unsigned int remotePort = 12345;

// ============================================================================
// ============================================================================
// Setup
// ============================================================================

void setupWiFi() {

  WiFi.mode(WIFI_STA);                      // Set WiFi to station mode
  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);
  WiFi.begin(ssidHome, passHome);           // Connect to WiFi network

  Serial.println("WiFi begin");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    WiFiRetryCount++;
    Serial.print(".");

    if(WiFiRetryCount > WiFiretryMax) {
      WiFi.mode(WIFI_OFF);
	  bitClear(sysFlags, sysFlag_WiFiConnected);
	  WiFiRetryCount = 0;
	  Serial.println();
	  Serial.println("WiFi Connection Failed");
      return; // exit function
    }
  }

  bitSet(sysFlags, sysFlag_WiFiConnected);

  Serial.println("WiFi connected");
  Serial.println("SSID : " + WiFi.SSID());
  Serial.println("IP   : " + WiFi.localIP().toString());
  Serial.println("MAC  : " + WiFi.macAddress());

  Serial.println("Setup Complete: WiFi");
  delay(100);
}

void setupComms() {

  Wire.begin(SDA, SCL);

  // addd SPI bus for external devices? not internal SPI bus with flash


  // Initialize I2C communication
                        // Set up UDP
                        // displayUDP.begin(remotePort);
                        // Serial.print("UDP Server Started, port: ");
                        // Serial.println(String(remotePort));

  // // Set up Telnet
  // telnet.setWelcomeMsg(F("|=== Welcome to Weather Staion Telnet ===| \r\n > enter ? for list of commands \r\n\n"));
  // telnet.setCallbackOnConnect(telnetConnected);
  // telnet.setCallbackOnDisconnect(telnetDisconnected);
  // telnet.setFilter(char(1), F("\r\nNVT command: AO\r\n"), disconnectClientWrapper);
  // telnet.setDebugOutput(false); // Set to true to enable debug output
  // // telnet.setBufferSize(0); //Set it to 0 to disable buffering
  // telnet.setStoreOffline(false); // Store data if Telnet is not connected

  // telnet.begin(9600);
  // Serial.println(F("Telnet Server Started"));
}

// ============================================================================
// ============================================================================
// Update
// ============================================================================

void updateComms() {
	static unsigned long lastCheckTime = 0;
    unsigned long currentTime = millis();

    // telnet.handle(); // Handle Telnet connection

	// Check WiFi connection every 1 minute (60000 milliseconds)
    if (currentTime - lastCheckTime >= 60000) {
        lastCheckTime = currentTime;
        if (WiFi.status() != WL_CONNECTED) {
            setupWiFi();
        }
    }
}

// ====================================
// Comms
// ====================================

// Function to send the structure over UDP
// void sendWXDEvent(unsigned long currentEpochTime, float cTemperature, float cHumidity, float cPressure, float cWindSpeed, float cLightLevel, float cEnclosureTemp) {
//   //Build Data Stucture
//   outgoingMsg.id = 1;
//   outgoingMsg.epochTime = currentEpochTime; //need to add NTP time
//   outgoingMsg.temperature = cTemperature; //need better ewawy to stro data or use globals......
//   outgoingMsg.humidity = cHumidity;
//   outgoingMsg.pressure = cPressure;
//   outgoingMsg.windSpeed = cWindSpeed;
//   outgoingMsg.lightLevel = cLightLevel;
//   outgoingMsg.enclosureTemp = cEnclosureTemp;

//   outgoingMsg.nodeStatus = sysFlags;    // set status flags for outgoing data

//     // Send UDP Data to multiple IP addresses
//   for (int i = 0; i < MAX_IP_ADDRESSES; i++) {
//       displayUDP.beginPacket(remoteIPs[i], remotePort);
//       displayUDP.write((uint8_t*)&outgoingMsg, sizeof(outgoingMsg));
//       displayUDP.endPacket();
//   }

//   // Send Telnet Data
//   if(bitRead(sysFlags, sysflag_terminalActive)) {
//       telnet.print(outgoingMsg.epochTime);
//       telnet.print("  T: ");
//       telnet.print(outgoingMsg.temperature);
//       telnet.print("  H: ");
//       telnet.print(outgoingMsg.humidity, 0);
//       telnet.print("  P: ");
//       telnet.print(outgoingMsg.pressure, 0);
//       telnet.print("  W: ");
//       telnet.print(outgoingMsg.windSpeed, 0);
//       telnet.print("  L: ");
//       telnet.print(outgoingMsg.lightLevel, 0);
// 	  telnet.print("  ET: ");
// 	  telnet.println(outgoingMsg.enclosureTemp, 0);

//   }
// }

// ====================================
// Telnet Functions
// ====================================

// String readTelnetString() {
//   String receivedData = "";
//   while (telnet.available()) {
//       char incomingChar = (char)telnet.read();
//       if (incomingChar == '\n') {
//       } else {
//           receivedData += incomingChar;
//       }
//   }
//   receivedData.trim(); // Remove any leading/trailing whitespace
//   return receivedData;
// }

// void processTelnetString(String data) {
//   if (data == "w") {
//     Serial.println("Processing (w) command");

//   } else if (data == "d") {
//     Serial.println("Processing (d) command");  // send data string

//   } else if (data == "s") {
//     Serial.println("Processing (s) command");  // send status update on sensor and NTP

//   } else if (data == "c") {
//     Serial.println("Processing (c) command");  // enter calibration mode

//   } else if (data == "r") {
//     Serial.println("Processing (r) command");  // restart ESP
//     ESP.restart();
//   } else if (data == "?") {
//     Serial.println("Processing (?) command");  // request list of commannds

//   } else {
//     Serial.println("Unknown Command");
//   }
// }

#endif // COMM_H