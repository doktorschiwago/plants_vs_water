

int mostureSensor = 4;

#include "DHT.h"
#include "pvw_wifi_pw.h"

#define DHTPIN 50     // what pin we're connected to

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11

#define DELAY 30000   

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht1(50, DHTTYPE);
DHT dht2(52, DHTTYPE);

String readLineFromWifi() {
  String res="";
  while(true) {
    if (Serial1.available()) {
      char inByte = Serial1.read();
      
      
      if (inByte=='\n') break;
      if (inByte=='\r') break;
      res+=inByte;
    }
  }
  
  return res;
}

void readLineFromWifi2(String check) {
   String res="";
  while(true) {
     res=readLineFromWifi();
     Serial.println(res);
     if (res==check) break;
  }
}

String readLineFromWifi3(String check, String check2) {
   String res="";
  while(true) {
     res=readLineFromWifi();
     Serial.println(res);
     if (res==check) break;
     if (res==check2) break;
  }
  return res;
}

String readLineFromWifi4(String check, String check2, String check3) {
   String res="";
  while(true) {
     res=readLineFromWifi();
     Serial.println(res);
     if (res==check) break;
     if (res==check2) break;
     if (res==check3) break;
  }
  return res;
}

void tryConnect() {
  String res="";
  while (res != "OK") {
    Serial1.write("AT+CIPSTART=\"TCP\",\"192.168.178.47\",9090\r\n");
    res=readLineFromWifi3("OK","CLOSED");
    Serial.println(res);
    delay(1000);
  } 
  Serial.println(readLineFromWifi());   
}

void waitSend(String msg) {
  Serial1.print("AT+CIPSEND=");
  Serial1.println(int(msg.length()+2));
  Serial.println(readLineFromWifi());
  Serial.println(readLineFromWifi());
  Serial.println(readLineFromWifi());
  Serial.println(readLineFromWifi());
  delay(500);
  Serial1.println(msg);
  String res=readLineFromWifi4("SEND OK", "ERROR", "SEND FAIL");
  if (res=="ERROR") {
    delay(1000);
    tryConnect();
  }
}

void setup() { 
  Serial.begin(9600);
  dht1.begin();
  dht2.begin();
  
  Serial1.begin(115200);
  
  delay(5000);
  
  Serial1.write("AT+RST\r\n");
  readLineFromWifi2("invalid");
  Serial.print("wifi resetted");
  delay(1000);
  
  Serial1.write("AT+CWMODE=1\r\n");
  readLineFromWifi2("OK");
  delay(1000);

  String initWPA="AT+CWJAP=\"vorholzstr2\",\"";
  initWPA+=WPA_PW;
  initWPA+="\"\r\n";
  
  Serial1.print(initWPA);
  readLineFromWifi2("OK");
  delay(1000);
  
  
  Serial1.write("AT+CIPMUX=0\r\n");
  readLineFromWifi2("OK");
  delay(1000);
  
  tryConnect();
  
}
// the loop routine runs over and over again forever: 

void loop() { 
  for (int i=0;i<mostureSensor;i++) {
    int sensorValue = analogRead(i+12);
    String line="M";
    line=line +  + i + "|" + sensorValue;
    Serial.println(line);
    
    waitSend(line);
    delay(DELAY);
  }

  float h = dht1.readHumidity();
  float t = dht1.readTemperature();
  
  String line="H1|";
  line+= (int)h;
  Serial.println(line);
  waitSend(line);
  
  delay(DELAY);

  line="T1|";
  line+= (int)t;
  Serial.println(line);
  waitSend(line);
  
  delay(DELAY);
  
  h = dht2.readHumidity();
  t = dht2.readTemperature();
  
  line="H2|";
  line+= (int)h;
  Serial.println(line);
  waitSend(line);
  
  delay(DELAY);

  line="T2|";
  line+= (int)t;
  Serial.println(line);
  waitSend(line);
  
  delay(DELAY);
}
