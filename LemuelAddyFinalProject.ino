#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <Update.h>
#include "first.h"
#include "second.h"
#include "third.h"
#include <Update.h>
#include "DHT.h"
#include <WiFiMulti.h>
#include <HTTPClient.h>
#include <EEPROM.h>
#include <FastLED.h>
#define LED_PIN     18
#define NUM_LEDS    60

#define USE_SERIAL Serial
#define DHTPIN 27
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
//define sound speed in cm/uS
#define SOUND_SPEED 0.034
#define uS_TO_S_FACTOR 1000000ULL /* Conversion factor for micro seconds to seconds */
#define EEPROM_SIZE 20
#define CM_TO_INCH 0.393701
// IPAddress local_IP(172,20,10,2);
// IPAddress gateway(172,20,10,1);
// IPAddress subnet(255,255,0,0);
// IPAddress primaryDNS(8,8,8,8);
// IPAddress secondaryDNS(8,8,4,4);
WiFiMulti wifiMulti;
CRGB leds[NUM_LEDS];
long duration;
float distanceCm;
float waterlevel;
float h;
float temp;
const int trigPin = 13;
const int echoPin = 12;
int relay = 26; //ultrasonic
int relay_fan = 19;
String hData;
const int LDR_PIN = 33;
int LDR_Reading;
int ledB = 32;
int ledR = 14;
int ledG = 25;
int redlight = 127;
int bluelight = 127;
int greenlight = 0;



unsigned long HumidityPreviousTime = millis();
unsigned long TempPreviousTime = millis();
unsigned long DBpreviousTime = millis();
unsigned long DBpreviousTime1 = millis();
unsigned long DBpreviousTime2 = millis();
unsigned long DBpreviousTime3 = millis();
unsigned long DBpreviousTime4 = millis();
long DBuploadFreq = 3000;
long DBuploadFreqUltra = 3333;
long DBuploadFreqLDR = 5555;
long DBuploadFreqTemp = 2222;
long DBuploadFreqHumid = 7777;
long HumidityTime = 10000;
long TempTime = 10000;
long LEDTime = 100;
int ledState = LOW;

int i=0;
int hVal[10];
int tVal[10];
int lVal[10];
int uVal[10];
int address=0;
int address2=0;
int address3=0;
int address4=0;


// const char* ssid = "DUFIE-HOSTEL";
// const char* password = "Duf1e@9723";
// const char* ssid = "Lemuels iPhone";
// const char* password = "password";
const char* ssid = "Esisarsah";
const char* password = "iseesi@hotmail";
// const char* ssid = "Pixel 4";
// const char* password = "yuxl642&";

WebServer server(80);

int state;
int state2;
int state3;
int light_notif;
int water_notif;
int temp_notif;
int man;



/* Style */
String style =
"<style>#file-input,input{width:100%;height:44px;border-radius:4px;margin:10px auto;font-size:15px}"
"input{background:#f1f1f1;border:0;padding:0 15px}body{background:#3498db;font-family:sans-serif;font-size:14px;color:#777}"
"#file-input{padding:0;border:1px solid #ddd;line-height:44px;text-align:left;display:block;cursor:pointer}"
"#bar,#prgbar{background-color:#f1f1f1;border-radius:10px}#bar{background-color:#3498db;width:0%;height:10px}"
"form{background:#fff;max-width:258px;margin:75px auto;padding:30px;border-radius:5px;text-align:center}"
".btn{background:#3498db;color:#fff;cursor:pointer}</style>";

/* Login page */
String loginIndex = 
"<form name=loginForm>"
"<h1>ESP32 Login</h1>"
"<input name=userid placeholder='User ID'> "
"<input name=pwd placeholder=Password type=Password> "
"<input type=submit onclick=check(this.form) class=btn value=Login></form>"
"<script>"
"function check(form) {"
"if(form.userid.value=='admin' && form.pwd.value=='admin')"
"{window.open('/serverIndex')}"
"else"
"{alert('Error Password or Username')}"
"}"
"</script>" + style;
 
