#include <ESP8266WiFi.h>  
#include <WiFiClient.h>

void pulseCounter(void);
void READ_SENSORS(void);
void CheckLeakage(void);

void CONNECT_TO_WIFI(void);
void WEB_PAGE(void);
void DATA_TO_CLOUD(void);

const char* ssid = "SRI_Device";  
const char* password = "Welcome12#";  
unsigned long myChannelNumber = 720210;  
String myWriteAPIKey = "8AC9AK250X9W8P7R";  
const char * myReadAPIKey  = "AMKDM81DYZBJ8CX8";
const char* SERVER = "api.thingspeak.com";

bool SendData = false;
bool ReadSensor = false;
bool leak_1_flag = false;
bool leak_2_flag = false;

const int FlowSensor_1 = D7; // variable for D0 pin
const int FlowSensor_2 = D3; // variable for D1 pin

const int FlowSensor_3 = D5; // variable for D2 pin
const int FlowSensor_4 = D1; // variable for D4 pin

float calibrationFactor = 13; 

volatile byte pulseCount_1 = 0;
volatile byte pulseCount_2 = 0;
volatile byte pulseCount_3 = 0;
volatile byte pulseCount_4 = 0;

float flowRate_1 = 0;
float flowRate_2 = 0;
float flowRate_3 = 0;
float flowRate_4 = 0;

float flowMilliLitres_1 = 0;
float flowMilliLitres_2 = 0;
float flowMilliLitres_3 = 0;
float flowMilliLitres_4 = 0;

unsigned long totalMilliLitres_1 = 0;
unsigned long totalMilliLitres_2 = 0;
unsigned long totalMilliLitres_3 = 0;
unsigned long totalMilliLitres_4 = 0;

unsigned long oldTime_1 = 0;
unsigned long oldTime_2 = 0;
unsigned long oldTime_3 = 0;
unsigned long oldTime_4 = 0;

byte sensorInterrupt_1 = 0; // 0 digital pin 2
byte sensorInterrupt_2 = 0; // 0 digital pin 2
byte sensorInterrupt_3 = 0; // 0 digital pin 2
byte sensorInterrupt_4 = 0; // 0 digital pin 2

unsigned long previousMillis_1 = 0;     
const long interval_1 = 2000;           

unsigned long previousMillis_2 = 0;        
const long interval_2 = 15000;

WiFiServer server(80);
WiFiClient client; 
WiFiClient localclient; 

void setup() {
  Serial.begin(115200); 
  delay(10);
  
  pinMode(FlowSensor_1, INPUT);
  digitalWrite(FlowSensor_1, HIGH);
  pinMode(FlowSensor_2, INPUT);
  digitalWrite(FlowSensor_2, HIGH);
  pinMode(FlowSensor_3, INPUT);
  digitalWrite(FlowSensor_3, HIGH);
  pinMode(FlowSensor_4, INPUT);
  digitalWrite(FlowSensor_4, HIGH);
  
  attachInterrupt(digitalPinToInterrupt(FlowSensor_1), pulseCounter_1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(FlowSensor_2), pulseCounter_2, CHANGE);
  attachInterrupt(digitalPinToInterrupt(FlowSensor_3), pulseCounter_3, CHANGE);
  attachInterrupt(digitalPinToInterrupt(FlowSensor_4), pulseCounter_4, CHANGE);
  
} // void setup ends here

void loop() {

  READ_SENSORS();
  CheckLeakage();   

  unsigned long currentMillis_1 = millis();
  if(currentMillis_1 - previousMillis_1 >= interval_1) {
    previousMillis_1 = currentMillis_1;
    PrintValues();
  }
  unsigned long currentMillis_2 = millis();
  if(currentMillis_2 - previousMillis_2 >= interval_2) {
    previousMillis_2 = currentMillis_2;
    SendData = true;
    WEB_PAGE();
  }
  if(SendData){
    SendData = 0;
    DATA_TO_CLOUD();
   
  }
     
 attachInterrupt(digitalPinToInterrupt(FlowSensor_1), pulseCounter_1, CHANGE);
 attachInterrupt(digitalPinToInterrupt(FlowSensor_2), pulseCounter_2, CHANGE);
 attachInterrupt(digitalPinToInterrupt(FlowSensor_3), pulseCounter_3, CHANGE);
 attachInterrupt(digitalPinToInterrupt(FlowSensor_4), pulseCounter_4, CHANGE);
} // void loop ends here

