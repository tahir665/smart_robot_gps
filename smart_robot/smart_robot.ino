#include "FirebaseESP8266.h"  // Install Firebase ESP8266 library
#include <ESP8266WiFi.h>
#include <TinyGPS++.h> // library for GPS module
#include <SoftwareSerial.h>
TinyGPSPlus gps;  // The TinyGPS++ object
SoftwareSerial ss(D1, D2); // The serial connection to the GPS device
float latitude , longitude;
String  lat_str , lng_str;
#define WIFI_SSID "speed"
#define WIFI_PASSWORD "18678a20"
#define FIREBASE_HOST "https://smartrobo-ad032-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "xYfEhvB9TdOcBfKPHXqKIe1ctjEKxzrkLyOfe63q"
FirebaseData fbdo;
FirebaseData getdata1;
FirebaseJson json;
String state="";
String d2="";
String d3="";
String d4="";
int motor2Pin1 = D5; // pin 6 on L293D IC
int motor2Pin2 = D6; // pin 7 on L293D IC

int motor1Pin1 = D7; // pin 4 on L293D IC
int motor1Pin2 = D8; // pin 5 on L293D IC
void setup() {
  Serial.begin(115200);
   ss.begin(9600);
    pinMode(motor1Pin1, OUTPUT);
    pinMode(motor1Pin2, OUTPUT);
    pinMode(motor2Pin1, OUTPUT);
    pinMode(motor2Pin2, OUTPUT);
  // put your setup code here, to run once:
   WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

}

void loop() {
  // put your main code here, to run repeatedly:
  Firebase.getString(getdata1,"temp");
  state=getdata1.stringData();
  Serial.println(state);
   if (state == "1"){
   forword();Serial.println("Go Forward!");}

   // if the state is '2' the motor will Reverse
   else if (state == "2"){
   backword();Serial.println("Reverse!");}
    
   // if the state is '3' the motor will turn left
   else if (state == "3"){
   turnLeft();Serial.println("Turn LEFT");}
    
   // if the state is '4' the motor will turn right
   else if (state == "4"){
   turnRight();Serial.println("Turn RIGHT");}
    
   // if the state is '5' the motor will Stop
   else if (state == "0") {
   Stop();Serial.println("STOP!");}    

   
while (ss.available() > 0) //while data is available
    if (gps.encode(ss.read())) //read gps data 
    {Serial.println(gps.encode(ss.read()));
      if (gps.location.isValid()) //check whether gps location is valid
      {
        latitude = gps.location.lat();
        
        lat_str = String(latitude , 6);// latitude location is stored in a string
        Serial.print("latitude:");
        Serial.println(lat_str);
        Firebase.setString(fbdo, "lat", lat_str);
        longitude = gps.location.lng();
        lng_str = String(longitude , 6); //longitude location is stored in a string
        Serial.print("longitude:");
        Serial.println(lng_str);
        Firebase.setString(fbdo, "lon", lng_str);
      }
}


}


void forword(){
    digitalWrite(motor1Pin1, HIGH);
    digitalWrite(motor1Pin2, LOW); 
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, HIGH);
}

void backword(){
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH); 
    digitalWrite(motor2Pin1, HIGH);
    digitalWrite(motor2Pin2, LOW);
}

void turnRight(){
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH); 
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, HIGH);
}

void turnLeft(){
    digitalWrite(motor1Pin1, HIGH);
    digitalWrite(motor1Pin2, LOW); 
    digitalWrite(motor2Pin1, HIGH);
    digitalWrite(motor2Pin2, LOW);
}

void Stop(){
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, LOW); 
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, LOW);
}
