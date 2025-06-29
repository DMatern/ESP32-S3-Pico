# ESP32-S3-Pico
Base configuration to initialize and setup all hardware and required llib's and be ready for program code.

Flash and PSRAM configuration: https://community.platformio.org/t/esp32-s3-devkitc-1-n32r8v-configuration-assistance/31967

# To Do List:

	- Add and Test Libraries for the following hardware:

# Library Infoamtion

> General

	NeoPixel      = FastLED
	WiFi          = WiFi.h   (arduino ESP32 core)
	BlueTooth      = BLE (Arduino ESP COre) https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleServer.cpp

> PicoCalc Specific

	Display       = TFT_eSPI / Bodmer
	Touchscreen   = XPT2046 / PaulStoffergen
	Keyvoard      = arduino_picocalc_kbd
	TF Card       = SD.h    (arduino core)
	Flash Memory  = SPIMemory / Marzogh

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

> USB UART Serial 0 (Host):

	TX  (U0TXD):                 GPIO 43
	RX: (U0RXD):                 GPIO 44

> USB UART Serial (Device):

	TX: (U1)                      GPIO 19
	RX: (U1)                      GPIO 20

> Onboard FLASH SPI0 (W25Q128JVSIQ):

	SPI_CS (Chip Select):         GPIO29
	SPI_D (Master Out Slave In):  GPIO32
	SPI_Q (Master In Slave Out):  GPIO31
	SPI_CLK (Clock):              GPIO30
	SPI_WP (Write Protect):       GPIO28
	SPI_HD (Hold):                GPIO27

> RGB Neo Pixel Onboard:

	Data PIN                      GPIO21

> I2C Pins (x2 Buses can be asigned to any GPIO Pins)

	I2CEXT0_SCL
	I2CEXT0_SDA
	I2CEXT1_SCL
	I2CEXT1_SDA

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

> UART Serial

	TX:                         GPIO 11
	RX:                         GPIO 12

> UART Serial

	TX:                         GPIO 33
	RX:                         GPIO 34

> FLASH SPI (ESP-PSRAM64H):

	RAM_CS (Chip Select):       GPIO 4
	RAM_CLK (Clock):            GPIO 5
	RAM_TX (MOSI):              GPIO 13
	RAM_RX (MISO):              GPIO 14
	RAM_IO2 ():                 GPIO 15
	RAM_IO3 ():                 GPIO 16

> TF Card Slot SPI:

	SPI_CS (Chip Select):       GPIO 41
	SPI_CLK (Clock):            GPIO 1
	SPI_TX (MOSI):              GPIO 2
	SPI_RX (MISO):              GPIO 42

	SD_DET (Card Detect):       GPIO 6

> TFT Display ():

	SPI1_CS:                    GPIO 38
	SPI1_CLK:                   GPIO 35
	SPI1_TX (MOSI):             GPIO 36
	SPI1_RX (MISO):             GPIO 37

	LCD_DC () :                 GPIO 39
	LCD_RST (Reset):            GPIO 40

> Audio Out (NC7WZ16):

	PWM_L:                      GPIO 7 
	PWM_R:                      GPIO 8

> Keyboard I2C (STM32):

	I2C1_SDA:                   GPIO 17
	I2C1_SCL:                   GPIO 18


![ESP32-S3 Pins](<Esp32-s3_datasheet_en Page 071.jpg>)

![900px-ESP32-S3-Pico-details-inter-1](https://github.com/user-attachments/assets/15d441bf-06bd-4bac-abaf-f670f46ad978)

Skematic: (https://files.waveshare.com/upload/a/a7/ESP32-S3-Pico-SCH.pdf)

Board Website: (https://www.waveshare.com/product/arduino/boards-kits/esp32/esp32-s3-pico.htm?___SID=U)
