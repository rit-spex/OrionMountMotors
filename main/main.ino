#include "Stepper.h"
#include "IRremote.h"
/*----- Variables, Pins -----*/
#define STEPS  10   // Number of steps per revolution of Internal shaft
#define steps = 20;  // 2048 = 1 Revolution
int receiver = 12; // Signal Pin of IR receiver to Arduino Digital Pin 6

/*-----( Declare objects )-----*/
// Setup of proper sequencing for Motor Driver Pins
// In1, In2, In3, In4 in the sequence 1-3-2-4
Stepper small_stepper(STEPS, 8, 10, 9, 11);
IRrecv irrecv(receiver);    // create instance of 'irrecv'
decode_results results;     // create instance of 'decode_results'
void setup()
{ 
  irrecv.enableIRIn(); // Start the receiver
  small_stepper.setSpeed(500);
}

void loop()
{
  if (irrecv.decode(&results)) // have we received an IR signal?
    {
      switch(results.value)
      {
        case 0xFFA857: // VOL+ button pressed
          stepForward();
        case 0xFF629D: // VOL- button pressed
          stepBackward();
      }

      irrecv.resume(); // receive the next value
        digitalWrite(8, LOW);
        digitalWrite(9, LOW);
        digitalWrite(10, LOW);
        digitalWrite(11, LOW);       
  }  
}/* --end main loop -- */

void stepForward()
{
  small_stepper.step(steps);
}
void stepBackward()
{
  small_stepper.step(steps);
}

