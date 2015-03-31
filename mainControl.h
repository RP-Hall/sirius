#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>
#include <util/delay.h>
#include "lcd.h"

//Main Function to stop all working on robots
void stop();

//Function that controls main car mode running
void car_mode_run();

//Function to make robot walk
void walk_mode_run();
