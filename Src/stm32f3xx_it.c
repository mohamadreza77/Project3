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
int flagADC = 1;
extern char keyboard[4][3][5];
int prevKey = -1;
int keyboardCounter = 0;
int oneAndHalfSecond = 0;
int override = 0;
int  passedTimeKey = 0;
//int x;
int y;
extern char name[8];
extern int mode; // 0 => prologue, 1 => menu, 2 => play
extern int plantsType;
extern int lastPlant[3];
extern int ascii;
extern int symb[4][20];
extern char map[4][20];
extern int totalNumberOfZs;
extern int chance;
extern int level;
extern int activeZombie;
extern float zombieSpeed;
extern int maxZombie;
extern unsigned char dd;
extern unsigned char buffer[1000];
extern int pos;
extern int plantsNumber;
int tempx, tempy;
extern int seed;
extern int nameLen;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim8;
////////////////////////////////////////CURSOR/////////////////////////////////////////
extern int cursor_x;
extern int cursor_y;
extern char* cursor_sign;
extern int gameStart;

////////////////////////////////////////CURSOR/////////////////////////////////////////
extern void printer(int p);
extern void blinking();
extern void updateCursor(int difX, int difY);
extern void menuInit();
extern void gameLogic();
extern void showPrologue();
extern void clearScreen();
extern void reverse_count();
extern void initZombies();
extern void loseInit();
extern void winInit();
extern void getName();
extern void printKeyboardData(int i, int j, int t, int o);
extern void bonusCreate();
extern void createSaveData();
extern void fillTheZ(int co, int x,int y, int type, int power, int time);///counter,x,y,type,power,time
/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern ADC_HandleTypeDef hadc1;
extern ADC_HandleTypeDef hadc2;
extern ADC_HandleTypeDef hadc3;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern UART_HandleTypeDef huart2;

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
			if(mode == 1 || mode == 2 || mode == 3){
				updateCursor(0,1);
			}
			else if(mode == 4){
				createSaveData();
//				HAL_UART_Transmit(&huart2,name,sizeof(unsigned char)*16,1000);
				printf(name);
				memset(name, 0, 1000 * (sizeof name[0]) );
				HAL_Delay(500);
				cursor_x = tempx;
				cursor_y = tempy;
				mode = 2;
				chmode = 1;
			}
			while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0)){
				if(mode == 2){
					HAL_Delay(5);
					TIM3_IRQHandler();
				}
			}
			HAL_Delay(20);
		}
		if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0) && i == 1){ //s9
			if(mode == 1 || mode == 2 || mode == 3){
				updateCursor(0,-1);
			}
			while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0)){
				if(mode == 2){
					HAL_Delay(5);
					TIM3_IRQHandler();
				}
			}
			HAL_Delay(20);
			
		}
		if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0) && i == 2){ //s5
			if(mode == 2){
				plantsType = (plantsType + 1)%4;
				if(plantsType == 0) ascii = 43;
				else ascii = plantsType;
			}
			while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0)){
				if(mode == 2){
					HAL_Delay(5);
					TIM3_IRQHandler();
				}
			}
			HAL_Delay(20);
			
		}
		if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0) && i == 3){ //s1
			if(mode == 0){
				mode = 1;
				chmode = 1;
			}
			while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0));
			HAL_Delay(20);
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
		
		if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1) && i == 0){ //s14
			if(mode == 4){
				if(prevKey == 14 && passedTimeKey != 1){ //stay here
					keyboardCounter = !keyboardCounter;
					override = 1;
				}
				else{
					 ;
					prevKey = 14;
					keyboardCounter = 0;
					override = 0;
				}
				passedTimeKey = 0;
				oneAndHalfSecond = 0;
				printKeyboardData(3,0,keyboardCounter,override);
			}
			while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1)){
				if(mode == 2){
					HAL_Delay(5);
					TIM3_IRQHandler();
				}
			}
			HAL_Delay(20);
		}
		if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1) && i == 1){ //s10
			if(mode == 4){
				if(prevKey == 10 && passedTimeKey != 1){ //stay here
					keyboardCounter = (keyboardCounter+1)%5;
					override = 1;
				}
				else{
					 ;
					prevKey = 10;
					keyboardCounter = 0;
					override = 0;
				}
				passedTimeKey = 0;
				oneAndHalfSecond = 0;
				printKeyboardData(2,0,keyboardCounter,override);
			}
			while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1)){
				if(mode == 2){
					HAL_Delay(5);
					TIM3_IRQHandler();
				}
			}
			HAL_Delay(20);
			
		}
		if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1) && i == 2){ //s6
			if(mode == 4){
				if(prevKey == 6 && passedTimeKey != 1){ //stay here
					keyboardCounter = (keyboardCounter+1)%4;
					override = 1;
				}
				else{
					 ;
					prevKey = 6;
					keyboardCounter = 0;
					override = 0;
				}
				passedTimeKey = 0;
				oneAndHalfSecond = 0;
				printKeyboardData(1,0,keyboardCounter,override);
			}
			while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1)){
				if(mode == 2){
					HAL_Delay(5);
					TIM3_IRQHandler();
				}
			}
			HAL_Delay(20);
			
		}
		if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1) && i == 3){ //s2
			if(mode == 4){
				if(prevKey == 2  && passedTimeKey != 1){ //stay here
					keyboardCounter = 0;
					override = 1;
				}
				else{
					 ;
					prevKey = 2;
					keyboardCounter = 0;
					override = 0;
				}
				passedTimeKey = 0;
				oneAndHalfSecond = 0;
				printKeyboardData(0,0,keyboardCounter,override);
			}
			while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1));
			HAL_Delay(20);
		}
		
		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_4,1);
		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_5,1);
		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_6,1);
		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_7,1);
		
	}
  /* USER CODE END EXTI1_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
  /* USER CODE BEGIN EXTI1_IRQn 1 */

  /* USER CODE END EXTI1_IRQn 1 */
}

