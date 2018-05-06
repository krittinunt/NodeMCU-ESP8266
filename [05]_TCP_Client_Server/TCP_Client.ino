#include <ESP8266WiFi.h>

#define SW1     D3
#define SW2     D4
#define SW3     D5

#define SERVER_PORT       8000
IPAddress server_ip = {192, 168, 1, 39};

const char* ssid = "MicroLab_SSID";
const char* password = "212224236";

WiFiServer server(SERVER_PORT);
WiFiClient client;

uint16_t i = 0;

void setup() {
  // put your setup code here, to run once:

  pinMode(SW1, INPUT);
  pinMode(SW2, INPUT);
  pinMode(SW3, INPUT);
  
  Serial.begin(115200);
  while(!Serial)
  {
    //
  }
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address : ");
  Serial.println(WiFi.localIP());

  Serial.println("Connect TCP Server");
  while (!client.connect(server_ip, SERVER_PORT))
  {
    Serial.println(".");
    delay(100);
  }
  Serial.println("Success");
  ESP.wdtDisable();
  ESP.wdtEnable(WDTO_8S);
}

void loop() {
  // put your main code here, to run repeatedly:
  ESP.wdtFeed();
  while (client.available())
  {
    uint8_t data = client.read();
    Serial.write(data);
  }
  //client.println("KRITTINUNT-NODE");
  //client.println("I Love gutur.");
  //client.println(i);
  //i++;
  //delay(1000);
  if (digitalRead(SW1) == LOW)
  {
    delay(100);
    while(digitalRead(SW1) != HIGH);
    delay(100);
    client.println("a");
  }
  if (digitalRead(SW2) == LOW)
  {
    delay(100);
    while(digitalRead(SW2) != HIGH);
    delay(100);
    client.println("b");
  }
  if (digitalRead(SW3) == LOW)
  {
    delay(100);
    while(digitalRead(SW3) != HIGH);
    delay(100);
    client.println("c");
  }
}
