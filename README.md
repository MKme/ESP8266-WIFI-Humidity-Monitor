# ESP8266-WIFI-Humidity-Monitor
Wireless humidity Monitor for my 3D printer filament. Samples DHT 11 every X hours/days, sends it to IFTTT and goes back in to deep sleep.

See the FULL Assembly and project video here: 

See this video for detailled IFTT Config (motion sensor) https://www.youtube.com/watch?v=y9XC5yHR5Bk

### Wiring For ESP12E LOLIN 

| Pin On DHT11| Pin On ESP8266|
| ------------- |----------------|
| GND     | G |
| VCC     | 3V3 |
| SIG    | GPIO0 (D3 on LOLIN) |

### Special Wiring

RST> D0 for wakeup (GPIO16/WAKE on NodeMCU)

NOTE: RST line wakeup Jumper must be removed to program!


### Support my projects by picking up the display/board here:

ESP8266: https://amzn.to/2vkxOP2

DHT11: https://amzn.to/2OP0RSD

### More Projects and Videos!
My Youtube Channel  : http://www.youtube.com/mkmeorg
My website   : http://www.mkme.org
