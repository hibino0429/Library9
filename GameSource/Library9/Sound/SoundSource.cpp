#include "SoundSource.h"


//コンストラクタ
SoundSource::SoundSource() : pSource(NULL),pPrimaryBuf(NULL),pDSBuf(NULL)
{

}
//デストラクタ
SoundSource::~SoundSource()
{
	if (pSource != NULL) { pSource->Release(); pSource = NULL; }
	if (pPrimaryBuf != NULL) { pPrimaryBuf->Release(); pPrimaryBuf = NULL; }
	if (pDSBuf != NULL) { pDSBuf->Release(); pDSBuf = NULL; }
}

//音の生成
bool	SoundSource::CreateSound(LPTSTR fileName)
{
	CWaveFile	waveFile;
	if (FAILED(waveFile.Open(fileName, NULL, WAVEFILE_READ)))
	{
		MessageBox(NULL, TEXT("Waveファイルのオープンに失敗しました"), TEXT("Open"), MB_OK);
		return false;
	}


	// セカンダリ・バッファを作成する
	// DSBUFFERDESC構造体を設定
	ZeroMemory(&dsBufDesc, sizeof(DSBUFFERDESC));
	dsBufDesc.dwSize = sizeof(DSBUFFERDESC);
	dsBufDesc.dwFlags = DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_GLOBALFOCUS | DSBCAPS_LOCDEFER | DSBCAPS_CTRL3D;
	//dsBufDesc.dwBufferBytes = waveFile.GetSize();
	//dsBufDesc.lpwfxFormat = waveFile.GetFormat();
	//dsBufDesc.guid3DAlgorithm = DS3DALG_HRTF_FULL;	// とりあえず高音質のアルゴリズムを要求しておく


	//サウンドバッファの作成
	Audio::CreateSoundBuf(&dsBufDesc, &pDSBuf);
	

	//サウンドバッファの作成
	//SoundBufferのインターフェイスの取得
	HRESULT hr;
	hr = pDSBuf->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)&pPrimaryBuf);
	SAFE_RELEASE(pDSBuf);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("SoundBufのインターフェイスの取得に失敗"), TEXT("QueryInterface"), MB_OK);
		return false;
	}
	

	hr = pPrimaryBuf->QueryInterface(IID_IDirectSound3DBuffer8, (LPVOID*)&pSource);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("Sound3DBufの取得に失敗しました"), TEXT("pPrimary"), MB_OK);
		return false;
	}

	//セカンダリ・バッファにWaveデータを書き込む
	LPVOID	lpvPtr1 = NULL;
	DWORD	dwByte1 = 0;
	LPVOID	lpvPtr2 = NULL;
	DWORD	dwByte2 = 0;

	hr = pPrimaryBuf->Lock(0, waveFile.GetSize(), &lpvPtr1, &dwByte1, &lpvPtr2, &dwByte2, 0);

	//DSERR_BUFFERLOSTが返された場合、Restore()でバッファを復元
	if (hr == DSERR_BUFFERLOST)
	{
		pPrimaryBuf->Restore();
		hr = pPrimaryBuf->Lock(0, waveFile.GetSize(), &lpvPtr1, &dwByte1, &lpvPtr2, &dwByte2, 0);
	}
	if (SUCCEEDED(hr))
	{
		//バッファに書き込む
		DWORD	rsize;
		waveFile.Read((LPBYTE)lpvPtr1, dwByte1, &rsize);
		if (dwByte2 != 0) { waveFile.Read((LPBYTE)lpvPtr2, dwByte2, &rsize); }

		//書き込み終了後、Unlockする
		hr = pPrimaryBuf->Unlock(lpvPtr1, dwByte1, lpvPtr2, dwByte2);
	}
	return true;
}

//音源の作成
bool	SoundSource::CreateSource()
{
	if (FAILED(pPrimaryBuf->QueryInterface(IID_IDirectSound3DBuffer8,
		(LPVOID*)&pSource)))
	{
		MessageBox(NULL, TEXT("音源の作成に失敗しました"), TEXT("CreateSource"), MB_OK);
		return false;
	}
	return true;
}

//最小距離
void	SoundSource::SetMinDistance(float minDist, DWORD apply)
{
	pSource->SetMinDistance(minDist, apply);
}
//最大距離
void	SoundSource::SetMaxDistance(float maxDist, DWORD apply)
{
	pSource->SetMaxDistance(maxDist, apply);
}

//3Dサウンド処理モードの設定
void	SoundSource::SetMode(DWORD mode, DWORD apply)
{
	//標準モード	(D3DMODE_NORMAL)
	//相対モード	(D3DMODE_HEADRELATIVE)
	//無効モード	(D3DMODE_DISABLE)
	if (FAILED(pSource->SetMode(mode, apply)))
	{
		MessageBox(NULL, TEXT("モードの設定に失敗しました"), TEXT("SetMode"), MB_OK);
		return;
	}
}

//位置と速度の設定
void	SoundSource::SetPositionSource(float x, float y, float z, DWORD apply)
{
	pSource->SetPosition(x, y, z, apply);
}
void	SoundSource::SetVelocitySource(float vx, float vy, float vz, DWORD apply)
{
	pSource->SetVelocity(vx, vy, vz, apply);
}

//サウンドコーンの設定
void	SoundSource::SetConeAngle(DWORD insideConeAngle, DWORD outsideConeAngle, DWORD apply)
{
	pSource->SetConeAngles(insideConeAngle, outsideConeAngle, apply);
}

//コーンの向きの設定
void	SoundSource::SetConeOrientation(float x, float y, float z, DWORD apply)
{
	pSource->SetConeOrientation(x, y, z, apply);
}
//外部コーンの音量の設定
void	SoundSource::SetConeOutsideVolume(LONG coneOutsideVolume, DWORD apply)
{
	pSource->SetConeOutsideVolume(coneOutsideVolume, apply);
}

//音源から音を鳴らす
void	SoundSource::Play(bool loop)
{
	int flags = 0;
	if (loop) { flags = flags | DSBPLAY_LOOPING; }
	pPrimaryBuf->Play(0, 0, flags);
}


//プライマリバッファの取得
void	SoundSource::GetPrimaryBuf(LPDIRECTSOUNDBUFFER8& pBuf)
{
	this->pPrimaryBuf = pBuf;
}


