/*
 * smartRGB.c
 *
 *  Created on: 2019
 *      Author: liujian
 */

/******************************************************************************
Includes <System Includes>
******************************************************************************/
#include "Cpu.h"
#include "smartRGB_E355.h"
#include "userCode.h"
#include <math.h>
#include <stdlib.h>
#include "e351Data.h"


/******************************************************************************
Imported global variables and functions (from other files)
******************************************************************************/
extern int RegulateBreathing[10] ;
extern const uint16_t V1_DATA[50][3];

/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/

/****** RGB Data   START ******/
E355_DATA e355_FrameBuff[TOTAL_LEDS];

unsigned int randNum; //kian@2019-05-21 20:48:52 随机数的种子

uint8_t offset1 = 0;// 语音氛围灯，偏移量
uint8_t offset2 = 0;

/****** RGB Data   END ******

/******************************************************************************
Private global variables and functions
******************************************************************************/

/*
 * 控制变量，为了能够再次刷新一次性动画(非循环动画)
 * global animation control val
 */
uint8_t animation_first_in = 1;


void FunctionData(unsigned char Value1,unsigned char Value2,unsigned char Value3,unsigned char Value4,unsigned char Value5)
{
	int i = 0;//

	SMART_RGB_DATA_L; //PE12 = 0; //DIA
    SMART_RGB_CLK_L;//PE13 = 0; //CKI
	
	Value1 = (Value1 | Sbit_1 | Cbit_1);
	Value5 = (Value5 | LbitStop);
    
	for(i = 0; i<=7; i ++)
	{		
		if((Value1 & 0x80) == 0x80)
		{
			SMART_RGB_DATA_H;//PE12 = 1;
		}
		else
		{
			SMART_RGB_DATA_L;//PE12 = 0;
		}
		SMART_RGB_CLK_L;//PE13 = 0;
		__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");
        __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");
		__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");
		SMART_RGB_CLK_H;//PE13 = 1;
		__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");
		__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");
		SMART_RGB_CLK_L;//PE13 = 0;
		Value1 = (Value1 << 1);
	}
	
	i = 0;
	for(i = 0; i<=7; i ++)
	{		
		if((Value2 & 0x80) == 0x80)
		{
			SMART_RGB_DATA_H;//PE12 = 1;
		}
		else
		{
			SMART_RGB_DATA_L;//PE12 = 0;
		}
		SMART_RGB_CLK_L;//PE13 = 0;
		__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");
        __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");
		__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");
		// __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");
		// __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");
		// __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");
		// __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");
		SMART_RGB_CLK_H;//PE13 = 1;
		__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");
		__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");
		// __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");
		// __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");
		// __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");
		SMART_RGB_CLK_L;//PE13 = 0;
		Value2 = (Value2 << 1);
	}

	i = 0;
	for(i = 0; i<=7; i ++)
	{		
		if((Value3 & 0x80) == 0x80)
		{
			SMART_RGB_DATA_H;//PE12 = 1;
		}
		else
		{
			SMART_RGB_DATA_L;//PE12 = 0;
		}
		SMART_RGB_CLK_L;//PE13 = 0;
		__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");
        __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");
		__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");
		__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");
		__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");
		__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");
		__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");
		SMART_RGB_CLK_H;//PE13 = 1;
		__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");
		__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");
		__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");
		__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");
		__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");
		SMART_RGB_CLK_L;//PE13 = 0;
		Value3 = (Value3 << 1);
	}
	
	i = 0;
	for(i = 0; i<=7; i ++)
	{		
		if((Value4 & 0x80) == 0x80)
		{
			SMART_RGB_DATA_H;//PE12 = 1;
		}
		else
		{
			SMART_RGB_DATA_L;//PE12 = 0;
		}
		SMART_RGB_CLK_L;//PE13 = 0;
		__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");
        __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");
		__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");
		__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");
		__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");
		__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");
		__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");
		SMART_RGB_CLK_H;//PE13 = 1;
		__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");
		__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");
		__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");
		__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");
		__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");
		SMART_RGB_CLK_L;//PE13 = 0;
		Value4 = (Value4 << 1);
	}
	
	i = 0;

	for(i = 0; i<=7; i ++)
	{		
		if((Value5 & 0x80) == 0x80)
		{
			SMART_RGB_DATA_H;//PE12 = 1;
		}
		else
		{
			SMART_RGB_DATA_L;//PE12 = 0;
		}
		SMART_RGB_CLK_L;//PE13 = 0;
		__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");
        __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");
		__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");
		__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");
		__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");
		__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");
		__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");
		SMART_RGB_CLK_H;//PE13 = 1;
		__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");
		__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");
		__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");
		__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");
		__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");
		SMART_RGB_CLK_L;//PE13 = 0;
		Value5 = (Value5 << 1);
	}
	
	SMART_RGB_DATA_L;//PE12 = 0; //DIA
	SMART_RGB_CLK_L;//PE13 = 0; //CKI
	__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");
	__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");
	__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");
	__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");
	__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");
	__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");
}

/*
	uint16_t RED, uint16_t GREEN, uint16_t BLUE: maxValue = 0x0fff (4095)
*/
void sendImageData12bitMode(uint16_t RED, uint16_t GREEN, uint16_t BLUE, uint8_t Lbit)
{
	uint64_t dataToSend = 0;
	uint64_t temp = 0;
	uint8_t scr_data = 0x80;
	uint8_t i = 0;
	SMART_RGB_DATA_L;//PE12 = 0; //DIA
	SMART_RGB_CLK_L;//PE13 = 0; //CKI

	temp = scr_data;
	dataToSend = dataToSend | (temp <<(63-7)); // ѹ��SCR����  3bit

	temp = RED & 0x0FFF;
	dataToSend = dataToSend | (temp <<(60-11));// ѹ��RED����  12bit

	temp = GREEN & 0x0FFF;
	dataToSend = dataToSend | (temp <<(48-11));// ѹ��GREEN���� 12bit

	temp = BLUE & 0x0FFF;
	dataToSend = dataToSend | (temp <<(36-11));// ѹ��BLUE���� 12bit

	temp = (Lbit!=0)?1:0;
	dataToSend = dataToSend | (temp <<24); // ѹ�� L ����

	for(i = 0; i<40; i++)
	{
		if((dataToSend & 0x8000000000000000) == 0x8000000000000000)
		{
			SMART_RGB_DATA_H;//PE12 = 1;
		}
		else
		{
			SMART_RGB_DATA_L;//PE12 = 0;
		}
		dataToSend = (dataToSend << 1);

		SMART_RGB_CLK_L;//PE13 = 0;
		__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); 
		__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); 
		SMART_RGB_CLK_H;//PE13 = 1;
		__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); 
		__asm("nop"); __asm("nop"); //asm("nop"); asm("nop"); asm("nop");
		SMART_RGB_CLK_L;//PE13 = 0;
	}
		SMART_RGB_DATA_L;
		SMART_RGB_CLK_L;
}

void sendData(E351_Type data)
{
	uint8_t i = 0;
	SMART_RGB_DATA_L;//PE12 = 0; //DIA
	SMART_RGB_CLK_L;//PE13 = 0; //CKI

	for(i = 0; i<40; i++)
	{
		switch(i)
		{
			case 0: if(data.bits.d0)SMART_RGB_DATA_H;else SMART_RGB_DATA_L; break;
			case 1: if(data.bits.d1)SMART_RGB_DATA_H;else SMART_RGB_DATA_L; break;
			case 2: if(data.bits.d2)SMART_RGB_DATA_H;else SMART_RGB_DATA_L; break;
			case 3: if(data.bits.d3)SMART_RGB_DATA_H;else SMART_RGB_DATA_L; break;
			case 4: if(data.bits.d4)SMART_RGB_DATA_H;else SMART_RGB_DATA_L; break;
			case 5: if(data.bits.d5)SMART_RGB_DATA_H;else SMART_RGB_DATA_L; break;
			case 6: if(data.bits.d6)SMART_RGB_DATA_H;else SMART_RGB_DATA_L; break;
			case 7: if(data.bits.d7)SMART_RGB_DATA_H;else SMART_RGB_DATA_L; break;
			case 8: if(data.bits.d8)SMART_RGB_DATA_H;else SMART_RGB_DATA_L; break;
			case 9: if(data.bits.d9)SMART_RGB_DATA_H;else SMART_RGB_DATA_L; break;
			case 10: if(data.bits.d10)SMART_RGB_DATA_H;else SMART_RGB_DATA_L; break;
			case 11: if(data.bits.d11)SMART_RGB_DATA_H;else SMART_RGB_DATA_L; break;
			case 12: if(data.bits.d12)SMART_RGB_DATA_H;else SMART_RGB_DATA_L; break;
			case 13: if(data.bits.d13)SMART_RGB_DATA_H;else SMART_RGB_DATA_L; break;
			case 14: if(data.bits.d14)SMART_RGB_DATA_H;else SMART_RGB_DATA_L; break;
			case 15: if(data.bits.d15)SMART_RGB_DATA_H;else SMART_RGB_DATA_L; break;
			case 16: if(data.bits.d16)SMART_RGB_DATA_H;else SMART_RGB_DATA_L; break;
			case 17: if(data.bits.d17)SMART_RGB_DATA_H;else SMART_RGB_DATA_L; break;
			case 18: if(data.bits.d18)SMART_RGB_DATA_H;else SMART_RGB_DATA_L; break;
			case 19: if(data.bits.d19)SMART_RGB_DATA_H;else SMART_RGB_DATA_L; break;
			case 20: if(data.bits.d20)SMART_RGB_DATA_H;else SMART_RGB_DATA_L; break;
			case 21: if(data.bits.d21)SMART_RGB_DATA_H;else SMART_RGB_DATA_L; break;
			case 22: if(data.bits.d22)SMART_RGB_DATA_H;else SMART_RGB_DATA_L; break;
			case 23: if(data.bits.d23)SMART_RGB_DATA_H;else SMART_RGB_DATA_L; break;
			case 24: if(data.bits.d24)SMART_RGB_DATA_H;else SMART_RGB_DATA_L; break;
			case 25: if(data.bits.d25)SMART_RGB_DATA_H;else SMART_RGB_DATA_L; break;
			case 26: if(data.bits.d26)SMART_RGB_DATA_H;else SMART_RGB_DATA_L; break;
			case 27: if(data.bits.d27)SMART_RGB_DATA_H;else SMART_RGB_DATA_L; break;
			case 28: if(data.bits.d28)SMART_RGB_DATA_H;else SMART_RGB_DATA_L; break;
			case 29: if(data.bits.d29)SMART_RGB_DATA_H;else SMART_RGB_DATA_L; break;
			case 30: if(data.bits.d30)SMART_RGB_DATA_H;else SMART_RGB_DATA_L; break;
			case 31: if(data.bits.d31)SMART_RGB_DATA_H;else SMART_RGB_DATA_L; break;
			case 32: if(data.bits.d32)SMART_RGB_DATA_H;else SMART_RGB_DATA_L; break;
			case 33: if(data.bits.d33)SMART_RGB_DATA_H;else SMART_RGB_DATA_L; break;
			case 34: if(data.bits.d34)SMART_RGB_DATA_H;else SMART_RGB_DATA_L; break;
			case 35: if(data.bits.d35)SMART_RGB_DATA_H;else SMART_RGB_DATA_L; break;
			case 36: if(data.bits.d36)SMART_RGB_DATA_H;else SMART_RGB_DATA_L; break;
			case 37: if(data.bits.d37)SMART_RGB_DATA_H;else SMART_RGB_DATA_L; break;
			case 38: if(data.bits.d38)SMART_RGB_DATA_H;else SMART_RGB_DATA_L; break;
			case 39: if(data.bits.d39)SMART_RGB_DATA_H;else SMART_RGB_DATA_L; break;
		}
		SMART_RGB_CLK_L;//PE13 = 0;
		__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); 
		__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); 
		__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); 
		__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); 
		__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); 
		__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); 
		    // __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); 
		    // __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); 
		SMART_RGB_CLK_H;//PE13 = 1;
		__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); 
		__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); 
		__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); 
		__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); 
		__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); 
		__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); 
		    // __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); 
		    // __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); 
		SMART_RGB_CLK_L;//PE13 = 0;
	}
	// SMART_RGB_DATA_L;
	// SMART_RGB_CLK_L;
}

