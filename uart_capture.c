/**
  ******************************************************************************
  * File Name          : uart_capture.c
  * Description        : to capture uart 
  ******************************************************************************
**/
/* Includes ------------------------------------------------------------------*/
#include "uart_capture.h"
#include "uart_def.h"
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

uint8_t pData1[rds];
uint8_t pData2[rds];
uint8_t wData[tds];
int restrt_flg1 =0;
int restrt_flg2 =0;
int txport = 0;
int txport_conf_flg = 0;

void uart_capture(void){

  HAL_UART_Receive_DMA(&PC_PORT, pData1, rds);
  HAL_UART_Receive_DMA(&PORT1, pData2, rds);
  while (1)
  {
    if(restrt_flg1){
      restrt_flg1=0;
      HAL_UART_Receive_DMA(&PC_PORT, pData1, rds);
    }
    if(restrt_flg2){
      restrt_flg2=0;
      if(txport) HAL_UART_Receive_DMA(&PORT2, pData2, rds);
      else HAL_UART_Receive_DMA(&PORT1, pData2, rds);
    }
    if(txport_conf_flg){
      txport_conf_flg = 0;
      if(txport) {
        txport = 0;
        HAL_UART_Init(&PORT1);
        HAL_UART_Receive_DMA(&PORT1, pData2, rds);
        HAL_UART_DeInit(&PORT2);
      }else {
        txport = 1;        
        HAL_UART_Init(&PORT2);
        HAL_UART_Receive_DMA(&PORT2, pData2, rds);
        HAL_UART_DeInit(&PORT1);
      }
    }
  }  
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if(huart == &PC_PORT){
    if(txport) HAL_UART_Transmit_DMA(&PORT2, pData1, rds);
    else      HAL_UART_Transmit_DMA(&PORT1, pData1, rds);
    HAL_UART_Transmit_DMA(&PC_PORT, pData1, rds);
    restrt_flg1 = 1;
  }
  if(huart == &PORT1 && txport == 0){
    HAL_UART_Transmit_DMA(&PC_PORT, pData2, rds);
    restrt_flg2 = 1;
  }
  if(huart == &PORT2 && txport == 1){
    HAL_UART_Transmit_DMA(&PC_PORT, pData2, rds);
    restrt_flg2 = 1;
  }
  
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  txport_conf_flg  = 1;  
}

#if 0
void HAL_UART_RxHalfCpltCallback(UART_HandleTypeDef *huart)
{
  if(huart == &PC_PORT){
    if(txport) HAL_UART_Transmit_DMA(&PORT2, pData1, rds);
    else      HAL_UART_Transmit_DMA(&PORT1, pData1, rds);
    HAL_UART_Transmit_DMA(&PC_PORT, pData1, rds);
    restrt_flg1 = 1;
  }
  if(huart == &PORT1 && txport == 0){
    HAL_UART_Transmit_DMA(&PC_PORT, pData2, rds);
    restrt_flg2 = 1;
  }
  if(huart == &PORT2 && txport == 1){
    HAL_UART_Transmit_DMA(&PC_PORT, pData2, rds);
    restrt_flg2 = 1;
  }
}
#endif



