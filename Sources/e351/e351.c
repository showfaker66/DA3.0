/**
  ******************************************************************************
  * 文件名程: e351.c
  * 作    者: kian
  * 版    本: V1.0
  * 编写日期: 2021-04-20
  * 功    能: 光宝E351灯珠驱动，匹配FPGA驱动板
  ******************************************************************************
  * 说明：
  * 
  ******************************************************************************
  */

/* 包含头文件 ----------------------------------------------------------------*/
/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "queue.h"
#include "pin_mux.h"
#include "dmaController1.h"
#include "clockMan1.h"
#include "can/bsp_CAN.h"
#include "BoardDefines.h"
#include "S32K144.h"
#include "../print/printf.h"
#include <string.h>
#include "e351.h"
#include "smartRGB_E355.h"
#include "userCode.h"

/* 私有类型定义 --------------------------------------------------------------*/
/* 私有宏定义 ----------------------------------------------------------------*/
/* 私有变量 ------------------------------------------------------------------*/
uint8_t Test_bit=0;
uint8_t LED_First=0;
uint8_t LED_direction=0;

uint16_t Ctl_Head[300];
uint16_t R_Data[300];
uint16_t G_Data[300];
uint16_t B_Data[300];
uint16_t Cfg_Head[300];
uint16_t Cfg1_Data[300];
uint16_t Cfg2_Data[300];
uint16_t Cfg3_Data[300];

/* 扩展变量 ------------------------------------------------------------------*/
uint8_t prev_lightType = 255, prev_lightMode = 255;
uint8_t cur_lightType = 0, cur_lightMode = 0;

extern uint8_t EOL_RCV_Flag;
extern ptrRRM_1 rcv_rrm1_data;
extern ptrRRM_2 rcv_rrm2_data ;
extern ptrRRM_4 rcv_rrm4_data ;
extern ptrITM_0 rcv_itm0_data ;

/* 私有函数原形 ---------------------------------------------------------------*/
/* 函数体 --------------------------------------------------------------------*/

void data_out(uint16_t data)
{
	D0((data&0x0001)?1:0);
	D1((data&0x0002)?1:0);
	D2((data&0x0004)?1:0);
	D3((data&0x0008)?1:0);
	D4((data&0x0010)?1:0);
	D5((data&0x0020)?1:0);
	D6((data&0x0040)?1:0);
	D7((data&0x0080)?1:0);
	D8((data&0x0100)?1:0);
	D9((data&0x0200)?1:0);
	D10((data&0x0400)?1:0);
	D11((data&0x0800)?1:0);
	D12((data&0x1000)?1:0);
	D13((data&0x2000)?1:0);
	D14((data&0x4000)?1:0);
	D15((data&0x8000)?1:0);
}

void COMMAND_4Byte()
{
	uint8_t i;
	cs_on();
	for(i=0;i<60;i++)
	{
		data_out(0x8000+i+Cfg_Head[i]);	//命令头
		one_clk();
		data_out(0x8000+Cfg1_Data[i]);	//命令1
		one_clk();
		data_out(0x8000+Cfg2_Data[i]);	//命令2
		one_clk();
		data_out(0x8000+Cfg3_Data[i]);	//命令3
		one_clk();
	}
		load_clk();
}

void DATA_4Byte()
{
	uint8_t i;
	cs_on();
	for(i=0;i<60;i++)
	{
		data_out(i+Ctl_Head[i]);	//命令头
		one_clk();
		data_out(R_Data[i]);		//RGB-R数据
		one_clk();
		data_out(G_Data[i]);		//RGB-G数据
		one_clk();
		data_out(B_Data[i]);		//RGB-B数据
		one_clk();
	}
	load_clk();
}

