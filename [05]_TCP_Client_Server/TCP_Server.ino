#include <ESP8266WiFi.h>

#define LED         D0

#define SERVER_PORT     8000
const char* ssid = "MicroLab_SSID";
const char* password = "212224236";
WiFiServer server(SERVER_PORT);

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
  while(!Serial)
  {
    //
  }
  Serial.println(""); Serial.println("");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("IP address : ");
  Serial.println(WiFi.localIP());
  server.begin();
  Serial.println("Server started");
  ESP.wdtDisable();
  ESP.wdtEnable(WDTO_8S);
}

void loop() {
  // put your main code here, to run repeatedly:
  ESP.wdtFeed();
  WiFiClient client = server.available();
  if (client)
  {
    Serial.println("new client");
    while (1)
    {
      while (client.available())
      {
        uint8_t data = client.read();
        Serial.write(data);
        if (data == 'a')
        {
          digitalWrite(LED, LOW);
        }
        if (data == 'b')
        {
          digitalWrite(LED, HIGH);
        }
        if (data == 'c')
        {
          digitalWrite(LED, !digitalRead(LED));
        }
      }
      if (server.hasClient())
      {
        return;
      }
    }
  }
}
