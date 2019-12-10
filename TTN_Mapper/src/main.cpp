#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <configuration.h>

static const int RXPin = A1, TXPin = 0; // GPS MODUL 
static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;

SoftwareSerial ss(RXPin, TXPin);
LiquidCrystal lcd(A5, A4, 5, 4, 3, A3);

const int buttonPin = A0; 

int buttonState;             
int lastButtonState = LOW;  
long lastDebounceTime = 0;  
long debounceDelay = 50;    

double lng = 0;
double lat = 0;

void os_getArtEui (u1_t* buf) { }
void os_getDevEui (u1_t* buf) { }
void os_getDevKey (u1_t* buf) { }

static uint8_t mydata[] = "Hello, world!";
static osjob_t sendjob;

const unsigned TX_INTERVAL = 6000; // 6 sek?

const lmic_pinmap lmic_pins = {

    .nss = 10,
    .rxtx = LMIC_UNUSED_PIN,
    .rst = 9,
    .dio = {2, 6, 7},
};


void do_send(osjob_t* j){

    if (LMIC.opmode & OP_TXRXPEND) {
        Serial.println(F("OP_TXRXPEND, not sending"));
    } else {
        LMIC_setTxData2(1, mydata, sizeof(mydata)-1, 0);
        Serial.println(F("Packet queued"));
    }
}

void onEvent (ev_t ev) {

    Serial.print(os_getTime());
    Serial.print(": ");
    switch(ev) {
        case EV_SCAN_TIMEOUT:
            Serial.println(F("EV_SCAN_TIMEOUT"));
            break;
        case EV_BEACON_FOUND:
            Serial.println(F("EV_BEACON_FOUND"));
            break;
        case EV_BEACON_MISSED:
            Serial.println(F("EV_BEACON_MISSED"));
            break;
        case EV_BEACON_TRACKED:
            Serial.println(F("EV_BEACON_TRACKED"));
            break;
        case EV_JOINING:
            Serial.println(F("EV_JOINING"));
            break;
        case EV_JOINED:
            Serial.println(F("EV_JOINED"));
            break;
        case EV_RFU1:
            Serial.println(F("EV_RFU1"));
            break;
        case EV_JOIN_FAILED:
            Serial.println(F("EV_JOIN_FAILED"));
            break;
        case EV_REJOIN_FAILED:
            Serial.println(F("EV_REJOIN_FAILED"));
            break;
        case EV_TXCOMPLETE:
            Serial.println(F("EV_TXCOMPLETE (includes waiting for RX windows)"));
            if (LMIC.txrxFlags & TXRX_ACK)
              Serial.println(F("Received ack"));
            if (LMIC.dataLen) {
              Serial.println(F("Received "));
              Serial.println(LMIC.dataLen);
              Serial.println(F(" bytes of payload"));
            }
            os_setTimedCallback(&sendjob, os_getTime()+sec2osticks(TX_INTERVAL), do_send);
            break;
        case EV_LOST_TSYNC:
            Serial.println(F("EV_LOST_TSYNC"));
            break;
        case EV_RESET:
            Serial.println(F("EV_RESET"));
            break;
        case EV_RXCOMPLETE:
            Serial.println(F("EV_RXCOMPLETE"));
            break;
        case EV_LINK_DEAD:
            Serial.println(F("EV_LINK_DEAD"));
            break;
        case EV_LINK_ALIVE:
            Serial.println(F("EV_LINK_ALIVE"));
            break;
         default:
            Serial.println(F("Unknown event"));
            break;
    }
}

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


 void setup() {

  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  lcd.begin(16,2); 
  ss.begin(GPSBaud);
  lcd.clear();

    os_init();
    LMIC_reset();

    #ifdef PROGMEM
    uint8_t appskey[sizeof(APPSKEY)];
    uint8_t nwkskey[sizeof(NWKSKEY)];
    memcpy_P(appskey, APPSKEY, sizeof(APPSKEY));
    memcpy_P(nwkskey, NWKSKEY, sizeof(NWKSKEY));
    LMIC_setSession (0x1, DEVADDR, nwkskey, appskey);
    #else
    // If not running an AVR with PROGMEM, just use the arrays directly
    LMIC_setSession (0x1, DEVADDR, NWKSKEY, APPSKEY);
    #endif

    #if defined(CFG_eu868)
    LMIC_setupChannel(0, 868100000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      
    LMIC_setupChannel(1, 868300000, DR_RANGE_MAP(DR_SF12, DR_SF7B), BAND_CENTI);      
    LMIC_setupChannel(2, 868500000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      
    LMIC_setupChannel(3, 867100000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      
    LMIC_setupChannel(4, 867300000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      
    LMIC_setupChannel(5, 867500000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      
    LMIC_setupChannel(6, 867700000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      
    LMIC_setupChannel(7, 867900000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      
    LMIC_setupChannel(8, 868800000, DR_RANGE_MAP(DR_FSK,  DR_FSK),  BAND_MILLI);      
    #elif defined(CFG_us915)
    LMIC_selectSubBand(1);
    #endif

    LMIC_setLinkCheckMode(0);
    LMIC.dn2Dr = DR_SF9;

    LMIC_setDrTxpow(DR_SF7,14);

    do_send(&sendjob);
}

void loop() {  

   int reading = analogRead(buttonPin);   
   int tmpButtonState = LOW;             // the current reading from the input pin
   
   if(reading>RED_LOW && reading<RED_HIGH){
     tmpButtonState = RED_BUTTON;
     
   } else if(reading>BLUE_LOW && reading<BLUE_HIGH){
     tmpButtonState = BLUE_BUTTON;
     
   } else if(reading>GREEN_LOW && reading<GREEN_HIGH){
     tmpButtonState = GREEN_BUTTON;
     
   } else{
    
     tmpButtonState = LOW;
   }

   if (tmpButtonState != lastButtonState) {
     lastDebounceTime = millis();
   } 

   if ((millis() - lastDebounceTime) > debounceDelay) {
     buttonState = tmpButtonState;
     Serial.println(buttonState);
   }

   lastButtonState = tmpButtonState;
   
   switch(buttonState){
    
     case RED_BUTTON:
     Serial.println("RED_BUTTON");
     //os_runloop_once(); 
     break;
     
     case BLUE_BUTTON:
     Serial.println("BLUE_BUTTON");
     //displayInfo();
     break;
     
     case GREEN_BUTTON:
     Serial.println("GREEN BUTTON");
     break;
          
   }
   
}