/**
* @brief This function handles EXTI line2 and Touch Sense controller.
*/
void EXTI2_TSC_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI2_TSC_IRQn 0 */
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
		
		if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_2) && i == 0){ //s15
			if(mode == 4){
				if(prevKey == 15 && passedTimeKey != 1){ //stay here
					keyboardCounter = !keyboardCounter;
					override = 1;
				}
				else{
					 ;
					prevKey = 15;
					keyboardCounter = 0;
					override = 0;
				}
				passedTimeKey = 0;
				oneAndHalfSecond = 0;
				printKeyboardData(3,1,keyboardCounter,override);
			}
			while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_2)){
				if(mode == 2){
					HAL_Delay(5);
					TIM3_IRQHandler();
				}
			}
			HAL_Delay(20);
		}
		if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_2) && i == 1){ //s11
			if(mode == 4){
				if(prevKey == 11 && passedTimeKey != 1){ //stay here
					keyboardCounter = (keyboardCounter+1)%4;
					override = 1;
				}
				else{
					 ;
					prevKey = 11;
					keyboardCounter = 0;
					override = 0;
				}
				passedTimeKey = 0;
				oneAndHalfSecond = 0;
				printKeyboardData(2,1,keyboardCounter,override);
			}
			while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_2)){
				if(mode == 2){
					HAL_Delay(5);
					TIM3_IRQHandler();
				}
			}
			HAL_Delay(20);
			
		}
		if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_2) && i == 2){ //s7
			if(mode == 4){
				if(prevKey == 7 && passedTimeKey != 1){ //stay here
					keyboardCounter = (keyboardCounter+1)%4;
					override = 1;
				}
				else{
					 ;
					prevKey = 7;
					keyboardCounter = 0;
					override = 0;
				}
				passedTimeKey = 0;
				oneAndHalfSecond = 0;
				printKeyboardData(1,1,keyboardCounter,override);
			}
			while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_2)){
				if(mode == 2){
					HAL_Delay(5);
					TIM3_IRQHandler();
				}
			}
			HAL_Delay(20);
			
		}
		if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_2) && i == 3){ //s3
			if(mode == 4){
				if(prevKey == 3 && passedTimeKey != 1){ //stay here
					keyboardCounter = (keyboardCounter+1)%4;
					override = 1;
				}
				else{
					 ;
					prevKey = 3;
					keyboardCounter = 0;
					override = 0;
				}
				passedTimeKey = 0;
				oneAndHalfSecond = 0;
				printKeyboardData(0,1,keyboardCounter,override);
			}
			
			while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_2));
			HAL_Delay(20);
		}
		
		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_4,1);
		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_5,1);
		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_6,1);
		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_7,1);
		
	}
  /* USER CODE END EXTI2_TSC_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);
  /* USER CODE BEGIN EXTI2_TSC_IRQn 1 */

  /* USER CODE END EXTI2_TSC_IRQn 1 */
}

