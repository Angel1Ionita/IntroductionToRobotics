const int potRedPin = A1;
const int potGreenPin = A2;
const int potBluePin = A3;

const int ledRedPin = 9;
const int ledGreenPin = 10;
const int ledBluePin = 11;

void setup() {
  pinMode(potRedPin, INPUT);
  pinMode(potGreenPin, INPUT);  
  pinMode(potBluePin, INPUT); 

  pinMode(ledRedPin, OUTPUT);
  pinMode(ledGreenPin, OUTPUT);
  pinMode(ledBluePin, OUTPUT);
}

void updateColor(int potPin, int ledPin) {
  int potValue = analogRead(potPin);
  int mappedPotValue = map(potValue, 0, 1023, 0, 255); 
  analogWrite(ledPin, mappedPotValue);
}

void loop() {
  updateColor(potRedPin, ledRedPin);
  updateColor(potGreenPin, ledGreenPin);
  updateColor(potBluePin, ledBluePin);
}