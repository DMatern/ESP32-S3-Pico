#include <Arduino.h>
// #include <Wire.h>

#define ESP32

// ====================================
// Flags

uint8_t sysFlags = 0x00;
// const byte sysFlag_newData = 0; // sysFlags bit 0:  0 = inactive	1 = active
// const byte sysFlag_ = 1;  // sysFlags bit 1:  0 = inactive	1 = active
// const byte sysFlag_ = 2;             // sysFlags bit 2:  0 = inactive	1 = active
// const byte sysFlag_TareHold = 3; // sysFlags bit 3:  0 = inactive	1 = active
// const byte sysFlag_Tare = 4;     // sysFlags bit 4:  0 = inactive	1 = active
// const byte sysFlag_Select = 5;   // sysFlags bit 5:  0 = inactive	1 = active
// const byte sysFlag_UP = 6;       // sysFlags bit 6:  0 = inactive	1 = active
const byte sysFlag_WiFiConnected = 7;       // sysFlags bit 7:  0 = inactive	1 = active

// ====================================
// Global Variables

// ====================================
// Include Files

#include <U8g2lib.h>

// #include <fastled.h>  //Onboard RGB LED Driver
#include <comm.h>  //Communication Library
// #include <flash.h> // Flash Memory Library
#include <GPIO.h>  // GPIO Library

// Initialize the display
U8G2_SSD1306_64X32_1F_2W_SW_I2C u8g2(U8G2_R0, /* clock=*/SCL, /* data=*/SDA, /* reset=*/U8X8_PIN_NONE);

// ============================================================================
// Function Declarations

// ============================================================================
// Setup
// ============================================================================

void setup() {

  Serial.begin(115200);

  u8g2
  delay(1000); // Allow time for Serial Monitor to open

  // Wire.begin(SDA, SCL); // Initialize I2C communication


  // Initialize system flags
  sysFlags = 0x00;

  // Set up WiFi connection
  setupWiFi();

  // Set up communication protocols
  setupComms();

  // Initialize Flash Memory
  setupFlash();

  // Initialize GPIO pins
  setupGPIO();

  // Print initial status
  Serial.println("Setup Complete");
}

// ============================================================================
// Loop
// ============================================================================

void loop() {

  updateGPIO(); // Update GPIO state

}

// ====================================
// State Machine
// ====================================

// ====================================
// Misc Functions
// ====================================