void Config_Byte()
{
    uint8_t i,j;
	if(Test_bit==1)
    {
		for(i=0;i<11;i++)
        {
			Cfg_Head[i*6+0]=Config_Head;Cfg1_Data[i*6+0]=Config_Data;Cfg2_Data[i*6+0]=Config2_Data6;Cfg3_Data[i*6+0]=Config3_Data6;
			Cfg_Head[i*6+1]=Config_Head;Cfg1_Data[i*6+1]=Config_Data;Cfg2_Data[i*6+1]=Config2_Data6;Cfg3_Data[i*6+1]=Config3_Data6;
			Cfg_Head[i*6+2]=Config_Head;Cfg1_Data[i*6+2]=Config_Data;Cfg2_Data[i*6+2]=Config2_Data6;Cfg3_Data[i*6+2]=Config3_Data6;
			Cfg_Head[i*6+3]=Config_Head;Cfg1_Data[i*6+3]=Config_Data;Cfg2_Data[i*6+3]=Config2_Data6;Cfg3_Data[i*6+3]=Config3_Data6;
			Cfg_Head[i*6+4]=Config_Head;Cfg1_Data[i*6+4]=Config_Data;Cfg2_Data[i*6+4]=Config2_Data6;Cfg3_Data[i*6+4]=Config3_Data6;
			Cfg_Head[i*6+5]=Config_Head;Cfg1_Data[i*6+5]=Config_Data;Cfg2_Data[i*6+5]=Config2_Data6;Cfg3_Data[i*6+5]=Config3_Data6;
		}
	}
	if(Test_bit==0)
    {
		if(LED_direction)
        {
			if(LED_First>1)
			{
				LED_First--;
			}
			else
			{	
				LED_direction=0;
			}
		}
        else
        {
			if(LED_First<45)
			{
				LED_First++;
			}
			else
			{
				LED_direction=1;
			}
		}

		for(j=0;j<9;j++)
		{
			Cfg_Head[LED_First+j]=Config_Head;
			Cfg1_Data[LED_First+j]=Config_Data;
			Cfg2_Data[LED_First+j]=Config2_Data6;
			Cfg3_Data[LED_First+j]=Config3_Data6;
		}
		
		if(LED_First)
        {
			for(i=0;i<LED_First;i++)
            {
				Cfg_Head[i]=Config_Head;
				Cfg1_Data[i]=Config_Data;
				Cfg2_Data[i]=Config2_Data0;
				Cfg3_Data[i]=Config3_Data0;
			}
		}
		for(i=(LED_First+10);i<66;i++)
        {
			Cfg_Head[i]=Config_Head;
			Cfg1_Data[i]=Config_Data;
			Cfg2_Data[i]=Config2_Data0;
			Cfg3_Data[i]=Config3_Data0;
		}
	}
	Cfg_Head[0]=Config_Head | 0x100;
}


