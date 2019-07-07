
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
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
#include "main.h"
#include "stm32f3xx_hal.h"

/* USER CODE BEGIN Includes */
#include "LiquidCrystal.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;
ADC_HandleTypeDef hadc2;
ADC_HandleTypeDef hadc3;

I2C_HandleTypeDef hi2c1;

RTC_HandleTypeDef hrtc;

SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;

UART_HandleTypeDef huart2;

PCD_HandleTypeDef hpcd_USB_FS;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
#ifdef __GNUC__
	#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
	#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif
	
PUTCHAR_PROTOTYPE
{
	HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, 1000); // change &uart1 accordingly
	return ch;
}
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_SPI1_Init(void);
static void MX_USB_PCD_Init(void);
static void MX_ADC1_Init(void);
static void MX_RTC_Init(void);
static void MX_ADC2_Init(void);
static void MX_ADC3_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM3_Init(void);
static void MX_USART2_UART_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
extern int limity;
extern int gameTime;
RTC_TimeTypeDef t;
////////////////////////////////////////CURSOR/////////////////////////////////////////
int cursor_x = 0;
int cursor_y = 0;
char* cursor_sign;
////////////////////////////////////////CURSOR/////////////////////////////////////////

struct Zombie{
	int type;
	int x;
	int y;
	int time;
	int power;
	int alive;
};
struct Zombie zombies[5];
const int zombiesEnergy[4] = {1,2,3,4};
int zombieSpeed = 5;
int maxZombie = 5;
int activeZombie = 0;
int ascii = 43;
int lastChance = 0;
int seed;
int mode = 0;

char map[4][20];
char name[5000];
int nameLen = -1;
int symb[4][20];
const int plantsEnergy[3] = {1,2,4};
const int plantsCoolDown[3] = {4,8,10};
int lastPlant[3] = {-11,-11,-11};
int plantsNumber = 0;
int level = 1;
int chance = 5;
int plantsType = 0;
unsigned char dd = '1';
unsigned char buffer[1000] = "";
int pos = 0;
char keyboard[4][3][5] =
    {
    {{'1',' ', ' ', ' ', ' '},{'2','a','b','c',' '},{'3','d','e','f',' '}}
    ,{{'4','g','h','i',' '},{'5','j','k','l',' '},{'6','m','n','o',' '}}
    ,{{'7','p','q','r','s'},{'8','t','u','v',' '},{'9','w','x','y','z'}}
    ,{{'*','+',' ',' ',' '},{'0',' ',' ',' ',' '},{'#',' ',' ',' ',' '}}
    };

void printer(int p){
	char s[10];
	sprintf(s,"%d",p);
	setCursor(cursor_x,cursor_y);
	print(s);
	cursor_x+=3;
	cursor_y++;
}	
	
void showPrologue(){
		HAL_Delay(100);
		setCursor(7,0);
		print("Plants");
		setCursor(9,1);
		print("vs");
		setCursor(6,2);
		print("Zombies");
		setCursor(6,3);
		write(1);
		setCursor(7,3);
		write(2);
		setCursor(8,3);
		write(3);
		
		setCursor(10,3);
		write(4);
		setCursor(11,3);
		write(5);
		setCursor(12,3);
		write(6);
		setCursor(13,3);
		write(7);
		HAL_Delay(950);
		clear();
		
}

int blinkFlag = 0;
void blinking(){
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 20; j++){
			if(symb[i][j] == -1) continue;
			if(symb[i][j] == 160){
				setCursor(j,i);
				write(symb[i][j]);
				symb[i][j] = -1;
			}
			else{
					setCursor(j,i);
					write(symb[i][j]);
			}
		}
	}
}

