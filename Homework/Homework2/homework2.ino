const int redPinCar = 11;
const int yellowPinCar = 10;
const int greenPinCar = 9;

const int redPinPeople = 5;
const int greenPinPeople = 4;

const int buttonPin = 2;

bool stateRedPinCar;
bool stateYellowPinCar;
bool stateGreenPinCar;
bool stateRedPinPeople;
bool stateGreenPinPeople;

int buttonState = 1;
int currentButtonState = 1;

const int buzzerPin = 7;
const int buzzerTone = 500;

unsigned long previousMillis = 0;
unsigned long currentMillis = 0;
unsigned long previousMillis2 = 0;
unsigned long currentMillis2 = 0;
unsigned long previousMillis3 = 0;
unsigned long currentMillis3 = 0;
unsigned long previousMillis4 = 0;
unsigned long currentMillis4 = 0;

unsigned long previousMillisBuzzer = 0;
unsigned long currentMillisBuzzer = 0;
unsigned long previousMillisBuzzerAndLight = 0;
unsigned long currentMillisBuzzerAndLight = 0;


const int delayBeginState2 = 8000;
const int state2Duration = 3000;
const int state3Duration = 8000;
const int state4Duration = 4000;

const int buzzerDelay1 = 500;
const int buzzerDelay2 = 250;

int state1completed = 0;
int state2completed = 0;
int state3completed = 0;

int turnBuzzerOn;
int turnBuzzerAndLightOn;

void setup() {
  pinMode(greenPinCar, OUTPUT);
  pinMode(yellowPinCar, OUTPUT);

  pinMode(redPinCar, OUTPUT);
  pinMode(redPinPeople, OUTPUT);
  pinMode(greenPinPeople, OUTPUT);

  pinMode(buttonPin, INPUT_PULLUP);

  Serial.begin(9600);

  state1();
}
void state1() {
  /*
   * green for cars
   * red for people 
   * no sounds
   * duration: indefinite, or 8 seconds since the button is pressed
   */

  turnBuzzerOn = 1;
  turnBuzzerAndLightOn = 1;

  stateRedPinCar = LOW;
  stateYellowPinCar = LOW;
  stateGreenPinCar = HIGH;

  stateRedPinPeople = HIGH;
  stateGreenPinPeople = LOW;

  digitalWrite(greenPinPeople, stateGreenPinPeople);
  digitalWrite(redPinPeople, stateRedPinPeople);

  digitalWrite(greenPinCar, stateGreenPinCar);
  digitalWrite(redPinCar, stateRedPinCar);
  digitalWrite(yellowPinCar, stateYellowPinCar);
}

void state2() {
  /*
   * yellow for cars
   * red for people 
   * no sounds 
   * duration: 3 seconds.
   */

  stateGreenPinCar = LOW;
  stateYellowPinCar = HIGH;
  
  digitalWrite(greenPinCar, stateGreenPinCar);
  digitalWrite(yellowPinCar, stateYellowPinCar);
}

void state3() {
  /*
   * red for cars
   * green for people
   * a beeping sound from the buzzer at a constant interval
   * duration: 8 seconds
   */

  stateGreenPinPeople = HIGH;
  stateRedPinPeople = LOW;

  stateRedPinCar = HIGH;
  stateYellowPinCar = LOW;

  digitalWrite(greenPinPeople, stateGreenPinPeople);
  digitalWrite(redPinPeople, stateRedPinPeople);

  digitalWrite(redPinCar, stateRedPinCar);
  digitalWrite(yellowPinCar, stateYellowPinCar);
}


int isState1() {
  return !stateRedPinCar && !stateYellowPinCar && stateGreenPinCar && stateRedPinPeople && !stateGreenPinPeople;
}

void pushButton() {
  buttonState = digitalRead(buttonPin);

  if (isState1() && currentButtonState && !buttonState) {
    previousMillis = millis();
    currentButtonState = 0;
    state1completed = 0;
    state2completed = 0;
    state3completed = 0;
  }
}

void loop() {
  pushButton();

  Serial.println(currentButtonState);

  if (!currentButtonState) {
    currentMillis = millis();

    //if we are in state 1 and the time needed to begin state 2 since the button was pressed has passed
    if (!state1completed && currentMillis - previousMillis >= delayBeginState2) {
      state1completed = 1;

      state2();
      previousMillis2 = millis();
    }
    //if we are in state 2
    else if (state1completed && !state2completed) {
      currentMillis2 = millis();

      //if the time for state 2 has passed
      if (currentMillis2 - previousMillis2 >= state2Duration) {
        state2completed = 1;

        state3();

        previousMillis3 = millis();
        previousMillisBuzzer = millis();
      }
    }
    //if we are in state 3
    else if (state1completed && state2completed && !state3completed) {
      currentMillis3 = millis();

      //if we are still in state 3
      if (currentMillis3 - previousMillis3 < state3Duration) {
        currentMillisBuzzer = millis();
        //buzzer will be active for buzzerDelay1 milliseconds, then sleep for buzzerDelay2 milliseconds
        if ((turnBuzzerOn && currentMillisBuzzer - previousMillisBuzzer >= buzzerDelay2) || (!turnBuzzerOn && currentMillisBuzzer - previousMillisBuzzer >= buzzerDelay1)) {
          previousMillisBuzzer = currentMillisBuzzer;
          turnBuzzerOn = !turnBuzzerOn;
        }

        //activate the buzzer
        if (turnBuzzerOn) {
          tone(buzzerPin, buzzerTone);
        } else {
          noTone(buzzerPin);
        }
      } else {
        state3completed = 1;

        previousMillis4 = millis();
        previousMillisBuzzerAndLight = millis();
      }
    }
    //if we are in state 4
    else if (state1completed && state2completed && state3completed) {
      currentMillis4 = millis();

      if (currentMillis4 - previousMillis4 < state4Duration) {
        /*
         * red for cars
         * blinking green for people
         * a beeping sound from the buzzer at a constant interval, faster than the beeping in state 3.
         */
        currentMillisBuzzerAndLight = millis();

        //buzzer will be active for buzzerDelay1 milliseconds, then sleep for buzzerDelay2 milliseconds
        if (currentMillisBuzzerAndLight - previousMillisBuzzerAndLight >= buzzerDelay2) {
          turnBuzzerAndLightOn = !turnBuzzerAndLightOn;
          previousMillisBuzzerAndLight = currentMillisBuzzerAndLight;
        }

        //activate the buzzer and the green led for people
        if (turnBuzzerAndLightOn) {
          tone(buzzerPin, buzzerTone);
          digitalWrite(greenPinPeople, LOW);
        } else {
          noTone(buzzerPin);
          digitalWrite(greenPinPeople, HIGH);
        }
      }
      if (currentMillis4 - previousMillis4 >= state4Duration) {
        state1();
        currentButtonState = 1;
      }
    }
  }
}