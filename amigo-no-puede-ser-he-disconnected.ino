#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

//define I2C address......
LiquidCrystal_I2C lcd(0x27,16,2);

const char* ssid = "Club De Ciencias";
const char* password = "clubdeciencias";

//Your Domain name with URL path or IP address with path
String serverName = "http://192.168.0.100:3000";

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 5000;


void setup() {
  lcd.init();
  lcd.clear();
  lcd.backlight();
  Serial.begin(115200); 

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    lcd.print("en eso bro");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  lcd.print("amigo no puede ser");
  delay(1000);
  lcd.print(WiFi.localIP());
 
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
}

void loop() {
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;

      String serverPath = serverName + "/messi";
      
      // Your Domain name with URL path or IP address with path
      http.begin(client, serverPath.c_str());
      
      // Send HTTP GET request
      int httpResponseCode = http.GET();
      
      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
        lcd.print(payload);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
        lcd.print("cagaste");
      }
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
      lcd.print("he disconected");
    }
    lastTime = millis();
  }
}
