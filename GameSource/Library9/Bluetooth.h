#pragma once
#include <Windows.h>
#include <bthsdpdef.h>
#include <bluetoothapis.h>


////Bluetooth�̃C���^�[�t�F�C�X
//class Bluetooth
//{
//public:
//	Bluetooth();
//	~Bluetooth();
//
//	void	Passkey(wchar_t* name);		//�p�X�L�[�̃Z�b�g
//	void	SetDevice();	//�p�����[�^�f�o�C�X�̃Z�b�g
//	void	SetParam();		//�p�����[�^�̃Z�b�g
//
//private:
//	BLUETOOTH_FIND_RADIO_PARAMS	param;	//�p�����[�^
//	HANDLE		radioHandle;
//	HBLUETOOTH_RADIO_FIND	hfind;
//
//	BLUETOOTH_DEVICE_INFO	devInfo;
//	//�p�X��
//	wchar_t*	passkey;
//	unsigned long passlen;
//
//};
//