/**
* @brief This function handles EXTI line4 interrupt.
*/
void EXTI4_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI4_IRQn 0 */
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
		
		if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4) && i == 0){ //s16
			if(mode == 2){
				mode = 4; ///to get the name to save
				for(int i = 0; i < 100; i++){
					*(name + i) = '\0';
				}
				
				nameLen = -1;
				chmode = 1;
				tempx = cursor_x;
				tempy = cursor_y;
				HAL_Delay(300);
			}
			else if(mode == 4){
				if(prevKey == 16 && passedTimeKey != 1){ //stay here
					keyboardCounter = 0;
					override = 1;
				}
				else{
					 ;
					prevKey = 16;
					keyboardCounter = 0;
					override = 0;
				}
				passedTimeKey = 0;
				oneAndHalfSecond = 0;
				printKeyboardData(3,2,keyboardCounter,override);
			}
			while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)){
				if(mode == 2){
					HAL_Delay(5);
					TIM3_IRQHandler();
				}
			}
			HAL_Delay(20);
		}
		if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4) && i == 1){ //s12
			if(mode == 4){
				if(prevKey == 12 && passedTimeKey != 1){ //stay here
					keyboardCounter = (keyboardCounter+1)%5;
					override = 1;
				}
				else{
					 ;
					prevKey = 12;
					keyboardCounter = 0;
					override = 0;
				}
				passedTimeKey = 0;
				oneAndHalfSecond = 0;
				printKeyboardData(2,2,keyboardCounter,override);
			}
			while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)){
				if(mode == 2){
					HAL_Delay(5);
					TIM3_IRQHandler();
				}
			}
			HAL_Delay(20);
			
		}
		if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4) && i == 2){ //s8
			if(mode == 4){
				if(prevKey == 8 && passedTimeKey != 1){ //stay here
					keyboardCounter = (keyboardCounter+1)%4;
					override = 1;
				}
				else{
					 ;
					prevKey = 8;
					keyboardCounter = 0;
					override = 0;
				}
				passedTimeKey = 0;
				oneAndHalfSecond = 0;
				printKeyboardData(1,2,keyboardCounter,override);
			}
			while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)){
				if(mode == 2){
					HAL_Delay(5);
					TIM3_IRQHandler();
				}
			}
			HAL_Delay(20);
			
		}
		if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4) && i == 3){ //s4
			if(mode == 4){
				if(prevKey == 4 && passedTimeKey != 1){ //stay here
					keyboardCounter = (keyboardCounter+1)%4;
					override = 1;
				}
				else{
					 ;
					prevKey = 4;
					keyboardCounter = 0;
					override = 0;
				}
				passedTimeKey = 0;
				oneAndHalfSecond = 0;
				printKeyboardData(0,2,keyboardCounter,override);
			}
			while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4));
			HAL_Delay(20);
		}
		
		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_4,1);
		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_5,1);
		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_6,1);
		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_7,1);
		
	}
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
	
	
	if(mode == 2){
		int x = HAL_ADC_GetValue(&hadc1);
		x = x * 199/63;
		updateCursor(x/10,0);
	}
	if(flagADC == 1){
		seed = HAL_ADC_GetValue(&hadc2);
		srand(seed);
		flagADC = 0;
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
		
		HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
		HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
		HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_3);
		HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_4);
		HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
		HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2);
		HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3);
		HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_4);
		HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_1);
		HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_2);
		HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_3);
		
		///start ADCS
		HAL_ADC_Start_IT(&hadc1);
		HAL_ADC_Start_IT(&hadc2);
		HAL_ADC_Start_IT(&hadc3);
		
		HAL_TIM_Base_Start_IT(&htim1);
		HAL_TIM_Base_Start_IT(&htim8);
		
		HAL_UART_Receive_IT(&huart2, &dd, sizeof(unsigned char));
		
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
				__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,0);	
				__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,0);
				__HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_1,0);
				__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2,0);
				__HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_2,0);	
				__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_3,0);
				__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,0);
				__HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_3,0);
				__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,0);
				__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,0);
				__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_4,0);
				cursor_x = 0;
				cursor_y = 0;
				symb[0][0] = 43;
				limity = 2;
				menuInit();
