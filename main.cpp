#include <Arduino.h>
#include <sha256.h>
#include <LiquidCrystal_I2C.h>
#include <stdio.h>

static char* initialKey = "wwwww";
static char str[50];
LiquidCrystal_I2C lcd(0x3f, 15, 2);
uint8_t* hash;
Sha256 sha;

uint8_t toHash;

void setup()
{
	lcd.init();
	lcd.backlight();
	lcd.setCursor(0, 0);
	lcd.print("Hello, World");
	
	Serial.begin(9600);
	sha.init();

}

void loop()
{
	toHash = map(analogRead(0), 0, 1024, 0, 25);

	lcd.clear();
	lcd.setCursor(0, 1);
	lcd.print((int)toHash);

	lcd.setCursor(0, 0);
	// sha.initHmac(initialKey, sizeof(initialKey));
	// sha.init();
	sprintf(str, "%d %s", toHash, initialKey);
	
	sha.init();
	sha.print(str);
	hash = sha.result();
	for (auto i = 0;i<12;i++)
	{
		hash[i] = (hash[i] % (('~' - '!') + 1) + '!') & 0b01111111;
	}
	hash[12] = '\0';
	lcd.printstr((char*)hash);
}
