/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "liquidcrystal_i2c.h"
#include "time.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int x=0;
void stampa(int elem[],time_t now,int moob2[]);
void spersonaggio(int A);
int verifica(int elem[],int A,int deel,int moob2[]);
int updatea(int elem[],int c1);
int updatea2(int elem[],int c2,int moob[]);
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	GPIO_PinState GPIO_state;

	 time_t now=time(NULL);

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

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
  MX_USART2_UART_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */

  HD44780_Init(4);
  HD44780_Clear();
  HD44780_SetCursor(0,0);
  HD44780_PrintStr("HELLO");
  HD44780_SetCursor(10,1);
  HD44780_PrintStr("WORLD");
  HD44780_SetCursor(0,3);
  HD44780_PrintStr("____________________");
  HAL_Delay(2000);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  int A=1;
	 	  int elem[23]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	 	  int moob2[23]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

	 	  int deel=0;
	 	  int c1=0,c2=0,c3=0,c4=0;

	 	  srand((unsigned) time(&now));


	 		  for ( int x = 400; x >= 1 ; x-- )
	          {
	 			  	  char n=NULL;
	 			  	  int a,b,c;
	   //---------------------------------------------------------------
	    //stampa ostacoli

	 		 HD44780_Clear();
	     	 stampa(elem,now,moob2);

	   //---------------------------------------------------------------
	     //stampa personaggio

	     	 GPIO_state=HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13);
	     	           if(GPIO_state == GPIO_PIN_SET){
	     	        	  A=1;

	     	        	  spersonaggio(A);

	     	           }
	     	           else {
	     	        	  A=0;
	     	        	  spersonaggio(A);
	     	           }
	     	           HD44780_SetCursor(0,4);
	     	           HD44780_PrintStr("--------------------");

	     	           c1=updatea(elem, c1);
	     	           c1++;
	     	           c2++;
	     	           c2=updatea2(elem,c2,moob2);
	     	 HAL_Delay (500-deel);
	   //----------------------------------------------------------------
	     //GAME OVER --



	     	 if(c2%5==0 && deel<450){
	     		 deel=deel+10;
	     	 }
	     	 c3=verifica(elem,A,deel,moob2);
	     	 /*if(c3==1){
	     		 deel=0;

	     	 }*/

	   //----------------------------------------------------------------
	     	 	 if(x==2){

	     	 		 	 	HD44780_Clear();
	     	 				HD44780_SetCursor(10,0);
	     	 				HD44780_PrintStr("YOU");
	     	 				HD44780_SetCursor(10,1);
	     	 				HD44780_PrintStr("WIN XD");
	     	 				HAL_Delay (2000);
	     	 	 }


	          }
	      HD44780_Clear();
	 	  }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void stampa(int elem[],time_t now,int moob2[]){

	for(int i=0;i<23;i++){
		if(elem[i]==1&&i<20){
		    	HD44780_SetCursor(i,2);
		    	HD44780_PrintSpecialChar(7);;
		}
		if(moob2[i]==1&&i<20){
				    	HD44780_SetCursor(i,0);
				    	HD44780_PrintSpecialChar(0);
				}
		if(i<22 /*&& elem[i]==1 && elem[i+1]==0*/){
			elem[i]=elem[i+1];
			moob2[i]=moob2[i+1];
		}
	}

	elem[22]=0;
	moob2[22]=0;

}

int verifica(int elem[],int A,int deel,int moob2[]){
	if((elem[1]==1 && A==1) ||(moob2[1]==1 && A==0) ){
		HD44780_Clear();
		HD44780_SetCursor(10,0);
		HD44780_PrintStr("GAME");
		HD44780_SetCursor(10,1);
		HD44780_PrintStr("OVER");
		HAL_Delay (2000);
		for(int i=0;i<23;i++){
			elem[i]=0;
			moob2[i]=0;
		}
		deel=0;
	}
	return 1;
}

void spersonaggio(int A){
						  HD44780_SetCursor(0,A);
	    	        	  HD44780_PrintSpecialChar(1);
	    	        	  HD44780_SetCursor(1,A);
	    	        	  HD44780_PrintSpecialChar(2);
	    	        	  HD44780_SetCursor(2,A);
	    	        	  HD44780_PrintSpecialChar(3);
	    	        	  HD44780_SetCursor(0,A+1);
	    	        	  HD44780_PrintSpecialChar(4);
	    	        	  HD44780_SetCursor(1,A+1);
	    	        	  HD44780_PrintSpecialChar(5);
	    	        	  HD44780_SetCursor(2,A+1);
	    	        	  HD44780_PrintSpecialChar(6);


}

int updatea(int elem[],int c1){

    int y=0;
    y = rand()%6;
	  //printf("numero random : %d",y);
	  if(c1==5){
      //printf("condizione ...\n");
      c1=0;
      switch(y){
       case 0:
          elem[20]=0;
          elem[21]=1;
          elem[22]=0;
       break;

        case 1:
          elem[20]=1;
          elem[21]=1;
          elem[22]=0;
        break;

        case 2:
          elem[20]=1;
          elem[21]=1;
          elem[22]=1;
        break;
        case 3:
          elem[20]=1;
          elem[21]=0;
          elem[22]=1;
        break;
        case 4:
          elem[20]=0;
          elem[21]=1;
          elem[22]=1;
       break;
       case 5:
          elem[20]=1;
          elem[21]=0;
          elem[22]=0;
       break;
       default:
          elem[20]=0;
          elem[21]=0;
          elem[22]=0;
      }
	 }
    return c1;
}

int updatea2(int elem[],int c2,int moob[]){



    for(int i=0;i<16;i++){
        if(elem[i]==0 && elem[i+1]==0 && elem[i+2]==0){
          moob[i]=0;
          moob[i+1]=1;
          moob[i+2]=0;
        }
        if(elem[i]==1&&moob[i]==1){
          moob[i]=0;
        }

    }
    return c2;
}


/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
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
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
