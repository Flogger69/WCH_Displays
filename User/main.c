/********************************** (C) COPYRIGHT *******************************
* File Name          : main.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2021/06/06
* Description        : Main program body.
*********************************************************************************
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* Attention: This software (modified or not) and binary are used for 
* microcontroller manufactured by Nanjing Qinheng Microelectronics.
*******************************************************************************/

/*
 *@Note
 USART Print debugging routine:
 USART1_Tx(PA9).
 This example demonstrates using USART1(PA9) as a print debug port output.

*/
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "debug.h"

#include "ili9341.h"
#include "main.h"


/* Global typedef */

/* Global define */

/* Global Variable */



/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */

void MCU_INIT(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    SPI_InitTypeDef  SPI_InitStructure = {0};

    //RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
   // RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;// | GPIO_Pin_5 | GPIO_Pin_7;CS
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    //SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;


    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
     SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
     SPI_InitStructure.SPI_Mode = SPI_Mode_Master;

     SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
     SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
     SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
     SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
     SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
     SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
     //SPI_InitStructure.SPI_CRCPolynomial = 7;
     SPI_Init(SPI1, &SPI_InitStructure);

     SPI_Cmd(SPI1, ENABLE);
}

int main(void)
{
	u8 i = 0;


	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	SystemCoreClockUpdate();
	Delay_Init();
	USART_Printf_Init(115200);
	printf("SystemClk:%d\r\n",SystemCoreClock);
	printf( "ChipID:%08x\r\n", DBGMCU_GetCHIPID() );
	printf("This is printf example\r\n");

	MCU_INIT();
	ILI9341_Init();
	ILI9341_FillScreen(0x0000);
	ILI9341_FillRect(20,20,203,60,0xF800);
	//ILI9341_WriteString(uint16_t x, uint16_t y, const char* str, FontDef font, uint16_t color, uint16_t bgcolor)
	 //ILI9341_WriteChar(30, 30, 66, Font_11x18, 0xffff, 0);

	ILI9341_WriteString(30, 30,"HELO Font 11x18", Font_11x18, 0xffff,0);
	while(1)
    {
        Delay_Ms(500);
        GPIO_WriteBit(GPIOA, GPIO_Pin_0, (i == 0) ? (i = Bit_SET) : (i = Bit_RESET));
	}
}



