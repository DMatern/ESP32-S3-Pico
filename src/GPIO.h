#ifndef GPIO_H
#define GPIO_H

// ====================================
// Include Files

#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <SPIMemory.h> // Add SPIMemory library

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

// Create SPIFlash object using custom SPI bus and CS pin
SPIFlash flash(&flashSPI, CS_PIN);

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

    if (!flash.begin()) {
        Serial.println("Failed to initialize SPI Flash chip");
        while (1);
    }
    Serial.print("Flash JEDEC ID: 0x");
    Serial.println(flash.getJEDECID(), HEX);

    if (!flash.supported()) {
        Serial.println("Flash chip not supported by SPIMemory library!");
        while (1);
    }

    Serial.println("SPI Flash chip initialized successfully");
}

// ============================================================================
// Update
// ============================================================================

void updateGPIO() {

    
}

// ====================================
// LED functions
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
// FLASH functions using SPIMemory
// ====================================

bool writeDataToFlash(uint32_t address, const char *data, size_t length)
{
    // Erase sector before writing (W25Q128 sector size is 4096 bytes)
    if (!flash.eraseSector(address)) {
        Serial.println("Failed to erase sector!");
        return false;
    }
    delay(10);

    // Write data
    if (!flash.writeByteArray(address, (uint8_t*)data, length)) {
        Serial.println("Failed to write data!");
        return false;
    }
    return true;
}

bool readDataFromFlash(uint32_t address, char *buffer, size_t length)
{
    if (!flash.readByteArray(address, (uint8_t*)buffer, length)) {
        Serial.println("Failed to read data!");
        return false;
    }
    buffer[length] = '\0'; // Null-terminate if reading string data
    return true;
}

#endif // GPIO_H