void PrintValues(void){
  Serial.print(" Total liquid used From 1: "); // Output separator
  Serial.print(totalMilliLitres_1);
  Serial.println("mL");
  Serial.print(" Total liquid used From 2: "); // Output separator
  Serial.print(totalMilliLitres_2);
  Serial.println("mL");
  Serial.print(" Total liquid used From 3: "); // Output separator
  Serial.print(totalMilliLitres_3);
  Serial.println("mL");
  Serial.print(" Total liquid used From 4: "); // Output separator
  Serial.print(totalMilliLitres_4);
  Serial.println("mL");
}

void pulseCounter_1(void) {
    pulseCount_1++;     // Increment the pulse counter
}
void pulseCounter_2(void) {
    pulseCount_2++;     // Increment the pulse counter
}
void pulseCounter_3(void) {
    pulseCount_3++;     // Increment the pulse counter
}
void pulseCounter_4(void) {
    pulseCount_4++;     // Increment the pulse counter
}

void READ_SENSORS(void){
  
/*-------------------------------- Sensor 1 -----------------------------------------*/
  flowRate_1 = 0;
  flowMilliLitres_1 = 0;
  if ((millis() - oldTime_1) > 1000) {
    detachInterrupt(sensorInterrupt_1);
    flowRate_1 = ((1000.0 / (millis() - oldTime_1)) * pulseCount_1) / calibrationFactor;
    pulseCount_1 = 0;
    oldTime_1 = millis(); 
    flowMilliLitres_1 = (flowRate_1 / 60) * 1000;
    Serial.print("flowMilliLitres_1: ");
    Serial.print(flowMilliLitres_1);
    Serial.println("mL/Sec");
    totalMilliLitres_1 += flowMilliLitres_1;
    unsigned int frac_1 = 0;    
    frac_1 = (flowRate_1 - int(flowRate_1)) * 10;
    sensorInterrupt_1 = 0;
 }
/*-------------------------------- Sensor 1 -----------------------------------------*/ 

/*-------------------------------- Sensor 2 -----------------------------------------*/
  flowRate_2 = 0;
  flowMilliLitres_2 = 0;
  if ((millis() - oldTime_2) > 1000) {
    detachInterrupt(sensorInterrupt_2);
    flowRate_2 = ((1000.0 / (millis() - oldTime_2)) * pulseCount_2) / calibrationFactor;
    pulseCount_2 = 0;
    oldTime_2 = millis(); 
    flowMilliLitres_2 = (flowRate_2 / 60) * 1000;
    Serial.print("flowMilliLitres_2: ");
    Serial.print(flowMilliLitres_2);
    Serial.println("mL/Sec");
    totalMilliLitres_2 += flowMilliLitres_2;
    unsigned int frac_2 = 0;    
    frac_2 = (flowRate_2 - int(flowRate_2)) * 10;
    sensorInterrupt_2 = 0;
 }
/*-------------------------------- Sensor 2 -----------------------------------------*/ 

/*-------------------------------- Sensor 3 -----------------------------------------*/
  flowRate_3 = 0;
  flowMilliLitres_3 = 0;
  if ((millis() - oldTime_3) > 1000) {
    detachInterrupt(sensorInterrupt_3);
    flowRate_3 = ((1000.0 / (millis() - oldTime_3)) * pulseCount_3) / calibrationFactor;
    pulseCount_3 = 0;
    oldTime_3 = millis(); 
    flowMilliLitres_3 = (flowRate_3 / 60) * 1000;
    Serial.print("flowMilliLitres_3: ");
    Serial.print(flowMilliLitres_3);
    Serial.println("mL/Sec");
    totalMilliLitres_3 += flowMilliLitres_3;
    unsigned int frac_3 = 0;    
    frac_3 = (flowRate_3 - int(flowRate_3)) * 10;
    sensorInterrupt_3 = 0;
 }
/*-------------------------------- Sensor 3 -----------------------------------------*/ 

/*-------------------------------- Sensor 4 -----------------------------------------*/
  flowRate_4 = 0;
  flowMilliLitres_4 = 0;
  if ((millis() - oldTime_4) > 1000) {
    detachInterrupt(sensorInterrupt_4);
    flowRate_4 = ((1000.0 / (millis() - oldTime_4)) * pulseCount_4) / calibrationFactor;
    pulseCount_4 = 0;
    oldTime_4 = millis(); 
    flowMilliLitres_4 = (flowRate_4 / 60) * 1000;
    Serial.print("flowMilliLitres_4: ");
    Serial.print(flowMilliLitres_4);
    Serial.println("mL/Sec");
    totalMilliLitres_4 += flowMilliLitres_4;
    unsigned int frac_4 = 0;    
    frac_4 = (flowRate_4 - int(flowRate_4)) * 10;
    sensorInterrupt_4 = 0;
 }
/*-------------------------------- Sensor 4 -----------------------------------------*/ 
 
} // void READ_SENSORS ends here

