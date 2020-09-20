/*
 * SkyConv.c
 *
 *  Created on: Sep 20, 2020
 *      Author: RadaR
 */

/***********************************************
Include Section
***********************************************/

#include "SkyConv.h"


/***********************************************
PID Section
***********************************************/

struct PidController PidV;

/***********************************************
Var Section
***********************************************/


volatile enum TState SkyState=FLT;

volatile uint8_t WaveAB=0;

volatile uint16_t WaveIndex=0;

volatile float Duty=0;
volatile uint16_t softstart=0;

volatile uint16_t COMPV=MAX_VCOMP;
volatile uint16_t COMPI=MAX_ICOMP;

volatile uint8_t ADCIndex=0;

volatile uint32_t ocV=0;
volatile uint32_t ocI=0;

volatile float ocV_f=0;
volatile float ocI_f=0;

#ifdef USE_BRIDGE_MODE

uint16_t SinusVTable[SinusIndexCnt]={
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,

		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,


		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,


		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,

		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,

		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,

		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,


		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,


		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,

		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax,
		VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax, VPeakMax

};

uint16_t SinusITable[SinusIndexCnt]={
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,

		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,


		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,


		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,

		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,

		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,

		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,


		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,


		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,

		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax,
		IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax, IPeakMax
};
#endif

