
#include "simpletools.h" // Include simpletools
#include "s3.h" 
#include "encoder.h"
//#include "scribbler.h"
//#include "math.h"
//#include "servo.h"

//float encoder_vals[4] = {0, 0, 0, 0}; 

// constants
const float pi = 3.14159265358979323846;
const int L = 145; // Length between robot wheel centres


int encoder_start_time_ms; 
int encoder_time_ms;
int encoder_old_time_ms;  
int encoder_time_inc;

float dist_left;
float dist_right;
float vel_left;
float vel_right;
/*
float vel_left_;
float vel_right_;
float dist_left_;
float dist_right_;
*/

void encoder_update_cog(void) { 

    encoder_start_time_ms = CNT/st_msTicks;
    encoder_time_ms = CNT/st_msTicks;
    encoder_old_time_ms= CNT/st_msTicks;
  
      while(1){  
      // vel_left : velcoity of the left wheel in arbitrary unit
      // vel_right : velcoity of the right wheel in arbitrary unit 
      // dist_left : cumulative distance travelled by the left wheel
      // dist_right : cumulative distance travelled by the right wheel
      
      encoder_time_ms = CNT/st_msTicks;
      encoder_time_inc = encoder_time_ms - encoder_old_time_ms; 
      encoder_old_time_ms = encoder_time_ms; 
  
      int32_t value = scribbler_motion();
      
      //encoder_vals[0] = (value >> 24);// * 0.25;  //new 1 
      //vel_left = (value >> 24); // 0.00269;  //new 1            
      vel_left = (value >> 24) * 0.00252;
      
      int32_t e1 = (value >> 16) & 0xff; 
      if(e1 > 100){e1 -= 256;}       // if number has over-flowed subtract max value to make it a negative number           
      //vel_right = e1; // 0.00269;   //new 
      vel_right = e1 * 0.00252;
      
      //encoder_vals[2] += encoder_vals[0] * encoder_time_inc; 
      
      //encoder_vals[3] += encoder_vals[1] * encoder_time_inc; 
      
      //dist_left += vel_left * encoder_time_inc * 0.00252;  
      
      //dist_right += vel_right * encoder_time_inc * 0.00252;   
      
      dist_left += vel_left * encoder_time_inc;
      
      dist_right += vel_right * encoder_time_inc; 
      
      
      
      //encoder_old_time_ms = encoder_time_ms;
      pause(100);

  }                 

}