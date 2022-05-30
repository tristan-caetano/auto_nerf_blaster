// Tristan Caetano
// Auto Nerf Gun Project

// Stepper motor pin mapping
// 11 10 9  8
// 37 35 33 31

// Drivers for ultrasonic sensor
#include "SR04.h"

// Drivers for stepper motor (no longer used)
// #include "Stepper.h"

// Pins for ultrasonic sensor
#define TRIG_PIN 12
#define ECHO_PIN 11

// Light pins
#define RED_PIN 5
#define GREEN_PIN 6
#define BLUE_PIN 7

// Pin for insulting sound
#define SOUND_PIN 8

// Length of array
#define DEF_LENGTH 4

// Initializing ultrasonic sensor on pins 11 and 12
SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);

// Variable for getting current distance
long a;

// Variable that stores the last few distances
int lastFour[DEF_LENGTH];

// Counter that keeps track of distances
int counter = 0;

// Setting constants for stepper motor (no longer used)
//const int stepsPerRevolution = 2048;  // change this to fit the number of steps per revolution
//const int rolePerMinute = 18;         // Adjustable range of 28BYJ-48 stepper is 0~17 rpm

// Initializing stepper motor on pins 31 to 37 (no longer used)
// Stepper myStepper(stepsPerRevolution, 31, 35, 33, 37);

// Initialization
void setup() {

  // Initing ultrasonic sensor
   Serial.begin(9600);

   // Initing stepper motor (no longer used)
   // myStepper.setSpeed(rolePerMinute);
   
  // initialize the serial port:
  Serial.begin(9600);

  // Initing light outs
   pinMode(RED_PIN, OUTPUT);
   pinMode(GREEN_PIN, OUTPUT);
   pinMode(BLUE_PIN,OUTPUT);

   // Initing sound pin
   pinMode(SOUND_PIN, OUTPUT);
}

// Loop function
void loop() {

  // Getting distance from ultrasonic sensor
   a=sr04.Distance();

   // Starting distance tracking if counter is at 0
   if(counter == 0){
    lastFour[counter] = a;
    counter ++;
   }
   
   // If the counter is at max, shoot (set light to red)
   else if(counter == DEF_LENGTH){

    Serial.println("S H O O T");

    // Make insulting noise
    makeNoise(true);

    // Turn light red
    turnOnLight(true);

    // Rotates stepper motor (no longer used)
    //myStepper.step(stepsPerRevolution);

    // Delay allows for perfect timing of sound to play and stop
    delay(1200);

    // Stop sound
    makeNoise(false);

    // Resetting counter and array
    counter = 0;
    for(int i; i < DEF_LENGTH; i++){
      lastFour[i] = 0;
    }
   }

   // Save distance if the next distance is less than the last
   else if(lastFour[counter - 1] > a){
    lastFour[counter] = a; 
    counter ++;
   }

   // If distance is more reset counter and array
   else if(a <= (lastFour[counter - 1] * 2)){
    Serial.println("R E S E T");
    counter = 0;
    for(int i; i < DEF_LENGTH; i++){
      lastFour[i] = 0;
      }
    }

   // Prints for distance
   Serial.print(a);
   Serial.println("cm");

   // Reset light to green
   turnOnLight(false);
}

// Function that can turn the LED red or green
void turnOnLight(boolean activate){

  // Turn red
  if(activate){
    digitalWrite(RED_PIN, HIGH);
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(BLUE_PIN, LOW);

  // Turn green  
  }else{
    // Setting default lights
   digitalWrite(RED_PIN, LOW);
   digitalWrite(GREEN_PIN, HIGH);
   digitalWrite(BLUE_PIN, LOW);
    
  }
} 

// Function that plays and stops the sound 
void makeNoise(boolean activate){

  // Play sound
  if(activate){
    digitalWrite(SOUND_PIN, HIGH);

  // Stop sound  
  }else{
   digitalWrite(SOUND_PIN, LOW);
    
  }
}
