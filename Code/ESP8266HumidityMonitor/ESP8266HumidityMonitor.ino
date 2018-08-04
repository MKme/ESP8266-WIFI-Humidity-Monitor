/* 
ESP8266 DHT11 sensor to send you notifications via IFTTT
My Youtube Channel  : http://www.youtube.com/mkmeorg
My website   : http://www.mkme.org
If you use this code or personalize it etc- please consider sharing it back with the world Open-Source 
Tested with Arduino IDE 1.6.7

converting to IFTTT and temporarily removed temp detection. Disabled wificlient in setup and only activate when ifttt is called- power savings
   Some code borrowed from: https://github.com/beamzer/Wemos-IFTTT-Button/blob/master/Wemos-IFTTT-Button/Wemos-IFTTT-Button.ino
Another cool version: https://nobugsjustfeatures.wordpress.com/2017/12/11/pir-sensor-alarm-with-esp8266-and-ifttt-webhooks-maker/


Yes some variables are no longer used and should be removed. That is a future person problem- deal with it.
Yes credentials are hard coded- I did this to expressly annoy the internutz. Life is about joy in little wins....
*/

#include <ESP8266WiFi.h>
const char* ssid     = "xxxx";      // SSID of local network
const char* password = "xxxxxx";   // Password on network
String result;
String temp ;
String humidity ;

void setup() 
{
  pinMode(D4, INPUT);
  pinMode(D7, INPUT);
  delay(2000);
  Serial.begin(115200);
  WiFi.hostname("ESP8266HumiditySensor"); //This changes the hostname of the ESP8266 to display neatly on the network esp on router.
}

void ifttt() //Wifi connection and send all the data to IFTTT
{
  const char host[ ]        = "maker.ifttt.com";          // maker channel of IFTTT
  const char trigger[ ]     = "humidity";                   //name of the trigger you would like to send to IFTTT
  const char APIKey[ ]      = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";      //Your maker key for Webhooks on IFTTT
  Serial.print("Connect to: ");
  Serial.println(host);
  // WiFiClient to make HTTP connection
  WiFiClient client;
  if (!client.connect(host, 80)) {
    Serial.println("connection failed");
    return;
    }

// Build URL
  String url = String("/trigger/") + trigger + String("/with/key/") + APIKey;
  Serial.print("Requesting URL: ");
  Serial.println(url);

// Send request to IFTTT
  client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n"); 
  //FYI rn rn is just two new lines to comply with http format
   delay(20);

// Read all the lines of the reply from server and print them to Serial
  Serial.println("Respond:");
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
    }
  Serial.println();
  Serial.println("closing connection");
  Serial.println(); //space things our in serial monitor for purdy
  Serial.println();
  client.stop();  //V5 added this to disconnect
  delay (20000); //This delay here just to stop spamming of emails- should be polished to a better method/location
 }
  
void loop() //Where stuffz happens
{
 if(digitalRead(D4)== HIGH)  // ||digitalRead(D7)== HIGH) Removed MQ2 or condition -------------- change this to be deep sleep timer==elapsed
  {
   humidity = digitalRead(D4); //PIR sensor pin
   temp = digitalRead(D7);  //MQ2 temp sensor pin
   Serial.println("Alarm detected!"); //Send things to serial for handy dandy info
   Serial.print("humidity ");
   Serial.println(humidity);
   Serial.print("temp ");
   Serial.println(temp);
   ifttt(); //Tell IFTTT that intruder detected
  } 
  else 
  {
    //Serial.println("no trigger"); //enable for debugging of no event being triggered
  }
}


  
