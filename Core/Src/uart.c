/*
 * uart.c
 *
 *  Created on: Feb 3, 2023
 *      Author: npedu024
 */

#include "uart.h"
#include <stdio.h>

extern UART_HandleTypeDef huart1;

#define rxBufferMax 255
int rxBufferGp; // Get pointer (read)
int rxBufferPp; // Put pointer (write)
uint8_t rxBuffer[rxBufferMax]; // 메시지 보관
uint8_t rxChar;

// uart 장치 초기화. 입력 시 interrupt 발생.
void initUart()
{
	HAL_UART_Receive_IT(&huart1, &rxChar, 1);
}

// 문자 수신(interrupt) 처리.
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	rxBuffer[rxBufferPp++] = rxChar; // rxBuffer에 입력된 문자 저장.
	rxBufferPp %= rxBufferMax; // Put pointer가 255 도달 시 0으로.
	HAL_UART_Receive_IT(&huart1, &rxChar, 1); // Interrupt 재설정. uart 다시 켜주는 역할.
}

// 버퍼에서 문자 꺼내옴.
uint8_t getChar()
{
	uint8_t result;
	if (rxBufferGp == rxBufferPp)
		return 0; // 더 이상 꺼내올 정보가 없으면 0 반환.
	result = rxBuffer[rxBufferGp++]; // rxBuffer에 저장된 값 꺼내옴.
	rxBufferGp %= rxBufferMax; // Get pointer가 255 도달 시 0으로.
	return result;
}

// printf를 uart로 실행시키는 함수.
int _write(int file, char *p, int len)
{
	HAL_UART_Transmit(&huart1, p, len, 1);
	return len;
}
