// Tristan Caetano
// Auto Nerf Gun Project

// Drivers for ultrasonic sensor
#include "SR04.h"

// Pins for ultrasonic sensor
#define TRIG_PIN 12
#define ECHO_PIN 11

// Light pins
#define RED_PIN 5
#define GREEN_PIN 6
#define BLUE_PIN 7

// Length of array
#define DEF_LENGTH 3

// Creating instance of ultrasonic sensor driver
SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);

// Variable for getting current distance
long a;

// Variable that stores the last few distances
int lastFour[DEF_LENGTH];

// Counter that keeps track of distances
int counter = 0;

// Initialization
void setup() {

  // Initing ultrasonic sensor
   Serial.begin(9600);
   delay(1000);

  // Initing light outs
   pinMode(RED_PIN, OUTPUT);
   pinMode(GREEN_PIN, OUTPUT);
   pinMode(BLUE_PIN,OUTPUT);
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
    digitalWrite(RED_PIN, HIGH);
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(BLUE_PIN, LOW);
    delay(1000);

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
   else{
    counter = 0;
    for(int i; i < DEF_LENGTH; i++){
      lastFour[i] = 0;
    }
    }

   // Prints for distance
   Serial.print(a);
   Serial.println("cm");

   // Setting default lights
   digitalWrite(RED_PIN, LOW);
   digitalWrite(GREEN_PIN, HIGH);
   digitalWrite(BLUE_PIN, LOW);
   delay(100);
}