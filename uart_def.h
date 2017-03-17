/**
  ******************************************************************************
  * File Name          : uart_def.h
  * Description        : definition of uart port for each device
  ******************************************************************************
**/


#ifdef STM32F411xE
  extern UART_HandleTypeDef huart1;
  extern UART_HandleTypeDef huart2;
  extern UART_HandleTypeDef huart6;
  #define PC_PORT huart2
  #define PORT1 huart1
  #define PORT2 huart6
#endif

#ifdef STM32L476xx
  extern UART_HandleTypeDef huart1;
  extern UART_HandleTypeDef huart2;
  extern UART_HandleTypeDef huart3;
  #define PC_PORT huart2
  #define PORT1 huart1
  #define PORT2 huart3
#endif

