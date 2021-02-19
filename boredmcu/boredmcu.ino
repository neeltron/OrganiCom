#include <ESP8266WiFi.h>
const char *ssid =  "WiFi SSID";
const char *pass =  "WiFi Password";
const char* _getLink = "https://maker.ifttt.com/trigger/tweelon/with/key/dnDRzxYa_9QqoK-lOJYa_K?value1=";
const int sensor_pin = A0;
WiFiClient client;
void setup()
{
  Serial.begin(9600);
  delay(10);
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
}
void loop()
{
  float moisture_percentage;
  moisture_percentage = ( 100.00 - ( (analogRead(sensor_pin) / 1023.00) * 100.00 ) );
  Serial.print("Soil Moisture(in Percentage) = ");
  Serial.print(moisture_percentage);
  if (moisture_percentage < 30) {
    String link = "maker.ifttt.com";
    if (client.connect(link, 80)) {
      String getStr = _getLink + String(random(0, 100000));
      Serial.println(getStr);
      client.print("GET " + getStr + "\n");
      client.print("HTTP/1.1\n");
      client.print("Host: maker.ifttt.com\n");
      client.print("Connection: close\n\n\n");
      while (client.available()) {
        char c = client.read();
        Serial.print(c);
        Serial.print("and done!");
      }
      Serial.println("");
    }
    else {
      Serial.println("nope");
    }
    delay(900000);
  }
}
