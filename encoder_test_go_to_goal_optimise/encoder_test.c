//#include "simpletools.h" // Include simpletools
//#include "s3.h" 
#include "scribbler.h"
#include "math.h"
//#include "servo.h"

//#include "encoder.h"
#include "move.h"

// functions
void encoder_update_cog(void); 

int main()                                    // Main function
{
  s3_setup();
  cog_run(encoder_update_cog, 65); 

  float x_pos[] = {40, 40, 40, 100, 100, 100, 160, 160, 200, 200, 160, 160, 200};
  float y_pos[] = {0, 100, 50, 50,  100, 0,   0,   100, 100, 50,  50,  0,   0 }; 
  int mark[]    = {0, 1,   1,  1,   1,   1,   0,   1,   1,   0,   1,   1,   1 }; 
  
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
     
    GoToGoal(x_pos[i] - global_pos[0], 
             y_pos[i] - global_pos[1], 
             global_pos[2], 
             50);
    
         } 
         //print("\t");
         
        //print("%f", global_pos[0]);
        //print("\t");
        //print("%f", global_pos[1]);
        //print("\t");          
     
}

//print("\t");

}




