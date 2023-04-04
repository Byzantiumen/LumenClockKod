/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define SEG_1_GPIO GPIOB
#define SEG_2_GPIO GPIOB
#define SEG_3_GPIO GPIOB
#define SEG_4_GPIO GPIOA
#define SEG_5_GPIO GPIOA
#define SEG_6_GPIO GPIOA
#define SEG_7_GPIO GPIOA
#define SEG_8_GPIO GPIOA
#define SEG_9_GPIO GPIOC

#define LUM_1_GPIO GPIOB
#define LUM_2_GPIO GPIOB
#define LUM_3_GPIO GPIOB
#define LUM_4_GPIO GPIOA
#define LUM_5_GPIO GPIOA
#define LUM_6_GPIO GPIOA
#define LUM_7_GPIO GPIOC
#define LUM_8_GPIO GPIOC
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM1_Init(void);
void TurnNumber(int number);
void TurnSegment(int number);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int del = 300;
int second = 0;
int minute = 0;
int hour = 0;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

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
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim1); // запуск таймера
  //TurnNumber(1);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  /*SEG_1 - LAST LEFT SEGMENT, SEG_9 - LAST RIGHT SEGMENT*/
	  /*SEG_1 - GPIOC, SEG_8_7_6_5_4 - GPIOA, SEG_3_2_1 - GPIOB*/
	  TurnSegment(1); // 1 second
	  TurnNumber(second%10);
	  HAL_Delay(0.8);
	  TurnSegment(2);// 2 second
	  TurnNumber(second/10);
	  HAL_Delay(0.8);
	  TurnSegment(3); // tire
	  TurnNumber(10);
	  HAL_Delay(0.8);
	  TurnSegment(4);
	  TurnNumber(minute%10);
	  HAL_Delay(0.8);
	  TurnSegment(5);
	  TurnNumber(minute/10);
	  HAL_Delay(0.8);
	  TurnSegment(6); // tire
	  TurnNumber(10);
	  HAL_Delay(0.8);
	  TurnSegment(7); // tire
	  TurnNumber(hour%10);
	  HAL_Delay(0.8);
	  TurnSegment(8); // tire
	  //TurnNumber(hour/10);
	  TurnNumber(0);
	  HAL_Delay(0.8);


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
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 800;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 10000;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, LUM_8_Pin|SEG_9_Pin|LUM_7_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, SEG_8_Pin|LUM_6_Pin|SEG_7_Pin|SEG_6_Pin
                          |LUM_5_Pin|SEG_5_Pin|SEG_4_Pin|LUM_4_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, SEG_3_Pin|LUM_3_Pin|SEG_2_Pin|SEG_1_Pin
                          |LUM_2_Pin|LUM_1_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LED_2_Pin|LED_1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LUM_8_Pin SEG_9_Pin LUM_7_Pin */
  GPIO_InitStruct.Pin = LUM_8_Pin|SEG_9_Pin|LUM_7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : SEG_8_Pin LUM_6_Pin SEG_7_Pin SEG_6_Pin
                           LUM_5_Pin SEG_5_Pin SEG_4_Pin LUM_4_Pin
                           LED_2_Pin LED_1_Pin */
  GPIO_InitStruct.Pin = SEG_8_Pin|LUM_6_Pin|SEG_7_Pin|SEG_6_Pin
                          |LUM_5_Pin|SEG_5_Pin|SEG_4_Pin|LUM_4_Pin
                          |LED_2_Pin|LED_1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : SEG_3_Pin LUM_3_Pin SEG_2_Pin SEG_1_Pin
                           LUM_2_Pin LUM_1_Pin */
  GPIO_InitStruct.Pin = SEG_3_Pin|LUM_3_Pin|SEG_2_Pin|SEG_1_Pin
                          |LUM_2_Pin|LUM_1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : TURN_Pin BUT_2_Pin BUT_1_Pin */
  GPIO_InitStruct.Pin = TURN_Pin|BUT_2_Pin|BUT_1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}