void sendFunctionData(uint8_t value1,uint8_t value2,uint8_t value3,uint8_t value4,uint8_t value5)
{
	E351_Type data;
	data.dBeyte[4] = value1;
	data.dBeyte[3] = value2;
	data.dBeyte[2] = value3;
	data.dBeyte[1] = value4;
	data.dBeyte[0] = value5;

	sendData(data);
}

void sendImageData(uint16_t red, uint16_t green, uint16_t blue, uint8_t Lbit)
{
	E351_Type data;	
	data.imgData.s = 1;
	data.imgData.c = 0;
	data.imgData.red = red;
	data.imgData.green = green;
	data.imgData.blue = blue;
	data.imgData.latch = Lbit;

	sendData(data);
}



void send12bitImgData(uint16_t R, uint16_t G, uint16_t B, uint8_t currentNum, uint8_t totalNum)
{
	uint8_t latchData = 0;

	if(currentNum == (totalNum-1) )
	{
		latchData = 1;
	}
	else
	{
		latchData = 0;
	}
	// sendImageData12bitMode(R,G,B,latchData);
	sendImageData(R,G,B,latchData);
}



void liteonLED_V2_inti(void)
{
	delay(10000);
	FunctionData(0xC0, 0x00, 0x00, 0x00, 0x01);
    delay(10000);
	FunctionData(0xC0, 0x05, 0x7F, 0xFF, 0xDF);
	// FunctionData(0xC0, 0x05, 0x7F, 0xFF, 0xC1);
	delay(10000);
}


void rainBown(uint8_t numLEDS)
{			
    static uint8_t initOnce = 0;
    uint8_t totalLEDs = 0;
    uint16_t R,G,B,latchData;
    static double angle = 0;
    static double startAngle = 0;
    static uint8_t fadeInOut = 0;

    double sinD = 0;
    
    if( startAngle >= 6.28)
    {
        startAngle = startAngle - 6.28;
    }
    else
    {
        startAngle = startAngle + 0.1;    
    }
    

    angle = startAngle;
    
    for(totalLEDs = 0; totalLEDs <numLEDS; totalLEDs++)
    {
        if( angle >= 6.28)
        {
            angle = angle-6.28;
        }
        else
        {
            angle = angle + 0.1;    
        }

        sinD = sin(angle);
        R = 4095 * ((1+sinD)/2);//sin(angle);
        sinD = sin(angle+1.57);
        G = 4095 * ((1+sinD)/2);//sin(angle+1.57);
        sinD = sin(angle+3.14);
        B = 4095 * ((1+sinD)/2);//sin(angle+3.14);

        if(totalLEDs == (numLEDS-1) )
        {
            latchData = 1;
        }
        else
        {
            latchData = 0;
        }
        sendImageData12bitMode(R,G,B,latchData);
    }
}

void ledsAllBlack(uint8_t numLEDS)
{			
    static uint8_t initOnce = 0;
    uint8_t totalLEDs = 0;
    uint16_t R,G,B,latchData;
    static double angle = 0;
    static double startAngle = 0;
    static uint8_t fadeInOut = 0;

    double sinD = 0;
        
    for(totalLEDs = 0; totalLEDs <numLEDS; totalLEDs++)
    {
        R = 0;
        G = 0;
        B = 0;

        if(totalLEDs == (numLEDS-1) )
        {
            latchData = 1;
        }
        else
        {
            latchData = 0;
        }
        sendImageData12bitMode(R,G,B,latchData);
    }
}

void ledsAllWhite(uint8_t numLEDS)
{			
    static uint8_t initOnce = 0;
    uint8_t totalLEDs = 0;
    uint16_t R,G,B,latchData;
        
    for(totalLEDs = 0; totalLEDs <numLEDS; totalLEDs++)
    {
        R = 0x001F;//0x00FF;
        G = 0x001F;//0x00FF;
        B = 0x001F;//0x00FF;

        if(totalLEDs == (numLEDS-1) )
        {
            latchData = 1;
        }
        else
        {
            latchData = 0;
        }
        sendImageData12bitMode(R,G,B,latchData);
    }
	// asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");
	// asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");
	// asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");
}

void rgbChange(uint8_t numLEDS)
{			
    volatile static uint16_t delay500ms = 0;
    uint8_t totalLEDs = 0;
    uint16_t R,G,B,latchData;

	volatile static uint8_t model = 0;

	delay500ms++;
	if(delay500ms>500)
	{
		delay500ms = 0;
		model++;
		if(model>2)
		{
			model = 0;
		}
	}
        
    for(totalLEDs = 0; totalLEDs <numLEDS; totalLEDs++)
    {
		switch(model)
		{
			case 0: R = 0x007F; G = 0x0000; B = 0x0000; break;
			case 1: R = 0x0000; G = 0x007F; B = 0x0000; break;
			case 2: R = 0x0000; G = 0x0000; B = 0x007F; break;
		}

        if(totalLEDs == (numLEDS-1) )
        {
            latchData = 1;
        }
        else
        {
            latchData = 0;
        }
        ///// sendImageData12bitMode(R,G,B,latchData);
		sendImageData(R,G,B,latchData);
    }
	// asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");
	// asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");
	// asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");
}

void ledsBreath(void)
{
    uint8_t num = 0;

    uint16_t Rhythm;

    static uint16_t prescalar = 0;
    static uint8_t times = 0;
    static uint8_t upDown = 0;

	uint16_t latchData;

    uint8_t localTempo = 2;

    if(times <= 4)
    {
        Rhythm = RegulateBreathing[0] * localTempo;
    }
    else if(times >= 5 || times <= 9)
    {
        Rhythm = RegulateBreathing[1] * localTempo;
    }
    else if(times >= 10 || times <= 14)
    {
        Rhythm = RegulateBreathing[2] * localTempo;
    }
    else if(times >= 15 || times <= 19)
    {
        Rhythm = RegulateBreathing[3] * localTempo;
    }
    else if(times >= 20 || times <= 24)
    {
        Rhythm = RegulateBreathing[4] * localTempo;
    }
    else if(times >= 25 || times <= 29)
    {
        Rhythm = RegulateBreathing[5] * localTempo;
    }
    else if(times >= 30 || times <= 34)
    {
        Rhythm = RegulateBreathing[6] * localTempo;
    }
    else if(times >= 35|| times <= 39)
    {
        Rhythm = RegulateBreathing[7] * localTempo;
    }
    else if(times >= 40 || times <= 44)
    {
        Rhythm = RegulateBreathing[8] * localTempo;
    }
    else if(times >= 45 || times <= 49)
    {
        Rhythm = RegulateBreathing[9] * localTempo;
    }

    prescalar++;

    if(prescalar < Rhythm)
    {
        return;
    }
    else
    {
        prescalar = 0;
    }


    switch (upDown)
    {
        case 0:
            times++;
            if(times >= 49)
            {
                upDown = 1;
            }
            break;

        case 1:
            times--;
            if(times == 0)
            {
                upDown = 0;
            }
            break;

        default : upDown = 0;
    }

    for(num = 0; num<TOTAL_LEDS; num++)
    {
		if(num == (TOTAL_LEDS-1) )
        {
            latchData = 1;
        }
        else
        {
            latchData = 0;
        }
        sendImageData12bitMode(V1_DATA[times][0],V1_DATA[times][1],V1_DATA[times][2],latchData);
	}
}





void warning_red(void)
{
	uint16_t totalTime_ms = 3000;	/*period according to specification*/
	uint16_t x_axis_total = totalTime_ms/REFRESH_T_MS;
	uint16_t x_axis_up_step = x_axis_total/3;
	uint16_t x_axis_down_step = 2 * x_axis_up_step;

	uint16_t maxRedValue = RGB_MAX_VALUE;
	uint16_t minRedValue = 0;
	uint16_t ratio_up = maxRedValue / x_axis_up_step;
	uint16_t ratio_down = maxRedValue / x_axis_down_step;

	static uint16_t redValue = 0;
	static uint16_t x_axis = 0;
	static uint8_t currentIndex = 0;

	if(x_axis<x_axis_up_step)
	{
		if(redValue< maxRedValue)
		{
			redValue = redValue + ratio_up;
		}
	}
	else if(x_axis>=x_axis_up_step && x_axis<x_axis_total)
	{
		redValue = (redValue<ratio_down)?0:(redValue- ratio_down);
		if(redValue> (minRedValue+ratio_down))
		{
			redValue = redValue - ratio_down;
		}
	}
	else
	{
		x_axis = 0;
	}
	x_axis++;

	for(currentIndex = 0;currentIndex < TOTAL_LEDS;currentIndex++)
	{
		send12bitImgData(redValue,0,0,currentIndex,TOTAL_LEDS);
	}

}

