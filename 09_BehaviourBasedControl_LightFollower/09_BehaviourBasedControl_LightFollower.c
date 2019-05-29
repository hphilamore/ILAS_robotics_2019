//--------------------------------------------------------------------------------------------------
// Hunts for a brightest light (20% brighter than other two light sensors)
// Turn to centre light in front of robot
// Moves towards light with speed inversely proportional to light intensity
//--------------------------------------------------------------------------------------------------
#include "simpletools.h"                      // Include simple tools
#include "s3.h"                               // Include simple tools
#include "encoder.h"                          // Include simple tools

// Variables
int bot_diameter = 145;

// Functions
void HuntLight(void);
void TurnToLight(void);
void ReachLight(void);

int main() 
{
  if (s3_resetButtonCount() == 1) {
    while(1){
      s3_setup();
      HuntLight();
      s3_motorSet(0, 0, 0); 
      //TurnToLight();
      //ReachLight();
    }
  }  
}

void HuntLight(void){
// Code to hunt for a light source
  int speed = 75;
  float left_count_start = dist_left;  // left encoder count at start 


      // turn 360 degrees
  while(fabs(dist_left - left_count_start) < bot_diameter * 3.142 &&      
        s3_simpleLight(S3_IS_NOT, SCRIBBLER_LEFT)  && 
        s3_simpleLight(S3_IS_NOT, SCRIBBLER_RIGHT) && 
        s3_simpleLight(S3_IS_NOT, SCRIBBLER_CENTER)){     
      

     s3_motorSet(speed, - speed, 0); 
         
  }

  left_count_start = dist_left;  // reset left encoder count

}

void TurnToLight(void){
  
  // Code to turn towards a light source
  int speed = 75;
  
  // Light is left, turn on spot towards left
  if (s3_simpleLight(S3_IS, SCRIBBLER_LEFT)){
  	s3_motorSet(-speed, speed, 0);} 
  
  
  // Light is right, turn on spot towards right
  else if (s3_simpleLight(S3_IS, SCRIBBLER_RIGHT)){
  	s3_motorSet(speed, -speed, 0);} 
  
  
  // No light or light centered, stop motors
  else {
  	s3_motorSet(0, 0, 0);} 

}

void ReachLight(void){
// Code to move towards light source
// If brightest light detected directly in front of robot,
// move in direction of light with speed inversely proportional to brightness.

if (s3_simpleLight(S3_IS, SCRIBBLER_CENTER)){
  
  int speed = mapInt(s3_lightSensor(SCRIBBLER_CENTER), 0, 255, 100, 0);
  
  s3_motorSet(speed, speed, 0);}

}


