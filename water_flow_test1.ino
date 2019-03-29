#include <ESP8266WiFi.h>  
#include <WiFiClient.h> 

void pulseCounter1(void);
void pulseCounter2(void);
void pulseCounter3(void);
void pulseCounter4(void);
void CONNECT_TO_WIFI(void);
void WEB_PAGE(void);
void DATA_TO_CLOUD(void);
void READ_SENSOR(void);

WiFiClient client; 
WiFiClient localclient; 

const char* ssid = "SRI_Device";  
const char* password = "Welcome12#";  
unsigned long myChannelNumber = 720210;  
String myWriteAPIKey = "8AC9AK250X9W8P7R";  
const char * myReadAPIKey  = "AMKDM81DYZBJ8CX8";
const char* SERVER = "api.thingspeak.com";

bool SendData = false;
bool ReadSensor = false;

const int FlowSensor1 = D2;// variable for D2 pin
const int FlowSensor2 =D3;
const int FlowSensor3 =D4;
const int FlowSensor4 =D5;
float calibrationFactor = 13; 
volatile byte pulseCount1 = 0;
volatile byte pulseCount2 = 0;
volatile byte pulseCount3 = 0;
volatile byte pulseCount4 = 0;
float flowRate1=0;
float flowRate2=0;
float flowRate3=0;
float flowRate4=0;
float flowMilliLitres1= 0;
float flowMilliLitres2= 0;
float flowMilliLitres3= 0;
float flowMilliLitres4= 0;
unsigned long totalMilliLitres1=0;
unsigned long totalMilliLitres2=0;
unsigned long totalMilliLitres3=0;
unsigned long totalMilliLitres4=0;
unsigned long oldTime = 0;
byte sensorInterrupt1 = 0; // 0 digital pin 2
byte sensorInterrupt2 = 0;
byte sensorInterrupt3 = 0;
byte sensorInterrupt4 = 0;
unsigned long previousMillis_1 = 0;     
const long interval_1 = 2000;           

unsigned long previousMillis_2 = 0;        
const long interval_2 = 15000;    
    

WiFiServer server(80);

void setup() {
  Serial.begin(115200); 
  delay(10);
  server.begin();
  CONNECT_TO_WIFI(); // Connect to WiFi network
  pinMode(FlowSensor1, INPUT);
  pinMode(FlowSensor2, INPUT);
  pinMode(FlowSensor3, INPUT);
  pinMode(FlowSensor4, INPUT);
  digitalWrite(FlowSensor1, HIGH);
  digitalWrite(FlowSensor2, HIGH);
  digitalWrite(FlowSensor3, HIGH);
  digitalWrite(FlowSensor4, HIGH);
  attachInterrupt(digitalPinToInterrupt(FlowSensor1), pulseCounter1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(FlowSensor2), pulseCounter2, CHANGE);
  attachInterrupt(digitalPinToInterrupt(FlowSensor3), pulseCounter3, CHANGE);
  attachInterrupt(digitalPinToInterrupt(FlowSensor4), pulseCounter4, CHANGE);
} // void setup ends here

void loop() {

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
  
  READ_SENSOR();   
  if(SendData){
    SendData = 0;
    DATA_TO_CLOUD();
   
  }
 attachInterrupt(digitalPinToInterrupt(FlowSensor1), pulseCounter1, CHANGE);
 attachInterrupt(digitalPinToInterrupt(FlowSensor2), pulseCounter2, CHANGE);
 attachInterrupt(digitalPinToInterrupt(FlowSensor3), pulseCounter3, CHANGE);
  attachInterrupt(digitalPinToInterrupt(FlowSensor4), pulseCounter41, CHANGE);
} // void loop ends here

void PrintValues(void){
//  Serial.print("  Current Liquid Flowing: "); // Output separator
//  Serial.print(flowMilliLitres);
//  Serial.println("mL/Sec");

  Serial.print(" Total liquid used: "); // Output separator
  Serial.print(totalMilliLitres1);
  Serial.println("mL");
  Serial.print(totalMilliLitres2);
  Serial.println("mL");
  Serial.print(totalMilliLitres3);
  Serial.println("mL");
  Serial.print(totalMilliLitres41);
  Serial.println("mL");
}