void createSaveData(){
	strcat(name,"*");
	char temp[50];
	
	sprintf(temp,"%d",chance);
	strcat(name,temp);
	strcat(name,"*");
	
	strcpy(temp," ");
	
	sprintf(temp,"%d",gameTime);
	strcat(name,temp);
	strcat(name,"*");
	
	strcpy(temp," ");
	
	sprintf(temp,"%d",level);
	strcat(name,temp);
	strcat(name,"*");
	
	strcpy(temp," ");
	
	sprintf(temp,"%d",lastPlant[0]);
	strcat(name,temp);
	strcat(name,"*");
	
	strcpy(temp," ");
	
	sprintf(temp,"%d",lastPlant[1]);
	strcat(name,temp);
	strcat(name,"*");
	
	strcpy(temp," ");
	
	sprintf(temp,"%d",lastPlant[2]);
	strcat(name,temp);
	strcat(name,"*");
	
	strcpy(temp," ");
	
	sprintf(temp,"%d",level * (gameTime * 2 - lastChance));
	strcat(name,temp);
	strcat(name,"*");
	
	strcpy(temp," ");
	
	sprintf(temp,"%d",activeZombie);
	strcat(name,temp);
	strcat(name,"*");
	
	strcpy(temp," ");
	
	sprintf(temp,"%d",plantsNumber);
	strcat(name,temp);
	strcat(name,"*");
	
	strcpy(temp," ");
	
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 20; j++){
			if(symb[i][j] != -1 && map[i][j] != 0){
				sprintf(temp,"%d",i);
				strcat(name,temp);
				strcat(name,":");
				sprintf(temp,"%d",j);
				strcat(name,temp);
				strcat(name,"-");
				
				sprintf(temp,"%d",symb[i][j]);
				strcat(name,temp);
				strcat(name,"-");
				sprintf(temp,"%d",map[i][j]);
				strcat(name,temp);
				strcat(name,"-");
				
				for(int k = 0; k < activeZombie; k++){
					if(zombies[k].x == i && zombies[k].y == j){
						sprintf(temp,"%d",zombies[k].time);
						strcat(name,temp);
						strcat(name,"-");
					}
				}
			}
		}
		strcpy(temp," ");
	}
	strcat(name,"*");
	
}

void updateCursor(int difX, int difY){
	if(map[cursor_x][cursor_y] == 0)
		symb[cursor_x][cursor_y] = 160;
	if(cursor_x == limity && difY > 0) cursor_x = limity;
	else if(cursor_x == 0 && difY < 0) cursor_x = 0;
	else{
		cursor_x += difY;
	}
	cursor_y = difX;

	if(map[cursor_x][cursor_y] == 0)
		symb[cursor_x][cursor_y] = ascii;
}


void fillTheZ(int co, int x,int y, int type, int power, int time){
	zombies[co].x = x; 
	zombies[co].y = y; 
	zombies[co].type = type; 
	zombies[co].power = power; 
	zombies[co].time = time;
	zombies[co].alive = 1;
}

int collision(i){
	if(zombies[i].x == 3) return 0;
	if(symb[zombies[i].x + 1][zombies[i].y] < 4 && symb[zombies[i].x + 1][zombies[i].y] > 0){
			zombies[i].power--;
			map[zombies[i].x + 1][zombies[i].y]--;
			if(zombies[i].power == 0){
				zombies[i].alive = -1;
				symb[zombies[i].x][zombies[i].y] = 160;
				activeZombie--;
			}
			if(map[zombies[i].x + 1][zombies[i].y] == 0){
				symb[zombies[i].x + 1][zombies[i].y] = 160;
				plantsNumber--;
			}
			return 1;
	}
	else if(symb[zombies[i].x + 1][zombies[i].y] > 3 && symb[zombies[i].x + 1][zombies[i].y] < 8)
		return 1;
	else
		return 0;
}

void moveZombie(int i){
	if(gameTime - zombies[i].time > zombieSpeed){
		zombies[i].time = gameTime;
		if(collision(i)) return;
		if(zombies[i].x != -1){
			map[zombies[i].x][zombies[i].y] = 0;
			symb[zombies[i].x][zombies[i].y] = 160;
		}
		
		zombies[i].x++;
		
		if(zombies[i].x == 0){
			activeZombie++;
		}
		
		if(zombies[i].x == 4){
			chance--;
			lastChance = gameTime;
			zombies[i].alive = -1;
			symb[3][zombies[i].y] = 160;
			activeZombie--;
		}else{
			map[zombies[i].x][zombies[i].y] = zombies[i].power;
			symb[zombies[i].x][zombies[i].y] = zombies[i].type;
		}
		
	}
}

void initZombies(){
	for(int i =0; i < maxZombie; i ++){
		zombies[i].alive = -1;
	}
}