uint8_t RGB_Switch_state=0;
void RGB_Switch()
{
	uint8_t i;
	
	if(Test_bit==0)
	{
		Ctl_Head[LED_First+0]=Control_Head;R_Data[LED_First+0]=Control_RGBData;G_Data[LED_First+0]=Control_RGB0Data;B_Data[LED_First+0]=Control_RGB0Data;
		Ctl_Head[LED_First+1]=Control_Head;R_Data[LED_First+1]=Control_RGB0Data;G_Data[LED_First+1]=Control_RGBData;B_Data[LED_First+1]=Control_RGB0Data;
		Ctl_Head[LED_First+2]=Control_Head;R_Data[LED_First+2]=Control_RGB0Data;G_Data[LED_First+2]=Control_RGB0Data;B_Data[LED_First+2]=Control_RGBData;
		Ctl_Head[LED_First+3]=Control_Head;R_Data[LED_First+3]=Control_RGB0Data;G_Data[LED_First+3]=Control_RGBData;B_Data[LED_First+3]=Control_RGB0Data;
		Ctl_Head[LED_First+4]=Control_Head;R_Data[LED_First+4]=Control_RGBData;G_Data[LED_First+4]=Control_RGB0Data;B_Data[LED_First+4]=Control_RGB0Data;
		Ctl_Head[LED_First+5]=Control_Head;R_Data[LED_First+5]=Control_RGB0Data;G_Data[LED_First+5]=Control_RGBData;B_Data[LED_First+5]=Control_RGB0Data;
		Ctl_Head[LED_First+6]=Control_Head;R_Data[LED_First+6]=Control_RGB0Data;G_Data[LED_First+6]=Control_RGB0Data;B_Data[LED_First+6]=Control_RGBData;
		Ctl_Head[LED_First+7]=Control_Head;R_Data[LED_First+7]=Control_RGB0Data;G_Data[LED_First+7]=Control_RGBData;B_Data[LED_First+7]=Control_RGB0Data;
		Ctl_Head[LED_First+8]=Control_Head;R_Data[LED_First+8]=Control_RGBData;G_Data[LED_First+8]=Control_RGB0Data;B_Data[LED_First+8]=Control_RGB0Data;
		Ctl_Head[LED_First+9]=Control_Head;R_Data[LED_First+9]=Control_RGB0Data;G_Data[LED_First+9]=Control_RGBData;B_Data[LED_First+9]=Control_RGB0Data;
	
		if(LED_First)
		{
			for(i=0;i<LED_First;i++)
			{
				Ctl_Head[i]=Control_Head;R_Data[i]=Control_RGB0Data;G_Data[i]=Control_RGB0Data;B_Data[i]=Control_RGB0Data;
			}
		}
		for(i=(LED_First+10);i<66;i++)
		{
			Ctl_Head[i]=Control_Head;R_Data[i]=Control_RGB0Data;G_Data[i]=Control_RGB0Data;B_Data[i]=Control_RGB0Data;
		}
	}

	Ctl_Head[0]=Control_Head | 0x100;
	
	if(Test_bit==1)
	{
		switch(RGB_Switch_state)
		{
			case 0:
				//for(i=0;i<55;i++){R_Data[i]=0xfff;G_Data[i]=0x000;B_Data[i]=0x000;Ctl_Head[i]=0x0b00;}
				for(i=0;i<11;i++){
					Ctl_Head[i*6]=0x0b00;R_Data[i*6]=0x0ff;G_Data[i*6]=0x000;B_Data[i*6]=0x000;
					Ctl_Head[i*6+1]=0x0b00;R_Data[i*6+1]=0x000;G_Data[i*6+1]=0x0ff;B_Data[i*6+1]=0x000;
					Ctl_Head[i*6+2]=0x0b00;R_Data[i*6+2]=0x000;G_Data[i*6+2]=0x000;B_Data[i*6+2]=0x0ff;
					Ctl_Head[i*6+3]=0x0b00;R_Data[i*6+3]=0x0ff;G_Data[i*6+3]=0x0ff;B_Data[i*6+3]=0x0ff;
					Ctl_Head[i*6+4]=0x0b00;R_Data[i*6+4]=0x000;G_Data[i*6+4]=0x000;B_Data[i*6+4]=0x000;
					Ctl_Head[i*6+5]=0x0b00;R_Data[i*6+5]=0x0ff;G_Data[i*6+5]=0x000;B_Data[i*6+4]=0x0ff0;
				}
				RGB_Switch_state=1;
				break;
			case 1:
				for(i=0;i<66;i++){R_Data[i]=0x000;G_Data[i]=0x0ff;B_Data[i]=0x000;Ctl_Head[i]=0x0b00;}
				RGB_Switch_state=2;
				break;
			case 2:
				for(i=0;i<66;i++){R_Data[i]=0x000;G_Data[i]=0x000;B_Data[i]=0x0ff;Ctl_Head[i]=0x0b00;}
				RGB_Switch_state=3;
				break;
			case 3:
				for(i=0;i<11;i++){R_Data[i]=0x0ff;G_Data[i]=0x000;B_Data[i]=0x000;Ctl_Head[i]=0x0b00;}
				for(i=11;i<22;i++){R_Data[i]=0x000;G_Data[i]=0x0ff;B_Data[i]=0x000;Ctl_Head[i]=0x0b00;}
				for(i=22;i<33;i++){R_Data[i]=0x000;G_Data[i]=0x000;B_Data[i]=0x0ff;Ctl_Head[i]=0x0b00;}
				for(i=33;i<44;i++){R_Data[i]=0x0ff;G_Data[i]=0x0ff;B_Data[i]=0x000;Ctl_Head[i]=0x0b00;}
				for(i=44;i<55;i++){R_Data[i]=0x000;G_Data[i]=0x0ff;B_Data[i]=0x0ff;Ctl_Head[i]=0x0b00;}
				for(i=55;i<66;i++){R_Data[i]=0x0ff;G_Data[i]=0x000;B_Data[i]=0x0ff;Ctl_Head[i]=0x0b00;}
				RGB_Switch_state=4;
				break;
			case 4:
				for(i=0;i<66;i++){R_Data[i]=0x000;G_Data[i]=0x000;B_Data[i]=0x000;Ctl_Head[i]=0x0b00;}
				RGB_Switch_state=5;
				break;
			case 5:
				for(i=0;i<66;i++){R_Data[i]=0x0ff;G_Data[i]=0x0ff;B_Data[i]=0x0ff;Ctl_Head[i]=0x0b00;}
				RGB_Switch_state=0;
				break;
			default:RGB_Switch_state=0;break;
		}	
	}	 
}



