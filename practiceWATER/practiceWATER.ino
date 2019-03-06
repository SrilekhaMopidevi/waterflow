#include <ESP8266WiFi.h> 

void pulseCounter();
const int buttonPin = D2; // variable for D2 pin
byte sensorInterrupt = 0; // 0 digital pin 2
float calibrationFactor = 4.5; 
volatile byte pulseCount;
float flowRate;
unsigned int flowMilliLitres;
unsigned long totalMilliLitres;
unsigned long oldTime;
void setup() {
    Serial.begin(115200); 
    delay(10);
    Serial.println('\n');
    pinMode(buttonPin, INPUT);
    pulseCount = 0;
    flowRate = 0.0;
    flowMilliLitres = 0;
    totalMilliLitres = 0;
    oldTime = 0;
    digitalWrite(buttonPin, HIGH);
    //attachInterrupt(digitalPinToInterrupt(buttonPin), pulseCounter, CHANGE);
}


void loop() {
  attachInterrupt(digitalPinToInterrupt(buttonPin), pulseCounter, CHANGE);
    //pulseCount = 0;
    flowRate = 0.0;
    flowMilliLitres = 0;
    //totalMilliLitres = 0;
    //oldTime = 0;
       if ((millis() - oldTime) > 1000) {
        detachInterrupt(sensorInterrupt);
        flowRate = ((1000.0 / (millis() - oldTime)) * pulseCount) / calibrationFactor;
        oldTime = millis(); 
        flowMilliLitres = (flowRate / 60) * 1000;
        totalMilliLitres += flowMilliLitres;
        unsigned int frac;

        
        Serial.print("Flow rate: ");
        Serial.print(int(flowRate)); 
        Serial.print("."); // Print the decimal point
       
        frac = (flowRate - int(flowRate)) * 10;
        Serial.print(frac, DEC);
        Serial.print("L/min");
        
        Serial.print("  Current Liquid Flowing: "); // Output separator
        Serial.print(flowMilliLitres);
        Serial.print("mL/Sec");

        
        Serial.print("  Output Liquid Quantity: "); // Output separator
        Serial.print(totalMilliLitres);
        Serial.println("mL");
       }
delay (1000);

}
void pulseCounter() {
    // Increment the pulse counter
    pulseCount++;
}