void zombieCreator(){
	if(activeZombie < maxZombie){
		int i = 0;
		for(; i < maxZombie; i ++){
			if(zombies[i].alive == -1){
				break;
			}
		}
		if(i == maxZombie) return;
		zombies[i].time = (rand()%6)+8;
		zombies[i].y = rand()%20;
		zombies[i].x = -1;
		zombies[i].type = (rand()%4);
		zombies[i].power = zombiesEnergy[zombies[i].type];
		zombies[i].type += 4;
		zombies[i].alive = 1;
		
	}
}

void menuInit(){
//	clear();
	setCursor(2,0);
	print("New Game");
	setCursor(2,1);
	print("Load Game");
	setCursor(2,2);
	print("About");
}
void calScore(){
	int score = level * (gameTime * 2 - lastChance);
	char s[10];
	sprintf(s,"%d",score);
	setCursor(8,2);
	print(s);
}

void loseInit(){
	setCursor(8,0);
	print("Game");
	setCursor(8,1);
	print("Over");
	calScore();
}

void winInit(){
	setCursor(8,0);
	print("You");
	setCursor(8,1);
	print("Won");
	calScore();
}


void clearScreen(){
	clear();
}
void toPlant(){
	if(plantsNumber != 7){
		if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)){
			if(
					map[cursor_x][cursor_y] == 0 &&
					plantsType != 0 && 
					cursor_x != 0 && 
					gameTime - lastPlant[plantsType-1] > plantsCoolDown[plantsType-1]
				){
				map[cursor_x][cursor_y] = plantsEnergy[ascii-1] ;
				symb[cursor_x][cursor_y] = ascii;
				plantsNumber++;
				lastPlant[plantsType-1] = gameTime;
			}
			while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0));
		}
	}
}
void gameLogic(){
	toPlant();
	zombieCreator();
	for(int i=0; i < maxZombie; i ++){
		if(zombies[i].alive == 1){
				moveZombie(i);
		}
	}
}

void getName(){
	setCursor(2,0);
	print("Enter Your Name");
	setCursor(4,2);
	print("->");
	cursor_x = 5;
}

void printKeyboardData(int i, int j, int t, int o){
	
	if(o == 0){
		setCursor(++cursor_x,2);
//		strcat(name,&keyboard[i][j][t]);
		
		nameLen++;
	}else{
		setCursor(cursor_x,2);
//		name[nameLen] = keyboard[i][j][t];
	}
	*(name + nameLen) = keyboard[i][j][t];
	write(keyboard[i][j][t]);
	
}

void moduleBlinking(){
//	int y = 200;
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
//	HAL_Delay(300);
//	y = 0;
//		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,y);
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
//	HAL_Delay(100);
}
	
void setPins(int binsDigit[], int d4, int d3, int d2, int d1){
	
	if(d1 == 0)
		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_1,1);
	else 
		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_1,0);
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,d4);  
  HAL_GPIO_WritePin(GPIOC,GPIO_PIN_12,d3);
  HAL_GPIO_WritePin(GPIOC,GPIO_PIN_11,d2);
  HAL_GPIO_WritePin(GPIOC,GPIO_PIN_10,d1);
	
	
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_9,binsDigit[0]);
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,binsDigit[1]);
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_9,binsDigit[2]);
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_10,binsDigit[3]);
	
}

void dec2bin(int n, int d4, int d3, int d2, int d1){
	
	int binsDigit[4];
		for (int i = 3; i >= 0; i--) {  
        int k = n >> i;  
        if ((k & 1) > 0)  
            binsDigit[i] = 1;
        else
            binsDigit[i] = 0;
    }  
  
	setPins(binsDigit, d4, d3, d2, d1);
  
}

int k =0;
void reverse_count(int time,int d4, int d3, int d2, int d1){
      int low = time % 10;
      int mid = (time / 10) - 10;
			if (mid < 0) mid = time / 10;
			int hi = time / 100;
			
			int amount = chance;
			if(k == 1) amount = hi;
			else if(k == 2) amount = mid;
			else if(k == 3) amount = low;
			k = (k +1)%4;
      dec2bin(amount,d4, d3, d2, d1);
}