/* Server Index Page */
String serverIndex = 
"<script src='https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js'></script>"
"<form method='POST' action='#' enctype='multipart/form-data' id='upload_form'>"
"<input type='file' name='update' id='file' onchange='sub(this)' style=display:none>"
"<label id='file-input' for='file'>   Choose file...</label>"
"<input type='submit' class=btn value='Update'>"
"<br><br>"
"<div id='prg'></div>"
"<br><div id='prgbar'><div id='bar'></div></div><br></form>"
"<script>"
"function sub(obj){"
"var fileName = obj.value.split('\\\\');"
"document.getElementById('file-input').innerHTML = '   '+ fileName[fileName.length-1];"
"};"
"$('form').submit(function(e){"
"e.preventDefault();"
"var form = $('#upload_form')[0];"
"var data = new FormData(form);"
"$.ajax({"
"url: '/update',"
"type: 'POST',"
"data: data,"
"contentType: false,"
"processData:false,"
"xhr: function() {"
"var xhr = new window.XMLHttpRequest();"
"xhr.upload.addEventListener('progress', function(evt) {"
"if (evt.lengthComputable) {"
"var per = evt.loaded / evt.total;"
"$('#prg').html('progress: ' + Math.round(per*100) + '%');"
"$('#bar').css('width',Math.round(per*100) + '%');"
"}"
"}, false);"
"return xhr;"
"},"
"success:function(d, s) {"
"console.log('success!') "
"},"
"error: function (a, b, c) {"
"}"
"});"
"});"
"</script>" + style;

void home() {
  server.send(200, "text/html", fistpage);
}

void second() {
  server.send(200, "text/html", secondpage);
}

void third() {
  server.send(200, "text/html", thirdpage);
}


void UltrasonicD(){
  server.send(200, "text/plain", String(waterlevel));
}

void LDR() {
  server.send(200, "text/plain", String(LDR_Reading));
}

void Humidity() {
  server.send(200, "text/plain", String(h));
}

void Temp(){
  server.send(200, "text/plain", String(temp));
}

void LightN(){
  server.send(200, "text/plain", String(light_notif));
}
void WaterN(){
  server.send(200, "text/plain", String(water_notif));
}
void TempN(){
  server.send(200, "text/plain", String(temp_notif));
}

void printHumidity(){
  
  int index=0;
  int j=0;
  for(j=0; j<10;j++){
    hData+=String(EEPROM.read(index));
    hData+="</br>";
    index=index+2;
  }
  server.send(200, "text/plain", String(hData));
}

void printTemp(){
  String tData;
  int index=0;
  int j=0;
  for(j=0; j<10;j++){
    tData+=String(EEPROM.read(index));
    tData+="</br>";
    index=index+2;
  }
  server.send(200, "text/plain", String(tData));
}


void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void Start() {
  state = 1;
}

void Stop() {
  state = 0;
}
void Start2() {
  state2 = 1;
}

void Stop2() {
  state2 = 0;
}
void Start3() {
  state3 = 1;
}

void Stop3() {
  state3 = 0;
}

void Manual(){
  man = 1;
}

void Nonmanual(){
  man = 0;
}

void inputhandler() {
  String data = server.arg("data");
  Serial.println("Data received: " + data);

  // Split the data into individual values using a comma as delimiter
  String values[5];
  int index = 0;
  while (data.length() > 0) {
    int pos = data.indexOf(",");
    if (pos == -1) {
      values[index++] = data;
      break;
    }
    values[index++] = data.substring(0, pos);
    data = data.substring(pos + 1);
  }

  // Assign each value to a separate variable
   DBuploadFreqTemp = values[0].toInt();
   DBuploadFreqHumid = values[1].toInt();
   DBuploadFreqLDR = values[2].toInt();
   DBuploadFreqUltra = values[3].toInt();
 

}


void setColor(int R, int B, int G) {
  analogWrite(ledR,   R);
  
  analogWrite(ledB,  B);
  
  analogWrite(ledG, G);
}


void red100(){
  redlight=255;
  greenlight=0;
}

void red75(){
  redlight=190;
  greenlight=0;
}

void red50(){
  redlight=127;
  greenlight=0;
}

void red25(){
  redlight=63;
  greenlight=0;
}

void red0(){
  redlight=0;
  greenlight=0;
}

void blue100(){
  bluelight=255;
  greenlight=0;
}

void blue75(){
  bluelight=190;
  greenlight=0;
}

void blue50(){
  bluelight=127;
  greenlight=0;
}

void blue25(){
  bluelight=63;
  greenlight=0;
}

void blue0(){
  bluelight=0;
  greenlight=0;
}

void white100(){
  bluelight=255;
  redlight=255;
  greenlight=255;
}

void white75(){
  bluelight=190;
  redlight=190;
  greenlight=190;
}

void white50(){
  bluelight=127;
  redlight=127;
  greenlight=127;
}

void white25(){
  bluelight=63;
  redlight=63;
  greenlight=63;
}

void white0(){
  bluelight=0;
  redlight=0;
  greenlight=0;
}