#ifndef USE_BRIDGE_MODE
uint16_t SinusVTable[SinusIndexCnt]={
		0,0,0,0,0,
		1, 21, 42, 62, 83, 103, 124, 144, 165, 185, 206, 226, 247, 267, 287, 308, 328, 349, 369, 389, 409, 430, 450,
		470, 491, 511, 531, 551, 571, 591, 611, 631, 651, 671, 691, 711, 731, 751, 771, 791, 810, 830, 850, 869, 889,
		909, 928, 948, 967, 986, 1006, 1025, 1044, 1063, 1082, 1102, 1121, 1140, 1159, 1177, 1196, 1215, 1234, 1252,
		1271, 1289, 1308, 1326, 1345, 1363, 1381, 1399, 1417, 1435, 1453, 1471, 1489, 1507, 1525, 1542, 1560, 1577,
		1595, 1612, 1629, 1646, 1663, 1680, 1697, 1714, 1731, 1748, 1764, 1781, 1797, 1814, 1830, 1846, 1862, 1878,
		1894, 1910, 1926, 1942, 1957, 1973, 1988, 2003, 2019, 2034, 2049, 2064, 2078, 2093, 2108, 2122, 2137, 2151,
		2165, 2179, 2194, 2207, 2221, 2235, 2249, 2262, 2276, 2289, 2302, 2315, 2328, 2341, 2354, 2366, 2379, 2391,
		2404, 2416, 2428, 2440, 2452, 2464, 2475, 2487, 2498, 2510, 2521, 2532, 2543, 2554, 2564, 2575, 2585, 2596,
		2606, 2616, 2626, 2636, 2646, 2655, 2665, 2674, 2683, 2692, 2701, 2710, 2719, 2728, 2736, 2744, 2753, 2761,
		2769, 2777, 2784, 2792, 2799, 2807, 2814, 2821, 2828, 2835, 2841, 2848, 2854, 2860, 2867, 2873, 2878, 2884,
		2890, 2895, 2901, 2906, 2911, 2916, 2920, 2925, 2930, 2934, 2938, 2942, 2946, 2950, 2954, 2957, 2961, 2964,
		2967, 2970, 2973, 2976, 2978, 2981, 2983, 2985, 2987, 2989, 2991, 2993, 2994, 2995, 2997, 2998, 2998, 2999,
		3000, 3000, 3001, 3001, 3001, 3001, 3001, 3000, 3000, 2999, 2998, 2998, 2997, 2995, 2994, 2993, 2991, 2989,
		2987, 2985, 2983, 2981, 2978, 2976, 2973, 2970, 2967, 2964, 2961, 2957, 2954, 2950, 2946, 2942, 2938, 2934,
		2930, 2925, 2920, 2916, 2911, 2906, 2901, 2895, 2890, 2884, 2878, 2873, 2867, 2860, 2854, 2848, 2841, 2835,
		2828, 2821, 2814, 2807, 2799, 2792, 2784, 2777, 2769, 2761, 2753, 2744, 2736, 2728, 2719, 2710, 2701, 2692,
		2683, 2674, 2665, 2655, 2646, 2636, 2626, 2616, 2606, 2596, 2585, 2575, 2564, 2554, 2543, 2532, 2521, 2510,
		2498, 2487, 2475, 2464, 2452, 2440, 2428, 2416, 2404, 2391, 2379, 2366, 2354, 2341, 2328, 2315, 2302, 2289,
		2276, 2262, 2249, 2235, 2221, 2207, 2194, 2179, 2165, 2151, 2137, 2122, 2108, 2093, 2078, 2064, 2049, 2034,
		2019, 2003, 1988, 1973, 1957, 1942, 1926, 1910, 1894, 1878, 1862, 1846, 1830, 1814, 1797, 1781, 1764, 1748,
		1731, 1714, 1697, 1680, 1663, 1646, 1629, 1612, 1595, 1577, 1560, 1542, 1525, 1507, 1489, 1471, 1453, 1435,
		1417, 1399, 1381, 1363, 1345, 1326, 1308, 1289, 1271, 1252, 1234, 1215, 1196, 1177, 1159, 1140, 1121, 1102,
		1082, 1063, 1044, 1025, 1006, 986, 967, 948, 928, 909, 889, 869, 850, 830, 810, 791, 771, 751, 731, 711, 691,
		671, 651, 631, 611, 591, 571, 551, 531, 511, 491, 470, 450, 430, 409, 389, 369, 349, 328, 308, 287, 267, 247,
		226, 206, 185, 165, 144, 124, 103, 83, 62, 42, 21,

		0,0,0,0,0,
		1, 21, 42, 62, 83, 103, 124, 144, 165, 185, 206, 226, 247, 267, 287, 308, 328, 349, 369, 389, 409, 430, 450,
		470, 491, 511, 531, 551, 571, 591, 611, 631, 651, 671, 691, 711, 731, 751, 771, 791, 810, 830, 850, 869, 889,
		909, 928, 948, 967, 986, 1006, 1025, 1044, 1063, 1082, 1102, 1121, 1140, 1159, 1177, 1196, 1215, 1234, 1252,
		1271, 1289, 1308, 1326, 1345, 1363, 1381, 1399, 1417, 1435, 1453, 1471, 1489, 1507, 1525, 1542, 1560, 1577,
		1595, 1612, 1629, 1646, 1663, 1680, 1697, 1714, 1731, 1748, 1764, 1781, 1797, 1814, 1830, 1846, 1862, 1878,
		1894, 1910, 1926, 1942, 1957, 1973, 1988, 2003, 2019, 2034, 2049, 2064, 2078, 2093, 2108, 2122, 2137, 2151,
		2165, 2179, 2194, 2207, 2221, 2235, 2249, 2262, 2276, 2289, 2302, 2315, 2328, 2341, 2354, 2366, 2379, 2391,
		2404, 2416, 2428, 2440, 2452, 2464, 2475, 2487, 2498, 2510, 2521, 2532, 2543, 2554, 2564, 2575, 2585, 2596,
		2606, 2616, 2626, 2636, 2646, 2655, 2665, 2674, 2683, 2692, 2701, 2710, 2719, 2728, 2736, 2744, 2753, 2761,
		2769, 2777, 2784, 2792, 2799, 2807, 2814, 2821, 2828, 2835, 2841, 2848, 2854, 2860, 2867, 2873, 2878, 2884,
		2890, 2895, 2901, 2906, 2911, 2916, 2920, 2925, 2930, 2934, 2938, 2942, 2946, 2950, 2954, 2957, 2961, 2964,
		2967, 2970, 2973, 2976, 2978, 2981, 2983, 2985, 2987, 2989, 2991, 2993, 2994, 2995, 2997, 2998, 2998, 2999,
		3000, 3000, 3001, 3001, 3001, 3001, 3001, 3000, 3000, 2999, 2998, 2998, 2997, 2995, 2994, 2993, 2991, 2989,
		2987, 2985, 2983, 2981, 2978, 2976, 2973, 2970, 2967, 2964, 2961, 2957, 2954, 2950, 2946, 2942, 2938, 2934,
		2930, 2925, 2920, 2916, 2911, 2906, 2901, 2895, 2890, 2884, 2878, 2873, 2867, 2860, 2854, 2848, 2841, 2835,
		2828, 2821, 2814, 2807, 2799, 2792, 2784, 2777, 2769, 2761, 2753, 2744, 2736, 2728, 2719, 2710, 2701, 2692,
		2683, 2674, 2665, 2655, 2646, 2636, 2626, 2616, 2606, 2596, 2585, 2575, 2564, 2554, 2543, 2532, 2521, 2510,
		2498, 2487, 2475, 2464, 2452, 2440, 2428, 2416, 2404, 2391, 2379, 2366, 2354, 2341, 2328, 2315, 2302, 2289,
		2276, 2262, 2249, 2235, 2221, 2207, 2194, 2179, 2165, 2151, 2137, 2122, 2108, 2093, 2078, 2064, 2049, 2034,
		2019, 2003, 1988, 1973, 1957, 1942, 1926, 1910, 1894, 1878, 1862, 1846, 1830, 1814, 1797, 1781, 1764, 1748,
		1731, 1714, 1697, 1680, 1663, 1646, 1629, 1612, 1595, 1577, 1560, 1542, 1525, 1507, 1489, 1471, 1453, 1435,
		1417, 1399, 1381, 1363, 1345, 1326, 1308, 1289, 1271, 1252, 1234, 1215, 1196, 1177, 1159, 1140, 1121, 1102,
		1082, 1063, 1044, 1025, 1006, 986, 967, 948, 928, 909, 889, 869, 850, 830, 810, 791, 771, 751, 731, 711, 691,
		671, 651, 631, 611, 591, 571, 551, 531, 511, 491, 470, 450, 430, 409, 389, 369, 349, 328, 308, 287, 267, 247,
		226, 206, 185, 165, 144, 124, 103, 83, 62, 42, 21
};

