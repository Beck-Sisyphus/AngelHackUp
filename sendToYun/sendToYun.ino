// Angel Hack Seattle, 2015, June 28
// Beck Pang

#include <ESP8266WiFi.h>
#include <SPI.h>
#include <WifiUdp.h>
#include <Wire.h>

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

// IMU reading
const int MPU = 0x68;  // I2C address of the MPU-6050

int AcX[7] = {0, 0, 0, 0, 0, 0, 0};
int AcY[7] = {0, 0, 0, 0, 0, 0, 0};
int AcZ[7] = {0, 0, 0, 0, 0, 0, 0};
int Tmp[7] = {0, 0, 0, 0, 0, 0, 0};
int GyX[7] = {0, 0, 0, 0, 0, 0, 0};
int GyY[7] = {0, 0, 0, 0, 0, 0, 0};
int GyZ[7] = {0, 0, 0, 0, 0, 0, 0};

int AcXAvg = 0;
int AcYAvg = 0;
int AcZAvg = 0;
int GyXAvg = 0;
int GyYAvg = 0;
int GyZAvg = 0;

void setup() {
    Serial.begin(115200);
    delay(10);

    connectToYun();
    Udp.begin(UDP_PORT);

    prepareIMUread();
    Serial.println("STARTING");
}

void loop() {
    readMPU6050();
    avgArrays();
    outputDataToMonitor();
    outputDataToUdp();
    reset();
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

void prepareIMUread() {
    Wire.begin();
    Wire.beginTransmission(MPU);
    Wire.write(0x6B);  // PWR_MGMT_1 register
    Wire.write(0);     // set to zero (wakes up the MPU-6050)
    Wire.endTransmission(true);
}