void operation() {

  unsigned long HumidityCurrentTime = millis();
  if (HumidityCurrentTime - HumidityPreviousTime > HumidityTime) {
    HumidityPreviousTime = HumidityCurrentTime;
    h = dht.readHumidity();
    Serial.print(F("Humidity: "));
    Serial.println(h);
  }

  unsigned long TempCurrentTime = millis();
  if (TempCurrentTime - TempPreviousTime > TempTime) {
    TempPreviousTime = TempCurrentTime;
    temp = dht.readTemperature();
    Serial.print(F("Temperature: "));
    Serial.println(temp);
  }

  hVal[i]=waterlevel;
  EEPROM.write(address, hVal[i]);
  EEPROM.commit();
  i++;
  address = address+2;
  if(i>10){
    i=0;
  }
  if(address>20){
    address=0;
  }

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  if(man == 1){
    
  if (state == 0) {
    digitalWrite(relay, LOW);
  } else if (state == 1) {
    digitalWrite(relay, HIGH);
    
  }
  if (state2 == 0) {
    setColor(0,0,0); 
    fill_solid(leds, NUM_LEDS, CRGB(0,0,0));
    FastLED.show();
    
  } else if (state2 == 1) {
    setColor(redlight,bluelight,greenlight); 
    fill_solid(leds, NUM_LEDS, CRGB(redlight,greenlight,bluelight));
    FastLED.show();    
  }
  if (state3 == 0) {
    digitalWrite(relay_fan, LOW);
  } else if (state3 == 1) {
    digitalWrite(relay_fan, HIGH);
  }
  }
  duration = pulseIn(echoPin, HIGH);
  
  LDR_Reading = analogRead(LDR_PIN);

  // Calculate the distance
  distanceCm = duration * 0.034 / 2;
  waterlevel = distanceCm * CM_TO_INCH;
//  delay(1000);
  //    lcd.clear();
  Serial.print("Distance: ");
  Serial.println(waterlevel);
  float LDR_Voltage = ((float)LDR_Reading * 3.3 / 1023);
  Serial.print("Reading: ");
  Serial.print(hData);
  Serial.print("\t");
  Serial.print("Voltage: ");
  Serial.println(LDR_Voltage);
}


void setup(void) {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.clear();
  FastLED.show();
  pinMode(ledB, OUTPUT);
  pinMode(ledR, OUTPUT);
  wifiMulti.addAP(ssid, password);
  pinMode(trigPin, OUTPUT);  // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);   // Sets the echoPin as an Input
  pinMode(relay, OUTPUT);
  pinMode(relay_fan, OUTPUT);
  analogReadResolution(10);
  EEPROM.begin(EEPROM_SIZE);

  dht.begin();
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  // if(!WiFi.config(local_IP,gateway,subnet, primaryDNS, secondaryDNS)){
  //   Serial.println("STA Failed to configure");
  // }
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }

  server.on("/first", home);
  server.on("/second", second);
  server.on("/third", third);
  server.on("/LDR", LDR);
  server.on("/Ultrasonic", UltrasonicD);
  server.on("/Humidity", Humidity);
  server.on("/Temperature", Temp);
  server.on("/start", Start);
  server.on("/stop", Stop);
  server.on("/start2", Start2);
  server.on("/stop2", Stop2);
  server.on("/start3", Start3);
  server.on("/stop3", Stop3);
  server.on("/LightN", LightN);
  server.on("/WaterN", WaterN);
  server.on("/TempN", TempN);
  server.on("/true", Nonmanual);
  server.on("/false", Manual);
  server.on("/printHumidity", printHumidity);
  server.on("/printTemp", printTemp);
  server.on("/01", red0);
  server.on("/251", red25);
  server.on("/501", red50);
  server.on("/751", red75);
  server.on("/1001", red100);
  server.on("/02", blue0);
  server.on("/252", blue25);
  server.on("/502", blue50);
  server.on("/752", blue75);
  server.on("/1002", blue100);
  server.on("/03", white0);
  server.on("/253", white25);
  server.on("/503", white50);
  server.on("/753", white75);
  server.on("/1003", white100);
  server.on("/handle_input.php", HTTP_POST, inputhandler);
  // server.on("/update", []() {
  //   server.send(200, "text/plain", "this works as well");
  // });


    server.on("/loginIndex", HTTP_GET, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/html", loginIndex);
  });
  server.on("/serverIndex", HTTP_GET, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/html", serverIndex);
  });
  /*handling uploading firmware file */
  server.on("/update", HTTP_POST, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
    ESP.restart();
  }, []() {
    HTTPUpload& upload = server.upload();
    if (upload.status == UPLOAD_FILE_START) {
      Serial.printf("Update: %s\n", upload.filename.c_str());
      if (!Update.begin(UPDATE_SIZE_UNKNOWN)) { //start with max available size
        Update.printError(Serial);
      }
    } else if (upload.status == UPLOAD_FILE_WRITE) {
      /* flashing firmware to ESP*/
      if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
        Update.printError(Serial);
      }
    } else if (upload.status == UPLOAD_FILE_END) {
      if (Update.end(true)) { //true to set the size to the current progress
        Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
      } else {
        Update.printError(Serial);
      }
    }
  });
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) { 
  server.handleClient();
  delay(2);  //allow the cpu to switch to other tasks
  operation();
    if(man == 0){
    digitalWrite(relay, HIGH);  
    if (LDR_Reading < 200) {
       setColor(redlight,bluelight,greenlight); // Turn the relay on (HIGH is the voltage level = 1)
       light_notif = 1;
       fill_solid(leds, NUM_LEDS, CRGB(redlight,greenlight,bluelight));
       FastLED.show();
      // for (int i = 0; i <= 60; i++) {
      //   leds[i] = CRGB(redlight,bluelight,greenlight);
      //   FastLED.show();
      //   delay(50); 
      // }
    }
    else {
        light_notif = 0;
        setColor(0,0,0);   // Turn the relay off by making the voltage LOW = 0
        fill_solid(leds, NUM_LEDS, CRGB(0,0,0));
        FastLED.show();
       // delay(1000);
      //   for (int i = 0; i <= 60; i++) {
      //   leds[i] = CRGB(0,0,0);
      //   FastLED.show();
      //   delay(50); 
      // }
    }

    if (waterlevel > 100){
      
      water_notif = 1;
    }
    else{
      water_notif = 0;
      
    }
    if (temp > 32){
      temp_notif = 1;
      digitalWrite(relay_fan, HIGH); 

    }
    else{
      temp_notif = 0;
      digitalWrite(relay_fan, LOW); 
    }
    
    }

  if ((wifiMulti.run() == WL_CONNECTED)) {

    HTTPClient http;
    unsigned long DBcurrentTime = millis();

    if (DBcurrentTime - DBpreviousTime > DBuploadFreq) {
      DBpreviousTime = DBcurrentTime;
      toDB();

    }
    if (DBcurrentTime - DBpreviousTime1 > DBuploadFreqUltra) {
      DBpreviousTime1 = DBcurrentTime;
      UltratoDB();

    }
    if (DBcurrentTime - DBpreviousTime2 > DBuploadFreqLDR) {
      DBpreviousTime2 = DBcurrentTime;
      LDRtoDB();

    }
    if (DBcurrentTime - DBpreviousTime3 > DBuploadFreqTemp) {
      DBpreviousTime3 = DBcurrentTime;
      TemptoDB();

    }
    if (DBcurrentTime - DBpreviousTime4 > DBuploadFreqHumid) {
      DBpreviousTime4 = DBcurrentTime;
      HumidtoDB();

    }

    USE_SERIAL.print("[HTTP] begin...\n");
    // configure traged server and url
    //http.begin("https://www.howsmyssl.com/a/check", ca); //HTTPS


    USE_SERIAL.print("[HTTP] GET...\n");
    // start connection and send HTTP header
    int httpCode = http.GET();

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        USE_SERIAL.println(payload);
      }
    } else {
      USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  }
}

