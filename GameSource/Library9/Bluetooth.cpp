#include "Bluetooth.h"


////コンストラクタ
//Bluetooth::Bluetooth() : radioHandle(nullptr), hfind(nullptr)
//{
//	ZeroMemory(&param,sizeof(BLUETOOTH_FIND_RADIO_PARAMS));
//}
////デストラクタ
//Bluetooth::~Bluetooth()
//{
//	radioHandle = nullptr;
//}
//
//
////パスキーのセット
//void	Bluetooth::Passkey(wchar_t* name)
//{
//	passkey = name;
//	passlen = wcslen(passkey) * sizeof(wchar_t);
//	BluetoothAuthenticateDevice(nullptr, nullptr, &devInfo, passkey, passlen);
//}
////パラメータデバイスのセット
//void	Bluetooth::SetDevice()
//{
//	BLUETOOTH_DEVICE_SEARCH_PARAMS	searchParam;
//	memset(&searchParam, 0, sizeof(BLUETOOTH_DEVICE_SEARCH_PARAMS));
//	searchParam.dwSize = sizeof(BLUETOOTH_DEVICE_SEARCH_PARAMS);
//	searchParam.fReturnAuthenticated = true;
//	searchParam.fReturnRemembered = true;
//	searchParam.fReturnConnected = true;
//	searchParam.fReturnUnknown = true;
//	searchParam.fIssueInquiry = false;
//	searchParam.cTimeoutMultiplier = 0;
//	searchParam.hRadio = nullptr;		//all
//
//	HBLUETOOTH_DEVICE_FIND	hfind = nullptr;
//	memset(&devInfo, 0, sizeof(BLUETOOTH_DEVICE_INFO));
//	devInfo.dwSize = sizeof(BLUETOOTH_DEVICE_INFO);
//	
//	if (hfind = BluetoothFindFirstDevice(&searchParam, &devInfo))
//	{
//		do
//		{
//			//devInfo.szName		//デバイス名
//			//devInfo.Address		//アドレス
//			//devInfo.fConnected
//			//devInfo.fRememberd
//			//devInfo.fAuthenticated
//		} while (BluetoothFindNextDevice(hfind, &devInfo));
//
//		BluetoothFindDeviceClose(hfind);
//	}
//
//}
//
//
////パラメータのセット
//void	Bluetooth::SetParam()
//{
//	memset(&param, 0, sizeof(BLUETOOTH_FIND_RADIO_PARAMS));
//	param.dwSize = sizeof(BLUETOOTH_FIND_RADIO_PARAMS);
//
//	if (hfind = BluetoothFindFirstRadio(&param, &radioHandle))
//	{
//		do
//		{
//			BLUETOOTH_RADIO_INFO	radioInfo;
//			memset(&radioInfo, 0, sizeof(BLUETOOTH_RADIO_INFO));
//			radioInfo.dwSize = sizeof(BLUETOOTH_RADIO_INFO);
//			BluetoothGetRadioInfo(radioHandle, &radioInfo);
//
//			//radioInfo.szName = Local HostName
//			//radioInfo.address = Local Address
//
//			CloseHandle(radioHandle);
//		} while (BluetoothFindNextRadio(hfind, &radioHandle));
//
//		BluetoothFindRadioClose(hfind);
//	}
//}