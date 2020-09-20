/*
 * SkyConv.h
 *
 *  Created on: Sep 20, 2020
 *      Author: RadaR
 */

#ifndef SKY_SKYCONV_H_
#define SKY_SKYCONV_H_

/***********************************************
Include Section
***********************************************/

#include "main.h"

#include "SkyPid.h"

/***********************************************
Defines Section
***********************************************/

#define USE_BRIDGE_MODE					(uint8_t)(1)

#define HOLOST							(uint16_t)(250)


#define DT_A							(uint16_t)(5)
#define DT_B							(uint16_t)(470)

#ifdef USE_BRIDGE_MODE
	#define DT_A_S							(uint16_t)(0)
	#define DT_B_S							(uint16_t)(465)
#endif

#define SinusIndexCnt					(uint16_t)(930)

#define WaveIndexCnt					(uint16_t)(930)

#define Pulse_Max_duty					(uint16_t)(20400)
#define Pulse_Min_duty					(uint16_t)(0)

#define Pulse_A_shift					(uint32_t)(4600)
#define Pulse_B_shift					(uint32_t)(29600)

#define min_step_softstart				(uint16_t)(2040) // 20400/100
#define mmin_step_softstart				(uint16_t)(204) // 20400/100

#define MAX_VCOMP						(uint16_t)(3250)
#define MAX_ICOMP						(uint16_t)(3250)

#define COMPV_Shift						(uint16_t)(750)
#define COMPI_Shift						(uint16_t)(750)


#ifdef USE_BRIDGE_MODE
	#define IPeakMax						(uint16_t)(2500)
	#define VPeakMax						(uint16_t)(2500)
#endif


#define ADCIndexMax								(uint8_t)  (8)

enum TState {GEN, GENon, FLT, DTzone};

/***********************************************
Var Section
***********************************************/

extern volatile enum TState SkyState;

extern volatile uint8_t WaveAB;

extern volatile uint16_t WaveIndex;

extern volatile float Duty;
extern volatile uint16_t softstart;

extern volatile uint16_t COMPV;
extern volatile uint16_t COMPI;

extern volatile uint8_t ADCIndex;

extern volatile uint32_t ocV;
extern volatile uint32_t ocI;

extern volatile float ocV_f;
extern volatile float ocI_f;

extern uint16_t SinusVTable[SinusIndexCnt];
extern uint16_t SinusITable[SinusIndexCnt];
extern uint16_t Sinus50HzTable[SinusIndexCnt];

extern struct PidController PidV;


/***********************************************
Code Section
***********************************************/

void InitSKY(void);
void InitSkyADC(void);

__STATIC_INLINE uint16_t min ( uint16_t a, uint16_t b ) { return a < b ? a : b; }

__STATIC_INLINE void Off50Hz(void)
{
	GPIOA->BRR=GPIO_BRR_BR_8; // off 50HZ_1
	GPIOA->BRR=GPIO_BRR_BR_9; // off 50HZ_2
}

__STATIC_INLINE void PWMon(void)
{
	HRTIM1->sCommonRegs.OENR = HRTIM_OENR_TB1OEN | HRTIM_OENR_TB2OEN;
}

__STATIC_INLINE void PWMoff(void)
{
	HRTIM1->sCommonRegs.ODISR = HRTIM_ODISR_TB1ODIS | HRTIM_ODISR_TB2ODIS;
}

__STATIC_INLINE void MaxDACs(void)
{
	COMPV=MAX_VCOMP;
	COMPV=MAX_ICOMP;
}

__STATIC_INLINE void UpdateDACs(void)
{
	DAC1->DHR12R2=(uint32_t)(COMPV);//COMPV_Shift+SinusVTable[WaveIndex];
	DAC2->DHR12R1=(uint32_t)(COMPI);//COMPI_Shift+SinusITable[WaveIndex];
}

__STATIC_INLINE void SetDuty(float _Duty)
{
	Duty=softstart+_Duty;

	if (Duty<=0) {
		Duty=Pulse_Min_duty;
	}
	if (Duty>softstart) {
		Duty=softstart;
	}
	HRTIM1->sTimerxRegs[1].CMP2xR=Pulse_A_shift+(uint32_t)(Duty);
	HRTIM1->sTimerxRegs[1].CMP4xR=Pulse_B_shift+(uint32_t)(Duty);
}

/*void SkyADC(void)
{
	GPIOB->BSRR=GPIO_BSRR_BS_3;

	OC_V[BufferIndex]=ADC1->JDR1;
	OC_I[BufferIndex]=ADC2->JDR1;

	if (BufferIndex==BufferSize) {
		BufferIndex=0;
	}

	if (ADCIndex==ADCIndexMax) {
		ADCIndex=0;

		//calc
		ocV=0;
		ocI=0;

		for (uint8_t i=0;i<BufferSize;i++) {
			ocV=ocV+OC_V[i];
			ocI=ocI+OC_I[i];
		}

		ocV=(uint32_t)(ocV/BufferSize);
		ocI=(uint32_t)(ocI/BufferSize);


		PidV.input.reference=(BufferSize*COMPdata.Vpeak);// ref current

		PidV.input.saturation.lowThershold=-Pulse_Max_duty;
		PidV.input.saturation.highThershold=Pulse_Min_duty;

		PidV.input.feedback=ocV;
		PidV.input.deltaTimeSampling=.0002;

		PidV.input.coefficient.proportional =1000; //kp
		PidV.input.coefficient.integral = 0; //Ki
		PidV.input.coefficient.derivative = 0; // Kd
		PidV.input.coefficient.coefficientBackSaturation = 0; // BackSaturation
		PidV.input.coefficient.filterDerivative = 0; //filterDerivative

		PidCompute(&PidV);

		//if (ocV>SinusVTable[wave_shift]) {
		//	SetDuty(0);
		//} else {
			SetDuty(Pulse_Max_duty);
		//}

	}

	BufferIndex++;
	ADCIndex++;

	GPIOB->BRR=GPIO_BRR_BR_3;
}*/
#endif /* SKY_SKYCONV_H_ */
