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
#include "spi.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

#define LED_COUNT 12  // 定义LED的数量
/*LED全局变量*/
uint8_t led_data[12][4]={0x1f,0x00,0x00,0x00,	//led阵列设置：亮度(最大0x1f)，蓝，绿，红
                    0x1f,0x00,0x00,0x00,
                    0x1f,0x00,0x00,0x00,
                    0x1f,0x00,0x00,0x00,
                    0x1f,0x00,0x00,0x00,
                    0x1f,0x00,0x00,0x00,
                    0x1f,0x00,0x00,0x00,
                    0x1f,0x00,0x00,0x00,
                    0x1f,0x00,0x00,0x00,
                    0x1f,0x00,0x00,0x00,
                    0x1f,0x00,0x00,0x00,
                    0x1f,0x00,0x00,0x00};
void SK9822_SendByte(uint8_t data)
{
    HAL_SPI_Transmit(&hspi1, &data, 1, HAL_MAX_DELAY);
}
void SK9822_StartFrame(void)
{
    uint8_t startFrame[4] = {0x00, 0x00, 0x00, 0x00};
    HAL_SPI_Transmit(&hspi1, startFrame, sizeof(startFrame), HAL_MAX_DELAY);
}
void SK9822_EndFrame(void)
{
    uint8_t endFrame[4] = {0xFF, 0xFF, 0xFF, 0xFF};
    HAL_SPI_Transmit(&hspi1, endFrame, sizeof(endFrame), HAL_MAX_DELAY);
}

void SK9822_SetLEDColor(uint8_t *led_data)
{
    SK9822_SendByte((*led_data)|0xE0);
    SK9822_SendByte(*(led_data+1));
    SK9822_SendByte(*(led_data+2));
    SK9822_SendByte(*(led_data+3));
}
void SK9822_clear(uint8_t led_num)
{
    uint8_t i,led_clear[4]={0,0,0,0};
    SK9822_StartFrame();
    for(i=0;i<led_num;i++)
    {
        SK9822_SetLEDColor(led_clear);
    }
    SK9822_EndFrame();
}
void SK9822_disp(uint8_t led_num,uint8_t led_data[][4])
{
    uint8_t i;
    SK9822_StartFrame();
    for(i=0;i<led_num;i++)
    {
        SK9822_SetLEDColor(*(led_data+i));
    }
    SK9822_EndFrame();
}
void controlLEDPattern(uint8_t ledIndex, uint8_t red, uint8_t green, uint8_t blue) {
    led_data[ledIndex][3] = red;    // 设置红色分量
    led_data[ledIndex][2] = green;  // 设置绿色分量
    led_data[ledIndex][1] = blue;   // 设置蓝色分量

    SK9822_disp(LED_COUNT, led_data);  // 更新LED显示
}

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
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
    while (1) {
    /* USER CODE END WHILE */
        for (int i = 0; i < 12; i++) {
            controlLEDPattern(i, 255/i, 8*i, 3*i);
            HAL_Delay(500);
        }
        controlLEDPattern(13, 25, 25, 30);
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
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

/* USER CODE BEGIN 4 */

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
    while (1) {
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
