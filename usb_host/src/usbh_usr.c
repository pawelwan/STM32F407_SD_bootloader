#include "usbh_usr.h"
#include "stm32f4xx.h"
#include "term_io.h"

USBH_Usr_cb_TypeDef USR_Callbacks = {
	USBH_USR_Init,
	USBH_USR_DeInit,
	USBH_USR_DeviceAttached,
	USBH_USR_ResetDevice,
	USBH_USR_DeviceDisconnected,
	USBH_USR_OverCurrentDetected,
	USBH_USR_DeviceSpeedDetected,
	USBH_USR_Device_DescAvailable,
	USBH_USR_DeviceAddressAssigned,
	USBH_USR_Configuration_DescAvailable,
	USBH_USR_Manufacturer_String,
	USBH_USR_Product_String,
	USBH_USR_SerialNum_String,
	USBH_USR_EnumerationDone,
	USBH_USR_UserInput,
	USBH_USR_MSC_Application,
	USBH_USR_DeviceNotSupported,
	USBH_USR_UnrecoveredError
};

extern USBH_Usr_Result_t USBH_Usr_INT_Result;
uint8_t Application = USH_USR_FS_INIT;

void USBH_USR_Init(void) {
	/* USB Library has been initialized, device is not connected yet */
	USBH_Usr_INT_Result = USBH_Usr_Result_Disconnected;
	/* We have to initialize first */
	Application = USH_USR_FS_INIT;

	xprintf("USBH_USR_Init, A=%d, Res=%d\n",Application,USBH_Usr_INT_Result);
}

void USBH_USR_DeviceAttached(void) {
	/* Device has been initialized, device is not connected yet */
	USBH_Usr_INT_Result = USBH_Usr_Result_Disconnected;
	/* We have to initialize first */
	Application = USH_USR_FS_INIT;
	xprintf("USBH_USR_DeviceAttached, A=%d, Res=%d\n",Application,USBH_Usr_INT_Result);
}

void USBH_USR_UnrecoveredError (void) {
	/*  */
	USBH_Usr_INT_Result = USBH_Usr_Result_Disconnected;
	/* We have to initialize first */
	Application = USH_USR_FS_INIT;
	xprintf("USBH_USR_UnrecoveredError, A=%d, Res=%d\n",Application,USBH_Usr_INT_Result);
}

void USBH_USR_DeviceDisconnected (void) {
	/* Device disconnected */
	USBH_Usr_INT_Result = USBH_Usr_Result_Disconnected;

	/* We have to initialize first */
	Application = USH_USR_FS_INIT;
	xprintf("USBH_USR_DeviceDisconnected , A=%d, Res=%d\n",Application,USBH_Usr_INT_Result);
}

void USBH_USR_ResetDevice(void) {
	/* We have to initialize first */
	Application = USH_USR_FS_INIT;
	xprintf("USBH_USR_ResetDevice, A=%d, Res=%d\n",Application,USBH_Usr_INT_Result);
}

void USBH_USR_DeviceSpeedDetected(uint8_t DeviceSpeed) {
	/*if ((DeviceSpeed != HPRT0_PRTSPD_FULL_SPEED) && (DeviceSpeed != HPRT0_PRTSPD_LOW_SPEED)) {
		USBH_Usr_INT_Result = USBH_Usr_Result_Disconnected;
	}*/
	xprintf("USBH_USR_DeviceSpeedDetected, A=%d, Res=%d, spd=%d\n",Application,USBH_Usr_INT_Result,DeviceSpeed);
}

void USBH_USR_Device_DescAvailable(void *DeviceDesc) {

	xprintf("USBH_USR_Init, A=%d, Res=%d\n",Application,USBH_Usr_INT_Result);
}

void USBH_USR_DeviceAddressAssigned(void) {

	xprintf("USBH_USR_Init, A=%d, Res=%d\n",Application,USBH_Usr_INT_Result);
}

void USBH_USR_Configuration_DescAvailable(USBH_CfgDesc_TypeDef * cfgDesc,
    USBH_InterfaceDesc_TypeDef *itfDesc,
    USBH_EpDesc_TypeDef *epDesc) {

	xprintf("USBH_USR_Init, A=%d, Res=%d\n",Application,USBH_Usr_INT_Result);
}

void USBH_USR_Manufacturer_String(void *ManufacturerString) {

	xprintf("USBH_USR_Manufacturer_String, A=%d, Res=%d\n  MS: %s\n",Application,USBH_Usr_INT_Result,(char*)ManufacturerString);
}

void USBH_USR_Product_String(void *ProductString) {

	xprintf("USBH_USR_Product_String, A=%d, Res=%d\n   PS: %s\n",Application,USBH_Usr_INT_Result,(char*)ProductString);
}

void USBH_USR_SerialNum_String(void *SerialNumString) {

	xprintf("USBH_USR_SerialNum_String, A=%d, Res=%d\n  SN: %s\n",Application,USBH_Usr_INT_Result,(char*)SerialNumString);
}

void USBH_USR_EnumerationDone(void) {

	xprintf("USBH_USR_EnumerationDone, A=%d, Res=%d\n",Application,USBH_Usr_INT_Result);
}

void USBH_USR_DeviceNotSupported(void) {
	/* Device is not supported */
	USBH_Usr_INT_Result = USBH_Usr_Result_DeviceNotSupported;
	xprintf("USBH_USR_DeviceNotSupported, A=%d, Res=%d\n",Application,USBH_Usr_INT_Result);
}

USBH_USR_Status USBH_USR_UserInput(void) {
	xprintf("USBH_USR_UserInput, A=%d, Res=%d\n",Application,USBH_Usr_INT_Result);
	return USBH_USR_RESP_OK;
}

void USBH_USR_OverCurrentDetected (void) {
	/* Error */
	xprintf("USBH_USR_OverCurrentDetected, A=%d, Res=%d\n",Application,USBH_Usr_INT_Result);
	USBH_Usr_INT_Result = USBH_Usr_Result_Error;
}

int USBH_USR_MSC_Application(void) {
	/* Device is connected */
	if (Application == USH_USR_FS_INIT) {
		Application = USH_USR_FS_LOOP;

		/* Device is connected */
		USBH_Usr_INT_Result = USBH_Usr_Result_Connected;
		if (USBH_MSC_Param.MSWriteProtect == DISK_WRITE_PROTECTED) {
			/* Device is write protected */
			USBH_Usr_INT_Result = USBH_Usr_Result_WriteProtected;
		}
	}

	//xprintf("USBH_USR_MSC_Application, A=%d, Res=%d\n",Application,USBH_Usr_INT_Result);
	return 0;
}

void USBH_USR_DeInit(void) {
	/* Device disconnected */
	//USBH_Usr_INT_Result = USBH_Usr_Result_Disconnected;
	/* We have to initialize first */
	Application = USH_USR_FS_INIT;
	xprintf("USBH_USR_DeInit, A=%d, Res=%d\n",Application,USBH_Usr_INT_Result);
}