#if 1
void warning_yellow(void)
{
	uint16_t totalTime_ms = 2000;
	uint16_t x_time_axis = totalTime_ms/REFRESH_T_MS;
	uint16_t x_half_time_axis = x_time_axis / 2;

	uint16_t maxRedValue = RGB_MAX_VALUE;//0x7ff;
	uint16_t minRedValue = 0;
	static uint16_t redValue = 0;

	uint16_t maxGreenValue = RGB_MAX_VALUE;//0x7ff;
	uint16_t minGreenValue = 0;
	static uint16_t greenValue = 0;

	static uint16_t x_axis = 0;

	uint16_t ratio_up = 2 * maxRedValue / x_time_axis;
	uint16_t ratio_down = 2 * maxRedValue / x_time_axis;

	static uint8_t currentIndex = 0;

	if(x_axis < x_half_time_axis)
	{
		if(redValue< maxRedValue)
		{
			redValue = redValue + ratio_up;
			greenValue = greenValue + ratio_up;
		}
	}
	else if(x_axis>=x_half_time_axis && x_axis<x_time_axis)
	{
		if(redValue> (minRedValue+ratio_down))
		{
			redValue =(redValue>=ratio_down)?(redValue - ratio_down):0;
			greenValue =(greenValue>=ratio_down)?(greenValue - ratio_down):0;
		}
	}
	else
	{
		x_axis = 0;
	}
	x_axis++;

	for(currentIndex = 0;currentIndex < TOTAL_LEDS;currentIndex++)
	{
		// if(currentIndex < 50)
		send12bitImgData(redValue,greenValue,0,currentIndex,TOTAL_LEDS);
		// else
		// send12bitImgData(0,0,0,currentIndex,TOTAL_LEDS);
		
	}

}
#else

void warning_yellow(void)
{
	uint16_t totalTime_ms = 200;

	uint16_t maxRedValue = 0x7ff;
	uint16_t minRedValue = 0;
	static uint16_t redValue = 0;

	uint16_t maxGreenValue = 0x7ff;
	uint16_t minGreenValue = 0;
	static uint16_t greenValue = 0;

	static uint16_t x_axis = 0;

	uint16_t ratio_up = 20;
	uint16_t ratio_down = 20;

	static uint8_t currentIndex = 0;

	if(x_axis<100)
	{
		if(redValue< maxRedValue)
		{
			redValue = redValue + ratio_up;
			greenValue = greenValue + ratio_up;
		}
	}
	else if(x_axis>=100 && x_axis<totalTime_ms)
	{
		if(redValue> (minRedValue+ratio_down))
		{
			redValue = redValue - ratio_down;
			greenValue = greenValue - ratio_down;
		}
	}
	else
	{
		x_axis = 0;
	}
	x_axis++;

	for(currentIndex = 0;currentIndex < TOTAL_LEDS;currentIndex++)
	{
		if(currentIndex < 50)
		send12bitImgData(redValue,greenValue,0,currentIndex,TOTAL_LEDS);
		else
		send12bitImgData(0,0,0,currentIndex,TOTAL_LEDS);
		
	}

}


#endif


/***********************************************************************************/

/*
 * @function 
 */

void set_positions_rgb(uint8_t start_pos, uint8_t end_pos, uint16_t r, uint16_t g, uint16_t b)
{
    uint8_t pos;

    if(start_pos > end_pos) {
        return;
    }

    sendFunctionData(0xc0, 0x00, 0x00, 0x00, 0x01);
    sendFunctionData(0xc0, 0x05, 0x7f, 0xff, 0xd7);


    for(pos = end_pos + 1; pos <= TOTAL_LEDS - 1; pos ++) {
        sendImageData(0, 0, 0, 0);
    }

    if(start_pos == 0) {
        for(pos = start_pos + 1; pos <= end_pos; pos ++) {
            sendImageData(r, g, b, 0);
        }
        sendImageData(r, g, b, 1);

    }
    else {
        for(pos = start_pos; pos <= end_pos; pos ++) {
            sendImageData(r, g, b, 0);
        }

        for(pos = 0; pos < start_pos; pos ++) {
            if(pos + 1 == start_pos) {
                sendImageData(0, 0, 0, 1);
            }
            else {
                sendImageData(0, 0, 0, 0);
            }
        }
    }
}

void set_positions_rgb2(uint8_t start_pos, uint8_t end_pos, uint16_t r, uint16_t g, uint16_t b,uint8_t latch)
{
    uint8_t pos;

    if(start_pos > end_pos) {
        return;
    }

    sendFunctionData(0xc0, 0x00, 0x00, 0x00, 0x01);
    sendFunctionData(0xc0, 0x05, 0x7f, 0xff, 0xd7);


    for(pos = end_pos + 1; pos <= TOTAL_LEDS - 1; pos ++) {
        sendImageData(0, 0, 0, 0);
    }

    if(start_pos == 0) {
        for(pos = start_pos + 1; pos <= end_pos; pos ++) {
            sendImageData(r, g, b, 0);
        }
        sendImageData(r, g, b, latch);

    }
    else {
        for(pos = start_pos; pos <= end_pos; pos ++) {
            sendImageData(r, g, b, 0);
        }

        for(pos = 0; pos < start_pos; pos ++) {
            if(pos + 1 == start_pos) {
                sendImageData(0, 0, 0, latch);
            }
            else {
                sendImageData(0, 0, 0, 0);
            }
        }
    }
}


/*
 * @leds: proceent of the r, g, b, 0~100
 */
void update_according_array(uint8_t leds[TOTAL_LEDS], uint16_t r, uint16_t g, uint16_t b)
{
    int cnt;
    uint16_t r_val;
    uint16_t g_val;
    uint16_t b_val;

    sendFunctionData(0xc0, 0x00, 0x00, 0x00, 0x01);
    sendFunctionData(0xc0, 0x05, 0x7f, 0xff, 0xdf);


    for(cnt = TOTAL_LEDS-1; cnt >= 0; cnt --) {
        r_val = r * (leds[cnt] / ((float)100));
        g_val = g * (leds[cnt] / ((float)100));
        b_val = b * (leds[cnt] / ((float)100));

        if(cnt == 0) {
            sendImageData(r_val, g_val, b_val, 1);
        }
        else{
            sendImageData(r_val, g_val, b_val, 0);
        }
    }
}


/*
 *
 */

int show_color_n_ms(uint8_t start_pos, uint8_t end_pos, uint16_t r, uint16_t g, uint16_t b, uint32_t N, uint8_t letOff, uint8_t *firstIn) 
{
    static uint32_t cnt = 0;
    

    if(firstIn && *firstIn == 1) {
        *firstIn = 0;
        cnt = 0;
    }

    if(cnt >= N) {
        return 1;
    }

    cnt ++;

    if(cnt == 1) {
        set_positions_rgb(start_pos, end_pos, r, g, b);
    }
    else if(cnt == N && letOff) {
        set_positions_rgb(start_pos, end_pos, 0x0, 0x0, 0x0);
    }

    return cnt < N;
}

int delay_n_ms(uint32_t N, uint8_t *firstIn) {
    static uint32_t cnt = 0;

    if(firstIn && *firstIn == 1) {
        *firstIn = 0;

        cnt = 0;
    }

    if(cnt < N) {
        cnt ++;
    }

    return cnt == N;
}

int spread_specific_positions(uint16_t r, uint16_t g, uint16_t b, uint8_t speed, uint8_t tempo, uint8_t limit_left, uint8_t limit_right, uint8_t *firstIn)
{
    static uint8_t start_pos = 0;
    static uint8_t end_pos = 0;
    static uint8_t prescalar = 0;

    if(limit_left > limit_right) {
        return 1;
    }

    if(firstIn && *firstIn == 1) {
        *firstIn = 0;
        start_pos = (limit_left + limit_right)/2;
        end_pos = (limit_left + limit_right)/2;
        prescalar = 0;
    }

    if(start_pos == limit_left && end_pos == limit_right) {
        return 1;
    }

    prescalar ++;
    if(prescalar < tempo) {
        return 0;
    }
    else {
        prescalar = 0;
    }

    start_pos = (start_pos > limit_left + speed)? (start_pos -speed) : limit_left;
    end_pos = (end_pos + speed < limit_right)? (end_pos + speed) : (limit_right);
    set_positions_rgb(start_pos, end_pos, r, g, b);

    return (start_pos == limit_right && end_pos == limit_right);
}

int shrink_specific_positions(uint16_t r, uint16_t g, uint16_t b, uint8_t speed, uint8_t tempo, uint8_t limit_left, uint8_t limit_right, uint8_t cond, uint8_t *firstIn)
{
    static uint8_t start_pos = 0;
    static uint8_t end_pos = 0;
    static uint8_t prescalar = 0;

    if(firstIn && *firstIn == 1) {
        *firstIn = 0;
        start_pos = limit_left;
        end_pos = limit_right;
        prescalar = 0;
    }

    if(end_pos < start_pos + cond) {
        return 1;
    }

    prescalar ++;

    if(prescalar < tempo) {
        return 0;
    }
    else {
        prescalar = 0;
    }


    start_pos += speed;
    end_pos -= speed;

    if(start_pos > end_pos) {
        return 1;
    }

    set_positions_rgb(start_pos, end_pos, r, g, b);
    return 0;
}

/*
 * @function: color change from a to b according to preserved data
 * @direction:0: 0 --> 49; 1: 49 --> 0;
 */
