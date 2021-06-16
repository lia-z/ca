//#include <SoftwareSerial.h>
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>

#define WIFI_SSID "iptime2"//wifi_name  wifi_test  연결할 와이파이 이름
#define WIFI_PASSWORD "12345670"//wifi_password 1234567890   연결할 와이파이 비밀번호
#define FIREBASE_HOST "fir-ex1-83c94-default-rtdb.firebaseio.com/" //firebase_address
#define FIREBASE_AUTH "ojjrM9MhvXn6CfwZd5wnLF4VkSK0VIEAsiRFaW9W" //firebase_password

FirebaseData firebaseData;
FirebaseJson json;

String path = "/Cars";
int data_A1 = 0;
int data_A2 = 0;
int old_data_A1 = 0;
int old_data_A2 = 0;

void setup() {
  pinMode(2,INPUT);
  pinMode(0,INPUT); 
  
  WiFi.begin(WIFI_SSID,WIFI_PASSWORD);

  while(WiFi.status() != WL_CONNECTED){  //wifi 연결될때까지 while 
    //Serial.print(".");
    delay(1000);
  }

  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  Firebase.setString(firebaseData,path + "/A1", "0");
  Firebase.setString(firebaseData,path + "/A2", "0");
}

void loop() {

  //장애물감지 센서부분
  data_A1 = digitalRead(0);
  data_A2 = digitalRead(2);

  //HIGH가 감지를 안했을때 물제를 감지못하면 0 감지하면 1
  if(data_A1 == HIGH){
    data_A1 = 0;
  }
  else{
    data_A1 = 1;
  }

  if(data_A2 == HIGH){
    data_A2 = 0;
  }
  else{
    data_A2 = 1;
  }

  if(old_data_A1 != data_A1){
    if(data_A1 == 0){
      Firebase.setString(firebaseData,path + "/A1", "0");
    }
    else if(data_A1 == 1){
      Firebase.setString(firebaseData,path + "/A1", "1");
    }
    old_data_A1 = data_A1;
  }

  if(old_data_A2 != data_A2){
    if(data_A2 == 0){
      Firebase.setString(firebaseData,path + "/A2", "0");
    }
    else if(data_A2 == 1){
      Firebase.setString(firebaseData,path + "/A2", "1");
    }
    old_data_A2 = data_A2;
  }

  delay(1000);
}
