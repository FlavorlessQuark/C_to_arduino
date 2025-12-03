#ifndef _ARM_H
# define _ARM_H

#include "IK.h"
# define SERVO_Z 1
# define SERVO_JOINT_1 2
# define SERVO_JOINT_2 3
# define SERVO_JAW 4
# define SERVO_JAW_ROTATE 5

typedef struct Servo_Component
{
    Servo servo;
    int last_angle;
}               Servo_Component;


#endif
