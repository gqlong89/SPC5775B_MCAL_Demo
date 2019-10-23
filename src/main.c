/*
 * main implementation: use this 'C' sample to create your own application
 *
 */

#include "typedefs.h"
#include "Mcal.h"
#include "Mcu.h"
#include "Gpt.h"
#include "StdRegMacros.h"
#include "Reg_eSys.h"
#include "Port.h"
#include "Dio.h"
#include "IntCtrl.h"
#include "McanComm.h"
#include "EthComm.h"
#include "PhyTja110x.h"
#include "PhyDP83822I.h"



/*
@brief
@details
@para
@return
*/
int main(void)
{
	Std_ReturnType ret;

	Mcu_Init(&McuConfigPB_0);
	ret = Mcu_InitClock(McuConf_McuClockSettingConfig_McuClockSettingConfig);
	while (Mcu_GetPllStatus() != MCU_PLL_LOCKED){;}
	Mcu_DistributePllClock();

	InterruptController_Init();

	Port_Init(&PortConfigSet_0);

	SystemTickTimer_Init();

	McanComm_Init();
	McanComm_RxBufferInit();

	Ethernet_Init();
	PHY_TJA1101_Init();
	PHY_DP83822_Init();

	Switch_SJA1105_Init();

	/* Loop forever */
	for(;;)
	{
		Dio_FlipChannel(DioConf_DioChannel_LED1_DRIVE_EN);
		Dio_FlipChannel(DioConf_DioChannel_LED2_DRIVE_EN);

		McanComm_TransmitProcess();

		PHY_TJA1101_GetCurrentStatus();
		PHY_DP83822_GetCurrentStatus();

		SystemDelay_Ms(100);
	}
}
