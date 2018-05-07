#include <ESP8266WiFi.h>

void Line_Notify(String message);

#define SW1         D3
#define SW2         D4
#define SW3         D5

const char* ssid = "KTN-Machine";
const char* password = "embeddedwifinetwork";

const char* LINE_TOKEN = "1E066Wnpce524y0YYGw8Plv86sMF7s6zHoXghAKbGW2";
const char* TXT_MSG1 = "%E0%B8%AB%E0%B8%B8%E0%B8%9A%E0%B8%9B%E0%B8%B2%E0%B8%81";
const char* TXT_MSG2 = "%E0%B9%84%E0%B8%9B%E0%B8%A5%E0%B9%89%E0%B8%B2%E0%B8%87%E0%B8%88%E0%B8%B2%E0%B8%99";
const char* TXT_MSG3 = "%E0%B8%A1%E0%B8%B2%E0%B8%99%E0%B8%A7%E0%B8%94%E0%B8%82%E0%B8%B2%E0%B9%80%E0%B8%94%E0%B8%B5%E0%B9%8B%E0%B8%A2%E0%B8%A7%E0%B9%80%E0%B8%99%E0%B8%B5%E0%B9%89%E0%B8%A2....";


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
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
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

}

void loop() {
  // put your main code here, to run repeatedly:

  if (digitalRead(SW1) == LOW)
  {
    delay(100);
    while (digitalRead(SW1) != HIGH);
    delay(100);
    Line_Notify(TXT_MSG1);
  }
  
  if (digitalRead(SW2) == LOW)
  {
    delay(100);
    while (digitalRead(SW2) != HIGH);
    delay(100);
    Line_Notify(TXT_MSG2);
  }
  
  if (digitalRead(SW3) == LOW)
  {
    delay(100);
    while (digitalRead(SW3) != HIGH);
    delay(100);
    Line_Notify(TXT_MSG3);
  }

}

void Line_Notify(String message)
{
  String msg = String("message=") + message;

  WiFiClientSecure client;
  if (!client.connect("notify-api.line.me", 443))
  {
    Serial.println("connection failed");
    return;
  }

  String req = "";
  req += "POST /api/notify HTTP/1.1\r\n";
  req += "Host: notify-api.line.me\r\n";
  req += "Content-Type: application/x-www-form-urlencoded\r\n";
  req += "Authorization: Bearer " + String(LINE_TOKEN) + "\r\n";
  req += "Content-Length: " + String(msg.length()) + "\r\n";
  req += "\r\n";
  req += msg;

  client.print(req);

  unsigned long timeout = millis();
  while (client.available() == 0)
  {
    if (millis() - timeout > 5000)
    {
      Serial.print(">>> Client Timeout !");
      client.stop();
      return;
    }
  }

  while (client.available())
  {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

  Serial.println();
  Serial.println("closing connection");
}

