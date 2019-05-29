/*
Demonstrates basic motion capabilities of the scribbler robot.
*/

#include "simpletools.h" 
#include "s3.h" 


int main()                                    
{
  s3_setup();
  
  // "hello world" example
  if (s3_resetButtonCount() == 1) {  
  
    print("Hello World!");
    
  }
  
  // Move in a straight line
  if (s3_resetButtonCount() == 2) {  
  
    s3_motorSet(100, 100, 5000);
    
  }
  
  // Turn on the spot
  if (s3_resetButtonCount() == 3) {  
  
    s3_motorSet(100, -100, 5000);
    
  }
  
  
  // Arc Turn 
  if (s3_resetButtonCount() == 4) {  
    // Method 1 : Rotates clockwise
    //s3_motorSet(100, 50, 5000);
    
    // Method 2 : s3_motorSetRotate(	degrees, radius, max_speed)
    // 90 degrees clockwise, driving forwards
    s3_motorSetRotate(	90, 300, 75);
    
    // -90 degrees clockwise, driving backwards
    s3_motorSetRotate(	-90, 300, 75);
    
    // 90 degrees counter-clockwise, driving forwards
    s3_motorSetRotate(	90, -300, 75);

    // -90 degrees counter clockwise, driving backwards
    s3_motorSetRotate(	-90, -300, 75);
    
    
  }
  
  // Turn about one wheel
  if (s3_resetButtonCount() == 5) {  
  
    s3_motorSet(100, 0, 5000);
    
  }
  
  // Draw a triangle
  if (s3_resetButtonCount() == 6) {  
  
    for( int x = 0; x < 3; x++ ){ 
      int F = 1000 / 491;
      s3_motorSetDistance( 300 * F, 300 * F, 75);
      s3_simpleSpin(120, 75, 0); 
    }  
  }

}




