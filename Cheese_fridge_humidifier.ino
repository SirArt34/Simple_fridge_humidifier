//------Biblioteka Czujnika Wilgotnosci
#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11   // DHT 11 
DHT dht(DHTPIN, DHTTYPE);

//------Biblioteka Wyswietlacza 7seg
#include <Arduino.h>
#include <TM1637Display.h>
#define CLK 5
#define DIO 6
TM1637Display display(CLK, DIO);

//------Test baterii
float napiecie = 0;

//------Znaki dla wyswietlacza 7seg i tekst
uint8_t Hsign[]={
  SEG_F|SEG_E|SEG_G|SEG_C|SEG_B,
};
uint8_t STsign[]={
  SEG_A|SEG_F|SEG_G|SEG_B,
};
uint8_t Csign[]={
  SEG_A|SEG_F|SEG_E|SEG_D,
};
uint8_t PERsign[]={
  SEG_A|SEG_F|SEG_G|SEG_B,
  SEG_G|SEG_E|SEG_D|SEG_C,
};
uint8_t text[] = {
  SEG_G,                                            // _
  SEG_G,                                            // _
  SEG_G,                                            // _
  SEG_G,                                            // _
  SEG_G | SEG_E,                                    // R
  SEG_A | SEG_F | SEG_G | SEG_E | SEG_D,            // e
  SEG_F | SEG_G | SEG_E | SEG_A,                    // f
  SEG_E,                                            // i
  SEG_F | SEG_E | SEG_D,                            // l
  SEG_F | SEG_E | SEG_D,                            // l
  SEG_G,                                            // -
  SEG_A | SEG_F | SEG_E,                            // T
  SEG_F | SEG_E | SEG_G | SEG_B | SEG_C,            // h
  SEG_A | SEG_F | SEG_G | SEG_E | SEG_D,            // e
  SEG_G,                                            // _   
  SEG_A | SEG_F | SEG_E,                            // T
  SEG_A | SEG_F | SEG_B | SEG_G | SEG_E | SEG_C,    // a
  SEG_E | SEG_G | SEG_C,                            // n
  SEG_E | SEG_F | SEG_G,                            // k
  SEG_G,                                            // -
  SEG_G,                                            // -
  SEG_G,                                            // _
  SEG_G,                                            // _ 
  };

//------Definiowane piny wej-wyj z Arduino
#define Relay 3
#define OnButton 4
#define WaterLevel 7
#define LedAlarm 9

void setup() {
  Serial.begin(9600);
//------Wlaczenie czujnikow,wyswietlaczy i definiowanie pinow Ard
  dht.begin();
  display.clear();
  display.setBrightness(0x08);

  pinMode(Relay, OUTPUT);
  pinMode(OnButton, OUTPUT);
  pinMode(WaterLevel, INPUT);
  
  digitalWrite(Relay, LOW);
  digitalWrite(OnButton, LOW);

  pinMode(LedAlarm, OUTPUT);
  digitalWrite(LedAlarm, HIGH);
  delay(1000); 
  digitalWrite(LedAlarm, LOW);
} 

void loop() {
//------Pobieranie danych z czujnika wilgotnosci
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    return;
  }
//------Sprawdzanie napięcia baterii
float volt = analogRead(A0); //Odczytujemy wartość napięcia
  napiecie = (volt * (5.0/1024.0)) * 2.03; //Przeliczenie wartości na napięcie
Serial.println(napiecie);
  if (napiecie < 7.2){
    digitalWrite(Relay, LOW);
    LBAlarm();
  }
  
//------Wyswietlanie wilgotnosci wraz ze znakiem PER=%
  display.setSegments(PERsign, 2, 2);
  display.showNumberDec(h,false, 2, 0);
  
//------Jeśli wilgotnosc jest nizzsza niz to włacz przekaznik i wcisnij guzik  
 
  if (digitalRead(Relay) == LOW && h < 79)
    TOnHumidity();
  else if(digitalRead(Relay) == HIGH && h < 79){
  } else 
    TOffHumidity();
    
    delay(5000);
    
//------Sprawdzamy stan wody w zbiorniku    
    if (digitalRead(WaterLevel) == LOW){
        digitalWrite(LedAlarm, HIGH);
        alarm();
    } else {
        digitalWrite(LedAlarm, LOW);
    }

//------Wyswietlamy temperature wraz z dwoma znakami
  display.setSegments(STsign, 1, 2);
  display.setSegments(Csign, 1, 3);
  display.showNumberDec(t,false,2,0);
  
    delay(5000);
    
//------czyscimy wyswietlacz    
    display.clear();
}

void TOnHumidity(){
    digitalWrite (Relay, HIGH);
    delay(100);
    digitalWrite (OnButton, HIGH);
    delay(10);
    digitalWrite (OnButton, LOW); 
}
void TOffHumidity(){
    digitalWrite (Relay, LOW);
    delay(100);
}
void alarm(){
  for (int i=0; i<20; i++)
  {  display.setSegments(text+i);
  delay(200); }
}
void LBAlarm(){
  for (int i = 0; i<10000; i++)
{
    digitalWrite(LedAlarm, HIGH);
    delay(500);
    digitalWrite(LedAlarm, LOW);
    delay(1000);
}
}
