// joystick pins
const int pinSW = 2;
const int pinX = A0;
const int pinY = A1;

// shift register pins
const int latchPin = 11;  
const int clockPin = 10;  
const int dataPin = 12;   

// 4 digit 7 segment display pins
const int segD1 = 7;
const int segD2 = 6;
const int segD3 = 5;
const int segD4 = 4;

const int minThreshold = 400;
const int maxThreshold = 600;
const int resetPressDuration = 3000;

const int refreshRate = 5;

const int displayCount = 4;
const int displayDigits[] = {
  segD4, segD3, segD2, segD1
};

const int encodingsNumber = 16;
const int byteEncodings[encodingsNumber] = {
  //A B C D E F G DP
  B11111101,  // 0
  B01100001,  // 1
  B11011011,  // 2
  B11110011,  // 3
  B01100111,  // 4
  B10110111,  // 5
  B10111111,  // 6
  B11100001,  // 7
  B11111111,  // 8
  B11110111,  // 9
  B11101111,  // A
  B00111111,  // b
  B10011101,  // C
  B01111011,  // d
  B10011111,  // E
  B10001111   // F
};


unsigned long currentMillis;
unsigned long previousMillis = 0;
unsigned long previousMillis1 = 0;
unsigned long previousMillis2 = 0;
unsigned long lastPressedMillis;

int xValue;
int yValue;
byte swState;
byte lastSwState;

int joyMovedX;
int joyMovedY;

int savedDigits[4] = { 0, 0, 0, 0 };
int currentPos = 3;
byte dpState = 0;
int k = 0;

bool editMode = 0;

// Write to register
void writeReg(int encoding) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, encoding);
  digitalWrite(latchPin, HIGH);
}

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  for (int i = 0; i < displayCount; i++) {
    pinMode(displayDigits[i], OUTPUT);
  }

  pinMode(pinSW, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {
  xValue = analogRead(pinX);
  yValue = analogRead(pinY);
  swState = digitalRead(pinSW);

  currentMillis = millis();

  if (editMode) {
    if (currentMillis - previousMillis1 >= refreshRate) {
      previousMillis1 = currentMillis;
      for (int i = 0; i < displayCount; i++) {
        digitalWrite(displayDigits[i], HIGH);
      }
      digitalWrite(displayDigits[k], LOW);
      writeReg(byteEncodings[savedDigits[k]]);
      k++;
      Serial.println(k);
      if (k >= 4)
        k = 0;
    }

    // Vertical movement check
    if (xValue < minThreshold && joyMovedX == false) {
      joyMovedX = true;
      --savedDigits[currentPos];
    }
    if (xValue > maxThreshold && joyMovedX == false) {
      joyMovedX = true;
      ++savedDigits[currentPos];
    }
    if (xValue > minThreshold && xValue < maxThreshold) {
      joyMovedX = false;
    }

    if (savedDigits[currentPos] == -1)
      savedDigits[currentPos] = encodingsNumber-1;
    else if (savedDigits[currentPos] == encodingsNumber)
      savedDigits[currentPos] = 0;

  } else {
    if (currentMillis - previousMillis2 >= refreshRate) {
      previousMillis2 = currentMillis;
      for (int i = 0; i < displayCount; i++) {
        digitalWrite(displayDigits[i], HIGH);
      }
      digitalWrite(displayDigits[k], LOW);

      if (currentMillis - previousMillis >= 250) {
        previousMillis = currentMillis;

        dpState = !dpState;
      }
      if (dpState && k == currentPos)
        writeReg(byteEncodings[savedDigits[k]] - 1);  // Decreasing encoding by 1 will remove dp
      else
        writeReg(byteEncodings[savedDigits[k]]);
      k++;
      if (k >= 4)
        k = 0;
    }

    // Horizontal movement check
    if (yValue < minThreshold && joyMovedY == false) {
      joyMovedY = true;
      if (currentPos != 0)
        --currentPos;
    }
    if (yValue > maxThreshold && joyMovedY == false) {
      joyMovedY = true;
      if (currentPos != 3)
        ++currentPos;
    }
    if (yValue > minThreshold && yValue < maxThreshold) {
      joyMovedY = false;
    }
  }


  /* 
  Checks if the button was pressed for at least resetPressDuration milliseconds 
  and it wasn pressed during stage 1
  */

  if (swState == HIGH) {
    lastPressedMillis = currentMillis;
  }
  if (currentMillis - lastPressedMillis >= resetPressDuration && editMode) {
    //Reset everything
    editMode = 0;
    for (int i = 0; i < displayCount; i++)
      savedDigits[i] = 0;
    currentPos = 3;
  }

  if (swState != lastSwState) {
    if (swState == LOW) {
      editMode = !editMode;
    }
  }

  lastSwState = swState;
}