#include <WiFi.h>
#include <WiFiUdp.h>

#define fwd_back_flex 33
#define left_flex 26
#define right_flex 25

#define fwd_limit     900                     
#define back_limit 400
#define left_limit 900
#define right_limit 1200

const char* ssid = "Mascot";
const char* password = "12345678";

const char * udpAddress = "192.168.43.129";
const int udpPort = 1111;

boolean connected = false;
WiFiUDP udp;
IPAddress ip;

void setup() {
  pinMode(fwd_back_flex,INPUT);
  pinMode(left_flex,INPUT);
  pinMode(right_flex,INPUT);
  Serial.begin(115200);
  connectToWiFi();
}

void connectToWiFi(){
  Serial.println();
  Serial.println();
  Serial.print("Connecting to WIFI network");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  ip = WiFi.localIP();
  udp.begin(ip,udpPort);
  Serial.println(ip);
}

void loop() {

  Serial.print("flex 1:");Serial.println(analogRead(fwd_back_flex),DEC); 
  Serial.print("flex 2:");Serial.println(analogRead(left_flex),DEC); 
  Serial.print("flex 3:");Serial.println(analogRead(right_flex),DEC); 
  Serial.println();Serial.println();Serial.println();
  
//  udp.beginPacket(udpAddress,udpPort);
//  udp.printf("Connected");
//  udp.endPacket();
  
  if(analogRead(fwd_back_flex)>fwd_limit && analogRead(left_flex)>left_limit && analogRead(right_flex)>right_limit){
    //forward
    udp.beginPacket(udpAddress,udpPort);
    udp.printf("Forward");
    udp.endPacket();
  }
  else if(analogRead(fwd_back_flex)>fwd_limit && analogRead(left_flex)>left_limit && analogRead(right_flex)<=right_limit){
    //forward left
    udp.beginPacket(udpAddress,udpPort);
    udp.printf("softLeftF");
    udp.endPacket();
  }
  else if(analogRead(fwd_back_flex)>fwd_limit && analogRead(left_flex)<=left_limit && analogRead(right_flex)>right_limit){
    //forward right
    udp.beginPacket(udpAddress,udpPort);
    udp.printf("softRightF");
    udp.endPacket();
  }
  else if(analogRead(fwd_back_flex)>fwd_limit && analogRead(left_flex)<=left_limit && analogRead(right_flex)<=right_limit){
    //forward
    udp.beginPacket(udpAddress,udpPort);
    udp.printf("Forward");
    udp.endPacket();
  }

  else if(analogRead(fwd_back_flex)<back_limit && analogRead(left_flex)>left_limit && analogRead(right_flex)>right_limit){
    //back
    udp.beginPacket(udpAddress,udpPort);
    udp.printf("Backward");
    udp.endPacket();
  }
  else if(analogRead(fwd_back_flex)<back_limit && analogRead(left_flex)>left_limit && analogRead(right_flex)<=right_limit){
    //back left
    udp.beginPacket(udpAddress,udpPort);
    udp.printf("softLeftB");
    udp.endPacket();
  }
  else if(analogRead(fwd_back_flex)<back_limit && analogRead(left_flex)<=left_limit && analogRead(right_flex)>right_limit){
    //back right
    udp.beginPacket(udpAddress,udpPort);
    udp.printf("softRightB");
    udp.endPacket();
  }
  else if(analogRead(fwd_back_flex)<back_limit && analogRead(left_flex)<=left_limit && analogRead(right_flex)<=right_limit){
    //back
    udp.beginPacket(udpAddress,udpPort);
    udp.printf("Backward");
    udp.endPacket();
  }
  else if(analogRead(fwd_back_flex)<=fwd_limit && analogRead(fwd_back_flex)>=back_limit && analogRead(left_flex)>left_limit && analogRead(right_flex)>right_limit){
    //reset
    udp.beginPacket(udpAddress,udpPort);
    udp.printf("Reset");
    udp.endPacket();
  }
  else if(analogRead(fwd_back_flex)<=fwd_limit && analogRead(fwd_back_flex)>=back_limit && analogRead(left_flex)>left_limit && analogRead(right_flex)<=right_limit){
    //hard left
    udp.beginPacket(udpAddress,udpPort);
    udp.printf("hardLeft");
    udp.endPacket();
  }
  else if(analogRead(fwd_back_flex)<=fwd_limit && analogRead(fwd_back_flex)>=back_limit && analogRead(left_flex)<=left_limit && analogRead(right_flex)>right_limit){
    //hard right
    udp.beginPacket(udpAddress,udpPort);
    udp.printf("hardRight");
    udp.endPacket();
  }
  else if(analogRead(fwd_back_flex)<=fwd_limit && analogRead(fwd_back_flex)>=back_limit && analogRead(left_flex)<=left_limit && analogRead(right_flex)<=right_limit){
    //reset
    udp.beginPacket(udpAddress,udpPort);
    udp.printf("Reset");
    udp.endPacket();
  }
  delay(2000);
}
