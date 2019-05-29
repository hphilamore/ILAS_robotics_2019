//--------------------------------------------------------------------------------------------------
//Lifs and lowers a  pen using a servo motor while driving along a series of pre-programmed points.
//--------------------------------------------------------------------------------------------------

// libraries
#include "simpletools.h" // Include simpletools
#include "s3.h" 
#include "scribbler.h"
#include "math.h"
#include "encoder.h"
#include "servo.h"

// constants
#define pi 3.14159265358979323846
#define L 145 // Length between robot wheel centres 

// variables
float global_pos[3] = {0, 0, 0};
float x_pos[] = {100, 200, 400, 450}; 
float y_pos[] = {200, 100, 170, 130};
float draw[] = {0, 1, 0, 1}; 
//float x_pos[] = {40, 40, 40, 100, 100, 100, 160, 160, 200, 200, 160, 160, 200};
//float y_pos[] = {0, 100, 50, 50,  100, 0,   0,   100, 100, 50,  50,  0,   0 };
int nElements = sizeof(x_pos)/sizeof(x_pos[0]);

// functions
float quad_angle(float angle);
float sgn(float v);
void GoToGoal(float xI, float yI, int speed);
void pen_lift(int pose);


int main()                                    
{
  s3_setup();
  cog_run(encoder_update_cog, 65); 

  if (s3_resetButtonCount() == 1) {  
   
    for(int i=0; i<nElements  ; i++){ 
      
        pen_lift(draw[i]);             
                
        GoToGoal(x_pos[i], 
                 y_pos[i], 
                 50);  
     }  
     
     s3_motorSet(0, 0, 0);   
             
   }
  
}


float quad_angle(float angle) {
  // Checks that angle is in set -pi to pi
  if      (angle < -pi){ return angle + ( 2 * pi ); }
  else if (angle > pi) { return angle - ( 2 * pi ); }
  else                 { return angle; }
}

float sgn(float v) {
  // The sign function 
  if      (v < 0){ return -1; }
  else if (v > 0){ return 1; }
  else           { return 0; }
  return 0;
}


void GoToGoal(float xI, float yI, int speed){
  
  // Drives the robot to a goal by turning on the spot then driving in a straight line.  
  // dxI : x distance to goal, global frame
  // dyI : y distance to goal, global frame
  // speed : robot linear velocity   

  // plan path 
  float dyI = yI - global_pos[1];
  float dxI = xI - global_pos[0]; 
  // cartesian -> polar
  float d = powf((powf(dxI,2) + powf(dyI,2)), 0.5);    // distance
  float B = atan2(dyI, dxI);
  // global -> local
  float a = B - global_pos[2];                           
  a = quad_angle(a);
  float len_a = a * L / 2;                             // convert angle to arc of wheel travel
                 
  
  // move
  float dist_start = dist_left;
  while( fabs(dist_left - dist_start) < fabs(len_a)){
	   s3_motorSet(-sgn(a) * speed, 
                 sgn(a) * speed, 
                 0);}
                  
  dist_start = dist_left;          
  while( fabs(dist_left - dist_start) < fabs(d)){
        s3_motorSet(speed, speed, 0);
        //print("%f", dist_left);
        //print("\t");
        }               
  
  // update position
  global_pos[0] += dxI;
  global_pos[1] += dyI;
  global_pos[2] += a; 
} 

void pen_lift(int pose){
  if(pose){servo_angle(5, 10 * 90);}  // lefts servo
  else{servo_angle(5, 10 * 45);}      // lowers servo
} 




