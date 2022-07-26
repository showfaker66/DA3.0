#ifndef _BSP_CAN_H_
#define _BSP_CAN_H_

/* CAN STB控制引脚 H:STB  L:NORMAL */
// #define CAN_STB_GPIO        PTE
// #define CAN_STB_PIN         (1U << 10)

/* BUFFER config */
#define TX_MAILBOX                  (2UL)
#define RX_MAILBOX                  (3UL)
#define EOL_TX_MAILBOX              (4UL)
#define EOL_RX_MAILBOX              (5UL)
#define exTX_MAILBOX                (6UL)/*专门用来发送扩展帧*/

/****** CAN Filiter define ******/
/* CAN Receive ID Filiter define */
#define RX_MSG_ID                   (0x507)
#define RX_EOL_ID                   (0x6F0)
/* CAN Receive ID MASK define */
#define RX_MSG_ID_MASK              (0X7F8)
#define RX_EOL_ID_MASK              (0X6FF)

#define CAN_MSG_QUEUE_LENGTH         16
#define queueSendDONT_BLOCK			( 0UL ) // 往队列发送的时候，不阻塞

/* CAN ID define */
#define RRM_1_ID                    (0X501)
#define RRM_2_ID                    (0X502)
#define RRM_3_ID                    (0X503)
#define RRM_4_ID                    (0X504)
#define FLM_1_ID                    (0X540)
#define RLM_1_ID                    (0X550)
#define ITM_0_ID                    (0X603)


typedef union{

    //[1] 通用8字节
    uint8_t DATA_8[8];

    //[3] 各种CAN报文的详细结构体
    struct {                      
        /* d0 */      
        uint8_t voiceLampMode   :4;
        uint8_t lightIntensity  :4;
        /* d1 */ 
        uint8_t voiceVolume;
        /* d2 */ 
        uint8_t volumeEnergyValue;
        /* d3 */ 
        uint8_t volume;
        /* d4~5 */ 
        uint16_t speed  : 10;
        uint8_t d45_reserved :6;
        /* d6 */
        uint8_t d6;
        /* d7 */
        uint8_t d7;
    }ID_501;

    struct {                      
        /* d01 */      
        uint16_t red_d  :15;
        uint16_t enginearMode :1;
        /* d23 */ 
        uint16_t green_d :15;
        uint16_t reserved1 :1;
        /* d45 */
        uint16_t blue_d :15;
        uint16_t reserved2 :1; 
        /* d67 */ 
        uint16_t reserved3;
    }ID_6F0;

    struct {
        uint8_t ambientLightMode      : 4;
        uint8_t switchOnOff           : 1;  //TODO: 加入氛围灯关闭功能
        uint8_t systemSwitch          : 2;  //TODO: 加入系统关闭功能
        uint8_t reserved1             : 1;
    }ID_502;

    struct
    {
        uint8_t lightTpye;
        uint8_t lightMode;
        uint8_t d2_reserved;
        uint8_t d3_reserved;
        uint8_t d4_reserved;
        uint8_t d5_reserved;
        uint8_t d6_reserved;
        uint8_t d7_reserved;
    }ID_504;

}CAN_MSG_Type;







void bspCAN_Init(void);
void CAN_ISR(uint32_t instance, can_event_t eventType, uint32_t objIdx, void *driverState);
void prvCAN_SendTask(void *pvParameters );
void prvCAN_RespondTask(void *pvParameters );


#endif
/* end of file*/