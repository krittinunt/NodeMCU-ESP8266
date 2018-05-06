#include <ESP8266WiFi.h>

#define LED1    D0
#define LED2    D1
#define LED3    D2

const char* ssid = "MicroLab_SSID";
const char* password = "212224236";

uint8_t status_led1 = 0;
uint8_t status_led2 = 0;
uint8_t status_led3 = 0;

WiFiServer server(80);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(10);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
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

  //Serial.println("new client");
  while (!client.available())
  {
    delay(1);
  }
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  if (req.indexOf("/led1off") != -1)
  {
    status_led1 = 0;
    digitalWrite(LED1, LOW);
    Serial.println("LED1 OFF");
  }
  else if (req.indexOf("/led1on") != -1)
  {
    status_led1 = 1;
    digitalWrite(LED1, HIGH);
    Serial.println("LED1 ON");
  }
  
  if (req.indexOf("/led2off") != -1)
  {
    status_led2 = 0;
    digitalWrite(LED2, LOW);
    Serial.println("LED2 OFF");
  }
  else if (req.indexOf("/led2on") != -1)
  {
    status_led2 = 1;
    digitalWrite(LED2, HIGH);
    Serial.println("LED2 ON");
  }
  if (req.indexOf("/led3off") != -1)
  {
    status_led3 = 0;
    digitalWrite(LED3, LOW);
    Serial.println("LED3 OFF");
  }
  else if (req.indexOf("/led3on") != -1)
  {
    status_led3 = 1;
    digitalWrite(LED3, HIGH);
    Serial.println("LED3 ON");
  }

  String web = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
  web += "<html>\r\n";
  web += "<body>\r\n";
  web += "<h1>LED Status</h1>\r\n";
  
  web += "<p>\r\n";
  if (status_led1 == 1)
    web += "LED1 On\r\n";
  else
    web += "LED1 Off\r\n";
  web += "</p>\r\n";
  web += "<p>\r\n";
  web += "<a href =\"/led1on\">\r\n";
  web += "<button>LED1 On</button>\r\n";
  web += "</a>\r\n";
  web += "<a href=\"/led1off\">\r\n";
  web += "<button>LED1 Off</button>\r\n";
  web += "</a>\r\n";

  web += "<p>\r\n";
  if (status_led2 == 1)
    web += "LED2 On\r\n";
  else
    web += "LED2 Off\r\n";
  web += "</p>\r\n";
  web += "<p>\r\n";
  web += "<a href =\"/led2on\">\r\n";
  web += "<button>LED2 On</button>\r\n";
  web += "</a>\r\n";
  web += "<a href=\"/led2off\">\r\n";
  web += "<button>LED2 Off</button>\r\n";
  web += "</a>\r\n";

  web += "<p>\r\n";
  if (status_led3 == 1)
    web += "LED3 On\r\n";
  else
    web += "LED3 Off\r\n";
  web += "</p>\r\n";
  web += "<p>\r\n";
  web += "<a href =\"/led3on\">\r\n";
  web += "<button>LED3 On</button>\r\n";
  web += "</a>\r\n";
  web += "<a href=\"/led3off\">\r\n";
  web += "<button>LED3 Off</button>\r\n";
  web += "</a>\r\n";
  
  web += "</body>\r\n";
  web += "</html>\r\n";
  client.print(web);
}