//				HAL_TIM_Base_Start_IT(&htim3);
			break;
			case 4:
				getName();
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
		/////////////////////////////////////////////////////////////////////////////////////////////////
		if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0) && cursor_x == 0){ //to newGame
//			printer(2);
			cursor_x = 0;
			cursor_y = 0;
			mode = 2;
			limity = 3;
//			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_8,1);
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,y); //////PE8 is set
			chmode = 1;
		}
		if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0) && cursor_x == 2){ // to go to About
			
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////
	}
	else if(mode == 2){ // NewGame
		
		if(chance <= 0){
			chance = 0;
			chmode = 1;
			mode = 5; //// lose
		}
		gameLogic();
		bonusCreate();
		
	}
	
	if(mode != 0 && mode != 5 && mode != 6 && mode != 4)
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

	if(mode == 4){
		oneAndHalfSecond++;
		if(oneAndHalfSecond == 350){
			passedTimeKey = 1;
			oneSecond = 0;
		}
	}
		
	if(gameStart){
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
				if(gameTime % 20 == 0 && gameTime != 0){
					level++;
					activeZombie = 0;
					maxZombie+=2;
					zombieSpeed *= 0.8;
					totalNumberOfZs = 5;
//					HAL_GPIO_WritePin(GPIOE,GPIO_PIN_9,level > 1);
//					HAL_GPIO_WritePin(GPIOE,GPIO_PIN_10,level > 2);
//					HAL_GPIO_WritePin(GPIOE,GPIO_PIN_11,level > 3);
//					HAL_GPIO_WritePin(GPIOE,GPIO_PIN_12,level > 4);
//					HAL_GPIO_WritePin(GPIOE,GPIO_PIN_13,level > 5);
//					HAL_GPIO_WritePin(GPIOE,GPIO_PIN_14,level > 6);
//					HAL_GPIO_WritePin(GPIOE,GPIO_PIN_15,level > 7);
			__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,level > 1?y:0);
			__HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_1,level > 2?y:0);
			__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2,level > 3?y:0);
			__HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_2,level > 4?y:0);	
			__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_3,level > 5?y:0);
			__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,level > 6?y:0);
			__HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_3,level > 7?y:0);
				}
				oneSecond =0;
				if(gameTime%2==0){
					createSaveData();
					printf(name);
					memset(name, 0, 1000 * (sizeof name[0]) );
				}
			}
			if(gameTime == 160){
				chmode = 1;
				mode = 6; //win
			}
		}
	}
  /* USER CODE END TIM3_IRQn 0 */
  HAL_TIM_IRQHandler(&htim3);
  /* USER CODE BEGIN TIM3_IRQn 1 */
	HAL_TIM_Base_Start_IT(&htim3);
  /* USER CODE END TIM3_IRQn 1 */
}

/**
* @brief This function handles USART2 global interrupt / USART2 wake-up interrupt through EXTI line 26.
*/
void USART2_IRQHandler(void)
{
  /* USER CODE BEGIN USART2_IRQn 0 */

  /* USER CODE END USART2_IRQn 0 */
  HAL_UART_IRQHandler(&huart2);
  /* USER CODE BEGIN USART2_IRQn 1 */
	if (dd != 0x0D){
			buffer[pos] = dd;
			pos++;
			buffer[pos] = '\0';
		}
		else if(mode == 1 && cursor_x == 1){
			
			pos = 0; 
	//		HAL_UART_Transmit(&huart2,buffer,sizeof(unsigned char)*1000,1000);
				
			int pointer = 0;
			int i = 0;
			int index[11];
			while(buffer[pointer] != '\0'){
				if(buffer[pointer] == '*'){
					index[i] = pointer;
					
					i++;
				}
				pointer++;
			}
			
			chance = buffer[index[0]+1] - '0';
			gameTime = 0;
			for(int i = index[1]+1; i < index[2];i++){
				int a = buffer[i] - '0';
				gameTime = gameTime * 10 +a;
			}
			/////////////////////////////////////////////////////////////////////////////////////////////////
			level = buffer[index[2]+1] - '0';
//			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_8,1);
//			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_9,level > 1);
//			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_10,level > 2);
//			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_11,level > 3);
//			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_12,level > 4);
//			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_13,level > 5);
//			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_14,level > 6);
//			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_15,level > 7);
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,y);	
			__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,level > 1?y:0);
			__HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_1,level > 2?y:0);
			__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2,level > 3?y:0);
			__HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_2,level > 4?y:0);	
			__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_3,level > 5?y:0);
			__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,level > 6?y:0);
			__HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_3,level > 7?y:0);
			
			lastPlant[0]=0;
			int ii = 0;
			int negsign = 0;
			if(index[4] - index[3] == 4){
				ii = index[3]+2;
				negsign = 1;
			}else
				ii = index[3]+1;
			
			for(; ii < index[4];ii++){
					int a = buffer[ii] - '0';
					lastPlant[0] = lastPlant[0] * 10 +a;
			}
			if(negsign == 1){
				lastPlant[0] = -lastPlant[0];
			}