int a2b_half(uint16_t data[50][3], uint8_t direction, uint8_t regulateBreathing[10], uint8_t localTempo, uint8_t *firstIn)
{
    uint8_t num;
    uint16_t rhythm;

    static uint16_t prescalar = 0;
    static uint8_t times;
    static uint8_t up_finished = 0, down_finished = 0; // up: 0 --> 49; down: 49 --> 0

    if(firstIn && *firstIn == 1) {
        *firstIn = 0;
        times = (direction == 0)? 0 : 49;
        up_finished = 0;
        down_finished = 0;
    }

    if(up_finished || down_finished) {
        return 1;
    }

    if(times <= 4) {
        rhythm = regulateBreathing[0] * localTempo;
    }
    else if(times >= 5 && times <= 9) {
        rhythm = regulateBreathing[1] * localTempo;
    }
    else if(times >= 10 && times <= 14) {
        rhythm = regulateBreathing[2] * localTempo;
    }
    else if(times >= 15 && times <= 19) {
        rhythm = regulateBreathing[3] * localTempo; 
    }
    else if(times >= 20 && times <= 24) {
        rhythm = regulateBreathing[4] * localTempo;
    }
    else if(times >= 25 && times <= 29) {
        rhythm = regulateBreathing[5] * localTempo; 
    }
    else if(times >= 30 && times <= 34) {
        rhythm = regulateBreathing[6] * localTempo;
    }
    else if(times >= 35 && times <= 39) {
        rhythm = regulateBreathing[7] * localTempo;
    }
    else if(times >= 40 && times <= 44) { 
        rhythm = regulateBreathing[8] * localTempo;
    }
    else if(times >= 45 && times <= 49) {
        rhythm = regulateBreathing[9] * localTempo;
    }

    prescalar ++;
    if(prescalar < rhythm) {
        return 0;
    }
    else {
        prescalar = 0;
    }

    switch(direction) {
        case 0:
            times ++;
            if(times >= 49) {
                up_finished = 1;
            }
            break;

        case 1:
            times --;
            if(times == 0) {
                down_finished = 1;
            }
            break;

    }

    set_positions_rgb(0, TOTAL_LEDS-1, data[times][0], data[times][1], data[times][2]);

    return (up_finished || down_finished)? 1 : 0;
}

/*
 * @function: 整条灯条为(r,g,b)，根据方向从亮-->灭，或者 灭-->亮, 只进行一次
 * @arguments:
 *      @r, g, b: red, green, blue value
 *      @direction: 0: 0 --> ntimes, 暗到亮; 1: ntimes --> 0, 亮到灭
 *      @tempo:  n次中断刷新进行一次渐变
 *      @ntimes: 从明到暗渐变所进行的步数
 *      @firstIn: 为1时重置所有的静态变量
 * @return: 完成半次呼吸返回1, 否则返回0
 */
int breath_half(uint16_t r, uint16_t g, uint16_t b, uint8_t direction, uint8_t tempo, uint8_t ntimes, uint8_t left_pos, uint8_t right_pos,  uint8_t *firstIn)
{
    uint16_t r_val, g_val, b_val;
    float procent = 0;
    float f_ntimes = (float)ntimes;
    static uint8_t prescalar = 0;
    static uint8_t times = 0;

    if(firstIn && *firstIn == 1) {
        *firstIn = 0;
        times = 0;
        prescalar = 0;
    }

    if(times >= ntimes) {
        return 1;
    }

    prescalar ++; 

    if(prescalar < tempo) {
        return 0;
    }
    else {
        prescalar = 0;
    }

    times ++;

    switch(direction) {
        case 0:
            procent = times/f_ntimes;
            r_val = r * procent;
            g_val = g * procent;
            b_val = b * procent;
            break;

        case 1:
            procent = 1 - times/f_ntimes;
            r_val = r * procent;
            g_val = g * procent;
            b_val = b * procent;
            break;
    }

    set_positions_rgb(left_pos, right_pos, r_val, g_val, b_val);

    return (times >= ntimes)? 1 : 0;

}

/*
 * @function: 整条灯条为(r,g,b)，根据方向从亮-->灭-->亮，或者 灭-->亮-->灭, 只进行一次
 * @arguments:
 *      @r, g, b: red, green, blue value
 *      @direction: 0: 0 --> ntimes, 暗-->亮-->暗; 1: ntimes --> 0, 亮-->灭-->亮
 *      @tempo:  n次中断刷新进行一次渐变
 *      @ntimes: 从明到暗渐变的次数
 *      @firstIn: 为1时重置所有的静态变量
 * @return: 完成一次呼吸返回1, 否则返回0
 */
int breath_once(uint16_t r, uint16_t g, uint16_t b, uint8_t direction, uint8_t tempo, uint8_t ntimes, uint8_t left_pos, uint8_t right_pos, uint8_t *firstIn)
{
    uint16_t r_val, g_val, b_val;
    float procent = 0;
    float f_ntimes = (float)ntimes;
    static uint8_t prescalar = 0;
    static uint8_t times = 0;

    if(firstIn && *firstIn == 1) {
        *firstIn = 0;
        times = 0;
        prescalar = 0;
    }

    if(times >= 2 * ntimes) {
        return 1;
    }

    prescalar ++; 

    if(prescalar < tempo) {
        return 0;
    }
    else {
        prescalar = 0;
    }

    times ++;

    switch(direction) {
        case 0:
            procent = (times < ntimes)? times/f_ntimes : (1 - (times - ntimes)/f_ntimes);
            r_val = r * procent;
            g_val = g * procent;
            b_val = b * procent;
            break;

        case 1:
            procent = (times < ntimes)? (1 - times/f_ntimes) : (times - ntimes)/f_ntimes;
            r_val = r * procent;
            g_val = g * procent;
            b_val = b * procent;
            break;
    }

    set_positions_rgb(left_pos, right_pos, r_val, g_val, b_val);

    return (times >= 2*ntimes)? 1 : 0;

}


/*
 * @function: 整条灯带不停的呼吸
 * @arguments:
 *      @r, g, b: red, green, blue value
 *      @direction: 0: 0 --> ntimes, 暗-->亮-->暗; 1: ntimes --> 0, 亮-->灭-->亮
 *      @tempo:  n次中断刷新进行一次渐变
 *      @ntimes: 从明到暗渐变的次数
 * NOTE: tempo和ntimes可以调节呼吸速度
 */
#if 0
void breath_repeat(uint16_t r, uint16_t g, uint16_t b, uint8_t direction, uint8_t tempo, uint8_t ntimes, uint8_t left_pos, uint8_t right_pos)
{
    static uint8_t firstInBreathOnce = 1;

    if(breath_once(r, g, b, direction, tempo, ntimes, left_pos, right_pos, &firstInBreathOnce) == 1) {
        firstInBreathOnce = 1;
    }
}
#else
/* 
 * 没有延迟的情况下，刷新一次大概是15ms
 * fade_in fade_out 各占50%
 */
void breath_repeat(uint16_t r, uint16_t g, uint16_t b, uint16_t period_ms, uint8_t left_pos, uint8_t right_pos)
{
    static uint8_t cnt = 0;

	uint16_t x_axis_total = period_ms/REFRESH_T_MS;
	uint16_t x_axis_half = x_axis_total/2;

	uint16_t maxRedValue = (r > RGB_MAX_VALUE)?RGB_MAX_VALUE:r;
    uint16_t maxGreenValue = (g > RGB_MAX_VALUE)?RGB_MAX_VALUE:g;
    uint16_t maxBlueValue = (b > RGB_MAX_VALUE)?RGB_MAX_VALUE:b;

    float red_ratio = (float)maxRedValue / x_axis_half;
    float green_ratio = (float)maxGreenValue / x_axis_half;
    float blue_ratio = (float)maxBlueValue / x_axis_half;

	static uint16_t redValue = 0;
    static uint16_t greenValue = 0;
    static uint16_t blueValue = 0;
	static uint16_t x_axis = 0;
	static uint8_t ledIndex = 0;

	if(x_axis < x_axis_half)
	{
        redValue = (redValue < maxRedValue)?(redValue+red_ratio):maxRedValue;
        greenValue = (greenValue < maxGreenValue)?(greenValue+green_ratio):maxGreenValue;
        blueValue = (blueValue < maxBlueValue)?(blueValue+blue_ratio):maxBlueValue;
	}
	else if(x_axis>=x_axis_half && x_axis<x_axis_total)
	{
        redValue = (redValue<red_ratio)?0:(redValue - red_ratio);
        greenValue = (greenValue<green_ratio)?0:(greenValue - green_ratio);
        blueValue = (blueValue<blue_ratio)?0:(blueValue - blue_ratio);
	}
	else
	{
		x_axis = 0;
	}
	x_axis++;

    cnt++;
    if(cnt>8)
    {
        cnt = 0;
        sendFunctionData(0xC0, 0x00, 0x00, 0x00, 0x01);
        sendFunctionData(0xC0, 0x05, 0x7F, 0xFF, 0xDF);
    }
    

	for(ledIndex = 0; ledIndex < TOTAL_LEDS; ledIndex ++)
	{
        if(ledIndex < left_pos)
        {
            send12bitImgData(0, 0, 0, ledIndex, TOTAL_LEDS);
        }
        else if( (ledIndex >= left_pos) && (ledIndex <= right_pos))
        {
            send12bitImgData(redValue, greenValue, blueValue, ledIndex, TOTAL_LEDS);
        }
        else if((ledIndex > right_pos) && (ledIndex <= TOTAL_LEDS))
        {
            send12bitImgData(0, 0, 0, ledIndex, TOTAL_LEDS);
        }
	}

}
#endif

/*********************** basic help functions end *******************************/



/*********************help function for light_welcome() start ***********************/
/*
 * @function: 整条灯带白光从中间往两边扩散
 * @arguments:
 *      @speed: 灯带第刷新一次单边所增加的亮的LED的颗数
 *      @tempo: how many interruputs/calls to refresh the total leds
 *      @firstIn: control to restart
 * @return: return 1 as the animation finished, otherwise return 0
 * NOTES:
 *      所有的非循环的动画，动画结束进return 1， 没有结束的时候return 0;
 */

