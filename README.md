# Daily Goal Tracker


## Introduction

This project was my final project for my PLTW Digital Electronics class. I was inspired by [Simone Giertz's Everyday Calendar](https://www.youtube.com/watch?v=-lpvy-xkSNA) as well as the goal to work out daily consistently. (Especially going into college, this goal seems to be more pertinent)

[insert gif of project working here]

## Main Parts

### Arduino Nano

While I used an Arduino Uno for prototyping, switched to the arduino nano as it allowed for a more compact final product and was more cost-effective. 

![Arduino Nano](https://cdn.shopify.com/s/files/1/0438/4735/2471/products/A000005_03.front_643x483.jpg?v=1628695103)

### Switches (x8)

Used to control "on" "off" functionality of each day and clear / next screen option as seen by the eighth switch.

### Adafruit 1.44" Color TFT with Micro SD Socket

LCD display used to showcase daily goal progress

## Prototyping

To get the basic switch and clear switch logic down, I first prototyped just the switch functionality using LEDs as demonstrated below:

[insert led gif here]

## Code Implementation

Note that a more detailed explanation of the code can be found by going to DEFinalProject.ino as the code is commented. 

### Technical Challenges

The main technical challenge concerned reading inputs from the switches. Depending on how the switch is closed, either 5V or 0V is read in by the arduino microcontroller. However, to make this project more user-friendly, I didn't want the switch state to be fixed (ie: 5V means you met your goal while 0V means you didn't) since it is expected that after clearing the lcd, that all the switches will be in a "goal not met mode" even if the previous state they're in is sending 5V to the microcontroller. Thus, I independently tracked the state of each switch and flipped the signal that needs to be read in for "goal to be met" each time the clear button is hit (see the clearAll() and flipSignal() functions)

Another technical challenge that required some debugging was implementing the Turtle library. I ended up simply having to edit some of the source code as the microcontroller used in the original source code was for a different arduino microcontroller. 

## Attributions:

Turtle Library Used: https://www.instructables.com/Arduino-TFT-Shield-Turtle-Graphics/
