#include "mosCtrl.h"

#define getLogoENStatus (((LOGO_EN_PORT->PDIR) & (1 << LOGO_EN_PIN)) >> LOGO_EN_PIN)

#define MOS_CTRL_DELAY_TICKS 100
void mosCtrl(void)
{
	PINS_DRV_WritePin(barCtrl_PORT, barCtrl_PIN, PIN_HIGH);
	PINS_DRV_WritePin(beltCtrl_PORT, beltCtrl_PIN, PIN_HIGH);

	while(1) {
		if(getLogoENStatus == PIN_LOW) {
			PINS_DRV_WritePin(EN_LOGO_PORT, EN_LOGO_PIN, PIN_HIGH);
			PINS_DRV_WritePin(logoCtrl_PORT, logoCtrl_PIN, PIN_HIGH);
		}
		else {
			PINS_DRV_WritePin(EN_LOGO_PORT, EN_LOGO_PIN, PIN_LOW);
			PINS_DRV_WritePin(logoCtrl_PORT, logoCtrl_PIN, PIN_LOW);
		}

		vTaskDelay(MOS_CTRL_DELAY_TICKS);
	}
}

void prvMosCtrlTask(void *pvParameters)
{
	mosCtrl();
}
