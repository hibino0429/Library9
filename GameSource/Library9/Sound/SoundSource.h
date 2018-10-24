#pragma once
#include "DSound.h"
#include "SoundManager.h"


//------------------------------------------------------
//サウンド・ソース	(音源)
//------------------------------------------------------
class	SoundSource
{
public:
	SoundSource();
	~SoundSource();

	bool	CreateSound(LPTSTR fileName);
	bool	CreateSource();			//音源の作成
	void	SetMinDistance(float minDist, DWORD apply);		//最小距離
	void	SetMaxDistance(float maxDist, DWORD apply);		//最大距離
	void	SetMode(DWORD mode, DWORD apply);				//3Dサウンド処理モードの設定
	void	SetPositionSource(float, float, float, DWORD);		//位置
	void	SetVelocitySource(float, float, float, DWORD);		//速度
	void	SetConeAngle(DWORD, DWORD, DWORD);					//サウンド・コーンの設定
	void	SetConeOrientation(float x, float y, float z, DWORD);
	void	SetConeOutsideVolume(LONG, DWORD);
	void	Play(bool loop);

	void	GetPrimaryBuf(LPDIRECTSOUNDBUFFER8& pBuf);		//プライマリバッファの取得


	
public:
	LPDIRECTSOUND3DBUFFER8		pSource;			//音源(ソース)
	LPDIRECTSOUNDBUFFER8		pPrimaryBuf;		//プライマリバッファ
	LPDIRECTSOUNDBUFFER			pDSBuf;				//8に対応するためのバッファ
	DSBUFFERDESC				dsBufDesc;			//サウンドバッファ

};