/**
  ******************************************************************************
  * @file    stm32f3xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  *
  * COPYRIGHT(c) 2019 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"

/* USER CODE BEGIN 0 */
int chmode = 1;
int limity = 2;
int timerFlag = 0;
int gameTime = 0;
int oneSecond = 0;
int d1 = 0,d2 = 1,d3= 1,d4= 1;

extern int mode; // 0 => prologue, 1 => menu, 2 => play
extern int plantsType;
extern int counter;
extern int ascii;
extern int symb[4][20];
extern int chance;
extern int level;
extern RTC_TimeTypeDef t;
extern RTC_HandleTypeDef hrtc;
extern TIM_HandleTypeDef htim3;

////////////////////////////////////////CURSOR/////////////////////////////////////////
extern int cursor_x;
extern int cursor_y;
extern char* cursor_sign;
////////////////////////////////////////CURSOR/////////////////////////////////////////

extern void blinking();
extern void updateCursor(int difX, int difY);
extern void menuInit();
extern void newGame();
extern void showPrologue();
extern void clearScreen();
extern void reverse_count();
extern void moduleBlinking();
extern void initZombies();
extern void loseInit();
extern void winInit();
/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern ADC_HandleTypeDef hadc1;
extern ADC_HandleTypeDef hadc2;
extern ADC_HandleTypeDef hadc3;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;

/******************************************************************************/
/*            Cortex-M4 Processor Interruption and Exception Handlers         */ 
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
  /* USER CODE BEGIN HardFault_IRQn 1 */

  /* USER CODE END HardFault_IRQn 1 */
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
  /* USER CODE BEGIN MemoryManagement_IRQn 1 */

  /* USER CODE END MemoryManagement_IRQn 1 */
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
  /* USER CODE BEGIN BusFault_IRQn 1 */

  /* USER CODE END BusFault_IRQn 1 */
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
  /* USER CODE BEGIN UsageFault_IRQn 1 */

  /* USER CODE END UsageFault_IRQn 1 */
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
  HAL_IncTick();
  HAL_SYSTICK_IRQHandler();
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
* @brief This function handles EXTI line0 interrupt.
*/
void EXTI0_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI0_IRQn 0 */
		for(int i = 0; i < 4; i++){
		if(i == 0){
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_4,1);
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_5,0);
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_6,0);
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_7,0);		
		}
		else if(i == 1){
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_4,0);
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_5,1);
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_6,0);
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_7,0);
		}
		else if(i == 2){
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_4,0);
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_5,0);
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_6,1);
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_7,0);	
		}
		else if(i == 3){
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_4,0);
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_5,0);
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_6,0);
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_7,1);
		}
		
		if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0) && i == 0){ //s13
			if(mode != 0){
				updateCursor(0,1);
			}
			while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0)){
				HAL_Delay(5);
				TIM3_IRQHandler();
			}
			HAL_Delay(30);
		}
		if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0) && i == 1){ //s9
			if(mode != 0){
				updateCursor(0,-1);
			}
			while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0)){
				HAL_Delay(5);
				TIM3_IRQHandler();
			}
			HAL_Delay(30);
			
		}
		if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0) && i == 2){ //s5
			if(mode == 2){
				plantsType = (plantsType + 1)%4;
				if(plantsType == 0) ascii = 43;
				else ascii = plantsType;
			}
			while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0)){
				HAL_Delay(5);
				TIM3_IRQHandler();
			}
			HAL_Delay(30);
			
		}
		if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0) && i == 3){ //s1
			if(mode == 0){
				mode = 1;
				chmode = 1;
			}
			while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0));
			HAL_Delay(30);
		}
		
		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_4,1);
		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_5,1);
		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_6,1);
		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_7,1);
		
	}
  /* USER CODE END EXTI0_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
  /* USER CODE BEGIN EXTI0_IRQn 1 */

  /* USER CODE END EXTI0_IRQn 1 */
}

/**
* @brief This function handles EXTI line1 interrupt.
*/
void EXTI1_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI1_IRQn 0 */

  /* USER CODE END EXTI1_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
  /* USER CODE BEGIN EXTI1_IRQn 1 */

  /* USER CODE END EXTI1_IRQn 1 */
}

/**
* @brief This function handles EXTI line4 interrupt.
*/
void EXTI4_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI4_IRQn 0 */

  /* USER CODE END EXTI4_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);
  /* USER CODE BEGIN EXTI4_IRQn 1 */

  /* USER CODE END EXTI4_IRQn 1 */
}

/**
* @brief This function handles ADC1 and ADC2 interrupts.
*/
void ADC1_2_IRQHandler(void)
{
  /* USER CODE BEGIN ADC1_2_IRQn 0 */
	
	int x = HAL_ADC_GetValue(&hadc1);
	x = x * 199/63;
	
//	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_10,x > 10);
//	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_11,x > 20);
//	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_12,x > 30);
//	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_13,x > 40);
//	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_14,x > 50);
	if(mode == 2){
		updateCursor(x/10,0);
	}
	
  /* USER CODE END ADC1_2_IRQn 0 */
  HAL_ADC_IRQHandler(&hadc1);
  HAL_ADC_IRQHandler(&hadc2);
  /* USER CODE BEGIN ADC1_2_IRQn 1 */
	HAL_ADC_Start_IT(&hadc1);
	HAL_ADC_Start_IT(&hadc2);
  /* USER CODE END ADC1_2_IRQn 1 */
}

