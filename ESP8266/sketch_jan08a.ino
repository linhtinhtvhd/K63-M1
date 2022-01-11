
#include "DHT.h"
#include <ESP8266HTTPClient.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WebSocketsClient.h> //https://github.com/Links2004/arduinoWebSockets
WebSocketsClient webSocket;
const char* ssid = "Linh"; //Đổi thành wifi của bạn
const char* password = "12345678"; //Đổi pass luôn
const char* ip_host = "172.20.10.3"; //Đổi luôn IP host của PC nha
const uint16_t port = 3000; //Port thích đổi thì phải đổi ở server nữa
const int LED = 2;
const int BTN = 0;
#define MotorASpeed 5
#define MotorADir 0
int speedCar = 1000;

#define DHTPIN D4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:
      Serial.printf("[WSc] Disconnected!\n");
      break;
    case WStype_CONNECTED:
      {
        Serial.printf("[WSc] Connected to url: %s\n", payload);
      }
      break;
    case WStype_TEXT:
      Serial.printf("[WSc] get text: %s\n", payload);
      if (strcmp((char*)payload, "LED_ON") == 0) {
        digitalWrite(LED, 0); // Khi client phát sự kiện "LED_ON" thì server sẽ bật LED
      } else if (strcmp((char*)payload, "LED_OFF") == 0) {
        digitalWrite(LED, 1); // Khi client phát sự kiện "LED_OFF" thì server sẽ tắt LED
      }
      break;
    case WStype_BIN:
   
      Serial.printf("[WSc] get binary length: %u\n", length);
      if(length == 2){
       batBom();
       break;
        }
      else if(length == 3){
         tatBom();
        }
      break;
  }
}
void sendRequest(float temperature, float humidity, float doamdat){
  if (WiFi.status() == WL_CONNECTED){
     WiFiClient client;
     HTTPClient http;
    http.begin("http://172.20.10.3:3000/news/dht11?temperature=" + String(temperature) + "&humidity=" + String(humidity) + "&doamdat=" + String(doamdat));
    http.addHeader("Content-Type", "text/plain");

    int httpResponseCode = http.POST(String(temperature)+String(humidity)+String(doamdat));
    if(httpResponseCode > 0){
      String reponse=http.getString();
      Serial.println(httpResponseCode);
      }
     else{
      Serial.println("Can't sent DHT11 data to server\n");
      }  
    }
  }
void setup() {
  // khởi chạy DHT11
  dht.begin();
  pinMode(LED, OUTPUT);
  pinMode(BTN, INPUT);
  pinMode(MotorASpeed, OUTPUT);
  pinMode(MotorADir, OUTPUT);
  pinMode(5, INPUT_PULLUP);

  Serial.begin(115200);
  Serial.println("ESP8266 Websocket Client");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  webSocket.begin(ip_host, port);
  webSocket.onEvent(webSocketEvent);
   
}
void batBom(){ 
      digitalWrite(MotorADir, HIGH);
      analogWrite(MotorASpeed, 1500); 
  }
void tatBom(){ 
      digitalWrite(MotorADir, HIGH);
      analogWrite(MotorASpeed, 0); 
  }  
void loop() {
  
  webSocket.loop();
  

  static unsigned long l = 0;
  unsigned long t = millis();
  if((t - l) > 2000)
  {
    l = t;
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float hdat = analogRead(A0);
  float percent = map(hdat, 350, 1023, 0, 100);    // Set giá thang giá trị đầu và giá trị cuối để đưa giá trị về thang từ 0-100. 
                                                  // Cái này sẽ bằng thực nghiệm nhé
  percent=100-percent;   
  if (isnan(h) || isnan(t) ||isnan( percent)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  sendRequest(t,h,percent);
}
}
