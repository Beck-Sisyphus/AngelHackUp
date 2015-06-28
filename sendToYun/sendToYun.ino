// Angel Hack Seattle, 2015, June 28
// Beck Pang

#include <ESP8266WiFi.h>
#include <SPI.h>
// #include <Wifi.h>
#include <WifiUdp.h>

// const char* ssid = "Idol";
// const char* password = "how do you turn this on";
const char* ssid = "192.168.240.1";  // Yun SSID
const char* password = "";
const int UDP_PORT = 8888;

int status = WL_IDLE_STATUS;
int keyIndex = 0;            // your network key Index number (needed only for WEP)

unsigned int localPort = 2390;      // local port to listen on

char packetBuffer[255]; //buffer to hold incoming packet
char  ReplyBuffer[] = "acknowledged";       // a string to send back

WiFiUDP Udp;

void setup() {
    Serial.begin(115200);
    delay(10);
    connectToYun();
    Udp.begin(UDP_PORT);
}

void loop() {
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(ReplyBuffer);
    Udp.endPacket();
}

void connectToYun() {
  	// We start by connecting to a WiFi network

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    
    WiFi.begin(ssid, password);
    
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");  
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}
