
# Homework 1 - RGB LED with 3 potentiometers
### 
### Image:
![IMG_20221027_180646](https://user-images.githubusercontent.com/79210109/198347816-42e0f2e7-eb10-4b9a-b67c-3c3088e6fa44.jpg)
### Video:
[Introduction to Robotics - Homework 1](https://www.youtube.com/embed/GbboUF1w3iU)
### Requirements:
• Components: RBG LED (1 minimum), potentiometers (3 minimum),resistors and wires (per logic)
• Technical Task: Use a separate potentiometer in controlling each of the colors of the RGB led (Red, Green and Blue). The control must be done with digital electronics (aka you must read the value of the potentiometer with Arduino, and write a mapped value to each of the pins connected to the led.
• Publishing task: You must add the code to the Git repo and continue updating the readme with at least the following details (but feel free tobe more creative):
1. Task requirements
2. Picture of the setup
3. Link to video showcasing functionality (I recommend youtube, but anything I can access is ﬁne)
4. Remember to publish the video in the correct orientation. Don’t do this: https://youtu.be/Y8H0PlUtcto5. Hand in the homework on MS teams when done - aka when git is up to date

• Coding task: Coding style is of utmost importance. You must have a perfectly clean code in order to receive the maximum grade. Keep in mind that magic numbers are not accepted, although you might see them in the lab (as a trade-off for speed). Remember to be consistent in your style, check the style guide and the provided style document and use correct spacing.
Example used in lab which would not yield the maximum grade: ”analogWrite(ledPin, potValue / 4) or ”voltage = potValue * 5.0 / 1023.0”.

Mistakes observed there:
1. ”potValue / 4” is not precise, since the value does not always split into 4 perfectly. Use the map() function
2. We calculate the value inside the analogWrite function
3. potValue and potPin are not ideal naming versions. What happensif you change your potentiometer with a slider? (a slider has the same output range, so no change to the code would be needed - if written correctly)
4. 4 is a magic number. 5.0 and 1023.0 are magic numbers. They should be replaced with constants, such as maxAnalogValue, maxVoltageValue etc