#include <ESP8266WiFi.h>
const char* ssid = "Elec_Surat";
const char* password = "91992189327";

void setup() {
  // put your setup code here, to run once:
  //Serial.begin(115200);
  //delay(10);
  //Serial.println(); Serial.println();
  //Serial.print("Connecting to ");
  //Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    //Serial.print(".");
  }
  //Serial.println("");
  //Serial.println("WiFi connected");
  //Serial.print("IP address : ");
  //Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:

}
