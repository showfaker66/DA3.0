#ifndef _BSP_LIN_H_
#define _BSP_LIN_H_

/* LIN 使能引脚 */
#define LIN_EN_GPIO         PTC
#define LIN_EN_PIN          (1U << 9)


/************************************
    LIN Macro
*************************************/
/* (CLK (MHz)* timer period (us) / Prescaler) */
#define TIMER_COMPARE_VAL               (uint16_t)(2000U)
#define TIMER_TICKS_1US                 (uint16_t)(4U)
#define DATA_SIZE                       (8U)
#define TIMEOUT                         (500U)

/****** LIN ID define ******/
#define ID_3C_SLAVE_RECEIVE_DATA        (0x3C)
#define ID_3D_MASTER_RECEIVE_DATA       (0x3D)         

#define ID_11_MASTER_RECEIVE_DATA       (0x11)
#define ID_0A_SLAVE_RECEIVE_DATA        (0x0A)
#define ID_0B_SLAVE_RECEIVE_DATA        (0X0B)
#define ID_0D_SLAVE_RECEIVE_DATA        (0X0D)

#define ID_21_MASTER_RECEIVE_DATA       (0x21)
#define ID_1A_SLAVE_RECEIVE_DATA        (0x1A)
#define ID_1B_SLAVE_RECEIVE_DATA        (0X1B)
#define ID_1D_SLAVE_RECEIVE_DATA        (0X1D)

#define FRAME_MASTER_RECEIVE_DATA       (2U)
#define FRAME_GO_TO_SLEEP               (3U)


typedef enum
{
    LIN_ID_0X3C_L,
    LIN_ID_0X3D_L,
    LIN_ID_0X11,
    LIN_ID_0X0A,
    LIN_ID_0X0B,
    LIN_ID_0X0D,
    
    LIN_ID_0X3C_R,
    LIN_ID_0X3D_R,
    LIN_ID_0X21,
    LIN_ID_0X1A,
    LIN_ID_0X1B,
    LIN_ID_0X1D,
}LIN_IDS;

typedef union{
    uint64_t data_64bit;
    uint8_t data[8];
    struct {
        uint8_t data0;  /*DATA 0*/
        uint8_t data1;  /*DATA 1*/
        uint8_t left_low_beam   :1; /*DATA 2*/
        uint8_t right_low_beam  :1;
        uint8_t left_position   :1;
        uint8_t right_position  :1;
        uint8_t reserve1        :4;
        uint8_t reserve2;  /*DATA 3*/
        uint32_t reserve3; /*DATA 4~7*/
    }e115;
}linData8Bytes;

typedef struct
{
    linData8Bytes data;
    uint8_t size;   
}LIN_MSG_Type;



/*********************************************************************************************************************
 * Export Func
 *********************************************************************************************************************/
void bspLIN_Init(void);
void prvLIN_Task(void *pvParameters );

#endif
/* end of file*/
