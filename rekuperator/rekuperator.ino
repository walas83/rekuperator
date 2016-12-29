const int ledPin =  13;      // the number of the LED pin

int sensorPin = A0; // select the input pin for the potentiometer
int fan1PWMPin = 3;  // EBM fan IN
int fan2PWMPin = 11;  // EBM fan OUT
int fan1IntPin = 2;
int fan2IntPin = 7;
int OneWirePin = 5;
int humiditySensorPin = 4;

volatile byte fan1;
unsigned int fan1RPM;
unsigned long fan1TimeOld;


void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  
  pinMode(sensorPin,INPUT);
  pinMode(fan1PWMPin,OUTPUT); //scale of 0 - 255
  pinMode(fan2PWMPin,OUTPUT); //scale of 0 - 255 
  
  attachInterrupt(digitalPinToInterrupt(fan1IntPin), fan1_func, FALLING);
  fan1 = 0;
  fan1RPM = 0;
  fan1TimeOld = 0;
}

void loop() {
  delay(1000);
  //Don't process interrupts during calculations
  detachInterrupt(0);
  // put your main code here, to run repeatedly:
  int sensorValue = analogRead(sensorPin)/4; //scale of 0 - 255
  int sensorValuePercent = (int) sensorValue/255.00*100.00;
  analogWrite(fan1PWMPin, sensorValue);
  analogWrite(fan2PWMPin, sensorValue);
  // print out the sensorValue:
  //Serial.print(sensorValue);
  //Serial.print("  ");
  //Serial.println(sensorValuePercent);


  //Update RPM every 20 counts, increase this for better RPM resolution,
  //decrease for faster update
  fan1RPM = 60*1000/(millis() - fan1TimeOld)*fan1;
  Serial.println(fan1);
  Serial.println(millis()-fan1TimeOld);
  fan1TimeOld = millis();
  fan1 = 0;
  
  attachInterrupt(digitalPinToInterrupt(fan1IntPin), fan1_func, FALLING);   
}

void fan1_func() {
  fan1++;
  digitalWrite(ledPin, HIGH);
  digitalWrite(ledPin, LOW);
}
