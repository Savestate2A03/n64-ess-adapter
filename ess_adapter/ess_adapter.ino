// N64 Communication Libraries by Andrew Brown
// Check files for their respective licenses.

// Adapter math by Savestate aka Joseph El-Khouri

#include "pins_arduino.h"
#include "N64Controller.h"
#include "N64Communication.c"
#include <math.h>

///////////////////////////////////////////

/* SET THESE TO CUSTOMIZE YOUR SETTINGS! */

   #define MY_ESS_POSITION 40
   #define MY_MAX_POSITION 62

///////////////////////////////////////////

#define OOT_ESS 26     // OoT ESS position
#define OOT_MAX 67     // anything higher than this is treated as 67 by OoT
#define N64_MAX 127    // N64 max (ignoring 128)

N64Controller n64c (10); // This controller for player one is on PIN 10
                         // N64Communication.h has N64 pin on PIN 8
                         
void setup()
{
  n64c.begin(); // Initialisation
  n64_init();
}

void ess_map(char* x_axis, char* y_axis, double ess_threshold, double max_threshold) {
  // place both axes into an array for easier handling
  
  char* axes[] = {x_axis, y_axis};
  double temp_axes[2]; // writing new values here 
  
  for(int axis = 0; axis < 2; axis++) {
    double axis_value = ((double)*axes[axis]);
    bool negative = (axis_value < 0);
    axis_value = abs(axis_value);
    if (axis_value <= ess_threshold) {
      // if we're under our new ess threshold, map
      // all the values between zero and it to zero
      // and OOT_ESS (aka 26)
      temp_axes[axis] = (axis_value/ess_threshold) * OOT_ESS;
    } else if (axis_value <= max_threshold) {
      // same thing as before except we're mapping
      // a sub range to new values. we offset our 
      // axis value first to make the math way easier
      double new_range = max_threshold - ess_threshold;
      axis_value -= ess_threshold; 
      temp_axes[axis] = (axis_value/new_range) * (OOT_MAX-OOT_ESS) + OOT_ESS;
    } else {
      // exact same idea as above but for the max threshold
      double new_range = N64_MAX - max_threshold;
      axis_value -= max_threshold; 
      temp_axes[axis] = (axis_value/new_range) * (N64_MAX-OOT_MAX) + OOT_MAX;
    }
    // cheap hack to make the math WAY easier
    if (negative) temp_axes[axis] *= -1.0;
    *axes[axis] = (char)round(temp_axes[axis]); // final conversion
  }
}

// Prepare the data to send to the N64
// n64_buffer is defined in N64Communication.h
void buffer_setup() {
  char x = n64c.axis_x();
  char y = n64c.axis_y();
  ess_map(&x, &y, MY_ESS_POSITION, MY_MAX_POSITION);
  // translating between the two libraries
  n64_buffer[0] =    n64c.A() << 7 |      n64c.B() << 6 |      n64c.Z() << 5 | n64c.Start() << 4 |
                  n64c.D_up() << 3 | n64c.D_down() << 2 | n64c.D_left() << 1 | n64c.D_right();
  n64_buffer[1] =                                                    n64c.L() << 5 |     n64c.R() << 4 | 
                  n64c.C_up() << 3 | n64c.C_down() << 2 | n64c.C_left() << 1 | n64c.C_right();
  n64_buffer[2] = x;
  n64_buffer[3] = y;
}

void loop() {
    n64c.update();      // get controller inputs
    buffer_setup();     // process controller inputs 
    n64_command_wait(); // block for N64 to send controller inputs
}
