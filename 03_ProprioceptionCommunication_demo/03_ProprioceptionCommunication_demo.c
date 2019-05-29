//--------------------------------------------------------------------------------------------------
// Changes colour of LEDs
// Detects stall
// Performs an escape maneuver if stall detected
//--------------------------------------------------------------------------------------------------


#include "simpletools.h" 
#include "s3.h" 
#include "encoder.h"

// ----- FUNCTIONS ------
void ta_da();
void uh_oh();
void Beethoven(int vol);
void StallAvoid();


int main()
{
  s3_setup();

  cog_run(encoder_update_cog, 100);

  //while(1){ 
   
        // All LEDs --> green if robot is not stalled
        // All LEDs --> red if robot is stalled
        if (s3_resetButtonCount() == 1) {
          s3_motorSet(75, 75, 0); 
          while(1){
            if (!s3_tailWheelMoving()) {
                s3_setLED(S3_LEFT, S3_COLOR_FF0000);
                s3_setLED(S3_CENTER, S3_COLOR_FF0000);
                s3_setLED(S3_RIGHT, S3_COLOR_FF0000);
            }
   
            if (s3_tailWheelMoving()) {
                  s3_setLED(S3_LEFT, S3_COLOR_00FF00);
                  s3_setLED(S3_CENTER, S3_COLOR_00FF00);
                  s3_setLED(S3_RIGHT, S3_COLOR_00FF00);
            }
          }                     
        }
        
        
        // All LEDs --> green if robot is not stalled
        // All LEDs --> red if robot is stalled
        if (s3_resetButtonCount() == 2) { 
          s3_motorSet(75, 75, 0);
          while(1){
            if (!s3_tailWheelMoving()) {
                s3_setLED(S3_LEFT, S3_COLOR_FF0000);
                s3_setLED(S3_CENTER, S3_COLOR_FF0000);
                s3_setLED(S3_RIGHT, S3_COLOR_FF0000);
            }
   
            else {
                  s3_setLED(S3_LEFT, S3_COLOR_00FF00);
                  s3_setLED(S3_CENTER, S3_COLOR_00FF00);
                  s3_setLED(S3_RIGHT, S3_COLOR_00FF00);
            }
          }                     
        }
        
        
        // Play Tada
        if (s3_resetButtonCount() == 3) {
          ta_da();   
        }
        
        
        // Play Uh-Oh
        if (s3_resetButtonCount() == 4) { 
          uh_oh();
        }
        
        
        // Play Beethoven
        if (s3_resetButtonCount() == 5) { 
          Beethoven(100);
        } 
        
        
        // Drive in a square
        if (s3_resetButtonCount() == 6) { 
          float quarter_turn = pi * 145 / 4;
          int dist_start = dist_left;

          for (int i=0; i<4; i++) { 
            
            while( dist_left - dist_start < 200){
              s3_motorSet(75, 75, 0);
            } 
            
            while( dist_left - dist_start < 200 + quarter_turn){
              s3_motorSet(75, -75, 0);
            }               
        
          dist_start = dist_left;
        
          }
          // stop after 4 sides
          s3_motorSet(0, 0, 0);
        } 
        
        
        // Drive forwards, in a circle of radius 30cm, clockwise
        if (s3_resetButtonCount() == 7) {
           
          float l = 2 * pi * (300 + (145/2) );
          float r = 2 * pi * (300 - (145/2) );
          float ratio = r/l;
          float left_speed = 100;
          float right_speed = left_speed * ratio;
          
          int dist_start = dist_left;

          while( dist_left - dist_start < l){
            s3_motorSet(left_speed, right_speed, 0);
            print("%f, %f \n", dist_left, right_speed);
          } 
          s3_motorSet(0, 0, 0);             
        } 
        
        
        // Drive in a straight line.
        // If stalled perform escape maneuver, play sound and flash light
        if (s3_resetButtonCount() == 8) { 
          s3_motorSet(75, 75, 0);
          while(1){
            StallAvoid();
           
          }            
        }    
               
  //}         
}


void ta_da(){
  s3_setVolume(20);
  s3_playNote(659, 1046, 152);
  pause(35);
  s3_playNote(659, 1046, 562);
}

void uh_oh(){
  s3_setVolume(20);
  s3_playNote(200, 0, 175);
  pause(100);
  s3_playNote(160, 0, 562);
}

void Beethoven(int vol){
  s3_simplePlay((6272 / 16), 250, vol);
  s3_simplePlay((6272 / 16), 250, vol);
  s3_simplePlay((6272 / 16), 250, vol);
  s3_simplePlay((4978 / 16), 1000, vol);
  pause(300);
  s3_simplePlay((5588 / 16), 250, vol);
  s3_simplePlay((5588 / 16), 250, vol);
  s3_simplePlay((5588 / 16), 250, vol);
  s3_simplePlay((4699 / 16), 1000, vol);
}

void StallAvoid(){
    // escape maneuver if stall detected

    if (!s3_tailWheelMoving()) {
      print("Stalled \n");
      
      // LEDs
      s3_setLED(S3_LEFT, S3_COLOR_FF0000);
      s3_setLED(S3_CENTER, S3_COLOR_FF0000);
      s3_setLED(S3_RIGHT, S3_COLOR_FF0000);
      
      // sound
      uh_oh();
      
      // escape maneuver
      s3_motorSet(-75, -75, 1500);   // move backwards
      s3_simpleSpin(90, 75, 0);      // quarter clockwise turn
      s3_motorSet(75, 75, 0);        // drive straight
      
      
    }
    else
    {
      print("Not Stalled \n");
      
      // LEDs
      s3_setLED(S3_LEFT, S3_COLOR_000000);
      s3_setLED(S3_CENTER, S3_COLOR_000000);
      s3_setLED(S3_RIGHT, S3_COLOR_000000);
    }
} 