int two_sides_spread2(uint16_t r, uint16_t g, uint16_t b, uint8_t speed,uint8_t part, uint8_t tempo, uint8_t *firstIn)
{
    static uint8_t start_pos = TOTAL_LEDS/2-1;
    static uint8_t end_pos = TOTAL_LEDS/2;
    static uint8_t prescalar = 0;
    static uint8_t fsasl=0;
    if(firstIn && *firstIn == 1) {
        *firstIn = 0;
        start_pos = TOTAL_LEDS/2;
        end_pos = TOTAL_LEDS/2 + 2;
        prescalar = 0;
    }


    if(start_pos == 0 && end_pos == TOTAL_LEDS - 1) {
        return 1;
    }

    prescalar ++;
    if(prescalar < tempo) {
        return 0;
    }
    else {
        prescalar = 0;
    }

    if(end_pos<=part+start_pos)
    {
    	fsasl++;
    	start_pos=(start_pos > fsasl)? (start_pos -fsasl) : ((TOTAL_LEDS-part)/2-1);
    	end_pos = (end_pos + fsasl < TOTAL_LEDS - 1)? (end_pos + fsasl) : (TOTAL_LEDS-(TOTAL_LEDS-part)/2 - 1);
    }
    else
    {
    	fsasl--;
    	if(fsasl>speed)
    	{
    		start_pos = (start_pos > fsasl)? (start_pos -fsasl) : 0;
			end_pos = (end_pos + fsasl < TOTAL_LEDS - 1)? (end_pos + fsasl) : (TOTAL_LEDS - 1);
    	}
    	else
    	{
    		start_pos = (start_pos > speed)? (start_pos -speed) : 0;
			end_pos = (end_pos + speed < TOTAL_LEDS - 1)? (end_pos + speed) : (TOTAL_LEDS - 1);
    	}
    }
    set_positions_rgb(start_pos, end_pos, r, g, b);
    if(start_pos == 0 && end_pos == TOTAL_LEDS - 1) {
        return 1;
    }
    vTaskDelay(5);
    return 0;
}
// 从白光过渡到蓝光，暂时没有实现
int white2blue2( uint8_t speed, uint8_t tempo, uint8_t *firstIn)
{
	static uint8_t start_pos = 0;
	static uint8_t end_pos = TOTAL_LEDS-1;
	static uint8_t prescalar = 0;
	static uint8_t i=0;
	if(firstIn && *firstIn == 1) {
		*firstIn = 0;
		prescalar = 0;
		i = 0;
	}

	if(i>=41)
	{
		return 1;
	}

	prescalar ++;
	if(prescalar < tempo) {
		return 0;
	}
	else {
		prescalar = 0;
	}
	set_positions_rgb(start_pos, end_pos, welcome_white2blue_DATA2[i][0], welcome_white2blue_DATA2[i][1], welcome_white2blue_DATA2[i][2]);
	i++;
	vTaskDelay(5);
	if(i>=41)
	{
		return 1;
	}
	return 0;
}

// blue leds breath only once
int blue_breath_once(uint8_t *firstIn)
{

    uint16_t r_val = 0x0f;
    uint16_t g_val = 0x7f;
    uint16_t b_val = 0x7f;
    uint8_t direction = 1;
    uint8_t tempo = 3;
    uint8_t ntimes = 50;

    static uint8_t firstInBreathHalf = 1;

    if(firstIn && *firstIn == 1) {
        *firstIn = 0;

        firstInBreathHalf = 1;
    }

    return breath_half(r_val, g_val, b_val, direction, tempo, ntimes, 0, TOTAL_LEDS-1, &firstInBreathHalf);
}
/*********************help function for light_welcome() end ***********************/


/************* help function for light_INT_analyzing() start ****************/
/*
 * @function: flow from center to limit
 * @arguments:
 *      @center: 开始位置
 *      @flow_limit: the postion flow ends at
 *      @firstIN: control to restart the animation
 */
void INT_positions_analyzing(uint8_t center_pos_at_begin, uint8_t flow_limit, uint8_t *firstIn)
{

    uint8_t tempo = 2;
    uint8_t start_pos = 0;
    uint8_t end_pos = 0;
    uint8_t target_side_len = 5;
    uint8_t rhythmControl[3] = {2, 1, 2};
    uint8_t rhythm;

    static uint8_t prescalar = 0;
    static uint8_t center_pos = 50;
    static int side_len = 0;
    static uint8_t cur_period = 0;

    if(firstIn && *firstIn == 1) {
        *firstIn = 0;

        cur_period = 0;
        prescalar = 0;
        center_pos = center_pos_at_begin;
        side_len = 0;
    }

    if(side_len < 0) {
        return 1;
    }

    switch(cur_period) {
        case 0:
            rhythm = tempo * rhythmControl[0];
            break;

        case 1:
            rhythm = tempo * rhythmControl[1];
            break;

        case 2:
            rhythm = tempo * rhythmControl[2]; 
            break;
    }


    prescalar ++;
    if(prescalar < rhythm) {
        return;
    }
    else {
        prescalar = 0;
    }

    switch(cur_period) {
        case 0:
            side_len ++;
            if(side_len >= target_side_len) {
                cur_period = 1;
            }
            break;

        case 1:
            center_pos -= 1;
            if(center_pos == flow_limit) {
                cur_period = 2;
            }
            break;

        case 2:
            side_len --;
            break;
    }


    if(side_len >= 0) {
        start_pos = (center_pos >= side_len)? center_pos - side_len : 0;
        end_pos = (center_pos + side_len > TOTAL_LEDS -1)? TOTAL_LEDS-1 : center_pos + side_len;

        set_positions_rgb(start_pos, end_pos, 0x3f, 0x3f, 0x3f);
    }
    else {
        set_positions_rgb(start_pos, end_pos, 0x0, 0x0, 0x0);
    }
}
/************* help function for light_INT_analyzing() end ******************/

/************* help function for light_goodbye() start ***********/
/*
 * @function: 从两边收缩至中间
 */
int shrink2center(uint16_t r, uint16_t g, uint16_t b, uint8_t speed, uint8_t tempo, uint8_t cond, uint8_t *firstIn)
{
    static uint8_t start_pos = 0;
    static uint8_t end_pos = TOTAL_LEDS - 1;
    static uint8_t prescalar = 0;

    if(firstIn && *firstIn == 1) {
        *firstIn = 0;
        start_pos = 0;
        end_pos = TOTAL_LEDS - 1;
        prescalar = 0;
    }

    prescalar ++;

    if(prescalar < tempo) {
        return 0;
    }
    else {
        prescalar = 0;
    }

    if((end_pos - start_pos) < cond) {
        return 1;
    }

    start_pos += speed;
    end_pos -= speed;

    if(start_pos > end_pos) {
        return 1;
    }

    set_positions_rgb(start_pos, end_pos, r, g, b);
    return 0;
}


/*
 * @function: 敕条灯带由灭渐变到蓝色
 */
int out2blue(uint8_t *firstIn)
{
    uint8_t direction = 0;
    uint16_t r_val = 0x0f;
    uint16_t g_val = 0x7f;
    uint8_t ntimes = 20;
    uint16_t b_val = 0x7f;
    uint8_t tempo = 2;

    static uint8_t firstInBreathHalf = 1;

    if(firstIn && *firstIn == 1) {
        *firstIn = 0;
    }

    if(breath_half(r_val, g_val, b_val, direction, tempo, ntimes, 0, TOTAL_LEDS-1, &firstInBreathHalf) == 1) {
        return 1;
    }
    return 0;
}

#define INIT_SIDE_LEN 1
#define INIT_MID_LEN 5
/*
 * @function: 白光扩散，渐灭效果
 * @arguments:
 *      @firstIn: *firstIn为1时，重置所有的静态变量的值
 * @return: 扩散渐灭完成后返回1；否则返回0
 */
int white_crash_at_center(uint8_t *firstIn)
{
    uint8_t leds[TOTAL_LEDS] = {0};
    uint8_t tempo = 5;
    uint8_t cnt = 0;
    uint8_t limit_left, limit_right;
    uint8_t t0 = 4;
    uint8_t t1 = t0 + 4;
    uint8_t t2 = t1 + 5;
    uint8_t t3 = t2 + 20;
    uint8_t t4 = t3 + 20;
    uint8_t p3_fading_speed = 5;
    uint8_t p4_fading_speed = 5;
    uint8_t p4_shrink_speed = 1;
    uint8_t dumm = 0;

    static uint8_t center_left = TOTAL_LEDS/2 - (INIT_SIDE_LEN + INIT_MID_LEN) - 1;
    static uint8_t center_middle = TOTAL_LEDS/2;
    static uint8_t center_right = TOTAL_LEDS/2 + (INIT_SIDE_LEN + INIT_MID_LEN) +1;
    static uint8_t prescalar = 0;
    static uint8_t times = 0;
    static int side_len_left = INIT_SIDE_LEN, side_len_middle = INIT_MID_LEN, side_len_right = INIT_SIDE_LEN;


    if(firstIn && *firstIn == 1) {
        *firstIn = 0;
        center_left = TOTAL_LEDS/2 - (INIT_SIDE_LEN + INIT_MID_LEN) - 1;
        center_middle = TOTAL_LEDS/2;
        center_right = TOTAL_LEDS/2 + (INIT_SIDE_LEN + INIT_MID_LEN) + 1;
        prescalar = 0;
        times = 0;
        side_len_left = INIT_SIDE_LEN, side_len_middle = INIT_MID_LEN, side_len_right = INIT_SIDE_LEN;
    }

    if(times > t4) {
        return 1;
    }


    prescalar ++;
    if(prescalar < tempo) {
        return 0;
    }
    else {
        prescalar = 0;
    }

    times ++;

    if(times <= t0) { // p0: do nothing
    }
    else if(times >= t0+1 && times <= t1) { // p1: side move causing gap
        center_left -= 2;
        center_right += 2;
        side_len_middle += 1;
    }
    else if(times >= t1+1 && times <= t2) { // p2: Middle spread, side keep the gap
        center_left -= 1;
        center_right += 1;
        side_len_middle += 1;
    }
    else if(times >= t2+1 && times <= t3) { // p3: Middle fadeing, side keep moving
    	static int cnt1=0;
    	cnt1++;
    	if(cnt1%5==0)
    	{
    		center_left -= 1;
    		center_right += 1;
    	}
    }
    else if(times >= t3+1 && times <= t4) { // p4: side fading
    	static int cnt=0;
    	cnt++;
    	if(cnt%5==0)
    	{
    		center_left -= 1;
    		center_right += 1;
    		side_len_left-= 1;
    		side_len_right-= 1;
    	}
    }

    //update the leds array
    if(side_len_left >= 0) {
            limit_left = (center_left > side_len_left)? center_left-side_len_left: 0;
            limit_right = (center_left + side_len_left > TOTAL_LEDS -1)? TOTAL_LEDS-1 : center_left + side_len_left;
            for(cnt = limit_left; cnt <= limit_right; cnt ++) {
                if(times >= t3+1 && times <= t4) {
                	leds[cnt] = (100 > p4_fading_speed * (times - t3))? 100 - p4_fading_speed * (times - t3) : 0;
                }
                else if(times > t4) {
                    leds[cnt] = 0;
                }
                else {
                    leds[cnt] = 100;
                }
            }
        }

    if(side_len_middle >= 0) {
        limit_left = (center_middle > side_len_middle)? center_middle - side_len_middle : 0;
        limit_right = (center_middle + side_len_middle > TOTAL_LEDS-1)? TOTAL_LEDS-1 : center_middle + side_len_middle;
        for(cnt = limit_left; cnt <= limit_right; cnt ++) {
            if(times >= t2+1 && times <= t3) {
                leds[cnt] = (100 > p3_fading_speed * (times - t2))? 100 - p3_fading_speed * (times - t2) : 0;
            }
            else if(times >= t3+1) {
                leds[cnt] = 0;
            }
            else {
                leds[cnt] = 100;
            }
        }
    }

    if(side_len_right >= 0) {
            limit_left = (center_right > side_len_right)? center_right - side_len_right : 0;
            limit_right = (center_right + side_len_right > TOTAL_LEDS-1)? TOTAL_LEDS-1 : center_right + side_len_right;
            for(cnt = limit_left; cnt <= limit_right; cnt ++) {
                if(times >= t3+1 && times <= t4) {
                	leds[cnt] = (100 > p4_fading_speed * (times - t3))? 100 - p4_fading_speed * (times - t3) : 0;
                }
                else if(times > t4) {
                    leds[cnt] = 0;
                }
                else {
                    leds[cnt] = 100;
                }
            }
        }

    update_according_array(leds, 0x3f, 0x3f, 0x3f);
    return 0;
}
/********* help function for light_goodbye() ends *********************/

