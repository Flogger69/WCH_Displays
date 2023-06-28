/*
 * main.h
 *
 *  Created on: May 2, 2023
 *      Author: vl
 */

#include "ili9341.h"
#include "main.h"

//git proba

void ILI9341_Init(void){
	ILI9341_Reset();
	ILI9341_SoftReset();
	Delay_Ms(1);
	/* Power Control A */
	LCD_WR_REG(0xCB);
	LCD_WR_DATA(0x39);
	LCD_WR_DATA(0x2C);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x34);
	LCD_WR_DATA(0x02);
	/* Power Control B */
	LCD_WR_REG(0xCF);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0xC1);
	LCD_WR_DATA(0x30);
	/* Driver timing control A */
	LCD_WR_REG(0xE8);
	LCD_WR_DATA(0x85);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x78);
	/* Driver timing control B */
	LCD_WR_REG(0xEA);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);
	/* Power on Sequence control */
	LCD_WR_REG(0xED);
	LCD_WR_DATA(0x64);
	LCD_WR_DATA(0x03);
	LCD_WR_DATA(0x12);
	LCD_WR_DATA(0x81);
	/* Pump ratio control */
	LCD_WR_REG(0xF7);
	LCD_WR_DATA(0x30);
	/* Power Control 1 */
	LCD_WR_REG(0xC0);
	LCD_WR_DATA(0x10);
	/* Power Control 2 */
	LCD_WR_REG(0xC1);
	LCD_WR_DATA(0x10);
	/* VCOM Control 1 */
	LCD_WR_REG(0xC5);
	LCD_WR_DATA(0x3E);
	LCD_WR_DATA(0x28);
	/* VCOM Control 2 */
	LCD_WR_REG(0xC7);
	LCD_WR_DATA(0x86);
	/* VCOM Control 2 */
	LCD_WR_REG(0x36);
	LCD_WR_DATA(0x48);
	/* Pixel Format Set */
	LCD_WR_REG(0x3A);
	LCD_WR_DATA(0x55);    //16bit
	LCD_WR_REG(0xB1);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x18);
//#if 0
	// Little Endian for TouchGFX
//	LCD_WR_REG(0xF6);
//	LCD_WR_DATA(0x01);
//	LCD_WR_DATA(0x00);
//	LCD_WR_DATA(0x20); // Little Endian
//#endif
	/* Display Function Control */
	LCD_WR_REG(0xB6);
	LCD_WR_DATA(0x08);
	LCD_WR_DATA(0x82);
	LCD_WR_DATA(0x27);
	/* 3GAMMA FUNCTION DISABLE */
	LCD_WR_REG(0xF2);
	LCD_WR_DATA(0x00);
	/* GAMMA CURVE SELECTED */
	LCD_WR_REG(0x26); //Gamma set
	LCD_WR_DATA(0x01); 	//Gamma Curve (G2.2)
	//Positive Gamma  Correction
	LCD_WR_REG(0xE0);
	LCD_WR_DATA(0x0F);
	LCD_WR_DATA(0x31);
	LCD_WR_DATA(0x2B);
	LCD_WR_DATA(0x0C);
	LCD_WR_DATA(0x0E);
	LCD_WR_DATA(0x08);
	LCD_WR_DATA(0x4E);
	LCD_WR_DATA(0xF1);
	LCD_WR_DATA(0x37);
	LCD_WR_DATA(0x07);
	LCD_WR_DATA(0x10);
	LCD_WR_DATA(0x03);
	LCD_WR_DATA(0x0E);
	LCD_WR_DATA(0x09);
	LCD_WR_DATA(0x00);
	//Negative Gamma  Correction
	LCD_WR_REG(0xE1);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x0E);
	LCD_WR_DATA(0x14);
	LCD_WR_DATA(0x03);
	LCD_WR_DATA(0x11);
	LCD_WR_DATA(0x07);
	LCD_WR_DATA(0x31);
	LCD_WR_DATA(0xC1);
	LCD_WR_DATA(0x48);
	LCD_WR_DATA(0x08);
	LCD_WR_DATA(0x0F);
	LCD_WR_DATA(0x0C);
	LCD_WR_DATA(0x31);
	LCD_WR_DATA(0x36);
	LCD_WR_DATA(0x0F);
	//EXIT SLEEP
	LCD_WR_REG(0x11);

	Delay_Ms(120);

	//TURN ON DISPLAY
	LCD_WR_REG(0x29);
	LCD_WR_DATA(0x2C);

	LCD_direction(ROTATE_270);

}

void ILI9341_SetWindow(uint16_t start_x, uint16_t start_y, uint16_t end_x, uint16_t end_y){
	// Set Window
	LCD_WR_REG(0x2a);
	LCD_WR_DATA(start_x >> 8);
	LCD_WR_DATA(0xFF & start_x);
	LCD_WR_DATA(end_x >> 8);
	LCD_WR_DATA(0xFF & end_x);

	LCD_WR_REG(0x2b);
	LCD_WR_DATA(start_y >> 8);
	LCD_WR_DATA(0xFF & start_y);
	LCD_WR_DATA(end_y >> 8);
	LCD_WR_DATA(0xFF & end_y);

}

