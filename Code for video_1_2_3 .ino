#include "DHT.h"
#include <ESP8266WiFi.h>

const char* ssid     = "Pratheep 2g";
const char* password = "18112507";

#define D0 16   // 
#define FAN D0  // 
#define MOTION D2 
#define DHTPIN D7     // what digital pin we're connected to
#define DHTTYPE DHT22

//Motion
int val = 0;
int cou = 0;
//Temp sensor
DHT dht(DHTPIN, DHTTYPE);
 int timer = 0;
  int lastDHTRead = 0;
  
  
  
void setup() 
{
  Serial.begin(115200);
   Serial.println("Starting...");

   WiFi.begin(ssid, password);
   while (WiFi.status() != WL_CONNECTED) 
   {
      delay(250);
      Serial.print(".");
   }

   Serial.println("WiFi connected");  
   Serial.println("IP address: ");
   Serial.println(WiFi.localIP());
  dht.begin();
  pinMode(FAN,OUTPUT); // setup output
  pinMode(MOTION,INPUT);
}

void loop() 
{
  val = digitalRead(MOTION);
  Serial.print("val = ");
  Serial.println(val);
  Serial.println(cou);
  delay(2000);
  if (val == 1) {
  if (cou < 200) {
    cou = 150;
  }
  }
  if (val == 0) {
if (cou > 0) {
cou = cou - 1;
}
  }
  if(millis() - lastDHTRead > 2000){
    float humid = dht.readHumidity();     // read humidity
    float temp  = dht.readTemperature();  // read temperature
    lastDHTRead = millis();
          
    Serial.print("Humid: "); Serial.print(humid); Serial.print(" %, ");
    Serial.print("Temp: "); Serial.print(temp); Serial.println(" °C ");
    
    
    if (isnan(humid) || isnan(temp)) { // check humid/temp is valid or not
      Serial.println("Failed to read from DHT sensor!");
    }
    else{
      // from a string in this format --> "{humid},{temp}"
      String datastring = (String)humid+","+(String)temp;
      }  
  
  if(temp>26&&cou>0){
  digitalWrite(FAN,LOW); // Pin D0 is LOW
  }
  else if (temp<25||cou==0){
  digitalWrite(FAN,HIGH); // Pin D0 is HIGH
  }

}
}
