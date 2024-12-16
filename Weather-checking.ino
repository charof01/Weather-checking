#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 2         // กำหนดพินที่ใช้เชื่อมต่อกับเซ็นเซอร์ DHT22
#define DHTTYPE DHT22    // กำหนดประเภทเซ็นเซอร์ที่ใช้ (DHT22)

DHT dht(DHTPIN, DHTTYPE);  // สร้างตัวแปรสำหรับ DHT sensor

#define LDR_PIN A0      // กำหนดพินที่ใช้เชื่อมต่อกับเซ็นเซอร์ LDR

LiquidCrystal_I2C lcd(0x27, 20, 4);  // กำหนด LCD โดยใช้ I2C ที่ address 0x27 และขนาดหน้าจอ 20x4

#define RED_PIN 9
#define GREEN_PIN 10
#define BLUE_PIN 11

int temperature;
int humidity;
int lightLevel;
String weatherStatus = "Walk outside >-<"; // สถานะอากาศเริ่มต้น

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.begin(20, 4);
  lcd.backlight();
  lcd.clear();

  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
}

void loop() {
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
  lightLevel = analogRead(LDR_PIN);

  int lux = map(lightLevel, 0, 1023, 0, 2000);

  // ตรวจสอบเงื่อนไขอากาศ
  if ((temperature < 20 || temperature > 25) || (humidity < 40 || humidity > 60) || (lux < 100 || lux > 1000)) {
    weatherStatus = "Don't go out! -_-";  // หากไม่เหมาะสม
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Don't go out! -_-");
    lcd.setCursor(0, 1);
    lcd.print("Temp: " + String(temperature) + "C");
    lcd.setCursor(0, 2);
    lcd.print("Humidity: " + String(humidity) + "%");
    lcd.setCursor(0, 3);
    lcd.print("Lux: " + String(lux));

    setRGBColor(255, 0, 0);  // ตั้งค่า RGB LED เป็นสีแดง
  } else {
    weatherStatus = "Walk outside >-<";  // หากเหมาะสม
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Walk outside >-<");
    lcd.setCursor(0, 1);
    lcd.print("Temp: " + String(temperature) + "C");
    lcd.setCursor(0, 2);
    lcd.print("Humidity: " + String(humidity) + "%");
    lcd.setCursor(0, 3);
    lcd.print("Lux: " + String(lux));

    setRGBColor(0, 255, 0);  // ตั้งค่า RGB LED เป็นสีเขียว
  }

  delay(2000);  // หน่วงเวลา 2 วินาที
}

void setRGBColor(int redValue, int greenValue, int blueValue) {
  analogWrite(RED_PIN, redValue);
  analogWrite(GREEN_PIN, greenValue);
  analogWrite(BLUE_PIN, blueValue);
}
