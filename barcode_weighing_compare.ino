////ESP Code/////

/*
 * This code is used to program the ESP WiFi module such that it will take data from Arduino Mega
 * 
 * It compares the weight from weighing sensor and the barcode from Arduino Mega. First it reads the barcode, 
 * then it reads the weight and then it compares both the datas from an already defined database of Barcodes,
 * Item Name, price and Weight.
 */

#ifdef ESP32
  #include <WiFi.h>
  #include <HTTPClient.h>
#else
  #include <ESP8266WiFi.h>
  #include <ESP8266HTTPClient.h>
  #include <WiFiClient.h>
#endif

#include <Wire.h>
#include <SoftwareSerial.h>

// Replace with your network credentials
const char* ssid     = "FTTH/KM16D";
const char* password = "@TheRate@123";

// REPLACE with your Domain name and URL path or IP address with path
const char* serverName = "http://192.168.1.22/example/post-esp.php";

// Keep this API Key value to be compatible with the PHP code provided in the project page. 
// If you change the apiKeyValue value, the PHP file /post-esp-data.php also needs to have the same key 
String apiKeyValue = "tPmAT5Ab3j7F9";


char data1[17];
String pid, counter, pid1,pid2;
String wt; 
String pname;
String cost, payload;
int totalwt=0,wt1;
int payload1;
int c=0;

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }
}

void loop() {
  pid = "";
  wt = "";
  if (Serial.available()){
   for (int i=0; i<17; i++){
    data1[i] = (char)Serial.read();
   } 
   for(int i=0; i<13; i++){
    pid += data1[i];
  }
   for(int i=13; i<17; i++){
    wt += data1[i];
  }
  }

  if(WiFi.status()== WL_CONNECTED){                           //Check WiFi connection status
     HTTPClient http;
      // Your Domain name with URL path or IP address with path
      http.begin(serverName);
      // Specify content-type header
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");

      if(counter == "Proceed"){
        pid = pid2;
      }
      String httpRequestData = "api_key=" + apiKeyValue + "&pid=" + (pid) + "&counter=" + counter;   
      int httpResponseCode = http.POST(httpRequestData);       
      payload = http.getString();
      if (payload !="" && pid != pid2){
       payload1 = payload.toInt();
       totalwt += payload1;
      }

      wt1 = wt.toInt();
      if((totalwt > (wt1-10) && totalwt < (wt1+10)) && wt1!=0){
      delay(3000);
      counter = "Proceed";
      pid2 = pid;
      Serial.println("Success");
      }
      else{
        Serial.println("Error");
        counter = "";
      }

    // Free resources
    http.end();
  }
  
  else {
    Serial.println("WiFi Disconnected");
  }
  //Send an HTTP POST request every 30 seconds
  delay(3000); 
  
  }
