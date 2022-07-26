/*
 * userCode.h
 *
 *  Created on: 2019年2月28日
 *      Author: liujian
 */

#ifndef USERCODE_H_
#define USERCODE_H_


//#define HARDWARE_TEST       //硬件测试代码



/* CAN STB控制 H:STB  L:NORMAL */
#define CAN_STB_GPIO     PTE
#define CAN_STB_PIN      6U
#define CAN_STB_MASK      (0x1u << CAN_STB_PIN)

/* LIN 使能控制 */
#define LIN_EN_GPIO     PTC
#define LIN_EN_PIN      9U
#define LIN_ENABLE_MASK      (0x1u << LIN_EN_PIN)

/* RGB_DIN LED数据控制脚 */
#define RGB_DIN_GPIO     PTB
#define RGB_DIN_PIN      3U
#define RGB_DIN_MASK      (0x1u << RGB_DIN_PIN)

/* MCU_LOGO 电源控制脚 */
#define SW_LOGO_PWR_GPIO     PTC
#define SW_LOGO_PWR_PIN      14U
#define SW_LOGO_PWR_MASK     (0x1u << SW_LOGO_PWR_PIN)

/* MCU_RGB 电源控制脚 */
#define SW_RGB_PWR_GPIO     PTC
#define SW_RGB_PWR_PIN      15U
#define SW_RGB_PWR_MASK     (0x1u << SW_RGB_PWR_PIN)

/* MCU_BGR 电源控制脚 */
#define SW_BGR_PWR_GPIO     PTC
#define SW_BGR_PWR_PIN      16U
#define SW_BGR_PWR_MASK     (0x1u << SW_BGR_PWR_PIN)

/* MCU_BFW 电源控制脚 */
#define SW_BFW_PWR_GPIO     PTC
#define SW_BFW_PWR_PIN      17U
#define SW_BFW_PWR_MASK     (0x1u << SW_BFW_PWR_PIN)

/* SMRAT RGB DATA  */
//#define SMART_RGB_DATA_GPIO        PTD
//#define SMART_RGB_DATA_PIN         1U
//#define SMART_RGB_DATA_MASK        (0x1u << SMART_RGB_DATA_PIN)

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

#define TEST_PIN_H                 (PTA->PSOR = 0x0002)
#define TEST_PIN_L                 (PTA->PCOR = 0x0002)



/* BUFFER config */
#define TX_MAILBOX  (2UL)
#define RX_MAILBOX  (3UL)
#define EOL_TX_MAILBOX  (4UL)
#define EOL_RX_MAILBOX  (5UL)

/* CAN ID define */
#define RRM_1_ID                    (0X501)
#define RRM_2_ID                    (0X502)
#define RRM_3_ID                    (0X503)
#define RRM_4_ID                    (0X504)
#define FLM_1_ID                    (0X540)
#define RLM_1_ID                    (0X550)
#define ITM_0_ID                    (0X6F0)

#define TX_LCM_0_ID                 (0x602)
#define TX_LCM_REQ_ID               (0x520)

#define RX_MSG_ID                   (0x507)//(0x521)
#define RX_EOL_ID                   (0x6F0)

#define RX_MSG_ID_MASK              (0X7F8)
#define RX_EOL_ID_MASK              (0X6FF)

#define EOL_TX_MSG_ID               (1UL)
#define EOL_LED_CONFIG_ID           (2UL)
#define EOL_LED_SET_RGB_ID          (3UL)

/* CAN SID define */
#define SID_Do_nothing              0X00
#define SID_digLED_Init             0X01
#define SID_digLED_Set_RGB          0X02
#define SID_digLED_Test             0X03
#define SID_digLED_Reset            0X04
#define SID_digLED_Set_Config       0X05
#define SID_digLED_Set_PWM_Red      0X06
#define SID_digLED_Set_PWM_Green    0X07
#define SID_digLED_Set_PWM_Blue     0X08
#define SID_digLED_Set_Cur_Green    0X09
#define SID_digLED_Set_Cur_Blue     0X10
#define SID_digLED_Read_Param       0X11
#define SID_digLED_Read_Temp        0X12
#define SID_digLED_Read_Status      0X13
#define SID_digLED_Read_Diagnostic  0X14
#define SID_digLED_Set_Bias         0X17
#define SID_digLED_Set_Trg_Adc_Cal  0X23
#define SID_digLED_Set_Adc_Dac      0X24
#define SID_digLED_Set_Dim          0X25
#define SID_digLED_Define_Mcast     0X26
#define SID_digLED_Read_PWM_Red     0X27
#define SID_digLED_Read_PWM_Green   0X28
#define SID_digLED_Read_PWM_Blue    0X29
#define SID_digLED_Ping             0X30
#define SID_scanColor               0X33
#define SID_dmaBlock                0X34

