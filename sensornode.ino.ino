#include <ESP8266WiFi.h>


const char* ssid     = "Stark";
const char* password = "eachday97";

#define domaxi A0
#define axi1 5
#define axi2 4
#define sound 0
int domiaxi,domiaxi1,domiaxi2, axis1, axis2, cry, trigcount,inloopcnt;
const char* host = "iotgrid.000webhostapp.com";
//https://iotgrid.000webhostapp.com/
long previousMillis = 0;      
long interval = 5000; 
void setup() {
  // put your setup code here, to run once:
pinMode(domaxi,INPUT);
pinMode(axi1,INPUT);
pinMode(axi2,INPUT);
pinMode(sound,INPUT);
Serial.begin(115200);

  WiFi.begin(ssid, password); 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Netmask: ");
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: ");
  Serial.println(WiFi.gatewayIP());
    Serial.println("Now connected");
  Serial.print("connecting to ");
  Serial.println(host);
 
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  //https://iotgrid.000webhostapp.com/api/LED/update.php?id=1&status=sleep
  String url = "/api/LED/update.php?id=1&status=sleeping";
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  delay(500);
  
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  
  Serial.println();
  Serial.println("closing connection");
  delay(3000);
 
delay(100);
}

void loop() {
  // put your main code here, to run repeatedly:
domiaxi=analogRead(domaxi);
axis1=analogRead(axi1);
axis2=analogRead(axi2);
cry=analogRead(sound);
//String st="Dominant_axis: "+String(domiaxi)+"; axis1: "+String(axis1)+"; axis2: "+String(axis2)+"; cry_level: "+String(cry);
//Serial.println(st);
delay(200);
domiaxi1=analogRead(domaxi);
delay(200);
domiaxi2=analogRead(domaxi);
delay(200);
if((((domiaxi1-domiaxi2)*(domiaxi1-domiaxi2))>10)||(((domiaxi1-domiaxi2)*(domiaxi1-domiaxi2))>10)||(((domiaxi1-domiaxi2)*(domiaxi1-domiaxi2))>10))
{
  //Serial.println("Motion Detected");
  trigcount++;
  if(trigcount==2)
  {
    trigcount=0;
    for(int i=0;i<3;i++)
    {
      domiaxi=analogRead(domaxi);
      axis1=analogRead(axi1);
      axis2=analogRead(axi2);
      cry=analogRead(sound);
      //String st="Dominant_axis: "+String(domiaxi)+"; axis1: "+String(axis1)+"; axis2: "+String(axis2)+"; cry_level: "+String(cry);
      //Serial.println(st);
      delay(200);
      domiaxi1=analogRead(domaxi);
      delay(200);
      domiaxi2=analogRead(domaxi);
      delay(200);
      if((((domiaxi1-domiaxi2)*(domiaxi1-domiaxi2))>10)||(((domiaxi1-domiaxi2)*(domiaxi1-domiaxi2))>10)||(((domiaxi1-domiaxi2)*(domiaxi1-domiaxi2))>10))
      {
        inloopcnt++;
        }      
      delay(1000);
      }
      if(inloopcnt>1)
      {
        inloopcnt=0;
        Serial.println("Definite wakeup");
        /////////
  Serial.print("connecting to ");
  Serial.println(host);
 
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  
  String url = "/api/LED/update.php?id=1&status=awake";
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  delay(500);
  
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  
  Serial.println();
  Serial.println("closing connection");
  delay(3000);
        /////////
        delay(100);        
        loop();
        }
        
}}}
