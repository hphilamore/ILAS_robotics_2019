//--------------------------------------------------------------------------------------------------
// Button press 1 : Calibrate for light surface
// Button press 2 : Calibrate for dark surface
// Button press 3 : Follow a dark color line on a light surface using a binary controller
// Button press 4 : Follow a dark color line on a light surface using a proportional controller
//--------------------------------------------------------------------------------------------------

#include "simpletools.h" 
#include "s3.h" 
#include "encoder.h"

// Constants
# define PI 3.14159265358979323846
# define bot_diameter 145
# define white 0
# define black 1

// Functions
void Calibrate(int colour);
void LineFollowBinary(void);
void LineFollowProp(void);


int main()                                   
{
  // Startup code 
  s3_setup();
  cog_run(encoder_update_cog, 65); 
 
  /*
  while(1)
  {
    print("%d, %d \n", s3_lineSensor(S3_LEFT), s3_lineSensor(S3_RIGHT));
  } 
  */

  if (s3_resetButtonCount() == 1) {

    Calibrate( white );
  }
  
  if (s3_resetButtonCount() == 2) {

    Calibrate( black );
  }  
  
  if (s3_resetButtonCount() == 3) {

    LineFollowBinary();  
  } 
  
  
  if (s3_resetButtonCount() == 4) {

    LineFollowProp();  
  } 
 
}


void Calibrate(int colour){
  // Calibrate IR line sensors 
  // colour = "w" (white) or "b" (black)
  
  int left = 0;                              // variables for IR sensor values      
  int right = 0;
  int count = 0;
  
  float left_count_start = dist_left;        // left encoder count at start 
  
  // turn until full circle reached
  while(fabs(dist_left - left_count_start) < bot_diameter * 3.142){     
    
    s3_motorSet(-75, 75, 0);                 
    left += s3_lineSensor(S3_LEFT);         // cumulative sum left IR sensor
    right += s3_lineSensor(S3_RIGHT);       // cumulative sum right IR sensor
    print( "%d \t", s3_lineSensor(S3_LEFT) );
    print( "%d \n", s3_lineSensor(S3_RIGHT) );
    count += 1;                             // cumulative sum while loops
  }
  s3_motorSet(0, 0, 0);                     // stop moving         
  
  int L_ave = left/count;                   // average left IR sensor
  int R_ave = right/count;                  // average right IR sensor
  
  print( "\n" );
  print( "%d \t", left );
  print( "%d \n", right );
  print( "%d \n", count );
  print( "%d \t", L_ave );
  print( "%d \n", R_ave );
  
  if( colour == white ){
    s3_memoryWrite(1, L_ave);      // store in non-volatile memory 
    s3_memoryWrite(2, R_ave);
  }
  else if( colour == black ){
    s3_memoryWrite(3, L_ave);      // store in non-volatile memory 
    s3_memoryWrite(4, R_ave);
  }    
 
}  



void LineFollowBinary(void){
  // line following : binary controller
  
  // Average left and right sensor readings 
  int L_white = s3_memoryRead(1);                      // stored average IR sensor calibration values
  int R_white = s3_memoryRead(2);
  int L_black = s3_memoryRead(3);
  int R_black = s3_memoryRead(4);
  
  int mid_left = (L_white + L_black) / 2;              // midpoint between black and white
  int mid_right = (R_white + R_black) / 2;
  
  while(1){
    print("%d, %d \n", s3_lineSensor(S3_LEFT), s3_lineSensor(S3_RIGHT));
    print("%d, %d \n", mid_left, mid_right);
    print( "%d , %d, %d, %d \n \n", L_white, R_white, L_black, R_black );
    
    if(s3_lineSensor(S3_LEFT) > mid_left && s3_lineSensor(S3_RIGHT) < mid_right){       // left=white, right=black --> turn right
      s3_motorSet(40, -20, 0);
      s3_setLED(S3_LEFT, S3_COLOR_FF7F00);     s3_setLED(S3_CENTER, S3_COLOR_000000 );     s3_setLED(S3_RIGHT, S3_COLOR_000000); 
      pause(200);}
    
    else if(s3_lineSensor(S3_RIGHT) > mid_right && s3_lineSensor(S3_LEFT) < mid_left){  // left=black, right=white --> turn left
      s3_motorSet(-20, 40, 0);
      s3_setLED(S3_LEFT, S3_COLOR_000000 );     s3_setLED(S3_CENTER, S3_COLOR_000000 );     s3_setLED(S3_RIGHT, S3_COLOR_FF7F00); 
      pause(200);}
     
    else{                              // left = right = white/black --> go straight
      s3_motorSet(30, 30, 0); 
      s3_setLED(S3_LEFT, S3_COLOR_000000 );     s3_setLED(S3_CENTER, S3_COLOR_FF7F00 );     s3_setLED(S3_RIGHT, S3_COLOR_000000);     
      pause(200);}
  
  } 
}



void LineFollowProp(){
  // line following : proportional controller
      
  // Average left and right sensor readings 
  int L_white = s3_memoryRead(1);
  int R_white = s3_memoryRead(2);
  int L_black = s3_memoryRead(3);
  int R_black = s3_memoryRead(4);
  
  int mid_left = (L_white + L_black) / 2;              // midpoint between black and white
  int mid_right = (R_white + R_black) / 2;
  
  int v_min = 30;
  
  while(1){
  
    // Calculate right and left error
    int err_R = s3_lineSensor(S3_RIGHT) - R_black; 
    int err_L = s3_lineSensor(S3_LEFT) - L_black;
    
    // Calculate right and left velocity
    int v_L = mapInt(err_R, 0, R_white - R_black, v_min, 75);
    int v_R = mapInt(err_L, 0, L_white - L_black, v_min, 75);
    
    print("%d, %d \n", s3_lineSensor(S3_LEFT), s3_lineSensor(S3_RIGHT));
    print("%d, %d \n", mid_left, mid_right);
    
    if(v_L < v_min){ v_L = v_min; }
    if(v_R < v_min){ v_R = v_min; }
    if(v_L > 75){ v_L = 75; }
    if(v_R > 75){ v_R = 75; }
    
    print("%d, %d \n \n", v_L, v_R);
    
    
    if(s3_lineSensor(S3_LEFT) > mid_left &&          // left=white, right=black --> turn right
       s3_lineSensor(S3_RIGHT) < mid_right){          
          s3_motorSet(v_L, -v_L/2, 0);
          s3_setLED(S3_LEFT, S3_COLOR_FF7F00 );     s3_setLED(S3_CENTER, S3_COLOR_000000 );     s3_setLED(S3_RIGHT, S3_COLOR_000000); 
          pause(200);
          }
    else if(s3_lineSensor(S3_RIGHT) > mid_right &&   // left=black, right=white --> turn left
            s3_lineSensor(S3_LEFT) < mid_left){     
               s3_motorSet(-v_R/2, v_R, 0);
               s3_setLED(S3_LEFT, S3_COLOR_000000 );     s3_setLED(S3_CENTER, S3_COLOR_000000 );     s3_setLED(S3_RIGHT, S3_COLOR_FF7F00 ); 
               pause(200);}
    else{                                            // left = right = white/black --> go straight
      s3_motorSet(v_min, v_min, 0);
      s3_setLED(S3_LEFT, S3_COLOR_000000 );     s3_setLED(S3_CENTER, S3_COLOR_FF7F00  );     s3_setLED(S3_RIGHT, S3_COLOR_000000); 
      pause(200);}
      
     
  }
}