#define TEST_startMode              0XF0
#define TEST_wakeVoice              0XF1
#define TEST_receiveVoice           0XF2
#define TEST_errorMode              0XF3








typedef struct
{
    uint8_t TestNr;
    uint16_t Address;
} Test_Values;

typedef struct
{
    uint16_t Param;
    uint16_t Address;
} Set_Config_Values;

typedef struct
{
    uint8_t Red;
    uint8_t Green;
    uint8_t Blue;
    uint16_t Address;
} Set_RGB_Values;

typedef struct
{
    uint8_t Mode;
    uint16_t Address;
} Adc_Cal_Values;

typedef enum
{
    BUS_FREE,
    OPERATION_ONGOING
} APP_STATES;



/***  CAN MESSAGE  ***/
#define Default_MODE     0

#define V1_MODE     1
#define V2_MODE     2
#define V3_MODE     3
#define V4_MODE     4
#define V5_MODE     5
#define V6_MODE     6
#define V7_MODE     7
#define V8_MODE     8
#define V9_MODE     9
#define V10_MODE    10
#define V11_MODE    11
#define V12_MODE    12

#define WARNING     1
#define PLA         2
#define TA          3
#define WAKING      4
#define LISTEN      5
#define ANALYZE     6
#define BROADCAST   7
#define SPECIAL     8

#define WARNING_RED             1
#define WARNING_YELLOW          2
#define WARNING_RED_REPEAT      3
#define WARNING_YELLOW_REPEAT   4
#define WARNING_YELLOW_LEFT     5
#define WARNING_YELLOW_RIGHT    6

#define PLA_SEARCHING           1
#define PLA_FOUND               2
#define PLA_ACTIVE              3
#define PLA_BRAKE               4

#define TA_ACTIVATED            1
#define TA_DEACTIVATED          2

#define WAKING_FRONT_LEFT       1
#define WAKING_FRONT_RIGHT      2
#define WAKING_REAR             3

#define LISTEN_FRONT_LEFT       1
#define LISTEN_FRONT_RIGHT      2
#define LISTEN_REAR             3

#define ANALYZE_FRONT_LEFT      1
#define ANALYZE_FRONT_RIGHT     2
#define ANALYZE_REAR            3

#define BROADCAST_FRONT_LEFT    1
#define BROADCAST_FRONT_RIGHT   2
#define BROADCAST_REAR          3

#define SPECIAL_BIRTHDAY        1
#define SPECIAL_WELCOME         2
#define SPECIAL_BYE             3



typedef struct
{
    uint8_t lampMode4Voice      : 4;
    uint8_t reserved1           : 4;

    uint8_t volume;

    uint8_t ambientLightMode    : 4;
    uint8_t reserved2           : 4;

    uint8_t extIneractiveLightMode : 4;
    uint8_t FLMStatus           : 4;

    uint8_t RLMStatus           : 4;
    uint8_t reserved3           : 4;
} *ptrLCM_0;

typedef struct
{
    uint8_t lampMode4Voice      : 4;
    uint8_t ligthIntensity      : 4;

    uint8_t voiceVolume;        //语音音量值

    uint8_t volumeEnergyValue;  //语音音量占系统音量百分比

    uint8_t volume;             //系统音量音量值

    uint8_t vehicleSpeedLow     : 8;

    uint8_t vehicleSpeedHigh    : 2;
    uint8_t musicRhythm         : 6;
} *ptrRRM_1;

typedef struct
{
    uint8_t ambientLightMode      : 4;
    uint8_t switchOnOff           : 1;  //TODO: 加入氛围灯关闭功能
    uint8_t systemSwitch          : 2;  //TODO: 加入系统关闭功能
    uint8_t reserved1             : 1;
} *ptrRRM_2;

typedef struct
{
    uint8_t lightType;
    uint8_t lightMode;
    uint8_t d2_reserved;
    uint8_t d3_reserved;
    uint8_t d4_reserved;
    uint8_t d5_reserved;
    uint8_t d6_reserved;
    uint8_t d7_reserved;
} *ptrRRM_4;

typedef struct
{                      
    /* d01 */      
    uint16_t red_d  :12;
    uint16_t reserved1 : 3;
    uint16_t enginearMode :1;
    /* d23 */ 
    uint16_t green_d :12;
    uint16_t reserved2 :4;
    /* d45 */
    uint16_t blue_d :12;
    uint16_t reserved3 :4;
    /* d67 */ 
    uint16_t reserved4;
} *ptrITM_0;






void FreemasterStateMachine(void);
void delay(volatile uint16_t cycles);
void lptmrISR(void);
//void flexCAN_ISR(void);
void CAN_ISR(uint32_t instance, can_event_t eventType, uint32_t objIdx, void *driverState);
void initParameters(void);
void uart1RxCallback(void *driverState, uart_event_t event, void *userData);






#endif /* USERCODE_H_ */