/* USER CODE BEGIN 4 */
void TurnNumber(int number)
{
	HAL_GPIO_WritePin(GPIOA, LUM_6_Pin|LUM_5_Pin|LUM_4_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, LUM_8_Pin|LUM_7_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, LUM_3_Pin|LUM_2_Pin|LUM_1_Pin, GPIO_PIN_SET);

	switch (number)
	{
		case 0:
			HAL_GPIO_WritePin(GPIOA, LUM_6_Pin|LUM_5_Pin|LUM_4_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, LUM_8_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, LUM_3_Pin|LUM_2_Pin|LUM_1_Pin, GPIO_PIN_RESET);
			break;
		case 1:
			HAL_GPIO_WritePin(GPIOB, LUM_3_Pin|LUM_2_Pin, GPIO_PIN_RESET);
			break;
		case 2:
			HAL_GPIO_WritePin(GPIOA, LUM_6_Pin|LUM_5_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, LUM_7_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, LUM_2_Pin|LUM_1_Pin, GPIO_PIN_RESET);
			break;
		case 3:
			HAL_GPIO_WritePin(GPIOA, LUM_5_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, LUM_7_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, LUM_3_Pin|LUM_2_Pin|LUM_1_Pin, GPIO_PIN_RESET);
			break;
		case 4:
			HAL_GPIO_WritePin(GPIOC, LUM_8_Pin|LUM_7_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, LUM_3_Pin|LUM_2_Pin, GPIO_PIN_RESET);
			break;
		case 5:
			HAL_GPIO_WritePin(GPIOA, LUM_5_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, LUM_8_Pin|LUM_7_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, LUM_3_Pin|LUM_1_Pin, GPIO_PIN_RESET);
			break;
		case 6:
			HAL_GPIO_WritePin(GPIOA, LUM_6_Pin|LUM_5_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, LUM_8_Pin|LUM_7_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, LUM_3_Pin|LUM_1_Pin, GPIO_PIN_RESET);
			break;
		case 7:
			HAL_GPIO_WritePin(GPIOB, LUM_3_Pin|LUM_2_Pin|LUM_1_Pin, GPIO_PIN_RESET);
			break;
		case 8:
			HAL_GPIO_WritePin(GPIOA, LUM_6_Pin|LUM_5_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, LUM_8_Pin|LUM_7_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, LUM_3_Pin|LUM_2_Pin|LUM_1_Pin, GPIO_PIN_RESET);
			break;
		case 9:
			HAL_GPIO_WritePin(GPIOA, LUM_5_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, LUM_8_Pin|LUM_7_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, LUM_3_Pin|LUM_2_Pin|LUM_1_Pin, GPIO_PIN_RESET);
			break;
		case 10:
			HAL_GPIO_WritePin(GPIOC, LUM_7_Pin, GPIO_PIN_RESET);
			break;

	}
}

void TurnSegment(int number)
{
	HAL_GPIO_WritePin(SEG_1_GPIO, SEG_1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(SEG_2_GPIO, SEG_2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(SEG_3_GPIO, SEG_3_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(SEG_4_GPIO, SEG_4_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(SEG_5_GPIO, SEG_5_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(SEG_6_GPIO, SEG_6_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(SEG_7_GPIO, SEG_7_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(SEG_8_GPIO, SEG_8_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(SEG_9_GPIO, SEG_9_Pin, GPIO_PIN_SET);

	switch (number)
	{
		case 1:
			HAL_GPIO_WritePin(SEG_1_GPIO, SEG_1_Pin, GPIO_PIN_RESET);
			break;
		case 2:
			HAL_GPIO_WritePin(SEG_2_GPIO, SEG_2_Pin, GPIO_PIN_RESET);
			break;
		case 3:
			HAL_GPIO_WritePin(SEG_3_GPIO, SEG_3_Pin, GPIO_PIN_RESET);
			break;
		case 4:
			HAL_GPIO_WritePin(SEG_4_GPIO, SEG_4_Pin, GPIO_PIN_RESET);
			break;
		case 5:
			HAL_GPIO_WritePin(SEG_5_GPIO, SEG_5_Pin, GPIO_PIN_RESET);
			break;
		case 6:
			HAL_GPIO_WritePin(SEG_6_GPIO, SEG_6_Pin, GPIO_PIN_RESET);
			break;
		case 7:
			HAL_GPIO_WritePin(SEG_7_GPIO, SEG_7_Pin, GPIO_PIN_RESET);
			break;
		case 8:
			HAL_GPIO_WritePin(SEG_8_GPIO, SEG_8_Pin, GPIO_PIN_RESET);
			break;
		case 9:
			HAL_GPIO_WritePin(SEG_9_GPIO, SEG_9_Pin, GPIO_PIN_RESET);
			break;

	}
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
