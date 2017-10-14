#include <ESP8266WiFi.h>

#define SERVER_PORT       8000
IPAddress server_ip = {192, 168, 1, 13};

const char* ssid = "Elec_Surat";
const char* password = "91992189327";

WiFiServer server(SERVER_PORT);
WiFiClient client;

uint16_t i = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
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
  client.println("KRITTINUNT-NODE");
  client.println("I Love gutur.");
  delay(1000);
}
