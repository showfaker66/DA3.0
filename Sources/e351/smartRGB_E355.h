/*
 * smartRGB_E355.h
 *
 *  Created on: 2019-02-28
 *      Author: liujian
 */

#ifndef SMART_RGB_E355_H_
#define SMART_RGB_E355_H_

/*********************************************************************************************************************
 * Include list
 *********************************************************************************************************************/


/**********************************************************************************************************************
Macro definitions
**********************************************************************************************************************/

#define REAL_TOTAL_LEDS     150
#define TOTAL_LEDS          REAL_TOTAL_LEDS 

#define RGB_MAX_VALUE       0X3FF
#define REFRESH_T_MS        15

#define SMART_RGB_DATA_H            (PTD->PSOR = 0x0002)
#define SMART_RGB_DATA_L            (PTD->PCOR = 0x0002)

/* SMRAT RGB CLK  */
//#define SMART_RGB_CLK_GPIO        PTD
//#define SMART_RGB_CLK_PIN         0U
//#define SMART_RGB_CLK_MASK        (0x1u << SMART_RGB_CLK_PIN)

#define SMART_RGB_CLK_H            (PTD->PSOR = 0x0001)
#define SMART_RGB_CLK_L            (PTD->PCOR = 0x0001)

#define FPGA_RST_H				   (PTD->PSOR = 0x0004)
#define FPGA_RST_L            	   (PTD->PCOR = 0x0004)


#define Sbit_0 0x0
#define Sbit_1 0x80
#define Cbit_0 0
#define Cbit_1 0x40
#define Rbit_0 0
#define Rbit_1 0x20b
#define LbitNext 0
#define LbitStop 1
#define time 500000

#define DELAY_LOW {__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");}
#define DELAY_HIGH {__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");\
                    __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");}
//#define RGB_Current 0xEE0EE0EE0  // 25c & 85c turn on
//#define RGB_Current 0x8E98E98E9  // 105c turn on
//#define RGB_Current 0x8E98E98E9  // 105c on/off
#define RGB_Current1 0x100100100
#define RGB_Current0 0x000000000
#define RGB_Current  0xFFFFFFFFF


/******  RGB STRUCT  ******/
typedef struct {                            
    uint8_t RED;
    uint8_t GREEN;   
    uint8_t BLUE;          
} RGB_struct;


typedef union{

    uint8_t dBeyte[5];

    struct {
        uint8_t d39 : 1;
        uint8_t d38 : 1;
        uint8_t d37 : 1;
        uint8_t d36 : 1;
        uint8_t d35 : 1;
        uint8_t d34 : 1;
        uint8_t d33 : 1;
        uint8_t d32 : 1;
        uint8_t d31 : 1;
        uint8_t d30 : 1;
        uint8_t d29 : 1;
        uint8_t d28 : 1;
        uint8_t d27 : 1;
        uint8_t d26 : 1;
        uint8_t d25 : 1;
        uint8_t d24 : 1;
        uint8_t d23 : 1;
        uint8_t d22 : 1;
        uint8_t d21 : 1;
        uint8_t d20 : 1;
        uint8_t d19 : 1;
        uint8_t d18 : 1;
        uint8_t d17 : 1;
        uint8_t d16 : 1;
        uint8_t d15 : 1;
        uint8_t d14 : 1;
        uint8_t d13 : 1;
        uint8_t d12 : 1;
        uint8_t d11 : 1;
        uint8_t d10 : 1;
        uint8_t d9  : 1;
        uint8_t d8  : 1;
        uint8_t d7  : 1;
        uint8_t d6  : 1;
        uint8_t d5  : 1;
        uint8_t d4  : 1;
        uint8_t d3  : 1;
        uint8_t d2  : 1;
        uint8_t d1  : 1;
        uint8_t d0  : 1;
    }bits;

    //function defins
    struct {                            
        uint8_t latch : 1;
        uint8_t gbc   : 6;
        uint8_t crb   : 7;
        uint8_t crc   : 7;
        uint8_t pwm   : 1;
        uint8_t splt  : 1;
        uint8_t fgck  : 2;
        uint8_t eck   : 1;
        uint8_t prot  : 1;
        uint8_t reserved1 : 1;
        uint8_t reserved2 : 1;
        uint8_t rdao  : 1;
        uint8_t msg   : 1;
        uint8_t reserved3 : 1;
        uint8_t reserved4 : 2;
        uint8_t reserved5 : 1;
        uint8_t trf   : 1;
        uint8_t reserved6 : 2;
        uint8_t c     : 1;
        uint8_t s     : 1;
    } funcData;

    //image data defins
    struct {                            
        uint64_t latch : 1;
        uint64_t blue  : 12;
        uint64_t green : 12;
        uint64_t red   : 12;
        uint64_t reserved1 : 1;
        uint64_t c     : 1;
        uint64_t s     : 1;
        uint64_t reserved2 :24;
    } imgData;

}E351_Type;


typedef struct
{
    // uint32_t s :1;
    // uint32_t c :1;
    // uint32_t r :1;
    // uint32_t red :12;
    // uint32_t green :12;
    // uint32_t blue1 :5;
    
    // uint8_t blue_2 :7;
    // uint8_t latch :1;
    uint16_t red :12;
    uint16_t reserved1 :4;

    uint16_t green :12;
    uint16_t reserved2 :4;
    
    uint16_t blue :12;
    uint16_t reserved3 :4;
}E355_DATA;


// exported vals
extern uint8_t animation_first_in;



void FunctionData(unsigned char Value1,unsigned char Value2,unsigned char Value3,unsigned char Value4,unsigned char Value5);
void sendImageData12bitMode(uint16_t RED, uint16_t GREEN, uint16_t BLUE, uint8_t Lbit);
void send12bitImgData(uint16_t R, uint16_t G, uint16_t B, uint8_t currentNum, uint8_t totalNum);
void liteonLED_V2_inti(void);
void ledsAllBlack(uint8_t numLEDS);
void ledsAllWhite(uint8_t numLEDS);
void rainBown(uint8_t numLEDS);

void sendFunctionData(uint8_t value1,uint8_t value2,uint8_t value3,uint8_t value4,uint8_t value5);

void specific_animation_test(void);


#endif /* SMART_RGB_E355_H_ */
