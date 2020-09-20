/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f3xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f3xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <stdint.h>
#include <string.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/

/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */

  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F3xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f3xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles PVD interrupt through EXTI line 16.
  */
void PVD_IRQHandler(void)
{
  /* USER CODE BEGIN PVD_IRQn 0 */

  /* USER CODE END PVD_IRQn 0 */

  /* USER CODE BEGIN PVD_IRQn 1 */

  /* USER CODE END PVD_IRQn 1 */
}

/**
  * @brief This function handles ADC1 and ADC2 interrupts.
  */
void ADC1_2_IRQHandler(void)
{
  /* USER CODE BEGIN ADC1_2_IRQn 0 */
	ADC1->ISR|=LL_ADC_FLAG_JEOC;
	ADC2->ISR|=LL_ADC_FLAG_JEOC;
  /* USER CODE END ADC1_2_IRQn 0 */

  /* USER CODE BEGIN ADC1_2_IRQn 1 */
	//up flag
	GPIOB->BSRR=GPIO_BSRR_BS_3;

	ocV=ocV+(uint32_t)(ADC1->JDR1);

	ocI=ocI+(uint32_t)(ADC2->JDR1);

	if (ADCIndex==ADCIndexMax-1) {

			ocV_f=ocV/ADCIndexMax;

			ocI_f=ocV/ADCIndexMax;

			//ocV_f=100;

			if (SkyState==GENon) {

					PidV.input.reference=SinusVTable[WaveIndex];// ref voltage

					PidV.input.saturation.lowThershold=-Pulse_Max_duty;
					PidV.input.saturation.highThershold=Pulse_Max_duty;

					PidV.input.feedback=ocV_f;
					PidV.input.deltaTimeSampling=0.0001;

					PidV.input.coefficient.proportional =12; //kp

					PidV.input.coefficient.integral = 0; //Ki
					PidV.input.coefficient.derivative = 0; // Kd
					PidV.input.coefficient.coefficientBackSaturation = 0; // BackSaturation
					PidV.input.coefficient.filterDerivative = 0; //filterDerivative

					PidCompute(&PidV);

					SetDuty(PidV.outputPID);

			} else {
				SetDuty(0);
			}


			//reset accum
			ocV=0;
			ocI=0;

			ocV_f=0;
			ocI_f=0;
			ADCIndex=0;

		} else {
			ADCIndex++;
		}

	//down flag
	GPIOB->BRR=GPIO_BRR_BR_3;

  /* USER CODE END ADC1_2_IRQn 1 */
}

/**
  * @brief This function handles HRTIM master timer global interrupt.
  */
void HRTIM1_Master_IRQHandler(void)
{
  /* USER CODE BEGIN HRTIM1_Master_IRQn 0 */
	HRTIM1->sMasterRegs.MICR|=HRTIM_MICR_MREP; //LL_HRTIM_ClearFlag_REP(HRTIM1, LL_HRTIM_TIMER_MASTER);
  /* USER CODE END HRTIM1_Master_IRQn 0 */

  /* USER CODE BEGIN HRTIM1_Master_IRQn 1 */
		//up flag
		GPIOA->BSRR=GPIO_BSRR_BS_15;

		if ((HRTIM1->sCommonRegs.ISR & HRTIM_ISR_FLT1)==HRTIM_ISR_FLT1) {

				//set FLT
				SkyState=FLT;

				//reset index to start for 0
				WaveIndex=0;
				WaveAB=0; //start from A

				//reset Softstart
				softstart=0;

				//try to reset flag to apply start at next Pair
				HRTIM1->sCommonRegs.ICR|=HRTIM_ICR_FLT1C;

				// reset DACs to MAX Value
				MaxDACs();

				// off 50Hz
				Off50Hz();

				// off PWM
				PWMoff();
		} else {
			SkyState=GEN;

			if (WaveIndex==0) {
					WaveAB=0; //start from A

					//update softstart
					softstart=softstart+min_step_softstart;
					/*if (softstart>Pulse_Max_duty) {
						softstart=Pulse_Max_duty;
					}*/
					softstart=min(softstart,Pulse_Max_duty);
			}

			//DT
			if (SinusVTable[WaveIndex]==0) {
				SkyState=DTzone;

				// reset DACs to MAX Value
				MaxDACs();

				// off 50Hz
				Off50Hz();

				// off PWM
				PWMoff();
			} else {
				// on PWM

				if (SkyState!=GENon) {
					PWMon();
					SkyState=GENon;
				}

				COMPV=COMPV_Shift+SinusVTable[WaveIndex];
				COMPI=COMPI_Shift+SinusITable[WaveIndex];
			}

#ifdef USE_BRIDGE_MODE
			if ( ((WaveIndex>=DT_A_S) && (WaveIndex<DT_A))
			||  ((WaveIndex>=DT_B_S) && (WaveIndex<DT_B)) ) {
				// off 50Hz
				Off50Hz();
			}
#endif

			switch (WaveIndex) {
				case DT_B:
					WaveAB=1;
					// on A, off B
					GPIOA->BSRR=GPIO_BSRR_BS_8; // on 50HZ_1
					GPIOA->BRR=GPIO_BRR_BR_9; // off 50HZ_2
					break;
				case DT_A:
					WaveAB=0;
					// on B , off A
					GPIOA->BSRR=GPIO_BSRR_BS_9; // on 50HZ_2
					GPIOA->BRR=GPIO_BRR_BR_8; // off 50HZ_1
					break;
			}

			//update Index
			if (WaveIndex<WaveIndexCnt-1) {
				WaveIndex++;
			} else {
				WaveIndex=0;
			}
		}


		//update COMP level
		UpdateDACs();

		//down flag
		GPIOA->BRR=GPIO_BRR_BR_15;

  /* USER CODE END HRTIM1_Master_IRQn 1 */
}

/**
  * @brief This function handles HRTIM timer B global interrupt.
  */
void HRTIM1_TIMB_IRQHandler(void)
{
  /* USER CODE BEGIN HRTIM1_TIMB_IRQn 0 */
	HRTIM1->sTimerxRegs[1].TIMxICR|=HRTIM_TIMICR_CPT1C;
	HRTIM1->sTimerxRegs[1].TIMxICR|=HRTIM_TIMICR_CPT2C;
  /* USER CODE END HRTIM1_TIMB_IRQn 0 */

  /* USER CODE BEGIN HRTIM1_TIMB_IRQn 1 */

  /* USER CODE END HRTIM1_TIMB_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
