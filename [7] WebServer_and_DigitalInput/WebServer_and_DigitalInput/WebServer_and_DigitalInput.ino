#include <ESP8266WiFi.h>

#define SW      D3

const char* ssid = "MicroLab_SSID";
const char* password = "212224236";

WiFiServer server(80);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(10);
  Serial.println(""); Serial.println("");
  Serial.print("Connecting to "); Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  server.begin();
  Serial.println("Server started");
  Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:
  WiFiClient client = server.available();
  if (!client)
  {
    return;
  }

  Serial.println("new client");
  while (!client.available())
  {
    delay(1);
  }
  
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();

  String web = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
  web += "<html>\r\n";
  web += "<body>\r\n";
  web += "<head>Read Switch\r\n";
  web += "<style>\r\n";
  web += ".circle-gray,.circle-yellow\r\n";
  web += "{width: 100px;\r\n";
  web += "height: 100px;\r\n";
  web += "border-raduus: 50%;}\r\n";
  web += ".circle-gray\r\n";
  web += "{background-color: gray}\r\n";
  web += ".circle-yellow\r\n";
  web += "{background-color: yellow\r\n";
  web += "</style>\r\n";
  web += "</head>\r\n";
  web += "<meta http-equiv=\"refresh\" content=\"1\">";
  web += "<p>\r\n";

  uint8_t sw_input = digitalRead(SW);
  if (sw_input == 0)
  {
    web += "<div class = \"circle-gray\"></div>\r\n";
    web += "<p>SW = 0</p>\r\n";
  }
  else
  {
    web += "<div class=\"circle-yellow\"></div>\r\n";
    web += "<p>SW = 1</p>\r\n";
  }
  web += "</p>\r\n";
  web += "</body>\r\n";
  web += "</html>\r\n";
  client.print(web);
}
