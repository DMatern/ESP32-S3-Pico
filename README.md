# ESP32-S3-Pico
Base configuration to initialize and setup all hardware and required llib's and be ready for program code.

# To Do List:

- Add and Test Libraries for the following hardware:
-- 16MB Flash Memory  (W25Q128JVSIQ)
-- WiFi               (ESP32)
-- Bluetooth          (ESP32)
-- NTP Time           (LIB)

# Library Infoamtion

> General

NeoPixel      = FastLED
Flash Memory  = SPIMemory / Marzogh
WiFi          = WiFi.h   (arduino lib)

> PicoCalc Specific

Display       = TFT_eSPI / Bodmer
Touchscreen   = XPT2046 / PaulStoffergen
Keyvoard      = 

# Board Information:

Adopts ESP32-S3R2 chip with Xtensa 32-bit LX7 dual-core processor, capable of running at 240 MHz
Integrated 512KB SRAM, 384KB ROM, 2MB PSRAM
16MB W25Q128JVSIQ Flash memory (SPI)
Integrated 2.4GHz Wi-Fi and Bluetooth LE dual-mode wireless communication, with superior RF performance.
Onboard CH343 and CH334 chips can meet the needs of USB and UART development via a Type-C interface
Onboard DC-DC chip MP28164, high efficiency DC-DC buck-boost chip with load current up to 2A
27 × multi-function GPIO pins
Rich peripheral interfaces, including full-speed USB OTG, SPI, I2C, UART, ADC, PWM and DVP (8-bit ~ 16-bit camera interface), LCD interfaces (8-bit ~ 16-bit parallel RGB, I8080, MOTO6800), etc. to achieve various functions flexibly
4-inch IPS screen with a 320x320 resolution SPI Interface

# Board IO:

> SPI0 Pin Assignments for FLASH W25Q128JVSIQ:

SPICS0 (Chip Select):       GPIO29
SPID (Master Out Slave In): GPIO32
SPIQ (Master In Slave Out): GPIO31
SPICLK (Clock):             GPIO30
SPIWP (Write Protect):      GPIO28
SPIHD (Hold):               GPIO27

> RGB Neo Pixel:

Data PIN                    GPIO21

> I2C Pins (x2 Buses can be asigned to any GPIO Pins)

I2CEXT0_SCL
I2CEXT0_SDA
I2CEXT1_SCL
I2CEXT1_SDA

*Using GPIO8 for SDA and GPIO9 for SCL

> Pins to Avoid:

GPIO0   I2CSAR RTC, have to be GND at reset
GPIO1   I2CSAR RTC
GPIO2   I2CSAR RTC
GPIO3   I2CSAR RTC, have to be GND at reset

GPIO19  USB D-
GPIO20  USB D+

> ADC Pins:

GPIO01 - GPOI20

# PicoCalc IO for ESP32-S3-Pico

> UART Serial 0

TX: GPIO 2
RX: GPIO 3

> FLASH ESP-PSRAM64H:

RAM_CS (Chip Select):       GPIO 40
RAM_CLK (Clock):            GPIO 41
RAM_TX (MOSI):              GPIO 4
RAM_RX (MISO):              GPIO 5
SPI0_IO2 ():                GPIO 43
SPIQ_IO3 ():                GPIO 44

> TF Card Slot:

SPI0_CS (Chip Select):      GPIO 37
SPI0_CLK (Clock):           GPIO 38
SPI0_TX (MOSI):             GPIO 39
SPI0_RX (MISO):             GPIO 36

SD_DET (Card Detect):       GPIO 42

> TFT Display:

SPI1_CS:                    GPIO 13
SPI1_CLK:                   GPIO 10
SPI1_TX (MOSI):             GPIO 11
SPI1_RX (MISO):             GPIO 12

LCD_DC () :                 GPIO 34
LCD_RST (Reset):            GPIO 35

> Audio Out (NC7WZ16):

PWM_L:                      GPIO 6 
PWM_R:                      GPIO 7

> Keyboard I2C (STM32):

I2C1_SDA:                   GPIO 14
I2C1_SCL:                   GPIO 15


![ESP32-S3 Pins](<Esp32-s3_datasheet_en Page 071.jpg>)

![900px-ESP32-S3-Pico-details-inter-1](https://github.com/user-attachments/assets/15d441bf-06bd-4bac-abaf-f670f46ad978)

Skematic: (https://files.waveshare.com/upload/a/a7/ESP32-S3-Pico-SCH.pdf)

Board Website: (https://www.waveshare.com/product/arduino/boards-kits/esp32/esp32-s3-pico.htm?___SID=U)