void CheckLeakage(void){
  unsigned int leakage_1 = totalMilliLitres_1 - totalMilliLitres_2;
  if(leakage_1 > 10){
    leak_1_flag = true;
    leak_1_flag = 1;
    Serial.println("Leakage in Pipe 1");
  }
  else{
    leak_1_flag = false;
    leak_1_flag = 0;
  }
  unsigned int leakage_2 = totalMilliLitres_3 - totalMilliLitres_4;
  if(leakage_1 > 10){
    leak_2_flag = true;
    leak_2_flag = 1;
    Serial.println("Leakage in Pipe 2");
  }
  else{
    leak_2_flag = false;
    leak_2_flag = 0;
  }
}

void DATA_TO_CLOUD(void) {
  WiFiClient client; 
  if (client.connect(SERVER,80)){   //   "184.106.153.149" or api.thingspeak.com
    String postStr = myWriteAPIKey;
    postStr +="&field1=";
    postStr += String(totalMilliLitres_1);
    postStr +="&field2=";
    postStr += String(totalMilliLitres_2);
    postStr +="&field3=";
    postStr += String(totalMilliLitres_3);
    postStr +="&field4=";
    postStr += String(totalMilliLitres_4);
    postStr +="&field5=";
    postStr += String(leak_1_flag);
    postStr +="&field6=";
    postStr += String(leak_2_flag);
    postStr += "\r\n\r\n";
  
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: "+myWriteAPIKey+"\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);
  }
  client.stop();
  Serial.println("Waiting...");
  Serial.println();  
}


void CONNECT_TO_WIFI(void){
  Serial.begin(115200);
  delay(10);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password); 
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println(WiFi.localIP());
  delay(10000);
}

void WEB_PAGE(void){
  localclient = server.available();
  if (!localclient) {
    return;
  }
  
  String request = localclient.readStringUntil('\n');
  Serial.println(request);
  localclient.flush();
   
  localclient.println("HTTP/1.1 200 OK"); 
  localclient.println("Content-Type: text/html");
  localclient.println("");
  localclient.println("<!DOCTYPE HTML>");
  localclient.println("<head>");
  localclient.println("<meta http-equiv=\"refresh\" content=\"5\" >");
  localclient.println("</head>"); 
  localclient.println("<style>");
  localclient.println("body {background-color: #8baee8;}"); 
  localclient.println("</style>");
  localclient.print("<h1><b>VOLUME OF WATER FLOWING </b></h1>");
  localclient.println("<br><br><br>");
  localclient.print("<h3>VOLUME 1:</h3>");
  localclient.print(totalMilliLitres_1);
  localclient.println("ml");
  localclient.print("<h3>VOLUME 2:</h3>");
  localclient.print(totalMilliLitres_2);
  localclient.println("ml");
  localclient.print("<h3>VOLUME 3:</h3>");
  localclient.print(totalMilliLitres_3);
  localclient.println("ml");
  localclient.print("<h3>VOLUME 4:</h3>");
  localclient.print(totalMilliLitres_4);
  localclient.println("ml");
  
  localclient.println("</html>");
}
