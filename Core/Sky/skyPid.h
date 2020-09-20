/*
 * skyPid.h
 *
 *  Created on: Sep 17, 2020
 *      Author: RadaR
 */

#ifndef SKYPID_H_
#define SKYPID_H_

//****************************************************************************
//*Include
//****************************************************************************
#include "main.h"
#include "math.h"

/********************************************************************************
 * Class PID controller
 ********************************************************************************/
struct PidController {
		float error;
	    float integralFilter;
	    float derivativeFilter;
	    float proportionalComponent;
	    float integralComponent;
	    float derivativeComponent;
	    float tempPID;
	    float outputPID;

	    	struct {
	            float feedback;
	            float reference;
	            float deltaTimeSampling;

	            struct {
	                float proportional;
	                float integral;
	                float derivative;
	                float coefficientBackSaturation;
	                float filterDerivative;
	            } coefficient;

	            struct {
	                float lowThershold;
	                float highThershold;
	            } saturation;
	        } input;
};

void PidReset(struct PidController *fPid);
void PidSetReference (struct PidController *fPid, float reference);
void PidSetFeedback (struct PidController *fPid, float feedback, float deltaTimeSampling);
void PidSetCoefficient (struct PidController *fPid, float Kp, float Ki, float Kd, float BackSaturation, float filterDerivative);
void PidSetSaturation (struct PidController *fPid, float lowLimit, float highLimit);
void PidCompute(struct PidController *fPid);

#endif /* SKYPID_H_ */
