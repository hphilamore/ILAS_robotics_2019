#include "simpletools.h" // Include simpletools
#include "s3.h" 
#include "scribbler.h"
#include "math.h"
//#include "servo.h"

//#include "encoder.h"
#include "s3move.h"

// functions
//void encoder_update_cog(void); 

// constants
//#define pi 3.14159265358979323846
//#define L 145 // Length between robot wheel centres
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
  
  if (s3_resetButtonCount() == 1) {  
  
  print("%f", sgn(pi));
       
     
}

//;

}