void toDB() {
  HTTPClient http;
  Serial.println(" ");
  Serial.println("Uploading to DB");
  
  http.begin("http://192.168.86.39/IOT/retrieve.php?LDR=" + String(LDR_Reading) + "&Ultrasonic=" + String(waterlevel) + "&Humidity=" + String(h) + "&Temperature=" + String(temp));
  int httpCode = http.GET();
  String result = http.getString();
  Serial.println(result);
}

void TemptoDB() {
  HTTPClient http;
  Serial.println(" ");
  Serial.println("Uploading to DB");
  
  http.begin("http://192.168.86.39/Capstone/retrieve.php?Sensor_Value=" + String(temp) + "&Sensor_ID=1");
  int httpCode = http.GET();
  String result = http.getString();
  Serial.println(result);
}

void HumidtoDB() {
  HTTPClient http;
  Serial.println(" ");
  Serial.println("Uploading to DB");
  
  http.begin("http://192.168.86.39/Capstone/retrieve.php?Sensor_Value=" + String(h) + "&Sensor_ID=2");
  int httpCode = http.GET();
  String result = http.getString();
  Serial.println(result);
}

void LDRtoDB() {
  HTTPClient http;
  Serial.println(" ");
  Serial.println("Uploading to DB");
  
  http.begin("http://192.168.86.39/Capstone/retrieve.php?Sensor_Value=" + String(LDR_Reading) + "&Sensor_ID=3");
  int httpCode = http.GET();
  String result = http.getString();
  Serial.println(result);
}

void UltratoDB() {
  HTTPClient http;
  Serial.println(" ");
  Serial.println("Uploading to DB");
  
  http.begin("http://192.168.86.39/Capstone/retrieve.php?Sensor_Value=" + String(waterlevel) + "&Sensor_ID=4");
  int httpCode = http.GET();
  String result = http.getString();
  Serial.println(result);
}