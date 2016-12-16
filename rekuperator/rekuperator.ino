
int sensorPin = A0; // select the input pin for the potentiometer
int fan1PWMPin = 3;  // EBM fan IN
int fan2PWMPin = 11;  // EBM fan OUT
int fan1IntPin = 2;
int fan2IntPin = 7;
int OneWirePin = 5;
int humiditySensorPin = 4;


void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  
  pinMode(sensorPin,INPUT);
  pinMode(fan1PWMPin,OUTPUT); //scale of 0 - 255
  pinMode(fan2PWMPin,OUTPUT); //scale of 0 - 255 
  
  //attachInterrupt(digitalPinToInterrupt(pin), ISR, RISING);

}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorValue = analogRead(sensorPin)/4; //scale of 0 - 255
  int sensorValuePercent = sensorValue/255*100;
  analogWrite(fan1PWMPin, sensorValue);
  analogWrite(fan2PWMPin, sensorValue);
  // print out the sensorValue:
  Serial.println(sensorValue + "Percent: " + sensorValuePercent);
  delay(1);        // delay in between reads for stability
}
