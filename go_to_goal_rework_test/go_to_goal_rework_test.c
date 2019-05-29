#include "simpletools.h" // Include simpletools
#include "s3.h" 
#include "scribbler.h"
#include "math.h"
//#include "servo.h"

#include "encoder.h"
#include "go_to_goal.h"

// functions
void encoder_update_cog(void); 

// constants
#define pi 3.14159265358979323846
#define L 145 // Length between robot wheel centres
/*
int start_time_ms; 
int time_ms;
int old_time_ms;  
int time_inc;
*/





//volatile float left_vel;
//volatile float right_vel;



// variables
//static float encoder_vals[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; 

int main()                                    // Main function
{
  s3_setup();
  cog_run(encoder_update_cog, 65); 
  //float count = 0.0;
  
  //float x_pos[] = {100, 100, 0, 100, 300, 300};
  //float y_pos[] = {0, 100, 100, 200, 200, 100};

  float x_pos[] = {40, 40, 40, 100, 100, 100, 160, 160, 200, 200, 160, 160, 200};
  float y_pos[] = {0, 100, 50, 50,  100, 0,   0,   100, 100, 50,  50,  0,   0 }; 
  //int mark[]    = {0, 1,   1,  1,   1,   1,   0,   1,   1,   0,   1,   1,   1 }; 
  
  if (s3_resetButtonCount() == 1) {
  //start_time_ms = CNT/st_msTicks;
  //time_ms = CNT/st_msTicks;
  //old_time_ms = CNT/st_msTicks;
  
  
  /*
  s3_motorSet(-75, 75, 0);

      //while(time_ms - start_time_ms < 2000){
      while(fabs(dist_left) < 227.76){
        
        //time_ms = CNT/st_msTicks;
        //time_inc = time_ms - old_time_ms;
        
        print("%d \t", time_ms - start_time_ms);

        
        print("%f", dist_left);
        print("\t");
        print("%f", dist_right);
        print("\t");
        print("%f", vel_left);
        print("\t");
        print("%f", vel_right);
        print("\n");
        
        //old_time_ms = time_ms;

      } 
      s3_motorSet(0, 0, 0);
      */
  /*     
  GoToGoal(300, 400, pi/2, 50);
  */
  

  for(int i=0; i<13; i++){ 
  
    //pen_lift(mark[i]);
    s3_motorSet(50, 0, 0);
     
    /* 
    GoToGoal(x_pos[i] - global_pos[0], 
             y_pos[i] - global_pos[1], 
             global_pos[2], 
             50);
             */
             
    GoToGoal2(x_pos[i], 
             y_pos[i], 
             global_pos[2], 
             50);
             
    print("%f", dist_left);
    print("\t"); 
    } 
         
        
         //print("\t");
        //print("%f", global_pos[0]);
        //print("\t");
        //print("%f", global_pos[1]);
        //print("\t"); 
        
        
}

s3_motorSet(0, 0, 0);

//print("\t");

}

/*
void StallAvoid(int speed){
  // escape maneuver if stall detected
    float left_start = dist_left;
    float right_start = dist_right;
    float local_pos[3] = {0, 0, 0};
    
    if (!s3_tailWheelMoving()) {
      print("Stalled \n");
      s3_motorSet(-speed, -speed, 1500);   // move backwards
      
      // update local coords
      local_pos[0] = (dist_left - left_start) / 2;
      local_pos[2] = (dist_right - right_start) / L;
      
      // reset counter 
      left_start = dist_left;
      right_start = dist_right;
      
      
      //s3_simpleSpin(90, basic_speed, 0);               // quarter clockwise turn
      while( dist_left - dist_start < (pi * 145 / 4)){
              s3_motorSet(speed, -speed, 0);
            }
            
      // update local coords
      local_pos[0] += (dist_left - left_start) / 2;
      local_pos[2] += (dist_right - right_start) / L;
      
      // global coords
      global_pos[0] = local_pos[0] * cos((global_pos[2] + local_pos[2])/2);
      global_pos[1] = local_pos[0] * -sin((global_pos[2] + local_pos[2])/2);
      global_pos[2] += local_pos[2];
      
    }
    else
    {
      print("Not Stalled \n");
    }
}
*/ 






