#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include <LiquidCrystal.h>

// Set your access point network credentials
const char* ssid = "ESP32-Access-Point";
const char* password = "123456789";
const char *secrets[] = {"LUBIE JAZZ", "FROGS ROCK", "POOPERINO", "WHAT DE DOG DOIN", "LUZ PACHWINA", "MASNO"};
AsyncWebServer server(80);

LiquidCrystal lcd(19, 23, 18, 17, 16, 15);

String getSecret() {
  int secretIndex = millis() % (sizeof(secrets)/sizeof(secrets[0]));
  lcd.setCursor(0, 1);
  lcd.print("                 ");
  lcd.setCursor(0, 1);
  lcd.print(secrets[secretIndex]);
  delay(500);
  return secrets[secretIndex];
}

unsigned long previousMillis = 0;
const long interval = 2000; 

void setup(){
  lcd.begin(16, 2);
  lcd.print("MY SECRET IS:");
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  server.on("/secret", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", getSecret().c_str());
  });
  server.begin();
}
 
void loop(){
//  unsigned long currentMillis = millis();
//  if(currentMillis - previousMillis >= interval) {
//    lcd.setCursor(0, 1);
//    lcd.print("                 ");
//    lcd.setCursor(0, 1);
//    lcd.print(getSecret().c_str());
//    previousMillis = currentMillis;
//  }
}
