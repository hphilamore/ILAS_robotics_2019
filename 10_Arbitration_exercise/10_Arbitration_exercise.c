//--------------------------------------------------------------------------------------------------
// Button press 1 : Calibrate for light surface
// Button press 2 : Calibrate for dark surface
// Button press 3 : Subsumption architecture : Light follower. 
//                  Follow light. If brightest light cannot be detected, hunt light by turning on the spot        
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


float hunt_left_count_start;
float left_count_start;
int SenseLightLeft;
int SenseLightRight;
int SenseLightFront;
int SenseLightFront_A;
int FullTurnComplete;

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



void resetHuntLight(void);
void resetTurnFromLine(void);
void arbitrate(void);
void sense(void);
void Calibrate(int colour);



int main()                                    // Main function
{
  s3_setup();
  cog_run(encoder_update_cog, 65);
  resetHuntLight();
  
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
  FullTurnComplete = fabs(dist_left - left_count_start) > bot_diameter * PI;
  SenseLightLeft = s3_simpleLight(S3_IS, SCRIBBLER_LEFT);
  SenseLightRight = s3_simpleLight(S3_IS, SCRIBBLER_RIGHT);
  SenseLightFront = s3_simpleLight(S3_IS, SCRIBBLER_CENTER);
  SenseLightFront_A = s3_lightSensor(SCRIBBLER_CENTER);
} 



void arbitrate(){ 
  // Follow light. If brightest light cannot be detected, turn on the spot

  // if (!FullTurnComplete)
  v_L = speed;    
  v_R = -speed;
  readout = "Hunting Light"; 
  
  if( FullTurnComplete ){
      resetHuntLight();
      readout = "Hunt light reset";} 
  
  if( SenseLightFront ){
      int motor_speed = mapInt(SenseLightFront_A, 
                               0, 255, 100, 0);
      v_L = motor_speed;    
      v_R = motor_speed;
      readout = "Light Front"; }  
  
  if( SenseLightRight ){
      v_L = speed;    
      v_R = -speed;
      readout = "Light Right"; } 
  
  if( SenseLightLeft ){
      v_L = -speed;    
      v_R = speed;
      readout = "Light Left"; }  
  
  s3_motorSet(v_L, v_R, 0);
  print("%s\n", readout); 
}  



void resetHuntLight(void){
  // Resets the random walk distances
    hunt_left_count_start = dist_left;   // left encoder count at start 
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




