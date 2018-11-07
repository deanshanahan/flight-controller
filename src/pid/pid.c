/*****************************************************************************
* FILENAME:     pid.c
*
* AUTHOR :      Dean Shanahan
*
* DESCRIPTION :
*   Library for sending data to the I2C bus of the ATMega328P.
*
* FUNCTIONS :
*   float		i2c_init_master         (pid_t, int16_t, int16_t)
*
* NOTES :
*   -   This code runs a standard PID control algoritm. 
*   -   The differential gain can be harsh so be careful tuning.
*
*/

// Libraries included
#include <stdint.h>
#include "pid.h"

// Implements a simple PID control algorithm
float calc_pid( pid_t pid, int16_t target, int16_t actual )
{
	error = target-actual; //calculate error
	
	pid.integral = pid.integral + (pid.dt*error); //calculate integral
	
	derivative = (error - pid.pre_error)/pid.dt; //calculate slope
	
	pid.pre_error = error; // set previous error for next calculations
	
	// Return output of PID controller
	return((pid.kp*error)+(pid.ki*pid.integral)+(pid.kd*derivative));
}