/***************** help function for light_TA_activate() start **************/
// TA动画中间两边扩散
int TA_spread(uint8_t *firstIn) 
{
    uint8_t period_nums = 8;
    uint8_t cnt = 0;
    uint8_t leds[TOTAL_LEDS] = {0};
    uint8_t tempo = 20;

    // p0 config: No1 on
    uint8_t No1_P0_on_times = 3;

    // p1 config: No1 keep , No2 off
    uint8_t P1_len_limit = 4;
    uint8_t P1_L_limit = TOTAL_LEDS/2 - P1_len_limit;
    uint8_t P1_R_limit = TOTAL_LEDS/2 + P1_len_limit + 1;

    // p2 config: No1 spread, No2 off
    uint8_t P2_L_limit = 60;
    uint8_t P2_R_limit = TOTAL_LEDS - 1 - P2_L_limit;
    uint8_t P2_high_speed = 7;
    uint8_t P2_low_speed = 3;

    // p3 config: No1 slowly shrink, No2 keep
    uint8_t No1_P3_high_speed = 6;
    uint8_t No1_P3_low_speed = 2;

    uint8_t No2_P3_len_limit = 4;
    uint8_t No2_P3_L_limit = TOTAL_LEDS/2 - No2_P3_len_limit;
    uint8_t No2_P3_R_limit = TOTAL_LEDS/2 + No2_P3_len_limit + 1;
    uint8_t No2_P3_speed = 1;


    // p4 config: No1 shrink to edge; No2 slowly spread
    uint8_t No1_P4_L_limit = 0;
    uint8_t No1_P4_R_limit = TOTAL_LEDS - 1;
    uint8_t No1_P4_high_speed = 6;
    uint8_t No1_P4_low_speed = 4;

    uint8_t No2_P4_high_speed = 5;
    uint8_t No2_P4_low_speed = 2;

    // P5 config: No2 fast spread
    uint8_t No2_P5_L_limit = 53;
    uint8_t No2_P5_R_limit = TOTAL_LEDS - 1 - No2_P5_L_limit;
    uint8_t No2_P5_high_speed = 7;
    uint8_t No2_P5_low_speed = 3;


    // P6 config: No2 shrink
    uint8_t No2_P6_L_limit = 0;
    uint8_t No2_P6_R_limit = TOTAL_LEDS - 1;
    uint8_t No2_P6_high_speed = 8;
    uint8_t No2_P6_low_speed = 4;


    static uint8_t cur_period = 0;
    static uint8_t prescalar = 0;
    static uint8_t firstInDelay = 1;

    static uint8_t No1_L_start_pos = TOTAL_LEDS/2;
    static uint8_t No1_L_end_pos = TOTAL_LEDS/2 ;
    static uint8_t No1_R_start_pos = TOTAL_LEDS/2 + 1;
    static uint8_t No1_R_end_pos = TOTAL_LEDS/2 + 1;
    static uint8_t No1_on = 1;

    static uint8_t No2_L_start_pos = TOTAL_LEDS/2;
    static uint8_t No2_L_end_pos = TOTAL_LEDS/2 ;
    static uint8_t No2_R_start_pos = TOTAL_LEDS/2 + 1;
    static uint8_t No2_R_end_pos = TOTAL_LEDS/2 + 1;
    static uint8_t No2_on = 0;

    if(firstIn && *firstIn == 1) {
        *firstIn = 0;

        cur_period = 0;
        prescalar = 0;
        firstInDelay = 1;
        No1_L_start_pos = TOTAL_LEDS/2;
        No1_L_end_pos = TOTAL_LEDS/2 ;
        No1_R_start_pos = TOTAL_LEDS/2 + 1;
        No1_R_end_pos = TOTAL_LEDS/2 + 1;
        No1_on = 1;

        No2_L_start_pos = TOTAL_LEDS/2;
        No2_L_end_pos = TOTAL_LEDS/2 ;
        No2_R_start_pos = TOTAL_LEDS/2 + 1;
        No2_R_end_pos = TOTAL_LEDS/2 + 1;
        No2_on = 0;
    }

    if(cur_period >= period_nums) {
        return 1;
    }

    prescalar ++;

    if(prescalar < tempo) {
        return 0;
    }
    else {
        prescalar = 0;
    }

    switch(cur_period) {
        case 0:
            if(delay_n_ms(No1_P0_on_times, &firstInDelay) == 1) {
                cur_period = 1;
            }
            break;

        case 1:
            No1_L_start_pos = (No1_L_start_pos > P1_L_limit)? No1_L_start_pos-1 : P1_L_limit;
            No1_L_end_pos = No1_L_start_pos;

            No1_R_start_pos = (No1_R_start_pos < P1_R_limit)? No1_R_start_pos + 1 : P1_R_limit;
            No1_R_end_pos = No1_R_start_pos;

            No1_on = 1;
            No2_on = 0;
            if(No1_L_start_pos == P1_L_limit && No1_R_start_pos == P1_R_limit) {
                cur_period = 2;
            }
            break;

        case 2:
            No1_L_start_pos -= P2_high_speed;
            No1_L_end_pos -= P2_low_speed;

            No1_R_start_pos += P2_low_speed;
            No1_R_end_pos += P2_high_speed;

            No1_on = 1;
            No2_on = 0;
            if(No1_L_end_pos <= P2_L_limit && No1_R_start_pos >= P2_R_limit) {
                cur_period = 3;
            }
            break;

        case 3:
            No1_L_start_pos -= No1_P3_low_speed;
            No1_L_end_pos -= No1_P3_high_speed;

            No1_R_start_pos += No1_P3_high_speed;
            No1_R_end_pos += No1_P3_low_speed;

            No2_L_start_pos -= No2_P3_speed;
            No2_L_end_pos -= No2_P3_speed;

            No2_R_start_pos += No2_P3_speed;
            No2_R_end_pos += No2_P3_speed;

            if(No2_L_start_pos <= No2_P3_L_limit && No2_R_end_pos >= No2_P3_R_limit) {
                cur_period = 4;
            }

            No1_on = 1;
            No2_on = 1;
            break;

        case 4:
            No1_L_start_pos = (No1_L_start_pos > No1_P4_L_limit + No1_P4_low_speed)? No1_L_start_pos - No1_P4_low_speed : No1_P4_L_limit;
            No1_L_end_pos = (No1_L_end_pos > No1_L_start_pos + No1_P4_high_speed)? No1_L_end_pos - No1_P4_high_speed: No1_L_start_pos;

            No1_R_end_pos = (No1_R_end_pos + No1_P4_low_speed < No1_P4_R_limit)? No1_R_end_pos + No1_P4_low_speed: No1_P4_R_limit;
            No1_R_start_pos = (No1_R_start_pos + No1_P4_high_speed < No1_P4_R_limit)? No1_R_start_pos + No1_P4_high_speed : No1_P4_R_limit;

            No2_L_start_pos -= No2_P4_high_speed;
            No2_L_end_pos -= No2_P4_low_speed;

            No2_R_start_pos += No2_P4_low_speed;
            No2_R_end_pos += No2_P4_high_speed;

            No1_on = 1;
            No2_on = 1;

            if(No1_L_end_pos == No1_P4_L_limit && No1_R_start_pos == No1_P4_R_limit) {
                cur_period = 5;
            }
            break;

        case 5:
            No2_L_start_pos -= No2_P5_high_speed;
            No2_L_end_pos -= No2_P5_low_speed;

            No2_R_start_pos += No2_P5_low_speed;
            No2_R_end_pos += No2_P5_high_speed;

            No1_on = 0;
            No2_on = 1;

            if(No2_L_end_pos <= No2_P5_L_limit && No2_R_start_pos >= No2_P5_R_limit) {
                cur_period = 6;
            }
            break;

        case 6:
            No2_L_start_pos = (No2_L_start_pos > No2_P6_L_limit + No2_P6_low_speed)? No2_L_start_pos - No2_P6_low_speed : No2_P6_L_limit;
            No2_L_end_pos = (No2_L_end_pos > No2_P6_high_speed + No2_L_start_pos)? No2_L_end_pos - No2_P6_high_speed : No2_L_start_pos;

            No2_R_end_pos = (No2_R_end_pos + No2_P6_low_speed < TOTAL_LEDS - 1)? No2_R_end_pos + No2_P6_low_speed : TOTAL_LEDS - 1;
            No2_R_start_pos = (No2_R_start_pos + No2_P6_high_speed < No2_R_end_pos)? No2_R_start_pos + No2_P6_high_speed: No2_R_end_pos;

            No1_on = 0;
            No2_on = 1;
            if(No2_L_end_pos == No2_P6_L_limit && No2_R_start_pos == No2_P6_R_limit) {
                cur_period = 7;
            }
            break;

        case 7:
            No1_on = 0;
            No2_on = 0;
            cur_period = 8;
            break;
    }

    // update leds
    if(No1_on) {
        for(cnt = No1_L_start_pos; cnt <= No1_L_end_pos; cnt ++) {
            leds[cnt] = 100;
        }

        for(cnt = No1_R_start_pos; cnt <= No1_R_end_pos; cnt ++) {
            leds[cnt] = 100;
        }
    }

    if(No2_on) {
        for(cnt = No2_L_start_pos; cnt <= No2_L_end_pos; cnt ++) {
            leds[cnt] = 100;
        }

        for(cnt = No2_R_start_pos; cnt <= No2_R_end_pos; cnt ++) {
            leds[cnt] = 100;
        }
    }
    update_according_array(leds, 0, 0, 0x7f);
    return cur_period == period_nums;
}
/**************** help function for light_TA_activate() end ***********/


