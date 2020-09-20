/*
 * skyPID.cpp
 *
 *  Created on: Sep 17, 2020
 *      Author: RadaR
 */

//****************************************************************************
//*Include
//****************************************************************************
#include "skyPID.h"

//****************************************************************************
//*Code
//****************************************************************************
void PidReset(struct PidController *fPid) {
	fPid->error=0;
	fPid->integralFilter=0;
	fPid->derivativeFilter=0;
	fPid->proportionalComponent=0;
	fPid->integralComponent=0;
	fPid->derivativeComponent=0;
	fPid->tempPID=0;
	fPid->outputPID=0;

	fPid->input.feedback=0;
	fPid->input.reference=0;
	fPid->input.deltaTimeSampling=0;
	fPid->input.coefficient.proportional=0;
	fPid->input.coefficient.integral=0;
	fPid->input.coefficient.derivative=0;
	fPid->input.coefficient.coefficientBackSaturation=0;
	fPid->input.coefficient.filterDerivative=0;

	fPid->input.saturation.lowThershold=0;
	fPid->input.saturation.highThershold=0;
}

void PidSetReference (struct PidController *fPid, float reference) {
	fPid->input.reference = reference;
}

void PidSetFeedback (struct PidController *fPid, float feedback, float deltaTimeSampling) {
	fPid->input.feedback = feedback;
	fPid->input.deltaTimeSampling = deltaTimeSampling;
}

void PidSetCoefficient (struct PidController *fPid, float Kp, float Ki, float Kd, float BackSaturation, float filterDerivative) {
	fPid->input.coefficient.proportional = Kp;
	fPid->input.coefficient.integral = Ki;
	fPid->input.coefficient.derivative = Kd;
	fPid->input.coefficient.coefficientBackSaturation = BackSaturation;
	fPid->input.coefficient.filterDerivative = filterDerivative;
}

void PidSetSaturation (struct PidController *fPid, float lowLimit, float highLimit) {
	fPid->input.saturation.lowThershold = lowLimit;
	fPid->input.saturation.highThershold = highLimit;
}

void PidCompute(struct PidController *fPid) {
	fPid->error = fPid->input.reference - fPid->input.feedback;

	fPid->proportionalComponent = fPid->input.coefficient.proportional * fPid->error;

	fPid->integralComponent += fPid->input.deltaTimeSampling * fPid->integralFilter;
	fPid->integralFilter = fPid->input.coefficient.integral * fPid->error + fPid->input.coefficient.coefficientBackSaturation * (fPid->outputPID - fPid->tempPID);

	fPid->derivativeFilter += fPid->input.deltaTimeSampling * fPid->derivativeComponent;
	fPid->derivativeComponent = (fPid->input.coefficient.derivative * fPid->error - fPid->derivativeFilter) * fPid->input.coefficient.filterDerivative;

	fPid->outputPID = fPid->tempPID = fPid->proportionalComponent + fPid->integralComponent + fPid->derivativeComponent;
	fPid->outputPID = fminf(fmaxf(fPid->outputPID, fPid->input.saturation.lowThershold), fPid->input.saturation.highThershold);
}
