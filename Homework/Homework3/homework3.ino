// joystick pins
const int pinSW = 2;
const int pinX = A0;
const int pinY = A1;


// segment pins
const int pinA = 4;
const int pinB = 5;
const int pinC = 6;
const int pinD = 7;
const int pinE = 8;
const int pinF = 9;
const int pinG = 10;
const int pinDP = 11;

// segments
const int segA = 0;
const int segB = 1;
const int segC = 2;
const int segD = 3;
const int segE = 4;
const int segF = 5;
const int segG = 6;
const int segDP = 7;

// joystick directions
const int UP = 0;
const int DOWN = 1;
const int LEFT = 2;
const int RIGHT = 3;

const int segSize = 8;

byte swState = HIGH;
byte lastSwState = HIGH;

int xValue = 0;
int yValue = 0;

byte savedState[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
byte displayedState[8];

bool joyMovedX = false;
bool joyMovedY = false;

int minThreshold = 400;
int maxThreshold = 600;

int currentSegment = segDP;

unsigned long currentMillis;
unsigned long previousMillis = 0;
unsigned long interval = 200;
unsigned long lastPressedMillis = 0;

int ledState = 1;
int editMode = 0;

const int resetPressDuration = 3000;

int segments[segSize] = {
  pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP
};


byte digitMatrix[segSize][segSize] = {
  // a  b  c  d  e  f  g dp
  { 1, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 1, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 1, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 1, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 1, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 1, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 1, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 1 }

};

int move(int currentSegment, int direction) {
  switch (currentSegment) {
    case segA:
      switch (direction) {
        case UP:
          break;
        case DOWN:
          currentSegment = segG;
          break;
        case LEFT:
          currentSegment = segF;
          break;
        case RIGHT:
          currentSegment = segB;
          break;
      }
      break;
    case segB:
      switch (direction) {
        case UP:
          currentSegment = segA;
          break;
        case DOWN:
          currentSegment = segG;
          break;
        case LEFT:
          currentSegment = segF;
          break;
        case RIGHT:
          break;
      }
      break;
    case segC:
      switch (direction) {
        case UP:
          currentSegment = segG;
          break;
        case DOWN:
          currentSegment = segD;
          break;
        case LEFT:
          currentSegment = segE;
          break;
        case RIGHT:
          currentSegment = segDP;
          break;
      }
      break;
    case segD:
      switch (direction) {
        case UP:
          currentSegment = segG;
          break;
        case DOWN:
          break;
        case LEFT:
          currentSegment = segE;
          break;
        case RIGHT:
          currentSegment = segC;
          break;
      }
      break;
    case segE:
      switch (direction) {
        case UP:
          currentSegment = segG;
          break;
        case DOWN:
          currentSegment = segD;
          break;
        case LEFT:
          break;
        case RIGHT:
          currentSegment = segC;
          break;
      }
      break;
    case segF:
      switch (direction) {
        case UP:
          currentSegment = segA;
          break;
        case DOWN:
          currentSegment = segG;
          break;
        case LEFT:
          break;
        case RIGHT:
          currentSegment = segB;
          break;
      }
      break;
    case segG:
      switch (direction) {
        case UP:
          currentSegment = segA;
          break;
        case DOWN:
          currentSegment = segD;
          break;
        case LEFT:
          break;
        case RIGHT:
          break;
      }
      break;
    case segDP:
      switch (direction) {
        case UP:
          break;
        case DOWN:
          break;
        case LEFT:
          currentSegment = segC;
          break;
        case RIGHT:
          break;
      }
      break;
  }
  return currentSegment;
}

// Displays a state given by an array of states of each segment
void displayState(byte state[]) {
  for (int i = 0; i < segSize; i++) {
    digitalWrite(segments[i], state[i]);
  }
}

void setup() {
  // initialize all the pins
  for (int i = 0; i < segSize; i++) {
    pinMode(segments[i], OUTPUT);
  }
  pinMode(pinSW, INPUT_PULLUP);

  Serial.begin(9600);
}


void loop() {

  xValue = analogRead(pinX);
  yValue = analogRead(pinY);
  swState = digitalRead(pinSW);

  if (editMode) {
    // The X axis is used for changing segment values in stage 2
    if (xValue < minThreshold && joyMovedX == false) {
      savedState[currentSegment] = LOW;
      joyMovedX = true;
    }
    if (xValue > maxThreshold && joyMovedX == false) {
      savedState[currentSegment] = HIGH;
      joyMovedX = true;
    }
    if (xValue > minThreshold && xValue < maxThreshold) {
      joyMovedX = false;
    }
    displayState(savedState);
  } else {

    if (xValue < minThreshold && joyMovedX == false) {
      currentSegment = move(currentSegment, DOWN);
      joyMovedX = true;
    }
    if (xValue > maxThreshold && joyMovedX == false) {
      currentSegment = move(currentSegment, UP);
      joyMovedX = true;
    }
    if (xValue > minThreshold && xValue < maxThreshold) {
      joyMovedX = false;
    }

    if (yValue < minThreshold && joyMovedY == false) {
      currentSegment = move(currentSegment, LEFT);
      joyMovedY = true;
    }
    if (yValue > maxThreshold && joyMovedY == false) {
      currentSegment = move(currentSegment, RIGHT);
      joyMovedY = true;
    }
    if (yValue > minThreshold && yValue < maxThreshold) {
      joyMovedY = false;
    }

    /*
    A temporary array displayedState is used to copy the contents from savedState 
    and modify the value of the current segment because it should blink regardless of the saved state
    */
    currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {

      previousMillis = currentMillis;

      ledState = !ledState;

      for (int i = 0; i < segSize; i++)
        displayedState[i] = savedState[i];
      if (ledState)
        displayedState[currentSegment] = HIGH;
      else
        displayedState[currentSegment] = LOW;
      displayState(displayedState);
    }
  }

  /* 
  Checks if the button was pressed for at least resetPressDuration milliseconds 
  and it wasn't pressed during stage 2
  */
  currentMillis = millis();

  if (swState == HIGH) {
    lastPressedMillis = currentMillis;
  }
  if (currentMillis - lastPressedMillis >= resetPressDuration && editMode) {
    //Reset everything
    editMode = 0;
    currentSegment = segDP;
    for (int i = 0; i < segSize; i++)
      savedState[i] = LOW;
  }

  if (swState != lastSwState) {
    if (swState == LOW) {
      editMode = !editMode;
    }
  }

  lastSwState = swState;

  Serial.println(swState);
}