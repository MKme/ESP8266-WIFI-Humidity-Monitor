/* 
Eric's ESP8266 DHT11 sensor to send you temp and humidity notifications via IFTTT

My Youtube Channel  : http://www.youtube.com/mkmeorg
My website   : http://www.mkme.org
If you use this code or personalize it etc- please consider sharing it back with the world Open-Source 
Tested with Arduino IDE 1.8.5

Support the channel by buying an ESP8266 here: https://amzn.to/2M4lw6E
DHT11 sensor here: https://amzn.to/2MnNJTf

Some code borrowed from: https://github.com/beamzer/Wemos-IFTTT-Button/blob/master/Wemos-IFTTT-Button/Wemos-IFTTT-Button.ino
Another cool version: https://nobugsjustfeatures.wordpress.com/2017/12/11/pir-sensor-alarm-with-esp8266-and-ifttt-webhooks-maker/
Yes some variables are no longer used and should be removed. That is a future person problem- deal with it.
Yes credentials are hard coded- I did this to expressly annoy the internutz. Life is about joy in little wins....
ESP Deep sleep tutorial from Rui here: https://randomnerdtutorials.com/esp8266-deep-sleep-with-arduino-ide/
GPIO16 must be tied to reset to wake!
Video explains: https://www.youtube.com/watch?v=Q8GT-GBH7ok

DHT Library was a PITA- finally deleted all my DHT libraries and installed adfruit one from IDE and works!
DHT Signal> D3 or GPIO0 
DHT VCC> 3V
DHT GND> GND
RST> D0 for wakeup (GPIO16/WAKE on NodeMCU)
NOTE: RST line wakeup Jumper must be removed to program!!!!!!!!!!!!!!
*/

#include <ESP8266WiFi.h>
const char* ssid     = "xxxxx";      // SSID of local network
const char* password = "xxxxxxx";   // Password on network
String result;
float h = 111;
float t = 222;
#include "DHT.h"
#define DHTPIN 0     // GPIO 0 on ESP12E Lolin is labelled pin D3 
// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11 
//#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor
// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.

DHT dht(DHTPIN, DHTTYPE);
void setup() 
{
  Serial.begin(115200);
  Serial.setTimeout(2000);

  while(!Serial) { }
  WiFi.hostname("ESP8266HumiditySensor"); //This changes the hostname of the ESP8266 to display neatly on the network esp on router.
  WiFi.begin(ssid, password);
  Serial.println("DHT11 test!");
  dht.begin();
  delay(2000);
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
   h = dht.readHumidity();
   t = dht.readTemperature();
   delay(1000);

  // check if returns are valid, if they are NaN (not a number) then something went wrong!
 if (isnan(t) || isnan(h)) {
    Serial.println("Failed to read from DHT");
  } else {
    Serial.print("Humidity: "); 
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperature: "); 
    Serial.print(t);
    Serial.println(" *C");
  }
  const char host[ ]        = "maker.ifttt.com";          // maker channel of IFTTT
  const char trigger[ ]     = "humidity";                   //name of the trigger you would like to send to IFTTT
  const char APIKey[ ]      = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";      //Your maker key for Webhooks on IFTTT
  Serial.print("Connect to: ");
  Serial.println(host);
  // WiFiClient to make HTTP connection
  WiFiClient client;
   if (!client.connect(host, 80)) {
    Serial.println("connection failed");
    return;
    }

// Build URL
  String url = String("/trigger/") + trigger + String("/with/key/") + APIKey + String("?value1=") + h + String("Temp=") + t;
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
  Serial.println("Your Daily Report on 3D Printer Humidity level and Temp"); //Send things to serial for handy dandy info
  Serial.print("humidity ");
  Serial.println(h);
  Serial.print("temp ");
  Serial.println(t);
  Serial.println("Deep sleep mode entered");
  ESP.deepSleep(3000e6); //30 for 30 seconds 7200 for 2 hours 86400 for 1 day
 }
void loop() //Where nothing happens because of sleepytimez
{ 

}


  