void ILI9341_WritePixel(uint16_t x, uint16_t y, uint16_t color)
{
	uint8_t data[2];
	data[0] = color >> 8;
	data[1] = color;
	ILI9341_SetWindow(x, y, x, y);
	// Enable to access GRAM
	LCD_WR_REG(0x2c);
	LCD_WR_DATA(data[0]);
	LCD_WR_DATA(data[1]);

}
void ILI9341_WriteChar(uint16_t x, uint16_t y, char ch, FontDef font, uint16_t color, uint16_t bgcolor)
{
    uint32_t i, b, j;
    ILI9341_SetWindow(x, y, x+font.width-1, y+font.height-1);
    LCD_WR_REG(0x2c);
    for(i = 0; i < font.height; i++) {
        b = font.data[(ch - 32) * font.height + i];
        for(j = 0; j < font.width; j++) {
            if((b << j) & 0x8000)  {
                uint8_t data[] = { color >> 8, color & 0xFF };
               ILI9341_WriteData(data, sizeof(data));
            } else {
                uint8_t data1[] = { bgcolor >> 8, bgcolor & 0xFF };
                ILI9341_WriteData(data1, sizeof(data1));
            }
        }
    }
}
void ILI9341_WriteString(uint16_t x, uint16_t y, const char* str, FontDef font, uint16_t color, uint16_t bgcolor) {
  //  TFT9341_Select();

    while(*str) {
        if(x + font.width >= LCD_WIDTH) {
           // x = 0;
            y += font.height;
            if(y + font.height >= LCD_HEIGHT) {
                break;
            }
            if(*str == ' ') {
                // skip spaces in the beginning of the new line
                str++;
                continue;
            }
        }
        ILI9341_WriteChar(x, y, *str, font, color, bgcolor);
        x += font.width;
        str++;
   }
}
void ILI9341_FillRect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color){
  if((x1 >= LCD_WIDTH) || (y1 >= LCD_HEIGHT) || (x2 >= LCD_WIDTH) || (y2 >= LCD_HEIGHT)) return;
	if(x1>x2) swap(x1,x2);
	if(y1>y2) swap(y1,y2);
	ILI9341_SetWindow(x1, y1, x2, y2);
	LCD_WR_REG(0x2c);
  for(uint32_t i = 0; i < (x2-x1+1)*(y2-y1+1); i++){
	  uint8_t data[] = { color >> 8, color & 0xFF };
	    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY)){}
	    DC_H();
		SPI_I2S_SendData(SPI1, data[0]);
		SPI_I2S_SendData(SPI1, data[1]);
  }
}
void ILI9341_FillScreen(uint16_t color)
{
  ILI9341_FillRect(0, 0, LCD_WIDTH-1, LCD_HEIGHT-1, color);
}
/**
static void ConvHL(uint8_t *s, int32_t l)
{
	uint8_t v;
	while (l > 0) {
		v = *(s+1);
		*(s+1) = *s;
		*s = v;
		s += 2;
		l -= 2;
	}
}
**/
void ILI9341_Reset(void)
{
	RESET_L();
	Delay_Ms(100);
	RESET_H();
	Delay_Ms(100);
	CS_L();
	LED_H();
}

void ILI9341_SoftReset(void)
{
	uint8_t cmd;
	cmd = 0x01; //Software reset
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY)){}
	DC_L();
	SPI_I2S_SendData(SPI1, cmd);
}


void LCD_WR_REG(uint8_t data)
{
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY)){}
    DC_L();
	SPI_I2S_SendData(SPI1, data);
}

void LCD_WR_DATA(uint8_t data)
{


    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY)){}
    DC_H();
	SPI_I2S_SendData(SPI1, data);
}

void ILI9341_WriteData(uint8_t* buff, size_t buff_size) {

    DC_H();


    for(int i = 0; i<buff_size; i++){
        while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY)){}
    	SPI_I2S_SendData(SPI1, *buff);
    }
}

//void LCD_IO_WriteMultipleData(uint8_t *pData, uint32_t Size)
//{
	/* Swap endianes */
//	ConvHL(pData, (int32_t)Size*2);

//	DC_H();
//	HAL_SPI_Transmit(&hspi1, (uint8_t*)pData, Size * 2, HAL_MAX_DELAY);
//	SPI_I2S_GetFlagStatus(SPI1, (SPI_I2S_FLAG_TXE && SPI_I2S_FLAG_BSY));
	//spiDmaTransferComplete = 0;
//	SPI_I2S_SendData(SPI1, data);
	//HAL_SPI_Transmit_DMA(&hspi1, pData, Size*2 );
	//HAL_SPI_Transmit_DMA(&hspi1, (uint8_t*)pData, Size );
	//while(spiDmaTransferComplete == 0);
//}
void LCD_direction(LCD_Horizontal_t direction)
{
	switch (direction) {
	case ROTATE_0:
		LCD_WR_REG(0x36);
		LCD_WR_DATA(0x48);
		break;
	case ROTATE_90:
		LCD_WR_REG(0x36);
		LCD_WR_DATA(0x28);
		break;
	case ROTATE_180:
		LCD_WR_REG(0x36);
		LCD_WR_DATA(0x88);
		break;
	case ROTATE_270:
		LCD_WR_REG(0x36);
		LCD_WR_DATA(0xE8);
		break;
	}
}

void RESET_L(void){
	GPIO_WriteBit(GPIOA, GPIO_Pin_3, Bit_RESET);
}

void RESET_H(void){
	GPIO_WriteBit(GPIOA, GPIO_Pin_3, Bit_SET);
}

void CS_L(void){
	GPIO_WriteBit(GPIOA, GPIO_Pin_1, Bit_RESET); // CS_
}
void CS_H(void){
	GPIO_WriteBit(GPIOA, GPIO_Pin_1, Bit_SET); // CS
}
void DC_L(void){
	GPIO_WriteBit(GPIOA, GPIO_Pin_2, Bit_RESET); //CD command
}
void DC_H(void){
	GPIO_WriteBit(GPIOA, GPIO_Pin_2, Bit_SET); //CD command
}
void LED_H(void){
	GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_SET);}
