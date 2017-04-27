#include <IRremote.h>
#include <Stepper.h>

#include "Stepper.h"
#include "IRremote.h"
/*----- Variables, Pins -----*/
#define STEPS  10   // Number of steps per revolution of Internal shaft
#define s  500  // 2048 = 1 Revolution
#define SPEED 500
#define receiver 12 // Signal Pin of IR receiver to Arduino Digital Pin 12

/*-----( Declare objects )-----*/
// Setup of proper sequencing for Motor Driver Pins
// In1, In2, In3, In4 in the sequence 1-3-2-4
Stepper altitude(STEPS, 8, 10, 9, 11);
Stepper azimuth(STEPS, 4, 6, 5, 7);
IRrecv irrecv(receiver);    // create instance of 'irrecv'
decode_results results;     // create instance of 'decode_results'
void setup(){ 
  irrecv.enableIRIn(); // Start the receiver
  altitude.setSpeed(SPEED);
  azimuth.setSpeed(SPEED);
  Serial.begin(9600);
}

void loop(){
  if (irrecv.decode(&results)) // have we received an IR signal?
    {
      Serial.println(results.value, HEX);
      switch(results.value)
      {
        case 0xFF629D: // VOL+ button pressed
          stepUp();
          cleanAltitude();
          break;
        case 0xFFA857: // VOL- button pressed
          stepDown();
          cleanAltitude();
          break;
        case 0xFFC23D:
          stepClockwise();
          cleanAzimuth();
          break;
        case 0xFF22DD:
          stepCounterclockwise();
          cleanAzimuth();
          break;
      }      
  }  
}/* --end main loop -- */

void stepUp(){
  altitude.step(s);
}
void stepDown(){
  altitude.step(-s);
}
void stepClockwise(){
  azimuth.step(s);
}
void stepCounterclockwise(){
  azimuth.step(-s);
}
void cleanAltitude(){
  irrecv.resume(); // receive the next value
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
}
void cleanAzimuth(){
  irrecv.resume(); // receive the next value
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
}

