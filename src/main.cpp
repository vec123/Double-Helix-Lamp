// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

//----------------------------Definitions
#define FASTLED_ESP8266_NODEMCU_PIN_ORDER
#include <Arduino.h>
#include "FastLED.h"
#include <functions.h>
#include <led_functions.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESP8266WiFi.h>

#include "FS.h"
#include <LITTLEFS.h>

//#define PIN D4
//#define NUM_LEDS 100
#define LED 2
#define DELAYVAL 100 // Time (in milliseconds) to pause between pixels

//-------------------------REPLACE WITH YOUR NETWORK CREDENTIALS
const char* ssid = "Vodafonemagneticjesus";
const char* password = "Inthelandofnails:)";


String inputMode = "Off";
String currentMode = inputMode;
String inputColor = "Off";
String currentColor = inputColor;

//-----------------------Web-server
AsyncWebServer server(80);

String processor(const String& var){
  if(var == "MODE"){
    return currentMode;
  }
  if(var == "COLOR"){
    return currentColor;
  }
  return String();
}


//switch modes:
// Value-Defintions of the different String values
enum StringValue { evStringValueRBFade,
                          evStringValueRBRun,
                          evStringStrobe,
                          evStringSnake1,
                          evStringSnake2,
                          evStringFire,
                          evStringOff
                           };

static std::map<String, StringValue> s_mapStringValues;

void initialize_string_map()
{
  s_mapStringValues["Rainbow fade"] = evStringValueRBFade;
  s_mapStringValues["Rainbow run"] = evStringValueRBRun;
  s_mapStringValues["Strobe"] = evStringStrobe;
  s_mapStringValues["Snake1"] = evStringSnake1;
  s_mapStringValues["Snake2"] = evStringSnake2;
  s_mapStringValues["Fire"] = evStringFire;
  s_mapStringValues["Off"] = evStringOff;

}


// Map to associate the strings with the enum values



//------------------------------Setup
void setup()
{
  Serial.begin(115200); 
  Serial.print("start");  
  pinMode(LED, OUTPUT);


//---------WiFi
  WiFi_setup(ssid, password);
  Serial.print(WiFi.localIP());


  if(!LittleFS.begin()){
      Serial.println("An Error has occurred while mounting LITTLEFS");
      return;
    }
    
 //-----------Server-Send web page with input fields to client
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(LittleFS, "/index.html", String(), false, processor);
  });
      // Route to load style.css file
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(LittleFS, "/style.css", "text/css");
      });

    server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage;
    String inputParam;
    // GET input1 value on <ESP_IP>/get?input1=<inputMessage>
    if (request->hasParam("mode") ){
      int inputNr = request->params();
      AsyncWebParameter* p = request->getParam(1);
      currentMode = p->value();
      writeFile(LittleFS, "/inputMode.txt", currentMode.c_str());
    }
    if (request->hasParam("color") ){
      int inputNr = request->params();
      AsyncWebParameter* p = request->getParam(1);
      currentColor = p->value();
      writeFile(LittleFS, "/inputColor.txt", currentColor.c_str());
    }

    });
   server.begin();

   setup_leds();

   initialize_string_map();
}



//---------------------------Loop
void loop() {

      //digitalWrite(LED, HIGH);
      //delay(1000);
      //digitalWrite(LED, LOW);
      //delay(1000);
       //Serial.println(currentColor);
       //Serial.println(currentMode);

 
       switch(s_mapStringValues[currentMode])
      {  
        case evStringValueRBFade:
          Serial.println("1");

          break;
        case evStringValueRBRun:
          Serial.println("2");

          break;
        case evStringStrobe:
          Serial.println("3");
          Strobe(0xff, 0xff, 0xff, 10, 50, 10);
          break;
        case evStringSnake1:
          Serial.println("4");

          break;
        case evStringSnake2:
          Serial.println("5");

          break;
        case evStringFire:
          Serial.println("6");
          Fire(55,120,15);

          break;
        case evStringOff:
          Serial.println("7");

          break;
                 }
       
       //Fire(55,120,15);
       //fill_solid( leds, led_number, CRGB::Red); 
      //for(int i =0; i<led_number; i++){
       // leds[i] = CRGB::Red;
       // }
       //FastLED.clear();
       // FastLED.show();
      // leds[10] = CRGB::Green;
      // FastLED.show();
      //FastLED.delay(1000);
      //Fire(55,120,15);
}


