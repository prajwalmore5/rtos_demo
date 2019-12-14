/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */     
#include "usart.h"
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
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId redLEDHandle;
osThreadId greenLEDHandle;
osThreadId blueLEDHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
   
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void redLEDfn(void const * argument);
void greenLEDfn(void const * argument);
void blueLEDfn(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];
  
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}                   
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of redLED */
  osThreadDef(redLED, redLEDfn, osPriorityHigh, 0, 128);
  redLEDHandle = osThreadCreate(osThread(redLED), NULL);

  /* definition and creation of greenLED */
  osThreadDef(greenLED, greenLEDfn, osPriorityNormal, 0, 128);
  greenLEDHandle = osThreadCreate(osThread(greenLED), NULL);

  /* definition and creation of blueLED */
  osThreadDef(blueLED, blueLEDfn, osPriorityNormal, 0, 128);
  blueLEDHandle = osThreadCreate(osThread(blueLED), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{

  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {

    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_redLEDfn */
/**
* @brief Function implementing the redLED thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_redLEDfn */
void redLEDfn(void const * argument)
{
  /* USER CODE BEGIN redLEDfn */
  /* Infinite loop */

	char buffer[64];
	int count;
	int i;
  for(;;)
  {
	  HAL_GPIO_TogglePin(GPIOB, LD1_Pin);
	  for(i=0;i<5;i++)
	  {
		  count=sprintf(buffer,"Red LED running\r\n");
		  	  HAL_UART_Transmit(&huart2,buffer,count,100);
	  }
	  osDelay(2000);
  }
  /* USER CODE END redLEDfn */
}

/* USER CODE BEGIN Header_greenLEDfn */
/**
* @brief Function implementing the greenLED thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_greenLEDfn */
void greenLEDfn(void const * argument)
{
  /* USER CODE BEGIN greenLEDfn */
  /* Infinite loop */

	char buffer[64];
		int count;
		int i;
  for(;;)
  {
	  HAL_GPIO_TogglePin(GPIOB, LD2B4_Pin);
	  count=sprintf(buffer,"Green LED running\r\n");
	  	  HAL_UART_Transmit(&huart2,buffer,count,100);
    osDelay(2000);
  }
  /* USER CODE END greenLEDfn */
}

/* USER CODE BEGIN Header_blueLEDfn */
/**
* @brief Function implementing the blueLED thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_blueLEDfn */
void blueLEDfn(void const * argument)
{
  /* USER CODE BEGIN blueLEDfn */
  /* Infinite loop */

	char buffer[64];
		int count;
		int i;
  for(;;)
  {
	  HAL_GPIO_TogglePin(GPIOB, LD3_Pin);
	  count=sprintf(buffer,"Blue LED running\r\n");
	  	  	  HAL_UART_Transmit(&huart2,buffer,count,100);
    osDelay(2000);
  }
  /* USER CODE END blueLEDfn */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