void vRGB_EOL_test(ptrITM_0 para)
{
    uint8_t num = 0;

    uint16_t R_D = 0x0fff & para->red_d;
    uint16_t G_D = 0x0fff & para->green_d;
    uint16_t B_D = 0x0fff & para->blue_d;

    for(num = 0; num<TOTAL_LEDS; num++)
    {
		if(num<50 || num>99)
		{
			send12bitImgData(0, 0, 0,num,TOTAL_LEDS); //TOTAL_LEDS 150
		}
		else 
		{
			send12bitImgData(R_D, G_D, B_D,num,TOTAL_LEDS);
		}
    }
}

void allBlack(void)
{
    uint8_t num = 0;

    for(num = 0; num<TOTAL_LEDS; num++)
    {
        send12bitImgData(0,0,0,num,TOTAL_LEDS);
    }
}

void warningType(ptrRRM_4 para)
{
	switch(para->lightMode)
	{
		//case WARNING_RED:warning_red();
        case WARNING_RED: light_warning_red_once(&animation_first_in); //xzh modifiled
		break;

		//case WARNING_YELLOW: warning_yellow();
		case WARNING_YELLOW: light_warning_yellow_once(&animation_first_in); //xzh modified
		break;

		case WARNING_RED_REPEAT: light_warning_red_repeat();
		break;

		case WARNING_YELLOW_REPEAT: light_warning_yellow_repeat();
		break;

		case WARNING_YELLOW_LEFT: light_warning_yellow_left();
		break;

		case WARNING_YELLOW_RIGHT: light_warning_yellow_right();
		break;   

        default: allBlack();
        break;
	}
}

void plaType(ptrRRM_4 para)
{
	switch(para->lightMode)
	{
		case PLA_SEARCHING : light_PLA_searching();
		break;

		case PLA_FOUND: light_PLA_found();
		break;

		case PLA_ACTIVE: light_PLA_active();
		break;

		case PLA_BRAKE:light_PLA_break();
		break;
        
        default: allBlack();
        break;
	}
}

void taType(ptrRRM_4 para)
{
	switch(para->lightMode)
	{
		case TA_ACTIVATED : light_TA_activate(&animation_first_in);
		break;

		case TA_DEACTIVATED :light_TA_deactivate(&animation_first_in);
		break;

        default: allBlack();
        break;
	}
}

void wakingType(ptrRRM_4 para)
{
	switch(para->lightMode)
	{
		case WAKING_FRONT_LEFT: light_INT_waking(0, &animation_first_in);
		break;

		case WAKING_FRONT_RIGHT: light_INT_waking(1, &animation_first_in);
		break;

		case WAKING_REAR: light_INT_waking(2, &animation_first_in);
		break;       

        default: allBlack();
        break;
	}
}

void listenType(ptrRRM_4 para)
{
	switch(para->lightMode)
	{
		case LISTEN_FRONT_LEFT : light_INT_listening(0);
		break;

		case LISTEN_FRONT_RIGHT : light_INT_listening(1);
		break;

		case LISTEN_REAR: light_INT_listening(2);
		break;        

        default: allBlack();
        break;
	}
}

