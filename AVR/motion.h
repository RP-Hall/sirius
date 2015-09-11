#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
#include "roboservo.h"
#include "dynamixel.h"

#ifndef _motion_H
#define _motion_H

#define BASE_ANGLE_YAW5 -1
#define BASE_ANGLE_YAW6 1
#define BASE_ANGLE_YAW7 0
#define BASE_ANGLE_YAW8 -1
#define BASE_ANGLE_CUT1 -9
#define BASE_ANGLE_CUT3 0
#define BASE_ANGLE_CUT9 0
#define BASE_ANGLE_CUT11 0
#define BASE_ANGLE_NOTCH2 -7
#define BASE_ANGLE_NOTCH4 -6
#define BASE_ANGLE_NOTCH10 -10
#define BASE_ANGLE_NOTCH12 -5

#define SAFE_ANGLE 30

void move_bot();

void go_to_safe_angle();

void go_to_base_yaw();

void go_to_base_dynamixel();

void go_to_base_cut();

void go_to_base_notch();

void move_wheel_angle(char id_leg,int yaw, int cut_angle, int notch_angle);

void update_wheel_angle(char id_leg,int yaw, int cut_angle, int notch_angle,int dyn_angle);

void open_wheel();

void close_wheel();

#endif