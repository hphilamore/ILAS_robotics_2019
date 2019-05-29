//--------------------------------------------------------------------------------------------------
// Button press 1 : Calibrate for light surface
// Button press 2 : Calibrate for dark surface
// Button press 3 : Subsumption architecture : Line follower. 
//                  Follow a dark color line on a light surface using a proportional controller 
//--------------------------------------------------------------------------------------------------

#include "simpletools.h"                      // Include simple tools
#include "s3.h" 
#include "encoder.h"

# define PI 3.14159265358979323846
# define bot_diameter 145
# define speed 50
# define white 0
# define black 1

int v_L;
int v_R;
char* readout;
int turn_right;
int turn_left;
int v_min = 30;



// line follower variables
int L_white;                      
int R_white;
int L_black;
int R_black;     
int mid_left;              
int mid_right;



int32_t left_colour;
int32_t center_colour;
int32_t right_colour;


void arbitrate(void);
void sense(void);
void Calibrate(int colour);



int main()                                    // Main function
{
  s3_setup();
  cog_run(encoder_update_cog, 65);
  
  if (s3_resetButtonCount() == 1) {
    // Calibrate IR line sensors for WHITE   
    Calibrate(white);      
  }  
  
  
  if (s3_resetButtonCount() == 2) {
    // Calibrate IR line sensors for BLACK 
    Calibrate(black);     
  }  


  if (s3_resetButtonCount() == 3) {
    
    // stored average IR sensor calibration values
    L_white = s3_memoryRead(1);                      
    R_white = s3_memoryRead(2);
    L_black = s3_memoryRead(3);
    R_black = s3_memoryRead(4);
    // midpoint between black and white
    mid_left = (L_white + L_black) / 2;        
    mid_right = (R_white + R_black) / 2;  
    
   
    while(1)
    {
      sense();
      arbitrate();
      pause(200);
    }  
  }
  
   
     
}


void sense(){
  // Calculate right and left error
    int err_R = s3_lineSensor(S3_RIGHT) - R_black; 
    int err_L = s3_lineSensor(S3_LEFT) - L_black;
    
    // Calculate right and left velocity
    v_L = mapInt(err_R, 0, R_white - R_black, v_min, 75);
    v_R = mapInt(err_L, 0, L_white - L_black, v_min, 75);
    
    print("%d, %d \n", s3_lineSensor(S3_LEFT), s3_lineSensor(S3_RIGHT));
    print("%d, %d \n", mid_left, mid_right);
    
    if(v_L < v_min){ v_L = v_min; }
    if(v_R < v_min){ v_R = v_min; }
    if(v_L > 75){ v_L = 75; }
    if(v_R > 75){ v_R = 75; }
    
    // left=white, right=black --> turn right
    turn_right = (s3_lineSensor(S3_LEFT) > mid_left && s3_lineSensor(S3_RIGHT) < mid_right);         
       
    // left=black, right=white --> turn left  
    turn_left = (s3_lineSensor(S3_RIGHT) > mid_right && s3_lineSensor(S3_LEFT) < mid_left);
       

} 



void arbitrate(){ 
  // Follow light. If brightest light cannot be detected 

  // left == right == black or white --> go straight 
  v_L = v_min;    
  v_R = v_min;
  readout = "Going Straight";
  left_colour = S3_COLOR_000000;     center_colour = S3_COLOR_FF7F00;     right_colour = S3_COLOR_000000 ; 
  
  // left=white, right=black --> turn right
  if( turn_right ){
      v_L = v_L;    
      v_R = - v_L / 2;
      readout = "Turning right";
      left_colour = S3_COLOR_000000 ;     center_colour = S3_COLOR_000000;     right_colour = S3_COLOR_00FF00 ;} 
  
  // left=black, right=white --> turn left 
  if( turn_left ){
      v_L = - v_R / 2;    
      v_R = v_R;
      readout = "Turning left";
      left_colour = S3_COLOR_00FF00 ;     center_colour = S3_COLOR_000000;     right_colour = S3_COLOR_000000 ;}
 
  
  s3_motorSet(v_L, v_R, 0);
  print("%s\n", readout); 
  s3_setLED(S3_LEFT, left_colour );     s3_setLED(S3_CENTER, center_colour );     s3_setLED(S3_RIGHT, right_colour); 
  pause(100);
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
    int v_L = mapInt(err_R, 0, R_white - R_black, 30, 75);
    int v_R = mapInt(err_L, 0, L_white - L_black, 30, 75);
    
    print("%d, %d \n", s3_lineSensor(S3_LEFT), s3_lineSensor(S3_RIGHT));
    print("%d, %d \n", mid_left, mid_right);
    
    if(v_L < 30){ v_L = 30; }
    if(v_R < 30){ v_R = 30; }
    if(v_L > 75){ v_L = 75; }
    if(v_R > 75){ v_R = 75; }
    
    print("%d, %d \n \n", v_L, v_R);
    
    
    if(s3_lineSensor(S3_LEFT) > mid_left &&          // left=white, right=black --> turn right
       s3_lineSensor(S3_RIGHT) < mid_right){          
          s3_motorSet(v_L, -v_L/2, 0);
          s3_setLED(S3_LEFT, S3_COLOR_FF7F00 );     s3_setLED(S3_CENTER, S3_COLOR_000000 );     s3_setLED(S3_RIGHT, S3_COLOR_000000); }
          
    else if(s3_lineSensor(S3_RIGHT) > mid_right &&   // left=black, right=white --> turn left
            s3_lineSensor(S3_LEFT) < mid_left){     
               s3_motorSet(-v_R/2, v_R, 0);
               s3_setLED(S3_LEFT, S3_COLOR_000000 );     s3_setLED(S3_CENTER, S3_COLOR_000000 );     s3_setLED(S3_RIGHT, S3_COLOR_FF7F00 );}    
    else{                                            // left = right = white/black --> go straight
      s3_motorSet(v_min, v_min, 0);
      s3_setLED(S3_LEFT, S3_COLOR_000000 );     s3_setLED(S3_CENTER, S3_COLOR_FF7F00  );     s3_setLED(S3_RIGHT, S3_COLOR_000000); }
    
    pause(200);      
     
  }
}  
  
  

  
void Calibrate(int colour){
  // Calibrate IR line sensors 
  // colour = "w" (white) or "b" (black)
  
  int left = 0;                              // variables for IR sensor values      
  int right = 0;
  int count = 0;
  
  float left_count_start = dist_left;  // left encoder count at start 
  
  // turn until full circle reached
  while(fabs(dist_left - left_count_start) < bot_diameter * 3.142){     
    
    s3_motorSet(-75, 75, 0);                 
    left += s3_lineSensor(S3_LEFT);         // cumulative sum left IR sensor
    right += s3_lineSensor(S3_RIGHT);       // cumulative sum right IR sensor
    print( "%d \t", s3_lineSensor(S3_LEFT) );
    print( "%d \n", s3_lineSensor(S3_RIGHT) );
    count += 1;                             // cumulative sum while loops
  }
  s3_motorSet(0, 0, 0);                  // stop moving         
  
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




