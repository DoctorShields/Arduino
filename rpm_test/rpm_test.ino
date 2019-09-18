#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define interruptPin 2

LiquidCrystal_I2C lcd(0x27, 20, 4);
volatile int count = 0;
long now = 0;
long lastTime = 0;
int dt = 1000;
int RPM;

void setup()
{
	//Serial.begin(9600);
	//Serial.println("go!");
 	pinMode(interruptPin, INPUT_PULLUP);
 	attachInterrupt(digitalPinToInterrupt(interruptPin), blink, FALLING);
	lcd.begin();
	lcd.backlight();
	lcd.print("RPM!");
}

void loop()
{
	now = millis();
	if (now > lastTime + dt) {
		RPM = count * 60 / 5;
		lcd.setCursor(0,0);
		lcd.print(RPM);
		lcd.print("    ");
		count = 0;
		lastTime = now;
	}	
}

void blink() {
  count ++;
}