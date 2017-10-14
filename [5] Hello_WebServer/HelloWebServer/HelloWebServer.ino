#include <ESP8266WiFi.h>
const char* ssid = "Elec_Surat";
const char* password = "91992189327";
WiFiServer server(80);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(10);
  Serial.println(""); Serial.println("");
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
  server.begin();
  Serial.println("Server started");
  Serial.println(WiFi.localIP());
  ESP.wdtDisable();
  ESP.wdtEnable(WDTO_8S);
}

void loop() {
  // put your main code here, to run repeatedly:
  ESP.wdtFeed();
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
  web += "<h1>Hello web server</h1>\r\n";
  web += "<br>Name:Krittinunt Chobtrong\r\n>";
  web += "<br>Tel:0505512022\r\n>";
  web += "<br><img src=\"https://pbs.twimg.com/profile_images/593465700682956800/Y_I3_pnk.jpg\">\r\n";
  web += "</body>\r\n";
  web += "</html>\r\n";
  client.print(web);
}
