/*****************************************************************************
* FILENAME:     pid.h
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

#ifndef _PID_H_
#define _PID_H_

// Libraries included
#include <stdint.h>

// Default PID structure
typedef struct{
	float kp; //proportional gain
	float ki; //integral gain
	float kd; //derivative gain
	int16_t pre_error; //previous error for calculation of slope
	float integral;	//sum of integral gain to this point
	float dt; //change in time between each loop of the PID algorithm	
	} pid_t;

// Variables needed for PID controller
float derivative;
float error;

// Functions
float calc_pid( pid_t pid, int16_t target, int16_t actual );

#endif /* _PID_H_ */
