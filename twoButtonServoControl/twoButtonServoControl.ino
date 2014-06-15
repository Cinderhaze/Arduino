/*

  Referenced code from the Vilros Ultimate Starter Guide.  
  Example 5 (Push Buttons) and Example 8 (A Single Servo)
  
  
  TODO: Get button debouncing working
  TODO: Refactor so code is a bit more readable
  TODO: Figure out how to get a better test harnes for embedded code.

*/

#include <Servo.h>  // servo library

// First we'll set up constants for the pin numbers.
// This will make it easier to follow the code below.

const int button1Pin = 2;  // pushbutton 1 pin
const int button2Pin = 3;  // pushbutton 2 pin
const int ledPin =  13;    // LED pin
const int timeOn = 5000;

long timeToTurnOff = 0;

int inDebounce = true;
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers

const int servoPin = 9;
Servo servo1;  // servo control object
int servoDirection = -1; //Figure out which one is left and which one is right
int servoPosition = 0;
//int servoShouldMove = false; // Consider rolling the servoDirection into an enum.. LEFT (-1), STOP(0), RIGHT (1) for this portion of the logic


void setup()
{
  // Set up the pushbutton pins to be an input:
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);

  // Set up the LED pin to be an output:
  pinMode(ledPin, OUTPUT);      

  servo1.attach(servoPin);
}


void loop()
{
  int button1State, button2State;  // variables to hold the pushbutton states

  // Since a pushbutton has only two states (pushed or not pushed),
  // we've run them into digital inputs. To read an input, we'll
  // use the digitalRead() function. This function takes one
  // parameter, the pin number, and returns either HIGH (5V)
  // or LOW (GND).

  ///////////////////////
  //Figure out if the servo should move
  
  // Here we'll read the current pushbutton states into
  // two variables:

  button1State = digitalRead(button1Pin);
  button2State = digitalRead(button2Pin);
  
  if (((button1State == LOW) && (button2State == LOW)) /*|| inDebounce*/)
  {
    //Stop the motion if it is moving
    digitalWrite(ledPin, LOW);  // turn the LED on
    timeToTurnOff = millis() + timeOn;
    
    servoDirection = 0;
    
//    lastDebounceTime = millis(); // Handling two button debounce
    
  } else if((button1State == LOW))
  {
    //Move Left
    digitalWrite(ledPin, HIGH);  // turn the LED on
    timeToTurnOff = millis() + timeOn;
    servoDirection = 1;
    
  } else if(button2State == LOW) 
  {
    //Move Right
    digitalWrite(ledPin, HIGH);  // turn the LED on
    timeToTurnOff = millis() + timeOn;
    servoDirection = -1;
    
  }
   
//  if(millis()> timeToTurnOff) {
//    digitalWrite(ledPin, LOW);
//    servoDirection = 0;
//  }

  
//  if ((millis() - lastDebounceTime) > debounceDelay) {
//    inDebounce = false;
//  } else {
//    inDebounce = true;
//  }

  /////////////////////////////////
  //Move Servo
  
  servoPosition += servoDirection * 2;
  
  
  // Look into replacing this with a 'constrain'
  if(servoPosition < 0) {
   servoPosition = 0;
  }
  if (servoPosition > 180) {
    servoPosition = 180;
  }
  
  if(servoPosition <= 0 || servoPosition >= 180) {
    digitalWrite(ledPin, LOW);
    servoDirection = 0;
  }
 
 //Should we move the servo?
  if(servoDirection != 0) {
    servo1.write(servoPosition);
    delay(20);
  }
}