//			char s[5];
//			sprintf(s,"%d",lastPlant[0]);
//			print(s);
			
			lastPlant[1]=0;
			ii = 0;
			negsign = 0;
			if(index[5] - index[4] == 4){
				ii = index[4]+2;
				negsign = 1;
			}else
				ii = index[4]+1;
			
			for(; ii < index[5];ii++){
					int a = buffer[ii] - '0';
					lastPlant[1] = lastPlant[1] * 10 +a;
			}
			if(negsign == 1){
				lastPlant[1] = -lastPlant[1];
			}

			lastPlant[2]=0;
			ii = 0;
			negsign = 0;
			if(index[6] - index[5] == 4){
				ii = index[5]+2;
				negsign = 1;
			}else
				ii = index[5]+1;
			
			for(; ii < index[6];ii++){
					int a = buffer[ii] - '0';
					lastPlant[2] = lastPlant[2] * 10 +a;
			}
			if(negsign == 1){
				lastPlant[2] = -lastPlant[2];
			}
			
//			score = 0;
//			for(int i = index[6]+1; i < index[7];i++){
//				int a = buffer[i] - '0';
//				score = score * 10 +a;
//			}
			
			activeZombie=0;
			for(int i = index[7]+1; i < index[8];i++){
				int a = buffer[i] - '0';
				activeZombie = activeZombie* 10 +a;
			}
			
			plantsNumber= buffer[index[8]+1] - '0';

			
			int co = 0;
			cursor_x = 0;
			cursor_y = 0;
			int yPos = 0;
			int xPos = 0;
			int symbPos = 0;
			int mapPos = 0;
			
			for(int i = index[9]+1; i < index[10];){
				yPos = 0;
				xPos = buffer[i] - '0';///i
				i+=2;
				while(buffer[i] != '-'){
					int aa = (buffer[i] - '0');
					yPos = yPos*10 + aa;
					i++;
				}
				i++;
				symbPos = (buffer[i] - '0');///symb
				i+=2;
				mapPos = (buffer[i] - '0');///map
				i+=2;
				symb[xPos][yPos] = symbPos;
				map[xPos][yPos] = mapPos;
				
				if(symb[xPos][yPos] > 3){ //it is zombie
					int time = 0;
					while(buffer[i] != '-'){
						int aa = (buffer[i] - '0');
						time = time * 10 + aa;
						i++;
					}
					i++;
					fillTheZ(co,xPos,yPos,symbPos,mapPos,time);///counter,x,y,type,power,time
					co++;
				}
			}
			chmode=1;
			mode = 2;		
		}
		
	HAL_UART_Receive_IT(&huart2, &dd, sizeof(unsigned char));
  /* USER CODE END USART2_IRQn 1 */
}

/**
* @brief This function handles ADC3 global interrupt.
*/
void ADC3_IRQHandler(void)
{
  /* USER CODE BEGIN ADC3_IRQn 0 */
	y = HAL_ADC_GetValue(&hadc3)*8;

  /* USER CODE END ADC3_IRQn 0 */
  HAL_ADC_IRQHandler(&hadc3);
  /* USER CODE BEGIN ADC3_IRQn 1 */
	HAL_ADC_Start_IT(&hadc3);
  /* USER CODE END ADC3_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
