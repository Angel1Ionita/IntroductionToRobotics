const int readRedPin = A1;
const int readGreenPin = A2;
const int readBluePin = A3;

const int ledRedPin = 9;
const int ledGreenPin = 10;
const int ledBluePin = 11;

const int minAnalogRead = 0;
const int maxAnalogRead = 1023;

const int minAnalogWrite = 0;
const int maxAnalogWrite = 255;


void setup() {
  pinMode(readRedPin, INPUT);
  pinMode(readGreenPin, INPUT);  
  pinMode(readBluePin, INPUT); 

  pinMode(ledRedPin, OUTPUT);
  pinMode(ledGreenPin, OUTPUT);
  pinMode(ledBluePin, OUTPUT);
}

void updateColor(int readPin, int ledPin) {
  int readValue = analogRead(readPin);
  int ledValue = map(readValue, minAnalogRead, maxAnalogRead, minAnalogWrite, maxAnalogWrite); 
  analogWrite(ledPin, ledValue);
}

void loop() {
  updateColor(readRedPin, ledRedPin);
  updateColor(readGreenPin, ledGreenPin);
  updateColor(readBluePin, ledBluePin);
}