void pulseCounter1(void) {
    pulseCount1++;     // Increment the pulse counter
void pulseCounter2(void) {
    pulseCount2++;    
void pulseCounter3(void) {
    pulseCount3++;    
void pulseCounter4(void) {
    pulseCount4++;    
    
}

void READ_SENSOR(void){
  
  flowRate1 = 0;
  flowRate2 = 0;
  flowRate3 = 0;
  flowRate4 = 0;
  flowMilliLitres1 = 0;
  flowMilliLitres2 = 0;
  flowMilliLitres3 = 0;
  flowMilliLitres4 = 0;

  if ((millis() - oldTime) > 1000) {
    detachInterrupt(sensorInterrupt1);
    detachInterrupt(sensorInterrupt2);
    detachInterrupt(sensorInterrupt3);
    detachInterrupt(sensorInterrupt4);
    flowRate1 = ((1000.0 / (millis() - oldTime)) * pulseCount1) / calibrationFactor;
    pulseCount1 = 0;
    flowRate2 = ((1000.0 / (millis() - oldTime)) * pulseCount2) / calibrationFactor;
    pulseCount2 = 0;
    flowRate3= ((1000.0 / (millis() - oldTime)) * pulseCount3) / calibrationFactor;
    pulseCount3 = 0;
    flowRate4= ((1000.0 / (millis() - oldTime)) * pulseCount4) / calibrationFactor;
    pulseCount4= 0;
    oldTime = millis(); 
    flowMilliLitres1 = (flowRate1 / 60) * 1000;
    flowMilliLitres2 = (flowRate2 / 60) * 1000;
    flowMilliLitres3 = (flowRate3 / 60) * 1000;
    flowMilliLitres4 = (flowRate4 / 60) * 1000;
    Serial.print(flowMilliLitres1);
    Serial.println("mL/Sec");
    Serial.print(flowMilliLitres2);
    Serial.println("mL/Sec");
    Serial.print(flowMilliLitres3);
    Serial.println("mL/Sec");
    Serial.print(flowMilliLitres4);
    Serial.println("mL/Sec");
totalMilliLitres1 += flowMilliLitres1;
    totalMilliLitres2 += flowMilliLitres2;
    totalMilliLitres3 += flowMilliLitres3;
    totalMilliLitres4 += flowMilliLitres4;
    unsigned int frac = 0;
    
//    Serial.print("Flow rate: ");
//    Serial.print(int(flowRate)); 
//    Serial.print("."); // Print the decimal point
//    
    frac = (flowRate - int(flowRate)) * 10;
//    Serial.print(frac, DEC);
//    Serial.print("L/min");
//    
//    Serial.print("  Current Liquid Flowing: "); // Output separator
//    Serial.print(flowMilliLitres);
//    Serial.print("mL/Sec");
//    
//    Serial.print("  Output Liquid Quantity: "); // Output separator
//    Serial.print(totalMilliLitres);
//    Serial.println("mL");
    sensorInterrupt = 0;
 }
}

void DATA_TO_CLOUD(void) {
  WiFiClient client; 
  if (client.connect(SERVER,80)){   //   "184.106.153.149" or api.thingspeak.com
    String postStr = myWriteAPIKey;
    postStr +="&field1=";
    postStr += String(flowMilliLitres);
    postStr +="&field2=";
    postStr += String(totalMilliLitres);
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
  localclient.println("body {background-color: #e5ad29;}"); 
   localclient.println("font color=\"red| #00FF00|rgb(255,0,0)\"");
  localclient.println("</style>");
  localclient.print("<h1><b>VOLUME OF WATER FLOWING </b></h1>");
  localclient.println("<br><br><br>");
  localclient.print("<h3>VOLUME :</h3>");
  localclient.print(totalMilliLitres);
  localclient.println("ml");
  localclient.println("<h3>FLOW RATE :</h3>");
  localclient.print(flowRate);
  localclient.println("L/min");
  localclient.println("</html>");
}
