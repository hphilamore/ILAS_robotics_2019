#include "simpletools.h" // Include simpletools
#include "s3.h" 
#include "scribbler.h"
#include "math.h"
#include "servo.h"

//#include "encoder.h"

// functions
void encoder_update_cog(void); 

// constants
#define pi 3.14159265358979323846
#define L 145 // Length between robot wheel centres


int start_time_ms; 
int time_ms;
int old_time_ms;  
int time_inc;

volatile int encoder_start_time_ms; 
volatile int encoder_time_ms;
volatile int encoder_old_time_ms;  
volatile int encoder_time_inc;

volatile float left_vel;
volatile float right_vel;
volatile float left_dist;
volatile float right_dist;

// variables
static float encoder_vals[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; 

int main()                                    // Main function
{
  s3_setup();
  cog_run(encoder_update_cog, 100); 
  float count = 0.0;
  
  if (s3_resetButtonCount() == 1) {
  start_time_ms = CNT/st_msTicks;
  time_ms = CNT/st_msTicks;
  old_time_ms = CNT/st_msTicks;
  
  s3_motorSet(-75, -75, 0);
  //s3_motorSet(0, 0, 0); 
  //s3_enableMic();

      while(time_ms - start_time_ms < 2000){
        
        //encoder_update();
        time_ms = CNT/st_msTicks;
        time_inc = time_ms - old_time_ms;
        count += encoder_vals[7] * time_inc;
        print("%d \t", time_ms - start_time_ms);
        
        
        print("%f", encoder_vals[7]);
        print("\t");
        print("%f", encoder_vals[8]);
        print("\t");
        print("%f", count);
        print("\t");
        print("%f", encoder_vals[0]);
        print("\t");
        print("%f", encoder_vals[1]);
        print("\n");
        
        /* 
        print("%f", left_vel);
        print("\t");
        print("%f", right_vel);
        print("\t");
        //print("%f", count);
        //print("\t");
        print("%f", left_dist);
        print("\t");
        print("%f", right_dist);
        print("\n");
        */
        
        
        //print("%d \n", time_ms - start_time_ms);
        old_time_ms = time_ms;
      
        /*
        print("%d", s3_readMic());
        print("\n");
        */

        //print("%d", s3_readMic());
        //print("\n");
      //encoder_update();
      /*
      print("%d  \t", (value >> 24));
      print("%d  \t", (value >> 16) & 0xff);
      print("%f  \t", encoder_vals[0]); 
      print("%f  \n", encoder_vals[1]);
      */
      

      } 
      s3_motorSet(0, 0, 0);
      
}
}
/*
void encoder_update_cog(void) { 
    while(1){  
    // Value : a 32 bit integer containing registers describig the behavious of drive and idler wheel encoders
    // Updates an array of 9 values
    // 0 Left wheel distance count (mm)
    // 1 Right wheel distance count (mm)
    // 2 Time in 1/10 second since the last idler encoder edge
    // 3 Idler wheel velocity
    // 4 Non-zero if one or more motors are turning.  
    // 5-8 Variables used in encoder calcs     

    
    int32_t value = scribbler_motion();
    
    encoder_vals[7] = (value >> 24) * 0.25;  //new 1           
    //encoder_vals[8] = ((value >> 16) & 0xff) * 0.25;  //new 2
    
    int32_t e1 = (value >> 16) & 0xff; 
    if(e1 > 100){e1 -= 256;}       // if number has over-flowed subtract max value to make it a negative number           
    encoder_vals[8] = e1 * 0.25;   //new 
  
    if (abs(encoder_vals[7]) >= abs(encoder_vals[5])){
      encoder_vals[0] += encoder_vals[7] - encoder_vals[5];
    }
    else {  
      encoder_vals[0] += encoder_vals[7]; 
    }    
    
    if (abs(encoder_vals[8]) >= abs(encoder_vals[6])){
      encoder_vals[1] += encoder_vals[8] - encoder_vals[6];
    }
    else {  
      encoder_vals[1] += encoder_vals[8]; 
    }             
        
    //old = new;
    encoder_vals[5] = encoder_vals[7];  // old1 = new1
    encoder_vals[6] = encoder_vals[8];  // old2 = new2
              
    encoder_vals[2] = (value >> 8)  & 0xff;
             
    encoder_vals[3] = value & 0xfc;
              
    encoder_vals[4] = value & 0x3; 
    
    //print("%d  \t", (value >> 24)); 
    //print("%f  \n", encoder_vals[0]);  
  }                 

}
*/

void encoder_update_cog(void) { 
    encoder_start_time_ms = CNT/st_msTicks;
    encoder_time_ms = CNT/st_msTicks;
    encoder_old_time_ms = CNT/st_msTicks;

    while(1){  
    // Value : a 32 bit integer containing registers describig the behavious of drive and idler wheel encoders
    // Updates an array of 9 values
    // 0 Left wheel distance count (mm)
    // 1 Right wheel distance count (mm)
    // 2 Time in 1/10 second since the last idler encoder edge
    // 3 Idler wheel velocity
    // 4 Non-zero if one or more motors are turning.  
    // 5-8 Variables used in encoder calcs 
    
    encoder_time_ms = CNT/st_msTicks;
    encoder_time_inc = time_ms - old_time_ms;
    //count += encoder_vals[7] * time_inc;    

    
    int32_t value = scribbler_motion();
    
    encoder_vals[8] = (value >> 24);// * 0.25;  //new 1           
    //encoder_vals[8] = ((value >> 16) & 0xff) * 0.25;  //new 2
    
    int32_t e1 = (value >> 16) & 0xff; 
    if(e1 > 100){e1 -= 256;}       // if number has over-flowed subtract max value to make it a negative number           
    encoder_vals[7] = e1;// * 0.25;   //new 
  
    /*
    if (abs(encoder_vals[7]) >= abs(encoder_vals[5])){
      encoder_vals[0] += encoder_vals[7] - encoder_vals[5];
    }
    else {  
    */
    encoder_vals[0] += encoder_vals[7] * encoder_time_inc; 
    //}    
    /*
    if (abs(encoder_vals[8]) >= abs(encoder_vals[6])){
      encoder_vals[1] += encoder_vals[8] - encoder_vals[6];
    }
    else {  
    */
    encoder_vals[1] += encoder_vals[8] * encoder_time_inc; 
    //}             
        
    //old = new;
    //encoder_vals[5] = encoder_vals[7];  // old1 = new1
    //encoder_vals[6] = encoder_vals[8];  // old2 = new2
              
    //encoder_vals[2] = (value >> 8)  & 0xff;
             
    //encoder_vals[3] = value & 0xfc;
              
    //encoder_vals[4] = value & 0x3; 
    
    //print("%d  \t", (value >> 24)); 
    //print("%f  \n", encoder_vals[0]);  
    encoder_old_time_ms = encoder_time_ms;
    //pause(100);
  }                 

}

void encoder_update(void) { 
    //while(1){  
    // Value : a 32 bit integer containing registers describig the behavious of drive and idler wheel encoders
    // Updates an array of 9 values
    // 0 Left wheel distance count (mm)
    // 1 Right wheel distance count (mm)
    // 2 Time in 1/10 second since the last idler encoder edge
    // 3 Idler wheel velocity
    // 4 Non-zero if one or more motors are turning.  
    // 5-8 Variables used in encoder calcs     

    
    int32_t value = scribbler_motion();
    
    right_vel = (value >> 24);// * 0.25;  //new 1           
    //encoder_vals[8] = ((value >> 16) & 0xff) * 0.25;  //new 2
    
    int32_t e1 = (value >> 16) & 0xff; 
    if(e1 > 100){e1 -= 256;}       // if number has over-flowed subtract max value to make it a negative number           
    left_vel = e1;// * 0.25;   //new 
  
    /*
    if (abs(encoder_vals[7]) >= abs(encoder_vals[5])){
      encoder_vals[0] += encoder_vals[7] - encoder_vals[5];
    }
    else {  
    */
    right_dist += right_vel; 
    //}    
    /*
    if (abs(encoder_vals[8]) >= abs(encoder_vals[6])){
      encoder_vals[1] += encoder_vals[8] - encoder_vals[6];
    }
    else {  
    */
    left_dist += left_vel; 
    //}             
        
    //old = new;
    //encoder_vals[5] = encoder_vals[7];  // old1 = new1
    //encoder_vals[6] = encoder_vals[8];  // old2 = new2
              
    //encoder_vals[2] = (value >> 8)  & 0xff;
             
    //encoder_vals[3] = value & 0xfc;
              
    //encoder_vals[4] = value & 0x3; 
    
    //print("%d  \t", (value >> 24)); 
    //print("%f  \n", encoder_vals[0]);  
  //}                 

}

