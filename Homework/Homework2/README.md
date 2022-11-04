# Homework 2 - Crosswalk: Traffic lights for cars and people
### 
### Image:
![IMG_20221104_095612](https://user-images.githubusercontent.com/79210109/199923447-ed5fa7fd-7e44-48d2-a5d4-b027b6ff4a18.jpg)
### Video:
[Introduction to Robotics - Homework 2](https://youtube.com/embed/LeAKyZ5Trfg)
### Requirements:
• Components:  5 LEDs, 1 button, 1 buzzer, resistors and wires (per logic)
• General  description:Building  the  traffic  lights  for  a  crosswalk. You will use 2 LEDs to represent the traffic lights for people (red and green) and 3 LEDs to represent the traffic lights for cars (red, yellow and green). See the states it needs to go through.  If anything is not clear, ask.  Also,see the uploaded video (the intervals are different, but the states flow isthe same).  It’s a traffic lights system for people and cars - don’t overthinkit .The system has the following states:
1. State 1(default, reinstated after state 4 ends):  green light for cars,red  light  for  people,  no  sounds.   Duration:  indefinite,  changed  bypressing the button.
2. State 2(initiated by counting down 8 seconds after a button press): the  light  should  be  yellow  for  cars,  red  for  people  and  no  sounds.Duration:  3 seconds.
3. State 3(initiated after state 2 ends):  red for cars, green for peopleand a beeping sound from the buzzer at a constant interval. Duration:8 seconds.
4. State 4(initiated after state 3 ends):  red for cars,blinking greenfor people and a beeping sound from the buzzer,  at a constant in-terval,  faster than the beeping in state 3.  This state should last 4seconds.

Be  careful:  pressing  the  button  in  any  state  other  than  state  1  should NOT yield any actions.

• Publishing task: You must add the code to the Github repo and continue updating the readme with at least the following details (but feel free tobe more creative).  I recommend using dropdowns in the readme, for each project, if you feel the readme is too cluttered:
https://gist.github.com/citrusui/07978f14b11adada364ff901e27c7f61

1. Task Requirements
2. Picture of the setup
3. Link to video showcasing functionality (I recommend youtube,  butanything I can access is fine)
4. Remember to publish the video in the correct orientation.  Don’t do this:https://youtu.be/Y8H0PlUtcto5. Hand in the homework on MS teams when done - aka when Git is up to date

•Coding task:Coding style is of utmost importance.  You must have aperfectly clean code in order to receive the maximum grade.  An important coding challenge present in this task is using millis()instead of delay() .

 However, remember that the bulk of the grade is if the projects works. Do not tend to small details unless you have the entire functionality done.

 Addendum:using interrupts yields a bonus,  but it is not a must.  Becareful, however:  if you use interrupts, it must be properly coded (with debounce etc); coding it wrong can result in subtracted points (but we doappreciate any attempt, even unsuccessful ones).
