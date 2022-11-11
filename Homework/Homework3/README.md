# Homework 3 - 7 segment display drawing
### 
### Image:
![IMG_20221111_093015](https://user-images.githubusercontent.com/79210109/201291204-74f9e40d-7ed6-4892-b8db-9303073b5064.jpg)
### Video:
[Introduction to Robotics - Homework 3](https://youtube.com/embed/rECLg2LWgY8)
### Requirements:
• Components: 1 7-segment display, 1 joystick, resistors and wires (per logic)
• General description: You will use the joystick to control the position of the segment and ”draw” on the display. The movement between segments should be natural (meaning they should jump from the current position only to neighbors, but without passing through ”walls”.
The system has the following states:
1. State 1 (default, but also initiated after a button press in State 2): Current position blinking. Can use the joystick to move from
one position to neighbors. Short pressing the button toggles state 2. Long pressing the button in state 1 resets the entire display by
turning all the segments OFF and moving the current position to the decimal point.
2. State 2 (initiated after a button press in State 1): The current segment stops blinking, adopting the state of the segment before selection (ON or OFF). Toggling the X (or Y, you chose) axis should change the segment state from ON to OFF or from OFF to ON.
Clicking the joystick should save the segment state and exit back to state 1.
Be careful:
1. Long pressing the button to reset should only be available in State 1
2. Joystick movements should be done with toggle, as in the lab (joyMoved, etc)
3. Correctly using interrupts with debounce yields a bonus, but it is
not a must. Code for homework with bonus points should be
submitted before the course, not the lab.
4. The code in the lab for joystick movement is not perfect and can be improved. The state change is missing something (sounds familiar?),
the code should be wrapped in a function and the constraint between 0 and 9 can be simplified
![Screenshot 2022-11-11 100857](https://user-images.githubusercontent.com/79210109/201295347-aae2f0f1-a015-4897-8a11-fcc6daffbd89.png)
• Publishing task: You must add the code to the Github repo and continue updating the readme with at least the following details (but feel free to be more creative). I recommend using dropdowns in the readme, for each project, if you feel the readme is too cluttered:
https://gist.github.com/citrusui/07978f14b11adada364ff901e27c7f61
1. Task Requirements
2. Picture of the setup
3. Link to video showcasing functionality (I recommend youtube, but anything I can access is fine)
4. Remember to publish the video in the correct orientation. Don’t do this: https://youtu.be/Y8H0PlUtcto
5. Hand in the homework on MS teams when done - aka when Git is up to date
• Coding task: Coding style is of utmost importance. You must have a perfectly clean code in order to receive the maximum grade. An important coding challenge present in this task is using millis() instead of delay().
However, remember that the bulk of the grade is if the projects works.
Do not tend to small details unless you have the entire functionality done.