void analyzeType(ptrRRM_4 para)
{
	switch(para->lightMode)
	{
		case ANALYZE_FRONT_LEFT: light_INT_analyzing(0, &animation_first_in);
		break;

		case ANALYZE_FRONT_RIGHT : light_INT_analyzing(1, &animation_first_in); 
		break;

		case ANALYZE_REAR: light_INT_analyzing(2, &animation_first_in);
		break;        

        default: allBlack();
        break;
	}
}

void broadcastType(ptrRRM_4 para)
{
	switch(para->lightMode)
	{
		case BROADCAST_FRONT_LEFT : light_INT_broadcasting(0);
		break;

		case BROADCAST_FRONT_RIGHT : light_INT_broadcasting(1);
		break;

		case BROADCAST_REAR : light_INT_broadcasting(2); 
		break;

        default: allBlack();
        break;
	}
}

void specialType(ptrRRM_4 para)
{
	switch(para->lightMode)
	{
		case SPECIAL_BIRTHDAY : candle_modle_Timerint();
		break;

		case SPECIAL_WELCOME : light_welcome(&animation_first_in);
		break;

		case SPECIAL_BYE: light_goodbye(&animation_first_in); 
		break;

        default: allBlack();
        break;
	}
}



void lightModeSelect(ptrRRM_4 para)
{

	if((prev_lightType != para->lightType)
		|| (prev_lightMode != para->lightMode) )
		{
			sendFunctionData(0xC0, 0x00, 0x00, 0x00, 0x01);
			sendFunctionData(0xC0, 0x05, 0x7F, 0xFF, 0xDF);
			allBlack();
		}

    cur_lightType = para->lightType;
    cur_lightMode = para->lightMode;

    if(cur_lightType != prev_lightType || cur_lightMode != prev_lightMode) {
        animation_first_in = 1;
    }s

    prev_lightType = cur_lightType;
    prev_lightMode = cur_lightMode;


    switch (para->lightType)
    {
        case WARNING: warningType(para);
            break;

        case PLA: plaType(para);
            break;

        case TA: taType(para);
            break;

        case WAKING: wakingType(para);
            break;

        case LISTEN: listenType(para); 
            break;

        case ANALYZE: analyzeType(para);
            break;
    
        case BROADCAST:broadcastType(para);
            break;

        case SPECIAL: specialType(para);
        break;

        default: allBlack();
        break;
    }
}

void e351_refresh(void)
{
#if 0 //二代RGB灯条测试

	specific_animation_test();

#else
	if(rcv_itm0_data->enginearMode == 0)
    {

        if(rcv_rrm2_data->systemSwitch==1)//  RCV_RRM2_DATA->systemSwitch == 1)
        {
            lightModeSelect(rcv_rrm4_data);
        }
        else
        {
            // V2_modle_Timerint();
			allBlack();
            animation_first_in = 1; // restart the animation
        }
    }
    else if(rcv_itm0_data->enginearMode == 1)
    {
		sendFunctionData(0xC0, 0x00, 0x00, 0x00, 0x01);
        sendFunctionData(0xC0, 0x05, 0x7F, 0xFF, 0xDF);
        // if(EOL_RCV_Flag == 1)
        {
            EOL_RCV_Flag = 0;
			vRGB_EOL_test(rcv_itm0_data);
        }

        animation_first_in = 1;
    }
#endif
}

/**
  * 函数功能: E351显示刷新任务
  * 输入参数:
  * 返 回 值: 无
  * 说    明:
  */
void prvE351RefreshTask(void *pvParameters )
{

	/** FPGA 复位 **/
	FPGA_RST_L;
	vTaskDelay(500);
	FPGA_RST_H;

	while(1)
	{
		/* total ~ 15ms */
		// TEST_PIN_L;
		e351_refresh();//T=12.5MS
		// TEST_PIN_H;	
		vTaskDelay(2);
		
		#if 0
		vTaskDelay(50);

		if(PTC->PDIR == PIN_9)//LOGO POWER DISABLE
		{
			LOGO_POWER(OFF);
		}
		else
		{
			LOGO_POWER(ON);
		}

		switch(itm0.ID_6F0.enginearMode)
		{
			case NormalMode:
			break;

			case EnginearMode:
			break;
		}
		#endif
	}
}

/************************END OF FILE************************/
