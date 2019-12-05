#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>

static const int RXPin = A1, TXPin = 0;
static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;

SoftwareSerial ss(RXPin, TXPin);
LiquidCrystal lcd(A5, A4, 5, 4, 3, A3);

int buttonPin = A2;
int buttonState = 0;
double lng = 0;
double lat = 0;

void displayInfo() {

  if (gps.location.isValid()) {

    lng = gps.location.lng();
    lat = gps.location.lat();

    Serial.print("Latitude: " + String(gps.location.lat(),6));
    Serial.print(" Longitude: " + String(gps.location.lng(),6));

    lcd.setCursor(0,0);  // First position, first line
    lcd.print("LAT: ");
    lcd.print(lat, 6);

    lcd.setCursor(0,1) ; //Second line, first row
    lcd.print("LONG: ");
    lcd.print(lng, 6);

    delay(1000);

  } else {

    Serial.print(F("INVALID"));

    lcd.setCursor(0,0);  // First position, first line
    lcd.print("LAT: ");
    lcd.print(lat, 10);

    lcd.setCursor(0,1) ; //Second line, first row
    lcd.print("LONG: ");
    lcd.print(lng, 10);
    delay(1000);

  }

  Serial.print(F("  Date/Time: "));

  if (gps.date.isValid()) {

    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
  } else {

    Serial.print(F("INVALID"));
  }

  Serial.print(F(" "));

  if (gps.time.isValid()) {
    if (gps.time.hour() < 10) Serial.print(F("0"));

    Serial.print(gps.time.hour());
    Serial.print(F(":"));

    if (gps.time.minute() < 10) Serial.print(F("0"));

    Serial.print(gps.time.minute());
    Serial.print(F(":"));

    if (gps.time.second() < 10) Serial.print(F("0"));

    Serial.print(gps.time.second());
    Serial.print(F("."));

    if (gps.time.centisecond() < 10) Serial.print(F("0"));

    Serial.print(gps.time.centisecond());
  } else {

    Serial.print(F("INVALID"));

  }

  Serial.println();
}

 void checkButton(int buttonState) {

  if (buttonState == LOW) { 
    return;

    } else if (buttonState == HIGH){

      lcd.print ("BUTTON PRESSED!");
      Serial.println("BUTTON WAS PRESSED!");
    
    }  
  }

 
 void setup() {

  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP); 
  lcd.begin(16,2); 
  ss.begin(GPSBaud);
  lcd.clear();

}

void loop() {

  
  //buttonState = digitalRead(buttonPin);
  //checkButton(buttonState); 

  while (ss.available() > 0){

    if (gps.encode(ss.read())) {

        displayInfo();
    }  

  if (millis() > 5000 && gps.charsProcessed() < 10) {

    Serial.println(F("No GPS detected: check wiring."));
    while(true);

  }
 }


}

