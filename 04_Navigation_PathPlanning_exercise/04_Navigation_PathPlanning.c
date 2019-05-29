#include "simpletools.h" // Include simpletools#include "s3.h" #include "scribbler.h"#include "math.h"#include "encoder.h"// constants#define pi 3.14159265358979323846#define L 145 // Length between robot wheel centres // variablesfloat global_pos[3] = {0, 0, 0};float x_pos[] = {100, 200, 400, 450}; float y_pos[] = {200, 100, 170, 130};int nElements = sizeof(x_pos)/sizeof(x_pos[0]);// functionsfloat quad_angle(float angle);float sgn(float v);void GoToGoal(float xI, float yI, int speed);int main()                                    {  s3_setup();  cog_run(encoder_update_cog, 65);   if (s3_resetButtonCount() == 1) {     for(int i=0; i<nElements; i++){                                  GoToGoal(x_pos[i],                y_pos[i],                50);}                    }   s3_motorSet(0, 0, 0);}float quad_angle(float angle) {  if      (angle < -pi){ return angle + ( 2 * pi ); }  else if (angle > pi) { return angle - ( 2 * pi ); }  else                 { return angle; }}float sgn(float v) {  if      (v < 0){ return -1; }  else if (v > 0){ return 1; }  else           { return 0; }  return 0;}void GoToGoal(float xI, float yI, int speed){    // Drives the robot to a goal by turning on the spot then driving in a straight line.    // xI : x distance to goal, global frame  // yI : y distance to goal, global frame  // speed : robot linear velocity    // cartesian -> polar  // global -> local            // move  // update position}