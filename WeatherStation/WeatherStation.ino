#include<LiquidCrystal.h>
#include "DHT.h"
#define DHTPIN 8
#define DHTTYPE DHT11

DHT dht(DHTPIN,DHTTYPE);

LiquidCrystal lcd(7,6,5,4,3,2);//CONNECT THESE PINS ON LCD

void setup(){
  delay(2000);
  Serial.begin(9600);
  lcd.begin(16,2);
  dht.begin();
  lcd.print("Room Temp");
  delay(1000);
  lcd.clear();
}
void loop(){
  float h= dht.readHumidity(); // FUNCTION FOR READING HUMIDITY DATA
  float t= dht.readTemperature();// FUNCTION FOR READING TEMPERATURE DATA
  if(isnan(h) || isnan(t)){
  Serial.print("Failed to get data");
  lcd.setCursor(0,0);
  lcd.print("FAILED!");
  lcd.setCursor(0,1);
  lcd.print("TRY AGAIN");
  }
  else{
  // printing the humidity data on SERIAL MONITOR
  Serial.print("Current Humidity: ");
  Serial.print(h);
  Serial.print("%");
  Serial.print("||");
  
  Serial.print("Current Temperature: ");
  Serial.print(t);
  Serial.println("ºC\n");

  Serial.print("Current Temperature: ");
  Serial.print(t * 1.8 + 32);
  Serial.println("ºF\n");
  delay(1000);
  // Printing humidity On Screen
  lcd.setCursor(6,0);
  lcd.print("HUM ");
  lcd.setCursor(11,0);
  lcd.print(h);
  lcd.setCursor(15,0);
  lcd.print("%");
  
  // Printing Temp on LCD
  lcd.setCursor(0,1);
  lcd.print("TEMP ");
  lcd.setCursor(5,1);
  lcd.print(t);
  lcd.setCursor(9,1);
  lcd.println("C ");
  lcd.setCursor(11,1);
  lcd.print(t * 1.8 + 32);
  lcd.setCursor(15,1);
  lcd.println("F");
  }
}
