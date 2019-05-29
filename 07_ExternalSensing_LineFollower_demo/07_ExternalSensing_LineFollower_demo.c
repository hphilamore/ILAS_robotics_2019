//--------------------------------------------------------------------------------------------------
// Button press 1 : Calibrate for light surface
// Button press 2 : Calibrate for dark surface
// Button press 3 : Follow a dark color line on a light surface using binary controller
//--------------------------------------------------------------------------------------------------

#include "simpletools.h" 
#include "s3.h" 
#include "encoder.h"

// Functions
void Calibrate(char colour);
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

    Calibrate( "w" );
  }
  
  if (s3_resetButtonCount() == 2) {

    Calibrate( "b" );
  }  
  
  if (s3_resetButtonCount() == 3) {

    LineFollowBinary();  
  } 
  
  
  if (s3_resetButtonCount() == 4) {

    LineFollowProp();  
  } 
 
}


void Calibrate(char colour){
  // Calibrate IR line sensors 
  // colour = "w" (white) or "b" (black)
  
  int left = 0;                              // variables for IR sensor values      
  int right = 0;
  int count = 0;
  
  int bot_diameter = 145;                    // distance between two drive wheels 
  
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
  
  if( colour == "w" ){
    s3_memoryWrite(1, L_ave);      // store in non-volatile memory 
    s3_memoryWrite(2, R_ave);
  }
  else if( colour == "b" ){
    s3_memoryWrite(3, L_ave);      // store in non-volatile memory 
    s3_memoryWrite(4, R_ave);
  }    
 
}  



void LineFollowBinary(void){
      // line following : binary controller
      
      int L_white = s3_memoryRead(1);                      // stored average IR sensor calibration values
      int R_white = s3_memoryRead(2);
      int L_black = s3_memoryRead(3);
      int R_black = s3_memoryRead(4);
      
      int mid_left = (L_white - L_black) / 2;              // midpoint between black and white
      int mid_right = (R_white - R_black) / 2;
      
      int v_basic = 30;                                    // basic speed
      
      while(1){
          
        print("%d, %d \n", s3_lineSensor(S3_LEFT), s3_lineSensor(S3_RIGHT));
        print("%d, %d \n", mid_left, mid_right);
        
        if(s3_lineSensor(S3_LEFT) > mid_left && s3_lineSensor(S3_RIGHT) < mid_right){       // left=white, right=black --> turn right
          s3_motorSet(40, -20, 0);
          pause(200);}
        
        else if(s3_lineSensor(S3_RIGHT) > mid_right && s3_lineSensor(S3_LEFT) < mid_left){  // left=black, right=white --> turn left
          s3_motorSet(-20, 40, 0);
          pause(200);}
         
        else{                              // left = right = white/black --> go straight
          s3_motorSet(v_basic, v_basic, 0);     
          pause(200);}
      
      } 
}


void LineFollowProp(){
      
  // Calculate black / white threshold value
  // Change the memory locations to those used in your program
  int L_white = s3_memoryRead(1);
  int R_white = s3_memoryRead(2);
  int L_black = s3_memoryRead(3);
  int R_black = s3_memoryRead(4);
  
  int V_min = 30;
  
  while(1){
  
    // Write code : Calculate right and left error
    int err_R = s3_lineSensor(S3_RIGHT) - R_black; 
    int err_L = s3_lineSensor(S3_LEFT) - L_black;
    
    // Write code : Calculate right and left velocity
    int vel_L = mapInt(err_R, 0, R_white - R_black, 30, 100);
    int vel_R = mapInt(err_L, 0, L_white - L_black, 30, 100);
    
    // Write code : Set motor speed
    s3_motorSet(vel_L, vel_R, 0);
    
    /*
    if(s3_lineSensor(S3_LEFT) > mid_left && 
       s3_lineSensor(S3_RIGHT) < mid_right){          // left=white, right=black --> turn right
          s3_motorSet(v_L, -v_L/2, 0);
          pause(200);}
    else if(s3_lineSensor(S3_RIGHT) > mid_right && 
            s3_lineSensor(S3_LEFT) < mid_left){     // left=black, right=white --> turn left
               s3_motorSet(-v_R/2, v_R, 0);
               pause(200);}
    else{                                                                                  // left = right = white/black --> go straight
      s3_motorSet(v_min, v_min, 0);
      pause(200);}
      */
    
  }
}


