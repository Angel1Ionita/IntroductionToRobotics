# Homework 4 - 4 digit 7 segment display with shift register
### Image:
![IMG_20221117_152710](https://user-images.githubusercontent.com/79210109/202498815-49f61c11-52d7-4d32-9412-488b689025ea.jpg)
### Video:
[Introduction to Robotics - Homework 4 - YouTube](https://www.youtube.com/embed/pimvI3w5J_w)
### Basic requirements: 
• Components: a joystick, a 4 digit 7-segment display, a 74hc595 shift register
• General Description: Use the joystick to move through the 4 digit 7 segment displays digits, press the button to lock in on the current digit and use the other axis to increment or decrement the number. Keep the button pressed to reset all the digit values and the current position to the first digit in the first state. 
The system has the following states: 
1. First state: you can use a joystick axis to cycle through the 4 digits; using the other axis does nothing. A blinking decimal point shows the current digit position. When pressing the button, you lock in on the selected digit and enter the second state. 
2. Second state: in this state, the decimal point stays always on, no longer blinking and you can no longer use the axis to cycle through the 4 digits. Instead, using the other axis, you can increment on decrement the number on the current digit IN HEX (aka from 0 to F, as in the lab). Pressing the button again returns you to the previous state. Also, keep in mind that when changing the number, you must increment it for each joystick movement - it should not work continuously increment if you keep the joystick in one position (aka with joyMoved). 
3. Reset: toggled by long pressing the button only in the first state. When resetting, all the digits go back to 0 and the current position is set to the first (rightmost) digit, in the first state. 

• Publishing task: You must add the code to the Github repo and continue updating the readme with at least the following details (but feel free to be more creative): 

1. Task Requirements
2. Picture of the setup 
3. Link to video showcasing functionality (I recommend youtube, but anything I can access is fine) 
4. Remember to publish the video in the correct orientation. Don’t do this: https://youtu.be/Y8H0PlUtcto
5. Hand in the homework on MS teams when done - aka when github is up to date 

Useful links, Interrupts: 
1. https://www.arduino.cc/reference/en/language/functions/external-interrupts/ attachinterrupt/ 
2. https://create.arduino.cc/projecthub/rafitc/interrupts-basics-f475d5 
3. https://www.youtube.com/watch?v=QtyOiTw0oQc 
4. https://www.google.com/search?q=arduino+uno+interrupts&oq= arduino+uno+interrupts&aqs=chrome..69i57j0i67j0i512l7.5123j0j7&sourceid=chrome&ie=UTF-8 
See the video on MS teams for an basic example. 

Differences between the homework requirements and the video: 
1. You must use shift register 
2. You must cycle all the way up to ”F” in HEX 
3. You need to add the ”reset” functionality by keeping the button pressed 

Have fun!