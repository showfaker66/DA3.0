#ifndef __MOS_CTRL_H
#define _MOS_CTRL_H

#include "pin_mux.h"

#define PIN_HIGH 1
#define PIN_LOW 0
#define EN_LOGO_PORT PTC  // EN_LOGO
#define EN_LOGO_PIN 14
#define logoCtrl_PORT PTC // logoCtrl
#define logoCtrl_PIN 8
#define barCtrl_PORT PTB  // barCtrl
#define barCtrl_PIN 2
#define beltCtrl_PORT PTB // beltCtrl
#define beltCtrl_PIN 1
#define LOGO_EN_PORT PTC // LOGO_EN
#define LOGO_EN_PIN 9 


void prvMosCtrlTask(void *pvParameters);
#endif
