
// install esp8266wifi and esp8266ping library

#include <ESP8266WiFi.h>
#include <ESP8266Ping.h>
//connecting led to respective pin on node mcu
#define RYB 16  //D0
#define Blue 5 //D1
#define Red 4  //D2
#define indicator 13  //D7
#define Buzzer 14 //D5

int frequency=1000; //Specified in Hz
int timeOn=1000; //specified in milliseconds
int timeOff=1000; //specified in millisecods

const char* ssid     = "AndroidAP";  //enter your ssid
const char* password = "fxui3990.";  //enter your wifi password

const char* remote_host = "www.google.com"; // // Host to check


String avg_time_ms;
int i;

void setup() {
  Serial.begin(115200);
  
  pinMode(RYB,OUTPUT);
  pinMode(Blue,OUTPUT);
  pinMode(Red,OUTPUT);
  pinMode(indicator,OUTPUT);
  pinMode(Buzzer,OUTPUT);
  delay(10);
  
  Serial.println();
  Serial.println("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
     digitalWrite(indicator,HIGH); // turn the Indicator on (HIGH is the voltage level)
     delay(500); // wait for half second
      digitalWrite(indicator,LOW); //turn the LED off by making the voltage LOW
    delay(500);  // wait for a second
    Serial.print(".");
  }
  Serial.println();
  Serial.print("WiFi connected with ip ");  // Just for troubleshot purpose.  
  Serial.println(WiFi.localIP());
  Serial.print("Pinging host ");  // Just for troubleshot purpose.
  Serial.println(remote_host);
  digitalWrite(indicator,HIGH);
}

void loop() {

    if(Ping.ping(remote_host)) 
    {
    Ping.ping(remote_host, 10);  //10 time ping to google
    i= Ping.averageTime();
    avg_time_ms = Ping.averageTime(); // reading string and Int for easy display integration.
    Serial.println(i);
    int speedo;
    int Speedo= avg_time_ms.toInt();

 if(Speedo>0 && Speedo<150)  // low 
 {
  
   Serial.println("Poor Connection of Internet");
  Serial.println("Your Internet download speed is very low. Web browsing should work, but videos could load slowly.");
  Serial.println("RYB led on");
  digitalWrite(RYB,HIGH);
  digitalWrite(Blue,LOW);
  digitalWrite(Red,LOW);
 }
if(Speedo>150 && Speedo<200)  // average 
   Serial.println("Average Connection of Internet");
  Serial.println("Your Internet download speed is average. Web browsing should work,videos may have load slowly and online gaming may lag.");
  Serial.println("Blue led on");
  digitalWrite(RYB,LOW);
  digitalWrite(Blue,HIGH);
  digitalWrite(Red,LOW);
 }

if(Speedo>200 && Speedo<=1000)  // High 
 {
   
  Serial.println("Excellent connection of Internet");
  Serial.println("Your Internet speed is fast. Web browsing,Video uploading,Online gaming will run smoothly");
  Serial.println("Red led on");
  digitalWrite(RYB,LOW);
  digitalWrite(Blue,LOW);
  digitalWrite(Red,HIGH);
 }
     
   else 
    {
  Serial.println("No connection");
  Serial.println("Your device is not connected to internet");
    Serial.println("If you want to check your internet speed please connect your device with a stable internet");
  digitalWrite(RYB,LOW);
  digitalWrite(Blue,LOW);
  digitalWrite(Red,LOW);
   delay(100);
    digitalWrite(indicator,HIGH);
     delay(100);
     digitalWrite(Buzzer,HIGH);
     tone(Buzzer, frequency);
      delay(timeOn);
      noTone(Buzzer);
      delay(timeOff);


    }
  
 
 // delay(1000);  // Every minutes
 
}
