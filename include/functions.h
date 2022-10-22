#include <ESP8266WiFi.h>

void WiFi_setup(const char* ssid,const char* password){

      WiFi.begin(ssid, password);
      Serial.println("Connecting to WiFi");
      while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println(".");
      }
    Serial.println(WiFi.localIP());
}

void writeFile(fs::FS &fs, const char * path, const char * message){
  Serial.printf("Writing file: %s\r\n", path);
  File file = fs.open(path, "w");
  if(!file){
    Serial.println("- failed to open file for writing");
    return;
  }
  if(file.print(message)){
    Serial.println("- file written");
  } else {
    Serial.println("- write failed");
  }
}

String readFile(fs::FS &fs, const char * path){
  Serial.printf("Reading file: %s\r\n", path);
  File file = fs.open(path, "r");
  if(!file || file.isDirectory()){
    Serial.println("- empty file or failed to open file");
    return String();
  }
  Serial.println("- read from file:");
  String fileContent;
  while(file.available()){
    fileContent+=String((char)file.read());
  }
  Serial.println(fileContent);
  return fileContent;
}





/*
void server_setup(const String& var, float t, float h, const char index_html[]){
  
      // Create AsyncWebServer object on port 80
      AsyncWebServer server(80);

      // Print ESP8266 Local IP Address
      // Route for root / web page
      server.on("/", HTTP_GET, [](AsyncWebServerRequest *request,const char index_html,float t,float h){
        request->send_P(200, "text/html", index_html, processor());
      });
      server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request,const char index_html,float t,float h){
        request->send_P(200, "text/plain", String(t).c_str());
      });
      server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request,const char index_html,float t,float h){
        request->send_P(200, "text/plain", String(h).c_str());
      });

      // Start server
      server.begin();
}
*/


