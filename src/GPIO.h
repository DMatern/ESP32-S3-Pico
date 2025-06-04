#ifndef GPIO_H
#define GPIO_H

// ====================================
// Include Files

#include <Arduino.h>
#include <SerialFlash.h>
#include <Wire.h>
#include <SPI.h>
// #include <driver/spi_common.h> // Ensure VSPI_HOST is defined for ESP32

// ====================================
// RGB NanoPixel LED Driver
#include <FastLED.h>

#define PIN_LEDRGB 21 // GPIO pin connected to WS2812B
#define NUM_LEDS 1  // Number of LEDs in the strip

// Define the array of leds
CRGB leds[NUM_LEDS];

// Time scaling factors for each component
#define TIME_FACTOR_HUE 60
#define TIME_FACTOR_SAT 100
#define TIME_FACTOR_VAL 100

// ====================================
// I2C


// ====================================
// SPI

// ====================================
// FLash Memory

// Define the SPI pins
#define CS_PIN 29   // SPICS0
#define CLK_PIN 30  // SPICLK
#define MISO_PIN 31 // SPIQ
#define MOSI_PIN 32 // SPID
#define WP_PIN 28   // SPIWP
#define HD_PIN 27   // SPIHD

SPIClass flashSPI(FSPI); // Use FSPI for ESP32-S3, which has only FSPI and optionally HSPI

// If you want to specify pins directly, you can do so when calling begin():
// flashSPI.begin(CLK_PIN, MISO_PIN, MOSI_PIN, CS_PIN);

// ============================================================================
// Setup
// ============================================================================

void setupGPIO() {
    // Initialize GPIO pins here if needed
    // For example, set pin modes or initial states

    //NEOPixel LED setup
    FastLED.addLeds<WS2812, PIN_LEDRGB, GRB>(leds, NUM_LEDS).setRgbw(RgbwDefault());
    FastLED.setBrightness(128); // Set global brightness to 50%

    //SPI Flash Memory setup


    Serial.println("GPIO setup complete.");
}

void setupFlash()
{
  // Initialize SPI with custom pins
  flashSPI.begin(CLK_PIN, MISO_PIN, MOSI_PIN, CS_PIN);
  pinMode(CS_PIN, OUTPUT);
  digitalWrite(CS_PIN, HIGH);

  // Initialize SerialFlash library
  if (!SerialFlash.begin(CS_PIN, &flashSPI))
  {
    Serial.println("Failed to initialize SerialFlash chip");
    while (1)
      ;
  }
  Serial.println("SerialFlash chip initialized successfully");
}

// ============================================================================
// Update
// ============================================================================

void updateGPIO() {

    
}

// ====================================
// LED unctions
// ====================================

void cycleRGB() {
  uint32_t ms = millis();

  for (int i = 0; i < NUM_LEDS; i++)
  {
    // Use different noise functions for each LED and each color component
    uint8_t hue = inoise16(ms * TIME_FACTOR_HUE, i * 1000, 0) >> 8;
    uint8_t sat = inoise16(ms * TIME_FACTOR_SAT, i * 2000, 1000) >> 8;
    uint8_t val = inoise16(ms * TIME_FACTOR_VAL, i * 3000, 2000) >> 8;

    // Map the noise to full range for saturation and value
    sat = map(sat, 0, 255, 30, 255);
    val = map(val, 0, 255, 100, 255);

    leds[i] = CHSV(hue, sat, val);
  }

  FastLED.show();
}

// ====================================
// FLASH unctions
// ====================================

void writeDataToFlash(uint32_t address, const char *data)
{
  digitalWrite(CS_PIN, LOW);
  SPI.transfer(0x06); // Write Enable
  digitalWrite(CS_PIN, HIGH);
  delay(10);

  digitalWrite(CS_PIN, LOW);
  SPI.transfer(0x02); // Page Program
  SPI.transfer((address >> 16) & 0xFF);
  SPI.transfer((address >> 8) & 0xFF);
  SPI.transfer(address & 0xFF);
  for (size_t i = 0; i < strlen(data); i++)
  {
    SPI.transfer(data[i]);
  }
  digitalWrite(CS_PIN, HIGH);
  delay(10);
}

void readDataFromFlash(uint32_t address, char *buffer, size_t length)
{
  digitalWrite(CS_PIN, LOW);
  SPI.transfer(0x03); // Read Data
  SPI.transfer((address >> 16) & 0xFF);
  SPI.transfer((address >> 8) & 0xFF);
  SPI.transfer(address & 0xFF);
  for (size_t i = 0; i < length; i++)
  {
    buffer[i] = SPI.transfer(0x00);
  }
  digitalWrite(CS_PIN, HIGH);
}

#endif // GPIO_H