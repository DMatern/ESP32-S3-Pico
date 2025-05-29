#ifndef GPIO_H
#define GPIO_H

// ====================================
// Include Files

#include <Arduino.h>


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


// ============================================================================
// Setup
// ============================================================================

void setupGPIO() {
    // Initialize GPIO pins here if needed
    // For example, set pin modes or initial states

    FastLED.addLeds<WS2812, PIN_LEDRGB, GRB>(leds, NUM_LEDS).setRgbw(RgbwDefault());
    FastLED.setBrightness(128); // Set global brightness to 50%

    Serial.println("GPIO setup complete.");
}



// ============================================================================
// Update
// ============================================================================

void updateGPIO() {

    uint32_t ms = millis();

    for (int i = 0; i < NUM_LEDS; i++) {
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

// add LED functions

// Add GPIO function as below

// Structure to represent a GPIO pin configuration
typedef struct {
    uint8_t pin;        // GPIO pin number
    uint8_t mode;       // INPUT, OUTPUT, INPUT_PULLUP, etc.
    bool    state;      // Current state (HIGH/LOW)
    String  name;       // Optional: Pin name/description
} GPIO_t;

// Function prototypes

// Initialize a GPIO pin
void GPIO_init(GPIO_t &gpio);

// Set the state of a GPIO pin (HIGH/LOW)
void GPIO_write(GPIO_t &gpio, bool state);

// Read the state of a GPIO pin
bool GPIO_read(GPIO_t &gpio);

#endif // GPIO_H