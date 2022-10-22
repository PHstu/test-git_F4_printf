/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "usart.h"
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

#include "stdio.h"

// 重定向print BEGIN
int __io_putchar(int ch)
{
	while ((USART1->SR & 0X40) == 0);  //循环发送，直到发完，USART1可改为其他串口号
	USART1->DR = (uint8_t) ch;
	return ch;
}

//_write函数在syscalls.c中， 使用__weak定义， 所以可以直接在其他文件中定义_write函數
__attribute__((weak)) int _write(int file, char *ptr, int len)
{
	int DataIdx;
	for (DataIdx = 0; DataIdx < len; DataIdx++)
	{
		__io_putchar(*ptr++);
	}
	return len;
}
// 重定向print END
// 重定向scanf BEGIN
int __io_getchar()
{
	int ch;
	HAL_UART_Receive(&huart1, (uint8_t *)&ch, 1, 0xFFFF);	//接收一个字节
	return ch;
}
// 重定向scanf END


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
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */

  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

//	  float adc_reg = 0.0;//模拟ADC数据
//	  float adc_result;//模拟ADC数据的计算结果
////	  double adc_reg = 0.0;//模拟ADC数据//双精度浮点测试
////	  double adc_result;//模拟ADC数据的计算结果//双精度浮点测试
//
//	  for(adc_reg = 0.1;adc_reg<400;adc_reg++)
//	  {
//		  adc_result = adc_reg*33/4096;//ADC计算
//
//		  printf("ADC = %f\r\n",adc_result);//浮点输出
////		  printf("ADC = %lf\r\n",adc_result);//浮点输出//双精度浮点测试//%lf可以输出double类型的数据
//		  HAL_Delay(12);
//		  printf("OK\r\n");//正常文字输出
		  HAL_Delay(12);
		  HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);//翻转工作指示灯
//	  }

	  //22·10·22预期实现：
	  //scanf接收翻转接收LED √
	  //添加更多注释 √
	  //浮点接收 √
	  //git新增非代码文件 √
	  //dma@scanf高速接收
	  //git更改非代码文件

//	  char receive[20] = {0};//注意接收字符串要使用char数组，注意数组初始化方式，使用初始化为0来清空字符串
//	  printf("\r\nPlease Input:");
//	  scanf("%s",&receive[0]);//注意取地址符和数组配合//重定义的scanf()在读到 空格 时才会认为字符串结束
//	  if(receive[1])//如果判断receive，会有receive常为真的worring
//	  {
//		  printf("%s\r\n",receive);//printf最好加上换行符，不容易卡死
//		  HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);//翻转接收指示灯
//	  }

	  float receive = 0.0;//接收浮点数
	  printf("\r\nPlease Input float type:");
	  scanf("%f",&receive);//注意取地址符和数组配合//重定义的scanf()在读到 空格 时才会认为字符串结束
	  if(receive)
	  {
		  printf("%3.4f\r\n",receive);//printf要加上换行符，不容易卡死
		  HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);//翻转接收指示灯
	  }

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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 160;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
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