uint16_t SinusITable[SinusIndexCnt]={
		0,0,0,0,0,
		1, 21, 42, 62, 83, 103, 124, 144, 165, 185, 206, 226, 247, 267, 287, 308, 328, 349, 369, 389, 409, 430, 450,
		470, 491, 511, 531, 551, 571, 591, 611, 631, 651, 671, 691, 711, 731, 751, 771, 791, 810, 830, 850, 869, 889,
		909, 928, 948, 967, 986, 1006, 1025, 1044, 1063, 1082, 1102, 1121, 1140, 1159, 1177, 1196, 1215, 1234, 1252,
		1271, 1289, 1308, 1326, 1345, 1363, 1381, 1399, 1417, 1435, 1453, 1471, 1489, 1507, 1525, 1542, 1560, 1577,
		1595, 1612, 1629, 1646, 1663, 1680, 1697, 1714, 1731, 1748, 1764, 1781, 1797, 1814, 1830, 1846, 1862, 1878,
		1894, 1910, 1926, 1942, 1957, 1973, 1988, 2003, 2019, 2034, 2049, 2064, 2078, 2093, 2108, 2122, 2137, 2151,
		2165, 2179, 2194, 2207, 2221, 2235, 2249, 2262, 2276, 2289, 2302, 2315, 2328, 2341, 2354, 2366, 2379, 2391,
		2404, 2416, 2428, 2440, 2452, 2464, 2475, 2487, 2498, 2510, 2521, 2532, 2543, 2554, 2564, 2575, 2585, 2596,
		2606, 2616, 2626, 2636, 2646, 2655, 2665, 2674, 2683, 2692, 2701, 2710, 2719, 2728, 2736, 2744, 2753, 2761,
		2769, 2777, 2784, 2792, 2799, 2807, 2814, 2821, 2828, 2835, 2841, 2848, 2854, 2860, 2867, 2873, 2878, 2884,
		2890, 2895, 2901, 2906, 2911, 2916, 2920, 2925, 2930, 2934, 2938, 2942, 2946, 2950, 2954, 2957, 2961, 2964,
		2967, 2970, 2973, 2976, 2978, 2981, 2983, 2985, 2987, 2989, 2991, 2993, 2994, 2995, 2997, 2998, 2998, 2999,
		3000, 3000, 3001, 3001, 3001, 3001, 3001, 3000, 3000, 2999, 2998, 2998, 2997, 2995, 2994, 2993, 2991, 2989,
		2987, 2985, 2983, 2981, 2978, 2976, 2973, 2970, 2967, 2964, 2961, 2957, 2954, 2950, 2946, 2942, 2938, 2934,
		2930, 2925, 2920, 2916, 2911, 2906, 2901, 2895, 2890, 2884, 2878, 2873, 2867, 2860, 2854, 2848, 2841, 2835,
		2828, 2821, 2814, 2807, 2799, 2792, 2784, 2777, 2769, 2761, 2753, 2744, 2736, 2728, 2719, 2710, 2701, 2692,
		2683, 2674, 2665, 2655, 2646, 2636, 2626, 2616, 2606, 2596, 2585, 2575, 2564, 2554, 2543, 2532, 2521, 2510,
		2498, 2487, 2475, 2464, 2452, 2440, 2428, 2416, 2404, 2391, 2379, 2366, 2354, 2341, 2328, 2315, 2302, 2289,
		2276, 2262, 2249, 2235, 2221, 2207, 2194, 2179, 2165, 2151, 2137, 2122, 2108, 2093, 2078, 2064, 2049, 2034,
		2019, 2003, 1988, 1973, 1957, 1942, 1926, 1910, 1894, 1878, 1862, 1846, 1830, 1814, 1797, 1781, 1764, 1748,
		1731, 1714, 1697, 1680, 1663, 1646, 1629, 1612, 1595, 1577, 1560, 1542, 1525, 1507, 1489, 1471, 1453, 1435,
		1417, 1399, 1381, 1363, 1345, 1326, 1308, 1289, 1271, 1252, 1234, 1215, 1196, 1177, 1159, 1140, 1121, 1102,
		1082, 1063, 1044, 1025, 1006, 986, 967, 948, 928, 909, 889, 869, 850, 830, 810, 791, 771, 751, 731, 711, 691,
		671, 651, 631, 611, 591, 571, 551, 531, 511, 491, 470, 450, 430, 409, 389, 369, 349, 328, 308, 287, 267, 247,
		226, 206, 185, 165, 144, 124, 103, 83, 62, 42, 21,

		0,0,0,0,0,
		1, 21, 42, 62, 83, 103, 124, 144, 165, 185, 206, 226, 247, 267, 287, 308, 328, 349, 369, 389, 409, 430, 450,
		470, 491, 511, 531, 551, 571, 591, 611, 631, 651, 671, 691, 711, 731, 751, 771, 791, 810, 830, 850, 869, 889,
		909, 928, 948, 967, 986, 1006, 1025, 1044, 1063, 1082, 1102, 1121, 1140, 1159, 1177, 1196, 1215, 1234, 1252,
		1271, 1289, 1308, 1326, 1345, 1363, 1381, 1399, 1417, 1435, 1453, 1471, 1489, 1507, 1525, 1542, 1560, 1577,
		1595, 1612, 1629, 1646, 1663, 1680, 1697, 1714, 1731, 1748, 1764, 1781, 1797, 1814, 1830, 1846, 1862, 1878,
		1894, 1910, 1926, 1942, 1957, 1973, 1988, 2003, 2019, 2034, 2049, 2064, 2078, 2093, 2108, 2122, 2137, 2151,
		2165, 2179, 2194, 2207, 2221, 2235, 2249, 2262, 2276, 2289, 2302, 2315, 2328, 2341, 2354, 2366, 2379, 2391,
		2404, 2416, 2428, 2440, 2452, 2464, 2475, 2487, 2498, 2510, 2521, 2532, 2543, 2554, 2564, 2575, 2585, 2596,
		2606, 2616, 2626, 2636, 2646, 2655, 2665, 2674, 2683, 2692, 2701, 2710, 2719, 2728, 2736, 2744, 2753, 2761,
		2769, 2777, 2784, 2792, 2799, 2807, 2814, 2821, 2828, 2835, 2841, 2848, 2854, 2860, 2867, 2873, 2878, 2884,
		2890, 2895, 2901, 2906, 2911, 2916, 2920, 2925, 2930, 2934, 2938, 2942, 2946, 2950, 2954, 2957, 2961, 2964,
		2967, 2970, 2973, 2976, 2978, 2981, 2983, 2985, 2987, 2989, 2991, 2993, 2994, 2995, 2997, 2998, 2998, 2999,
		3000, 3000, 3001, 3001, 3001, 3001, 3001, 3000, 3000, 2999, 2998, 2998, 2997, 2995, 2994, 2993, 2991, 2989,
		2987, 2985, 2983, 2981, 2978, 2976, 2973, 2970, 2967, 2964, 2961, 2957, 2954, 2950, 2946, 2942, 2938, 2934,
		2930, 2925, 2920, 2916, 2911, 2906, 2901, 2895, 2890, 2884, 2878, 2873, 2867, 2860, 2854, 2848, 2841, 2835,
		2828, 2821, 2814, 2807, 2799, 2792, 2784, 2777, 2769, 2761, 2753, 2744, 2736, 2728, 2719, 2710, 2701, 2692,
		2683, 2674, 2665, 2655, 2646, 2636, 2626, 2616, 2606, 2596, 2585, 2575, 2564, 2554, 2543, 2532, 2521, 2510,
		2498, 2487, 2475, 2464, 2452, 2440, 2428, 2416, 2404, 2391, 2379, 2366, 2354, 2341, 2328, 2315, 2302, 2289,
		2276, 2262, 2249, 2235, 2221, 2207, 2194, 2179, 2165, 2151, 2137, 2122, 2108, 2093, 2078, 2064, 2049, 2034,
		2019, 2003, 1988, 1973, 1957, 1942, 1926, 1910, 1894, 1878, 1862, 1846, 1830, 1814, 1797, 1781, 1764, 1748,
		1731, 1714, 1697, 1680, 1663, 1646, 1629, 1612, 1595, 1577, 1560, 1542, 1525, 1507, 1489, 1471, 1453, 1435,
		1417, 1399, 1381, 1363, 1345, 1326, 1308, 1289, 1271, 1252, 1234, 1215, 1196, 1177, 1159, 1140, 1121, 1102,
		1082, 1063, 1044, 1025, 1006, 986, 967, 948, 928, 909, 889, 869, 850, 830, 810, 791, 771, 751, 731, 711, 691,
		671, 651, 631, 611, 591, 571, 551, 531, 511, 491, 470, 450, 430, 409, 389, 369, 349, 328, 308, 287, 267, 247,
		226, 206, 185, 165, 144, 124, 103, 83, 62, 42, 21
};
#endif



/***********************************************
Code Section
***********************************************/

void InitSKY(void)
{
	SetDuty(0);
}

void InitSkyADC(void)
{
	  LL_ADC_StartCalibration(ADC1, LL_ADC_SINGLE_ENDED);
	  LL_ADC_StartCalibration(ADC2, LL_ADC_SINGLE_ENDED);

	  LL_ADC_Enable(ADC1);
	  LL_ADC_Enable(ADC2);
	  LL_ADC_EnableIT_JEOS(ADC2);

	  LL_ADC_INJ_StartConversion(ADC1);
	  LL_ADC_INJ_StartConversion(ADC2);
}

uint32_t dsp_ema_i32(uint16_t in, uint32_t average, uint16_t alpha){
	uint32_t tmp0; //calcs must be done in 64-bit math to avoid overflow
  tmp0 = (uint16_t)in * (alpha) + (uint32_t)average * (65536 - alpha);
  return (uint32_t)((tmp0 + 32768) / 65536); //scale back to 32-bit (with rounding)
}

