#include <SPI.h>

// Define the SPI pins
#define CS_PIN 29   // SPICS0
#define CLK_PIN 30  // SPICLK
#define MISO_PIN 31 // SPIQ
#define MOSI_PIN 32 // SPID
#define WP_PIN 28   // SPIWP
#define HD_PIN 27   // SPIHD

bool initializeFlash();


void setupFlash()
{

  SPI.begin(CLK_PIN, MISO_PIN, MOSI_PIN, CS_PIN);
  pinMode(CS_PIN, OUTPUT);
  digitalWrite(CS_PIN, HIGH);

  // Initialize the flash chip
  if (!initializeFlash())
  {
    Serial.println("Failed to initialize flash chip");
    while (1)
      ;
  }
  Serial.println("Flash chip initialized successfully");

  // // Example: Write data to flash
  // writeDataToFlash(0x000000, "Hello, Flash!");

  // // Example: Read data from flash
  // char buffer[20];
  // readDataFromFlash(0x000000, buffer, 20);
  // Serial.println(buffer);
}

bool initializeFlash()
{
  digitalWrite(CS_PIN, LOW);
  SPI.transfer(0xAB); // Release from power-down / Device ID
  digitalWrite(CS_PIN, HIGH);
  delay(100);

  // Check if the flash chip is responding
  digitalWrite(CS_PIN, LOW);
  SPI.transfer(0x90); // Manufacturer/Device ID
  SPI.transfer(0x00);
  SPI.transfer(0x00);
  SPI.transfer(0x00);
  uint8_t manufacturerID = SPI.transfer(0x00);
  uint8_t deviceID = SPI.transfer(0x00);
  digitalWrite(CS_PIN, HIGH);

  return (manufacturerID == 0xEF && deviceID == 0x17); // Check against known IDs for W25Q128
}

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
