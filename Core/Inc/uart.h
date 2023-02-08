/*
 * uart.h
 *
 *  Created on: Feb 3, 2023
 *      Author: npedu024
 */

#ifndef INC_UART_H_
#define INC_UART_H_

#include "main.h"

// 프로토타입 설정 (main문에서 사용하기 위해)
void initUart();
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
uint8_t getChar();


#endif /* INC_UART_H_ */
