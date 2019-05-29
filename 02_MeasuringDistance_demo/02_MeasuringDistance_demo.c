// Continuously prints the distance travelled by each wheel in mm
// Demonstrates while loops for executing sequential blocks of code
// NOTE : Only enough running memory to have one program uncommented at a time
// (there is one program per reset button address) 

#include "simpletools.h" 
#include "s3.h" 
#include "encoder.h"


int main()
{
  s3_setup();

  cog_run(encoder_update_cog, 100);

 
        
        // Continuously prints the distance travelled by each wheel in mm
        if (s3_resetButtonCount() == 1) {
          s3_motorSet(75, 75, 0); 
          while(1){ 
            print("%f", dist_left);
            print("\t");
            print("%f", dist_right);
            print("\n");
          }          
        }
        
        
        
        /*
        // Turn by pi/2 rads then stop
        if (s3_resetButtonCount() == 2) { 
          while( dist_left <= 218.0 ){ 
            s3_motorSet(100, 47, 0);
            
            print("%f", dist_left);
            print("\t");
            print("%f", dist_right);
            print("\n");
            
          }
          s3_motorSet(0, 0, 0); 
          print("end");
        }
        */

        
        /*
        // Move forwards then back
        if (s3_resetButtonCount() == 3) {
          
          float dist_start = dist_left;
          while(1){
            while( dist_left - dist_start < 200 ){        
              s3_motorSet(75, 75, 0);
            }

            while( dist_left - dist_start > 0 ){        
              s3_motorSet(-75, -75, 0);
            } 
          }            
        }
        */
        
        /*
        // Move forward and make quarter turn
        if (s3_resetButtonCount() == 4) { 
          //print("hello"); 
          int dist_start = dist_left;
 
          while( dist_left - dist_start < 750 ){        
            s3_motorSet(75, 75, 0);
            //print("%f \n", dist_left - dist_start);
          }

          while( dist_left - dist_start < (750 + 113.88) ){        
            s3_motorSet(75, -75, 0);
            //print("%f \n", dist_left - dist_start);
          } 
        } 
        */

        /*
        // Drive in a square
        if (s3_resetButtonCount() == 5) { 
          float quarter_turn = pi * 145 / 4;
          float dist_start = dist_left;

          for (int i=0; i<4; i++) { 
            
            while( dist_left - dist_start < 750){
              s3_motorSet(75, 75, 0);
            } 
            
            while( dist_left - dist_start < 750 + quarter_turn){
              s3_motorSet(75, -75, 0);
            }               
        
            int dist_start = dist_left;        
          }
          // stop after 4 sides
          s3_motorSet(0, 0, 0);
        } 
        */
        /*
        // Exercise 2 : Movements using encoders and while loops
        if (s3_resetButtonCount() == 6) { 
        
          int dist_start = dist_left;
          float half_turn = pi * 145 / 2;
            
            // Move 20cm forward
            while( dist_left - dist_start < 200){
              s3_motorSet(50, 50, 0);
            } 
            
            // Turn 180 degrees anti-clockwise on the spot
            while( dist_left - dist_start > 200 - half_turn){
              s3_motorSet(-50, 50, 0);
            }
            
            // Arc turn: left wheel travels 10cm forward, right wheel travels 20cm forward
            while( dist_left - dist_start < 200 - half_turn + 100){
              s3_motorSet(50, 100, 0);
            }     
            
            s3_motorSet(0, 0, 0);          
        } 
        */
        
        // Drive in a triangle
        if (s3_resetButtonCount() == 7) { 
          float triangle_turn = pi * 145 / 3;
          int dist_start = dist_left;

          for (int i=0; i<3; i++) { 
            
            while( dist_left - dist_start < 200){
              s3_motorSet(75, 75, 0);
            } 
            
            while( dist_left - dist_start < 200 + triangle_turn){
              s3_motorSet(75, -75, 0);
            } 
            dist_start = dist_left;              
          }
          s3_motorSet(0, 0, 0);
        }
        
        
        /*
        // Drive a set distance or time printing time and distance while driving
        if (s3_resetButtonCount() == 8)   {
          int start_time_ms = CNT/st_msTicks;
          int time_ms = CNT/st_msTicks;
          float start_dist = dist_left;
          
          s3_motorSet(75, 75, 0);

          //while(time_ms - start_time_ms < 2000){
          while(dist_left - start_dist < 500){
            time_ms = CNT/st_msTicks;
            print("%d", time_ms - start_time_ms);
            print("\t");
            print("%f", dist_left);
            print("\t");
            print("%f", dist_right);
            print("\n");
          } 
          s3_motorSet(0, 0, 0);        
       }  
       */        
}





