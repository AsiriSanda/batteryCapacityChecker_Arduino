#define gatePin 10
#define highPin A0
#define lowPin A1

boolean finished = false;
int printStart = 0;
int interval = 5000; 

float mAh = 0.0;
float shuntRes = 0.15; // Shunt resistor resistance
float voltRef = 4.71; // Reference voltage
float current = 0.0;
float battVolt = 0.0;
float shuntVolt = 0.0;
float battLow = 2.9;

unsigned long previousMillis = 0;
unsigned long millisPassed = 0;

void setup() {
Serial.begin(9600);
Serial.println("Battery Capacity Checker v1.1");
Serial.println("battVolt current mAh");

pinMode(gatePin, OUTPUT);
digitalWrite(gatePin, LOW);

}

void loop() {
  
battVolt = analogRead(highPin) * voltRef / 1024.0;
shuntVolt = analogRead(lowPin) * voltRef / 1024.0;

if(battVolt >= battLow && finished == false)
{
digitalWrite(gatePin, HIGH);
millisPassed = millis() - previousMillis;
current = (battVolt - shuntVolt) / shuntRes;
mAh = mAh + (current * 1000.0) * (millisPassed / 3600000.0);
previousMillis = millis();

Serial.print(battVolt);
Serial.print("\t");
Serial.print(current);
Serial.print("\t");
Serial.println(mAh);

delay(interval);
}
if(battVolt < battLow)
{
digitalWrite(gatePin, LOW);

finished = true;

if(mAh < 10) {
printStart = 40;
}
else if(mAh < 100) {
printStart = 30;
}
else if(mAh <1000) {
printStart = 24;
}
else if(mAh <10000) {
printStart = 14;
}
else {
printStart = 0;

}

delay(interval * 2);
}

}
