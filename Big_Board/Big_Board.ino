#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SERVO_PIN      3 // Duh

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(54321);
LiquidCrystal_I2C lcd(0x27,16,2);
Servo myServo;

void setup() {
  Serial.begin(9600);
  myServo.attach(SERVO_PIN);
  // Initialize the OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3D)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  // Initialize the accelerometer
  if(!accel.begin())
  {
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    while(1);
  }
  // Initialize the LCD
  lcd.init();
  lcd.backlight();
  // Show initial display buffer contents (the library initializes this with an Adafruit splash screen)
  display.display();
  delay(1000); 
  // Clear the buffer
  display.clearDisplay();
}

void loop() {
    sensors_event_t event;
    accel.getEvent(&event);
    float x = event.acceleration.x;
    float y = event.acceleration.y;
    float z = event.acceleration.z;
    moveServo(z);
    accel2OLED(x, y, z);  
    accel2LCD(x, y, z);
    delay(1000);
}

void moveServo(float z) {
  if(z < 8)
    myServo.write(90);
  else if(z < 9)
    myServo.write(135);
  else
    myServo.write(180);
}

void accel2LCD(float x, float y, float z) {
  lcd.setCursor(0,0);
  lcd.print("X: "); lcd.print(x); lcd.print(" m/s^2");
  lcd.setCursor(0,1);
  lcd.print("Y: "); lcd.print(y); // lcd.print(" m/s^2");
  // lcd.setCursor(0,3);
  lcd.print(" Z: "); lcd.print(z); // lcd.print(" m/s^2");
}

void accel2OLED(float x, float y, float z) {
  display.clearDisplay();
  display.setTextColor(BLACK, WHITE); // Draw 'inverse' text
  display.setTextSize(2);      
  display.setCursor(0, 0);     // Start at top-left corner
  display.println("Accel :)");
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(WHITE); // Draw white text
  display.print("X: "); display.print(x); display.println(" m/s^2");
  display.print("Y: "); display.print(y); display.println(" m/s^2");
  display.print("Z: "); display.print(z); display.println(" m/s^2");
  display.display();
}