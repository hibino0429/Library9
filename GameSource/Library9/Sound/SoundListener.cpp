#include "SoundListener.h"


//コンストラクタ
SoundListener::SoundListener() : pListener(NULL), pPrimaryBuf(NULL)
{

}

//デストラクタ
SoundListener::~SoundListener()
{
	if (pListener != NULL) { pListener->Release(); pListener = NULL; }
	if (pPrimaryBuf != NULL) { pPrimaryBuf->Release(); pPrimaryBuf = NULL; }
}


//リスナーの作成
bool	SoundListener::CreateListener()
{
	if (FAILED(pPrimaryBuf->QueryInterface(IID_IDirectSound3DListener8,
		(LPVOID*)&pListener)))
	{
		MessageBox(NULL, TEXT("リスナーの作成に失敗しました"), TEXT("CreateListener"), MB_OK);
		return false;
	}
	return true;
}


//距離の設定
void	SoundListener::SetListener(float dist)
{
	pListener->SetDistanceFactor(dist, DS3D_IMMEDIATE);
}

//ドップラー効果の設定
void	SoundListener::SetDoppler(float doppler)
{
	//DS3D_MINDOPPLERFACTOR(0.0)		//最小
	//DS3D_MAXDOPPLERFACTOR(10.0)		//最大
	//1が標準
	pListener->SetDopplerFactor(doppler, DS3D_IMMEDIATE);
}

//位置の設定
void	SoundListener::SetPosition(float x, float y, float z, DWORD apply)
{
	pListener->SetPosition(x, y, z, apply);
}

//速度の設定
void	SoundListener::SetVelocity(float vx, float vy, float vz, DWORD apply)
{
	pListener->SetVelocity(vx, vy, vz, apply);
}

//方向の設定
void	SoundListener::SetOrientation(float xFront, float yFront, float zFront, float xTop, float yTop, float zTop, DWORD apply)
{
	pListener->SetOrientation(xFront, yFront, zFront, xTop, yTop, zTop, apply);
}

//ロール・オフの設定
void	SoundListener::SetRolloff(float rolloff, DWORD apply)
{
	//リスナーと音源との距離による、減衰の度合い
	//DS3D_MINROLLOFFFACTOR(0.0f)	//最小
	//DS3D_MAXROLLOFFFACTOR(10.0f)	//最大
	//1が標準
	pListener->SetRolloffFactor(rolloff, apply);
}

//DS3D_DEFEREEDの設定を反映させる
void	SoundListener::SetCommitDefferred()
{
	pListener->CommitDeferredSettings();
}


//プライマリバッファの確保
void	SoundListener::GetPrimaryBuf(LPDIRECTSOUNDBUFFER* pBuf)
{
	this->pPrimaryBuf = *pBuf;
	MessageBox(NULL, TEXT("pPrimaryの設定"), TEXT("プライマリバッファの生成に失敗"), MB_OK);
}