/**************** help function for light_TA_deactivate() start ******************/
/*
 * @function: 灯带从两端往中间收缩
 * @arguments:
 *      @firstIn: control to restart the animation
 * @return: return 1 as the animation finished, return 0 as not
 */
int twoLamp2center(uint8_t *firstIn)
{
    uint8_t leds[TOTAL_LEDS] = {0};
    uint8_t tempo = 5;
    uint8_t L_P1_limit = 30;
    uint8_t R_P1_limit = TOTAL_LEDS - 1 - L_P1_limit;
    uint8_t L_P2_limit = 55;
    uint8_t R_P2_limit = TOTAL_LEDS - 1 - L_P2_limit;
    uint8_t L_P3_limit = TOTAL_LEDS/2 - 3;
    uint8_t R_P3_limit = TOTAL_LEDS/2 + 3;
    uint8_t P1_fast_speed = 6;
    uint8_t P1_slow_speed = 2;
    uint8_t P2_speed = 3;
    uint8_t P3_fast_speed = 6;
    uint8_t P3_slow_speed = 3;
    int cnt = 0;

    static uint8_t L_start_pos = 0;
    static uint8_t L_end_pos = 1;
    static uint8_t R_start_pos = TOTAL_LEDS - 2;
    static uint8_t R_end_pos = TOTAL_LEDS - 1;
    static uint8_t prescalar = 0;
    static uint8_t cur_period = 0;

    if(firstIn && *firstIn == 1) {
        *firstIn = 0;

        L_start_pos = 0;
        L_end_pos = 1;
        R_start_pos = TOTAL_LEDS - 2;
        R_end_pos = TOTAL_LEDS - 1;
        prescalar = 0;
        cur_period = 0;
    }


    if(cur_period >= 3) {
        return 1;
    }

    prescalar ++;
    if(prescalar < tempo) {
        return 0;
    }
    else {
        prescalar = 0;
    }

    switch(cur_period) {
        case 0:
            L_start_pos += P1_slow_speed;
            L_end_pos += P1_fast_speed;

            R_start_pos -= P1_fast_speed;
            R_end_pos -= P1_slow_speed;

            if(L_end_pos >= L_P1_limit && R_start_pos <= R_P1_limit) {
                cur_period = 1;
            }
            break;

        case 1:
            L_start_pos += P2_speed;
            L_end_pos += P2_speed;

            R_start_pos -= P2_speed;
            R_end_pos -= P2_speed;
            if(L_end_pos >= L_P2_limit && R_start_pos <= R_P2_limit) {
                cur_period = 2;
            }
            break;

        case 2:
            L_end_pos = (L_end_pos + P3_slow_speed < L_P3_limit)? L_end_pos + P3_slow_speed : L_P3_limit;
            L_start_pos = (L_start_pos + P3_fast_speed < L_end_pos)? L_start_pos + P3_fast_speed : L_end_pos;

            R_start_pos = (R_start_pos > R_P3_limit + P3_slow_speed)? R_start_pos - P3_slow_speed : R_P3_limit;
            R_end_pos = (R_start_pos + P3_fast_speed < R_end_pos)? R_end_pos - P3_fast_speed : R_start_pos;
            if(L_start_pos == L_P3_limit && R_end_pos == R_P3_limit) {
                cur_period = 3;
            }
            break;
    }

    // update leds
    for(cnt = L_start_pos; cnt <= L_end_pos; cnt ++) {
        leds[cnt] = 100;
    }

    for(cnt = R_start_pos; cnt <= R_end_pos; cnt ++) {
        leds[cnt] = 100;
    }

    update_according_array(leds, 0, 0, 0x7f);

    return cur_period == 3;
}

/**************** help function for light_TA_deactivate() end ******************/


/*************** help function for light_INT_waking() start **********************/
void INT_positions_waking(uint8_t limit_left, uint8_t limit_right, uint8_t *firstIn)
{
    uint8_t period_nums = 3;
    uint8_t spreadSpeed = 2;
    uint8_t spreadTempo = 5;
    uint8_t shrinkCond = 10;
    uint8_t shrinkSpeed = 2;
    uint8_t shrinkTempo = 5;
    uint16_t r_val = INT_white_DATA[0];
    uint16_t g_val = INT_white_DATA[1];
    uint16_t b_val = INT_white_DATA[2];

    static uint8_t cur_period = 0;
    static uint8_t firstInSpread = 1;
    static uint8_t firstInShrink = 1;



    if(firstIn && *firstIn == 1) {
        *firstIn = 0;

        cur_period = 0;
        firstInSpread = 1;
        firstInShrink = 1;
    }

    if(cur_period >= period_nums) {
        return; 
    }

    switch(cur_period) {
        case 0:
            if(spread_specific_positions(r_val, g_val, b_val, spreadSpeed, spreadTempo, limit_left, limit_right, &firstInSpread) == 1) {
                cur_period = 1;
            }
            break;

        case 1:
            if(shrink_specific_positions(r_val, g_val, b_val, shrinkSpeed, shrinkTempo, limit_left, limit_right, shrinkCond, &firstInShrink) == 1) {
                cur_period = 2;
            }
            break;

        case 2:
            set_positions_rgb(0, TOTAL_LEDS-1, 0x0, 0x0, 0x0);
            cur_period = 3;
            break;
    }
}

/*************** help function for light_INT_waking() end **********************/


/****************************   TA animations start ********************************************/
void light_TA_activate(uint8_t *firstIn)
{
    static uint8_t firstInSpread = 1;

    if(firstIn && *firstIn == 1) {
        *firstIn = 0;

        firstInSpread = 1;
    }

    TA_spread(&firstInSpread);
}


void light_TA_deactivate(uint8_t *firstIn)
{
    uint32_t delayNms = 30;

    static uint8_t firstInFlow = 1;
    static uint8_t cur_period = 0;
    static uint8_t firstInDelay = 1;

    if(firstIn && *firstIn == 1) {
        *firstIn = 0;

        firstInFlow = 1;
        cur_period = 0;
        firstInDelay = 1;
    }

    switch(cur_period) {
        case 0:
            if(twoLamp2center(&firstInFlow) == 1) {
                cur_period = 1;
            }
            break;

        case 1:
            if(delay_n_ms(delayNms, &firstInDelay)) {
                cur_period = 2;
            }
            break;

        case 2:
            set_positions_rgb(0, TOTAL_LEDS-1, 0x0, 0x0, 0x0);
            cur_period = 3;
            break;
    }

}

/************************** TA animations end *************************/


/**************************** PLA animations start *****************************/
void light_PLA_searching(void)
{
    uint8_t direction = 0;
    uint8_t tempo = 5;
    uint8_t ntimes = 50;
    uint16_t r_val = 0x3f;
    uint16_t g_val = 0x3f;
    uint16_t b_val = 0x3f;

    // breath_repeat(r_val, g_val, b_val, direction, tempo, ntimes, 0, TOTAL_LEDS-1);
    breath_repeat(r_val, g_val, b_val, 1500, 0, TOTAL_LEDS);
}

void light_PLA_found(void)
{
    uint8_t direction = 0;
    uint8_t tempo = 5;
    uint8_t ntimes = 50;
    uint16_t r_val = 0x0;
    uint16_t g_val = 0x0;
    uint16_t b_val = 0x7f;

    // breath_repeat(r_val, g_val, b_val, direction, tempo, ntimes, 0, TOTAL_LEDS-1);
    breath_repeat(r_val, g_val, b_val, 1500, 0, TOTAL_LEDS);
}

void light_PLA_active(void)
{
    set_positions_rgb(0, TOTAL_LEDS-1, PLA_active_DATA[0], PLA_active_DATA[1], PLA_active_DATA[2]);
}


void light_PLA_break(void)
{
    uint8_t direction = 0;
    uint8_t tempo = 2;
    uint8_t ntimes = 100;
    uint16_t r_val = 0x0;
    uint16_t g_val = 0x0;
    uint16_t b_val = 0x7f;

    // breath_repeat(r_val, g_val, b_val, direction, tempo, ntimes, 0, TOTAL_LEDS-1);
    breath_repeat(r_val, g_val, b_val, 500, 0, TOTAL_LEDS);

}

/**************************** PLA animations end *****************************/

/**************** interaction INT animations start *******************/

/*
 * @mode: 0 for Left, 1 for Right, 2 for Rear
 * @firstIn: *fristIn == 1时，重置所有静态变量，灯效重头开始再来一遍
 */
void light_INT_waking(uint8_t mode, uint8_t *firstIn)
{
    switch(mode) {
        case 0:
            INT_positions_waking(0, 49, firstIn);
            break;

        case 1:
            INT_positions_waking(50, 99, firstIn);
            break;

        case 2:
            INT_positions_waking(100, 149, firstIn);
            break;
    }
}


/*
 * @mode: 0 for Left, 1 for Right, 2 for Rear
 */
void light_INT_listening(uint8_t mode)
{
    uint16_t r_val = INT_white_DATA[0];
    uint16_t g_val = INT_white_DATA[1];
    uint16_t b_val = INT_white_DATA[2];


    switch(mode) {
        case 0: 
            set_positions_rgb(0, 49, r_val, g_val, b_val);
            break;

        case 1:
            set_positions_rgb(50, 99, r_val, g_val, b_val);
            break;

        case 2:
            set_positions_rgb(100, 149, r_val, g_val, b_val);
            break;
    }

}


/*
 * @mode: 0 for Left, 1 for Right, 2 for Rear
 * @firstIn: *firstIn == 1时，重置所有静态变量，灯效重头再来一次
 */
void light_INT_analyzing(uint8_t mode, uint8_t *firstIn)
{
    uint8_t mode0_pos = 30, mode0_limit = 0;
    uint8_t mode1_pos = 80, mode1_limit = 50;
    uint8_t mode2_pos = 130, mode2_limit = 100;

    switch(mode) {
        case 0:
            INT_positions_analyzing(mode0_pos, mode0_limit, firstIn);
            break;

        case 1:
            INT_positions_analyzing(mode1_pos, mode1_limit, firstIn);
            break;

        case 2:
            INT_positions_analyzing(mode2_pos, mode2_limit, firstIn);
            break;
    }
}


/*
 * @mode: 0 for Left, 1 for Right, 2 for Rear
 */