void specialChar(){
	
	unsigned char potato[8]={0x04,
  0x0A,
  0x11,
  0x1B,
  0x11,
  0x11,
  0x11,
  0x1F};
//	
	unsigned char flower[8]={0x04,
  0x0A,
  0x15,
  0x0A,
  0x04,
  0x0E,
  0x15,
  0x04};
	
	unsigned char bomb[8]={0x00,
  0x04,
  0x0E,
  0x04,
  0x0E,
  0x11,
  0x11,
  0x0E};
	
	unsigned char z1[8]={0x04,
  0x0A,
  0x04,
  0x1F,
  0x04,
  0x04,
  0x0A,
  0x11};
	unsigned char z2[8]={0x1F,
  0x11,
  0x1F,
  0x04,
  0x04,
  0x04,
  0x0A,
  0x11};
	unsigned char z3[8]={0x04,
  0x0A,
  0x1F,
  0x04,
  0x0E,
  0x04,
  0x0A,
  0x11};
	unsigned char z4[8]={0x11,
  0x0A,
  0x0E,
  0x0A,
  0x0E,
  0x04,
  0x0A,
  0x11};
	unsigned char bonus[8]={0x00,
  0x00,
  0x15,
  0x0E,
  0x1F,
  0x0E,
  0x15,
  0x00};

	createChar(0,bonus);
	createChar(1,potato);
	createChar(2,flower);
	createChar(3,bomb);
	createChar(4,z1);
	createChar(5,z2);
	createChar(6,z3);
	createChar(7,z4);
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
	
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_SPI1_Init();
  MX_USB_PCD_Init();
  MX_ADC1_Init();
  MX_RTC_Init();
  MX_ADC2_Init();
  MX_ADC3_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
	LiquidCrystal(GPIOD, GPIO_PIN_8, GPIO_PIN_9, GPIO_PIN_10, GPIO_PIN_11, GPIO_PIN_12, GPIO_PIN_13, GPIO_PIN_14);
	begin(20,4);
	specialChar();
	
	HAL_TIM_Base_Start_IT(&htim2);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI
                              |RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB|RCC_PERIPHCLK_USART2
                              |RCC_PERIPHCLK_I2C1|RCC_PERIPHCLK_RTC
                              |RCC_PERIPHCLK_ADC12|RCC_PERIPHCLK_ADC34;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  PeriphClkInit.Adc12ClockSelection = RCC_ADC12PLLCLK_DIV1;
  PeriphClkInit.Adc34ClockSelection = RCC_ADC34PLLCLK_DIV1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_HSI;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  PeriphClkInit.USBClockSelection = RCC_USBCLKSOURCE_PLL_DIV1_5;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* ADC1 init function */
static void MX_ADC1_Init(void)
{

  ADC_MultiModeTypeDef multimode;
  ADC_ChannelConfTypeDef sConfig;

    /**Common config 
    */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc1.Init.Resolution = ADC_RESOLUTION_6B;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc1.Init.LowPowerAutoWait = DISABLE;
  hadc1.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the ADC multi-mode 
    */
  multimode.Mode = ADC_MODE_INDEPENDENT;
  if (HAL_ADCEx_MultiModeConfigChannel(&hadc1, &multimode) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure Regular Channel 
    */
  sConfig.Channel = ADC_CHANNEL_2;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.SamplingTime = ADC_SAMPLETIME_601CYCLES_5;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* ADC2 init function */
static void MX_ADC2_Init(void)
{

  ADC_ChannelConfTypeDef sConfig;

    /**Common config 
    */
  hadc2.Instance = ADC2;
  hadc2.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc2.Init.Resolution = ADC_RESOLUTION_6B;
  hadc2.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc2.Init.ContinuousConvMode = DISABLE;
  hadc2.Init.DiscontinuousConvMode = DISABLE;
  hadc2.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc2.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc2.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc2.Init.NbrOfConversion = 1;
  hadc2.Init.DMAContinuousRequests = DISABLE;
  hadc2.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc2.Init.LowPowerAutoWait = DISABLE;
  hadc2.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;
  if (HAL_ADC_Init(&hadc2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure Regular Channel 
    */
  sConfig.Channel = ADC_CHANNEL_5;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.SamplingTime = ADC_SAMPLETIME_601CYCLES_5;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* ADC3 init function */
static void MX_ADC3_Init(void)
{

  ADC_MultiModeTypeDef multimode;
  ADC_ChannelConfTypeDef sConfig;

    /**Common config 
    */
  hadc3.Instance = ADC3;
  hadc3.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc3.Init.Resolution = ADC_RESOLUTION_6B;
  hadc3.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc3.Init.ContinuousConvMode = DISABLE;
  hadc3.Init.DiscontinuousConvMode = DISABLE;
  hadc3.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc3.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc3.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc3.Init.NbrOfConversion = 1;
  hadc3.Init.DMAContinuousRequests = DISABLE;
  hadc3.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc3.Init.LowPowerAutoWait = DISABLE;
  hadc3.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;
  if (HAL_ADC_Init(&hadc3) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the ADC multi-mode 
    */
  multimode.Mode = ADC_MODE_INDEPENDENT;
  if (HAL_ADCEx_MultiModeConfigChannel(&hadc3, &multimode) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure Regular Channel 
    */
  sConfig.Channel = ADC_CHANNEL_5;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.SamplingTime = ADC_SAMPLETIME_601CYCLES_5;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* I2C1 init function */
static void MX_I2C1_Init(void)
{

  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x2000090E;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure Analogue filter 
    */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure Digital filter 
    */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* RTC init function */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */

    /**Initialize RTC Only 
    */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 39;
  hrtc.Init.SynchPrediv = 999;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* SPI1 init function */
static void MX_SPI1_Init(void)
{

  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_4BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;
  hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* TIM2 init function */
static void MX_TIM2_Init(void)
{

  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;

  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 719;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 10000;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* TIM3 init function */
static void MX_TIM3_Init(void)
{

  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;

  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 35;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 10000;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* USART2 init function */
static void MX_USART2_UART_Init(void)
{

  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* USB init function */
static void MX_USB_PCD_Init(void)
{

  hpcd_USB_FS.Instance = USB;
  hpcd_USB_FS.Init.dev_endpoints = 8;
  hpcd_USB_FS.Init.speed = PCD_SPEED_FULL;
  hpcd_USB_FS.Init.ep0_mps = DEP0CTL_MPS_64;
  hpcd_USB_FS.Init.phy_itface = PCD_PHY_EMBEDDED;
  hpcd_USB_FS.Init.low_power_enable = DISABLE;
  hpcd_USB_FS.Init.battery_charging_enable = DISABLE;
  if (HAL_PCD_Init(&hpcd_USB_FS) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, CS_I2C_SPI_Pin|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10 
                          |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14 
                          |GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, seg7_Pin|seg7D1_Pin|seg7D2_Pin|seg7D3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, seg7A8_Pin|seg7A9_Pin|seg7A10_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, seg7D4_Pin|seg7dot_Pin|GPIO_PIN_4|GPIO_PIN_5 
                          |GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pins : CS_I2C_SPI_Pin PE8 PE9 PE10 
                           PE11 PE12 PE13 PE14 
                           PE15 */
  GPIO_InitStruct.Pin = CS_I2C_SPI_Pin|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10 
                          |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14 
                          |GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : MEMS_INT4_Pin */
  GPIO_InitStruct.Pin = MEMS_INT4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(MEMS_INT4_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB2 PB4 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : seg7_Pin seg7D1_Pin seg7D2_Pin seg7D3_Pin */
  GPIO_InitStruct.Pin = seg7_Pin|seg7D1_Pin|seg7D2_Pin|seg7D3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : seg7A8_Pin seg7A9_Pin seg7A10_Pin */
  GPIO_InitStruct.Pin = seg7A8_Pin|seg7A9_Pin|seg7A10_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : seg7D4_Pin seg7dot_Pin */
  GPIO_InitStruct.Pin = seg7D4_Pin|seg7dot_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : PD4 PD5 PD6 PD7 */
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 1, 1);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  HAL_NVIC_SetPriority(EXTI1_IRQn, 1, 1);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  HAL_NVIC_SetPriority(EXTI2_TSC_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(EXTI2_TSC_IRQn);

  HAL_NVIC_SetPriority(EXTI4_IRQn, 1, 1);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
