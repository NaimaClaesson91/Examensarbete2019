#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal.h> 

LiquidCrystal lcd(12, 11, 5, 4, 3, 8);

int buttonPin = 9;
int buttonState = 0;

 void checkButton(int buttonState) {

  if (buttonState == LOW) { 
    return;

    } else if (buttonState == HIGH){

      lcd.print ("BUTTON PRESSED!");
      Serial.println("BUTTON WAS PRESSED!");
    
    }  
  }

void setup() {

  pinMode(buttonPin, INPUT_PULLUP); 
  lcd.begin(16,2); 
}

void loop() {

  lcd.clear();
  buttonState = digitalRead(buttonPin);
  checkButton(buttonState); 

}

