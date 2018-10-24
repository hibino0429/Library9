#pragma once
#include "DSound.h"



//-----------------------------------------------------------
//サウンド・リスナー
//-----------------------------------------------------------
class SoundListener
{
public:
	SoundListener();
	~SoundListener();

	bool	CreateListener();							//リスナーの作成

	void	SetListener(float dist);					//リスナーの設定
	void	SetDoppler(float doppler);					//ドップラーの設定
	void	SetPosition(float, float, float, DWORD);	//位置の設定
	void	SetVelocity(float, float, float, DWORD);	//速度の設定
	void	SetOrientation(float, float, float, float, float, float, DWORD);	//方向の設定
	void	SetRolloff(float rolloff, DWORD);			//ロール・オフの設定
	void	SetCommitDefferred();						//DS_3D_DEFFRREDの設定を反映させる

	void	GetPrimaryBuf(LPDIRECTSOUNDBUFFER* pBuf);	//プライマリバッファの確保

public:
	LPDIRECTSOUND3DLISTENER8	pListener;			//リスナー
	LPDIRECTSOUNDBUFFER			pPrimaryBuf;		//プライマリバッファ

};