void light_INT_broadcasting(uint8_t mode)
{
    uint8_t direction = 0;
    uint8_t tempo = 2;
    uint8_t ntimes = 50;
    uint16_t r_val = INT_white_DATA[0];
    uint16_t g_val = INT_white_DATA[1];
    uint16_t b_val = INT_white_DATA[2];

    switch(mode) {
        case 0:
            // breath_repeat(r_val, g_val, b_val, direction, tempo, ntimes, 0, 49);
            breath_repeat(r_val, g_val, b_val, 1000, 0, 49);
            break;

        case 1:
            // breath_repeat(r_val, g_val, b_val, direction, tempo, ntimes, 50, 99);
            breath_repeat(r_val, g_val, b_val, 1000, 50, 99);
            break;

        case 2:
            // breath_repeat(r_val, g_val, b_val, direction, tempo, ntimes, 100, 149);
            breath_repeat(r_val, g_val, b_val, 1000, 100, 149);
            break;
    }

}
/************************* INT animations end ***********************/

/*********************** SPECIAL animation *************************/ 
/* 烛光效果 */
void candle_modle_Timerint()
{
    uint8_t num;
    uint8_t index;

    uint16_t latchData;

    static uint16_t prescalar = 60;
    static uint16_t prescalar2 = 200;

    //static uint8_t offset1, offset2 = 0;

    uint16_t tempData = 0;
    uint16_t randMax = RAND_MAX;

    prescalar++;
    prescalar2++;

    if(prescalar2 >350)
    {
        //srand(randNum);
        tempData = rand();
        offset2 = 30 * tempData / randMax ;
        prescalar2 = 0;
    }

    if(prescalar < 60)
    {
        return;
    }
    else
    {
        prescalar = 0;
    }

    if(offset1>offset2)
    {
        offset1--;
    }
    if(offset1<offset2)
    {
        offset1++;
    }

    for(num = 0; num<TOTAL_LEDS; num++)
    {
        if(num == (TOTAL_LEDS-1) )
        {
            latchData = 1;
        }
        else
        {
            latchData = 0;
        }

        if(num < 40 || num > 100)
        {
            index = 0;
            sendImageData(0, 0, 0,latchData);
        }
        else
        {
            index = num - 40;

            sendImageData(candle_DATA[0+index+offset1][0],
                    candle_DATA[0+index+offset1][1],
                    candle_DATA[0+index+offset1][2],latchData);

        }

    }

}

/*
 * @fucntion: 欢迎效果
 * @arguments:
 *      @firstIn: 控制效果重新刷新的
 */
int light_welcome(uint8_t *firstIn)
{
    uint16_t center_pos = TOTAL_LEDS/2;
    uint8_t spreadSpeed = 3;
    uint8_t fastpart = 73;
    uint8_t spreadTempo = 5;
    static uint16_t side_len = 0;
    static uint8_t cur_period = 0; // 0: spread; 1: constant; 2: white to blue; 3: blue breath
    static uint8_t firstInTwoSidesSpread = 1;
    static uint8_t firstInWhite2Blue = 1;
    static uint8_t firstInBlueBreathOnce = 1;

    if(firstIn && *firstIn == 1) {
        *firstIn = 0;

        center_pos = TOTAL_LEDS/2;
        side_len = 0;
        cur_period = 0;
        firstInTwoSidesSpread = 1;
        firstInWhite2Blue = 1;
        firstInBlueBreathOnce = 1;
    }

    switch(cur_period)
    {
        case 0:
            if(two_sides_spread2(0x7f, 0x7f, 0x7f, spreadSpeed,fastpart, spreadTempo, &firstInTwoSidesSpread) == 1) {
                cur_period = 1;
            }
            break;

        case 1:
            if(white2blue2(3,5,&firstInWhite2Blue) == 1) {
                cur_period = 2;
            }
            break;

        case 2:
            if(blue_breath_once(&firstInBlueBreathOnce) == 1) {
                cur_period = 3;
            }
            break;
    }

    return cur_period == 3;
}

/*
 * @arguments:
 *      @firstIn: 控制效果重新刷新
 */
void light_goodbye(uint8_t *firstIn)
{
    uint8_t shrinkSpeed = 5;
    uint8_t shrinkTempo = 5;
    uint8_t shrinkCond = 10;
    static uint8_t cur_period = 0;
    static uint8_t firstInShrink = 1;
    static uint8_t firstInOut2Blue = 1;
    static uint8_t firstInCrash = 1;

    if(firstIn && *firstIn == 1) {
        *firstIn = 0;

        cur_period = 0;
        firstInShrink = 1;
        firstInOut2Blue = 1;
        firstInCrash = 1;
    }
    switch(cur_period)
    {
        case 0:
            if(out2blue(&firstInOut2Blue) == 1) {
                cur_period = 1;
            }
            break;

        case 1:
            if(shrink2center(0x0f, 0x7f, 0x7f, shrinkSpeed, shrinkTempo, shrinkCond, &firstInShrink) == 1) {
                cur_period = 2;
            }
            break;

        case 2:
            if(white_crash_at_center(&firstInCrash) == 1) {
                cur_period = 3;
            }
            break;
    }
}


#define BASIC_LEN 10
#define RANDOM_RANGE 10
/* 灯带抖动 */
void random_shake(void)
{
    uint8_t speed = 1;
    uint8_t rand_len = 0;
    uint8_t tempo = 10;
    uint8_t N = 5;

    static uint8_t prescalar = 0;
    static uint8_t cnt = 0;
    static uint8_t start_pos = TOTAL_LEDS/2 - (BASIC_LEN + RANDOM_RANGE/2);
    static uint8_t end_pos = TOTAL_LEDS/2 + (BASIC_LEN + RANDOM_RANGE/2);
    static uint8_t target_start_pos = 0;

    if(prescalar < tempo) {
        prescalar ++;
        return;
    }
    else {
        prescalar = 0;
    }

    if(cnt == 0) {
        rand_len = rand()%RANDOM_RANGE + BASIC_LEN;
        target_start_pos = TOTAL_LEDS/2 - rand_len;
    }

    if(start_pos > target_start_pos) {
        start_pos -= speed;
        end_pos += speed;
    }
    else {
        start_pos += speed;
        end_pos -= speed;
    }

    set_positions_rgb(start_pos, end_pos, 0x0, 0x0, 0x7f);
    cnt = (cnt + 1)%N;
}

/****************** SPECIAL animations end *************************/

/****************** WARNING animations start  *********************/

/* red breath only once*/
void light_warning_red_once(uint8_t *firstIn)
{
    uint8_t direction = 0;
    uint8_t localTempo = 5;
    uint8_t ntimes = 50;
    uint16_t r_val = 0x7f;
    uint16_t g_val = 0;
    uint16_t b_val = 0x0;

    static uint8_t firstInBreathOnce = 1;

    if(firstIn && *firstIn == 1) {
        *firstIn = 0;
        firstInBreathOnce = 1;
    }

    breath_once(r_val, g_val, b_val, direction, localTempo, ntimes, 0, TOTAL_LEDS-1, &firstInBreathOnce);

}

/* red breath repeatly */
void light_warning_red_repeat(void)
{
    uint8_t direction = 0;
    uint8_t localTempo = 5;
    uint8_t ntimes = 50;
    uint16_t r_val = 0x7f;
    uint16_t g_val = 0;
    uint16_t b_val = 0x0;

    // breath_repeat(r_val, g_val, b_val, direction, localTempo, ntimes, 0, TOTAL_LEDS-1);
    breath_repeat(r_val, g_val, b_val, 1000, 0, TOTAL_LEDS);

}

/* yellow breath once */
void light_warning_yellow_once(uint8_t *firstIn)
{
    uint8_t direction = 0;
    uint8_t localTempo = 5;
    uint8_t ntimes = 50;
    uint16_t r_val = 0x3f;
    uint16_t g_val = 0x3f;
    uint16_t b_val = 0x0;

    static uint8_t firstInBreathOnce = 1;

    if(firstIn && *firstIn == 1) {
        *firstIn = 0;

        firstInBreathOnce = 1;
    }

    breath_once(r_val, g_val, b_val, direction, localTempo, ntimes, 0, TOTAL_LEDS-1, &firstInBreathOnce);
}

/* yellow breath repeat */
void light_warning_yellow_repeat(void)
{
    uint8_t ntimes = 50;
    uint8_t direction = 0;
    uint8_t localTempo = 2;
    uint16_t r_val = 0x3f;
    uint16_t g_val = 0x3f;
    uint16_t b_val = 0x0;

    // breath_repeat(r_val, g_val, b_val, direction, localTempo, ntimes, 0, TOTAL_LEDS-1);
    breath_repeat(r_val, g_val, b_val, 1500, 0, TOTAL_LEDS);
}


#define WARNING_LIMIT 60
/* yellow flow at the left side*/
void light_warning_yellow_left(void)
{
    static uint8_t end_pos = 1;
    static uint8_t start_pos = 0;
    static uint16_t prescalar = 0;
    uint8_t limit_pos = WARNING_LIMIT;
    uint16_t r_val = 0x7f;
    uint16_t g_val = 0x7f;
    uint16_t b_val = 0;
    uint8_t tempo = 3;

    prescalar ++;
    if(prescalar < tempo) {
        return;
    }
    else {
        prescalar = 0;
    }

    end_pos += 1;

    if(end_pos > limit_pos) {
        end_pos = 1;
    }

    set_positions_rgb(start_pos, end_pos, r_val, g_val, b_val);
}


/* yellow flow at the right side*/
void light_warning_yellow_right(void)
{
    static uint8_t start_pos = TOTAL_LEDS - 1;
    static uint8_t end_pos = TOTAL_LEDS - 1;
    static uint16_t prescalar = 0;
    uint8_t limit_pos = TOTAL_LEDS - 1 - WARNING_LIMIT;
    uint16_t r_val = 0x7f;
    uint16_t g_val = 0x7f;
    uint16_t b_val = 0;
    uint8_t tempo = 3;

    prescalar ++;
    if(prescalar < tempo) {
        return;
    }
    else {
        prescalar = 0;
    }

    start_pos -= 1;

    if(start_pos < limit_pos) {
        start_pos = TOTAL_LEDS - 1;
    }

    set_positions_rgb(start_pos, end_pos, r_val, g_val, b_val);
}
/********************** WARNING animations end *************************/


/* test function */
void specific_animation_test(void)
{
//    static uint8_t firstIn = 1;
//    if(white_crash_at_center(&firstIn)) {
//    	vTaskDelay(500);
//    	firstIn = 1;
//    }
    light_warning_yellow_left();
//    light_welcome(1);
}
