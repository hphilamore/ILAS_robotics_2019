#include "simpletools.h" // Include simpletools
#include "s3.h" 
#include "encoder.h"
//#include "servo.h"

float global_pos[3] = {0, 0, 0}; 



float sgn(float v) {
  if      (v < 0){ return -1; }
  else if (v > 0){ return 1; }
  else           { return 0; }
  return 0;
}

/*
void GoToGoal(float dxI, float dyI, float th_i, int basic_speed){
  
  // Drives the robot by turning on the spot then driving in a straight line.  
  // dxI : x distance to goal, global frame
  // dyI : y distance to goal, global frame
  // th_f : final angle of orientation, global frame
  // th_i : initial angle of orientation, global frame 
  
  int turn_flag = 0;
  int straight_flag = 0;
  
  // convert goal global --> local
  float dxR = dxI * cos(th_i) + dyI * sin(th_i);
  float dyR = dxI * -sin(th_i)+ dyI * cos(th_i); 
  
  // plan path
  float a1 = atan2(dyR, dxR);                           // angle
  float len_a1 = a1 * L / 2;                             // convert angle to arc of wheel travel
  
  float d = powf((powf(dxR,2) + powf(dyR,2)), 0.5);    // distance               
  
  float left_count_start = dist_left;
   
  while(1){
    if(turn_flag == 0){   // turn to angle
    s3_motorSet(-sgn(a1)*basic_speed, 
                sgn(a1)*basic_speed, 
                0);
    if(fabs(dist_left - left_count_start) >= fabs(len_a1)){       // angle reached
      turn_flag = 1;                                              // put the flag up
      left_count_start = dist_left;}                              // reset the count
    } // if 
    
    
    else if(straight_flag == 0){  // drive to goal                             
      s3_motorSet( basic_speed, 
                   basic_speed, 
                   0);               
      if(fabs(dist_left - left_count_start) >= fabs(d)){ // goal reached
        straight_flag = 1;                               // put the flag up
        left_count_start = dist_left;
      } 
    } // else if
    
    
    else if(straight_flag == 1){
      s3_motorSet(0, 0, 0); 
      break;} 
  
  }// while 
  
  // update position
  global_pos[0] += dxI;
  global_pos[1] += dyI;
  global_pos[2] += a1;
} 
*/


void GoToGoal(float dxI, float dyI, float th_i, int basic_speed){
  
  // Drives the robot by turning on the spot then driving in a straight line.  
  // dxI : x distance to goal, global frame
  // dyI : y distance to goal, global frame
  // th_f : final angle of orientation, global frame
  // th_i : initial angle of orientation, global frame 
  
  int turn_flag = 0;
  int straight_flag = 0;
  
  // convert goal global --> local
  float dxR = dxI * cos(th_i) + dyI * sin(th_i);
  float dyR = dxI * -sin(th_i)+ dyI * cos(th_i); 
  
  // plan path
  float a1 = atan2(dyR, dxR);                           // angle
  float len_a1 = a1 * L / 2;                             // convert angle to arc of wheel travel
  
  float d = powf((powf(dxR,2) + powf(dyR,2)), 0.5);    // distance               
  
  float left_count_start = dist_left;
   
  //while(1){
    //if(turn_flag == 0){   // turn to angle
    s3_motorSet(-sgn(a1)*basic_speed, 
                sgn(a1)*basic_speed, 
                0);
    //if(fabs(dist_left - left_count_start) >= fabs(len_a1)){       // angle reached
    while(fabs(dist_left - left_count_start) <= fabs(len_a1)){       // angle reached
        //print("%f \n", dist_left);
        //print("\t");
      //turn_flag = 1;                                              // put the flag up
      //left_count_start = dist_left;}                              // reset the count
    } // if 
    
    
    //else if(straight_flag == 0){  // drive to goal                             
      s3_motorSet( basic_speed, 
                   basic_speed, 
                   0);               
      while(fabs(dist_left - left_count_start) <= fabs(d)){ // goal reached
      //if(fabs(dist_left - left_count_start) >= fabs(d)){ // goal reached
        //straight_flag = 1;                               // put the flag up
        //left_count_start = dist_left;
      } 
    //} // else if
    
    
    //else if(straight_flag == 1){
      //s3_motorSet(0, 0, 0); 
      //break;} 
  
  //}// while 
  
  // update position
  global_pos[0] += dxI;
  global_pos[1] += dyI;
  global_pos[2] += a1;
} 
/*
void pen_lift(int pose){
  // 1 lowers pen (write)
  // 0 lifts pen (no write)
  if(pose){servo_angle(0, 10 * 90);}
  else{servo_angle(0, 10 * 45);}
} 
*/ 