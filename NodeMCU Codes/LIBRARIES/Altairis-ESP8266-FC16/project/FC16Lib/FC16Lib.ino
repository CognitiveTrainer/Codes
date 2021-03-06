#include <LedControlSPIESP8266.h>	// Not needed for functionality, but for vMicro IntelliSense
#include "FC16.h"

// Hardware setup (ESP8266 <-> FC16):
// 5V <-> VCC, GND <-> GND, D7 <-> DIN, D8 <-> CS, D5 <-> CLK

const int csPin = D8;			// CS pin used to connect FC16
const int displayCount = 8;		// Number of displays; usually 4 or 8
const int scrollDelay = 30;		// Scrolling speed - pause in ms

// Sample bitmaps, every byte encodes single column
byte BMP_4D[] = {										// >HELLO< for 4-matrix configuration
	0xFF, 0x7E, 0x3C, 0x18, 0x00, 0x7E, 0x08, 0x08,		// Matrix 1
	0x7E, 0x00, 0x7E, 0x4A, 0x4A, 0x42, 0x00, 0x7E,		// Matrix 2
	0x40, 0x40, 0x00, 0x7E, 0x40, 0x40, 0x00, 0x3C,		// Matrix 3
	0x42, 0x42, 0x3C, 0x00, 0x18, 0x3C, 0x7E, 0xFF };	// Matrix 4
byte BMP_8D[] = {										// >HELLO WORLD< for 8-matrix configuration
	0xFF, 0x7E, 0x3C, 0x18, 0x00, 0x7E, 0x08, 0x08,		// Matrix 1
	0x7E, 0x00, 0x7E, 0x4A, 0x4A, 0x42, 0x00, 0x7E,		// Matrix 2
	0x40, 0x40, 0x40, 0x00, 0x7E, 0x40, 0x40, 0x40,		// Matrix 3
	0x00, 0x3C, 0x42, 0x42, 0x42, 0x3C, 0x00, 0x00,		// Matrix 4
	0x00, 0x00, 0x3E, 0x40, 0x30, 0x40, 0x3E, 0x00,		// Matrix 5
	0x3C, 0x42, 0x42, 0x42, 0x3C, 0x00, 0x7E, 0x12,		// Matrix 6
	0x32, 0x4C, 0x00, 0x7E, 0x40, 0x40, 0x00, 0x7E,		// Matrix 7
	0x42, 0x42, 0x3C, 0x00, 0x18, 0x3C, 0x7E, 0xFF };	// Matrix 8

FC16 display = FC16(csPin, displayCount);

void setup() {
	// Setup LED
	pinMode(LED_BUILTIN, OUTPUT);		// enable builtin LED
	digitalWrite(LED_BUILTIN, HIGH);	// turn it off

	// Setup display
	display.begin();					// turn on display
	display.clearDisplay();				// turn all LED off
	display.setIntensity(8);			// set medium brightness

	if (displayCount <= 4) {
		display.setBitmap(BMP_4D);		// show sample bitmap for 4 displays
	} else {
		display.setBitmap(BMP_8D);		// show sample bitmap for 8 displays
	}

	// Wait for 1 second
	delay(1000);

	// Set text to display
	display.setText("\x10 ESP 8266 & FC-16 \x11 MAX72xx-based LED display library demo");
}

void loop() {
	// Perform scroll
	bool done = display.update();

	// Wait for 30 ms
	delay(scrollDelay);

	if (done) {
		// Blink led when animation is done
		digitalWrite(LED_BUILTIN, LOW);
		delay(500);
		digitalWrite(LED_BUILTIN, HIGH);
	}
}
