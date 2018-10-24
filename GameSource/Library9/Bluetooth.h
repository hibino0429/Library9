#pragma once
#include <Windows.h>
#include <bthsdpdef.h>
#include <bluetoothapis.h>


////Bluetoothのインターフェイス
//class Bluetooth
//{
//public:
//	Bluetooth();
//	~Bluetooth();
//
//	void	Passkey(wchar_t* name);		//パスキーのセット
//	void	SetDevice();	//パラメータデバイスのセット
//	void	SetParam();		//パラメータのセット
//
//private:
//	BLUETOOTH_FIND_RADIO_PARAMS	param;	//パラメータ
//	HANDLE		radioHandle;
//	HBLUETOOTH_RADIO_FIND	hfind;
//
//	BLUETOOTH_DEVICE_INFO	devInfo;
//	//パス名
//	wchar_t*	passkey;
//	unsigned long passlen;
//
//};
//