/**
* @brief This function handles TIM2 global interrupt.
*/
void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */
	if(timerFlag == 0){
		for(int i = 0; i < 4; i++){
			for(int j = 0; j < 20; j++){
				symb[i][j] = -1;
			}
		}
	
		///start ADCS
		HAL_ADC_Start_IT(&hadc1);
		HAL_ADC_Start_IT(&hadc2);
		HAL_ADC_Start_IT(&hadc3);
		
		///start keypad
		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_4,1);
		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_5,1);
		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_6,1);
		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_7,1);
		initZombies();
		
		timerFlag=1;
	}
	if(chmode == 1){
		clearScreen();
		switch (mode){
			case 1:
				cursor_x = 0;
				cursor_y = 0;
				symb[0][0] = 43;
				limity = 2;
			break;
			case 5:
				loseInit();
			break;
			case 6:
				winInit();
			break;
				
		}
		chmode = 0;
	}
	if(mode == 0){
		showPrologue();
	}
	else if (mode == 1){ //Menu
		menuInit();
		if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)){
			cursor_x = 0;
			cursor_y = 0;
			mode = 2;
			limity = 3;
			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_8,1);
			chmode = 1;
		}
	}
	else if(mode == 2){ // NewGame
		HAL_TIM_Base_Start_IT(&htim3);
		if(chance == 0){
			chmode = 1;
			mode = 5; //// lose
		}
		newGame();
		
	}
	else if(mode == 3){ // LoadGame
		
	}
	if(mode != 0 && mode != 5 && mode != 6)
		blinking();
		
  /* USER CODE END TIM2_IRQn 0 */
  HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM2_IRQn 1 */
	HAL_TIM_Base_Start_IT(&htim2);
  /* USER CODE END TIM2_IRQn 1 */
}

/**
* @brief This function handles TIM3 global interrupt.
*/
void TIM3_IRQHandler(void)
{
  /* USER CODE BEGIN TIM3_IRQn 0 */
 
	
		reverse_count(gameTime,d4,d3,d2,d1);
		if(d1 == 0){
			d1 = 1;
			d2 = 0;
		}
		else if(d2 == 0){
			d2 = 1;
			d3 = 0;
		}
		else if(d3 == 0){
			d3 = 1;
			d4 = 0;
		}
		else if(d4 == 0){
			d4 = 1;
			d1 = 0;
		}
	if(mode == 2 || mode == 3){
		oneSecond++;
		if(gameTime != 160 && oneSecond == 200){
			gameTime++;
			if(gameTime % 20 == 0){
				level++;
				HAL_GPIO_WritePin(GPIOE,GPIO_PIN_9,level > 1);
				HAL_GPIO_WritePin(GPIOE,GPIO_PIN_10,level > 2);
				HAL_GPIO_WritePin(GPIOE,GPIO_PIN_11,level > 3);
				HAL_GPIO_WritePin(GPIOE,GPIO_PIN_12,level > 4);
				HAL_GPIO_WritePin(GPIOE,GPIO_PIN_13,level > 5);
				HAL_GPIO_WritePin(GPIOE,GPIO_PIN_14,level > 6);
				HAL_GPIO_WritePin(GPIOE,GPIO_PIN_15,level > 7);
			}
			oneSecond =0;
		}
		if(gameTime == 160){
			chmode = 1;
			mode = 6; //win
		}
	}
	
  /* USER CODE END TIM3_IRQn 0 */
  HAL_TIM_IRQHandler(&htim3);
  /* USER CODE BEGIN TIM3_IRQn 1 */
	HAL_TIM_Base_Start_IT(&htim3);
  /* USER CODE END TIM3_IRQn 1 */
}

/**
* @brief This function handles ADC3 global interrupt.
*/
void ADC3_IRQHandler(void)
{
  /* USER CODE BEGIN ADC3_IRQn 0 */
	if(mode != 2) return;
	int y = HAL_ADC_GetValue(&hadc3)*8;
//	char s[100];
//	sprintf(s,"%d",y);
//	print(s);
//	print("/");
//	__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,y);
//	__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2,y);
//	__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_3,y);
//	
//	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1 ,y);
//	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2,y);
//	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_3,y);
//	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,y);
//	
//	__HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_1 ,y);
//	__HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_2,y);
//	__HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_3,y);
//	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,y);
  /* USER CODE END ADC3_IRQn 0 */
  HAL_ADC_IRQHandler(&hadc3);
  /* USER CODE BEGIN ADC3_IRQn 1 */
	HAL_ADC_Start_IT(&hadc3);
  /* USER CODE END ADC3_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
