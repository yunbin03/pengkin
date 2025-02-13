#include <SoftwareSerial.h>
#include "Arduino.h"
 
//블루투스 모듈의 Rx , TX 핀 정의
int BT_RXD = 3;
int BT_TXD = 4;
 
// #define DHTPIN 2   
//MQ135가스 센서의 아날로그 출력 핀 정의  
#define MQ135_5V_PIN_AOUT  A1

// #define DHTTYPE DHT11   // DHT 11
//소프트웨어 시리얼 객체 생성(블루투스 통신용)
SoftwareSerial SerialBLE(BT_RXD,BT_TXD);

//공기질 센서 값 저장할 변수
int airquality = 0;
int freshnessSensor = 0;

//블루투스 입력을 저장할 문자열
String BT_input;

//온습도 값 저장할 변수
float h =0.0;
float t =0.0;
float f =0.0;
// DHT dht(DHTPIN, DHTTYPE);
//장치 ID 설정
String device_id ="Freshness-I-001";
 
 
void setup() {
  
// 시리얼 통신 초기화
Serial.begin(9600);
SerialBLE.begin(9600); //블루투스 시리얼 통신 초기화
// dht.begin();
 
}
//센서 데이터를 읽고 전송하는 함수
void read_data (){
     //MQ135센서에서 아날로그 값 읽기
    freshnessSensor = analogRead(MQ135_5V_PIN_AOUT); 
    String JSON = String(freshnessSensor);
    Serial.println(JSON);
 
    SerialBLE.println(JSON);
    delay(2000);
}
void loop(){
    read_data();
    if(Serial.available()){
      SerialBLE.write(Serial.read());
    }
}
