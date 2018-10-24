#include "DSound.h"

//コンストラクタ
Sound::Sound() : pDirectSound(NULL),pDirectSoundBuf(NULL), dwSpeakerConfig(0), pDSoundGuid(NULL)
, pNewSoundBuf(NULL)
{
	
}

//デストラクタ
Sound::~Sound()
{
	this->BufRelease();
	this->InterfaceRelease();
}

//サウンド・デバイスの取得
bool	Sound::DSoundEnumCallBack()
{
	
	//DirectSoundEnumerate((LPDSENUMCALLBACK)DSEnumProc, &hCombo);
	return true;
}
BOOL CALLBACK Sound::DSEnumProc(LPGUID lpGUID, LPCTSTR lpszDesc, LPCTSTR lpszDrvName, LPVOID lpContext)
{
	HWND hCombo = (HWND)lpContext;
	LPGUID lpTemp = NULL;
	
	if (lpGUID != NULL)
	{
		if ((lpTemp = (LPGUID)malloc(sizeof(GUID))) == NULL)
		{
			return true;
		}
		memcpy(lpTemp, lpGUID, sizeof(GUID));
	}

	//ComboBox_AddString(hCombo, lpszDesc);
	//ComboBox_SetItemData(hCombo, ComboBox_FindString(hCombo, 0, lpszDesc), lpTemp);
	free(lpTemp);
	lpTemp = NULL;

	return true;
}


//2:DirectSoundオブジェクトの作成
bool	Sound::DSoundCreate()
{
	if (FAILED(DirectSoundCreate8(
		NULL,		//デフォルトではNULL、GUIDを取得するならpDSoundGuid
		&pDirectSound,
		NULL
	)))
	{
		MessageBox(NULL, TEXT("DirectSoundオブジェクトの生成に失敗しました"), TEXT("DSoundCreate"), MB_OK);
		return false;
	}
	return true;
}



//3:協調レベルの設定
bool	Sound::SetCooperativeLevel(HWND hWnd)
{
	if (FAILED(pDirectSound->SetCooperativeLevel(
		hWnd, DSSCL_PRIORITY
	)))
	{
		MessageBox(NULL, TEXT("協調レベルの設定に失敗しました"), TEXT("SetCooperativeLevel"), MB_OK);
		return false;
	}
	return true;
}




//4:デバイスの性能の調査
bool	Sound::GetCaps()
{
	dsCaps.dwSize = sizeof(DSCAPS);	//必ず初期化

	if (FAILED(pDirectSound->GetCaps(&dsCaps)))
	{
		MessageBox(NULL, TEXT("デバイスの性能の取得に失敗しました"), TEXT("GetCaps"), MB_OK);
		return false;
	}
	return true;
}



//5:スピーカーの調査
bool	Sound::GetSpeakerConfig()
{
	if (FAILED(pDirectSound->GetSpeakerConfig(&dwSpeakerConfig)))
	{
		MessageBox(NULL, TEXT("スピーカーの情報の取得に失敗しました"), TEXT("GetSpeakerConfig"), MB_OK);
		return false;
	}

	switch (DSSPEAKER_CONFIG(dwSpeakerConfig))
	{
	case DSSPEAKER_5POINT1:		//サブウーファ付きの5サラウンド・スピーカー
		break;
	case DSSPEAKER_DIRECTOUT:	//スピーカー用の構成は行われない
		break;
	case DSSPEAKER_HEADPHONE:	//ヘッドホン
		break;
	case DSSPEAKER_MONO:		//モノラル・スピーカー
		break;
	case DSSPEAKER_QUAD:		//4チャンネル・ステレオ・スピーカー
		break;
	case DSSPEAKER_STEREO:		//ステレオ・スピーカー

		//2つのスピーカーの配置
		switch (DSSPEAKER_GEOMETRY(dwSpeakerConfig))
		{
		case DSSPEAKER_GEOMETRY_WIDE:		//リスナーを中心として20度の角度
			break;
		case DSSPEAKER_GEOMETRY_NARROW:		//リスナーを中心として10度の角度
			break;
		case DSSPEAKER_GEOMETRY_MIN:		//リスナーを中心として5度の角度
			break;
		case DSSPEAKER_GEOMETRY_MAX:		//リスナーを中心として180度の角度
			break;
		}
		break;

	case DSSPEAKER_SURROUND:	//サラウンド・スピーカー
		break;
	case DSSPEAKER_7POINT1:		//サブウーファ付きの7サラウンド・スピーカー
		break;
	}
	return true;
}





//6:プライマリ・バッファの作成
bool	Sound::CreateSoundBuffer()
{
	//DSBUFFERDESC構造体を設定
	ZeroMemory(&dsBufDesc, sizeof(DSBUFFERDESC));
	dsBufDesc.dwSize = sizeof(DSBUFFERDESC);

	//プライマリ・バッファを指定
	dsBufDesc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_PRIMARYBUFFER;
	dsBufDesc.dwBufferBytes = 0;
	dsBufDesc.lpwfxFormat = NULL;


	//バッファの作成
	if (FAILED(pDirectSound->CreateSoundBuffer(
		&dsBufDesc, &pDirectSoundBuf, NULL
	)))
	{
		MessageBox(NULL, TEXT("バッファの作成に失敗しました"), TEXT("CreateSoundBuffer"), MB_OK);
		return false;
	}


	//プライマリ・バッファのWaveフォーマットを設定
	//優先協調レベル以上の協調レベルが設定されている必要がある
	PCMWAVEFORMAT	pcmWF;
	ZeroMemory(&pcmWF, sizeof(PCMWAVEFORMAT));
	pcmWF.wf.wFormatTag = WAVE_FORMAT_PCM;		//Waveのフォーマット
	pcmWF.wf.nChannels = 2;						//2チャンネル(ステレオ)
	pcmWF.wf.nSamplesPerSec = 22050;			//サンプリング・レート	22kHz
	pcmWF.wf.nBlockAlign = 4;
	pcmWF.wf.nAvgBytesPerSec = pcmWF.wf.nSamplesPerSec * pcmWF.wf.nBlockAlign;	//固定
	pcmWF.wBitsPerSample = 16;					//16ビット

	pDirectSoundBuf->SetFormat((LPCWAVEFORMATEX)&pcmWF);	//バッファにフォーマットをセット
	
	return true;
}





//7:セカンダリ・バッファの作成
bool	Sound::CreateSecondaryBuffer()
{
	WAVEFORMATEX	pcmWF;
	DSBUFFERDESC	dsBufDesc;

	//Waveフォーマットの初期化
	ZeroMemory(&pcmWF, sizeof(WAVEFORMATEX));
	pcmWF.wFormatTag = WAVE_FORMAT_PCM;			//Waveフォーマット
	pcmWF.nChannels = 2;						//2チャンネル(ステレオ)
	pcmWF.nSamplesPerSec = 22050;				//サンプリング・レート(22kHz)
	pcmWF.nBlockAlign = 4;						//ブロック・アライメント
	pcmWF.nAvgBytesPerSec = pcmWF.nSamplesPerSec * pcmWF.nBlockAlign;	//1秒間のデータ転送サイズ
	pcmWF.wBitsPerSample = 16;					//16ビット


	//DSBUFFERDESC構造体のセット
	ZeroMemory(&dsBufDesc, sizeof(DSBUFFERDESC));
	dsBufDesc.dwSize = sizeof(DSBUFFERDESC);

	//サウンド・バッファを作成
	dsBufDesc.dwFlags = DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_GLOBALFOCUS | DSBCAPS_LOCDEFER;
	
	//上で設定したWaveフォーマットを持つ3秒のバッファを作成
	dsBufDesc.dwBufferBytes = 3 * pcmWF.nAvgBytesPerSec;		//3秒の転送バイト数
	dsBufDesc.lpwfxFormat = &pcmWF;

	//バッファを作成
	LPDIRECTSOUNDBUFFER		pDSB;
	if (FAILED(pDirectSound->CreateSoundBuffer(&dsBufDesc, &pDSB, NULL)))
	{
		MessageBox(NULL, TEXT("セカンダリバッファの作成に失敗しました"), TEXT("CreateSecondaryBuf"), MB_OK);
		return false;
	}

	//IDirectSoundBuffer8インターフェイスを取り出す
	if (FAILED(pDSB->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)pDirectSound)))
	{
		MessageBox(NULL, TEXT("サウンドバッファの取得に失敗しました"), TEXT("QueryInterface"), MB_OK);
		return false;
	}
	pDSB->Release();

	return true;
}



//8:セカンダリ・バッファへの書き込み
bool	Sound::WriteSecondaryBuffer()
{
	DWORD	dwOffset = 0;		//ロックを開始する、バッファの先頭からのバイト数を設定
	DWORD	dwBlockBytes = 0;//ロックするブロックのバイト数を設定

	LPVOID	lpvPtr1 = {};		//最初のブロックのポインタ
	DWORD	dwBytes1 = {};		//最初のブロックのサイズ
	LPVOID	lpvPtr2 = {};		//2番目のブロックのポインタ
	DWORD	dwBytes2 = {};		//2番目のブロックのサイズ
	HRESULT hr = S_OK;

	hr = pDirectSoundBuf->Lock(dwOffset, dwBlockBytes,
		&lpvPtr1, &dwBytes1, &lpvPtr2, &dwBytes2, 0);

	//DSERR_BUFFERLOSTが返された場合、Restore()を使用しバッファを復元
	if (hr == DSERR_BUFFERLOST)
	{
		pDirectSoundBuf->Restore();
		//hr = pDirectSoundBuf->Lock(dwOffset,dwSoundBytes,
		//	&lpvPtr1, &dwAudio1, &lpvPtr2, &dwAudio2, 0);
	}
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("セカンダリバッファのロックに失敗しました"), TEXT("Lock"), MB_OK);
		return false;
	}
	

	//バッファに書き込む


	//書き込みが終了したら、Unlockする
	hr = pDirectSoundBuf->Unlock(lpvPtr1, dwBytes1, lpvPtr2, dwBytes2);

	return true;
}




//9:セカンダリバッファのフォーマットの設定
bool	Sound::SecondarySetFormat(LPTSTR fileName)
{
	//WAVEファイルを開く
	CWaveFile	waveFile;
	waveFileName = fileName;
	if (FAILED(waveFile.Open(waveFileName, NULL, WAVEFILE_READ)))
	{
		MessageBox(NULL, TEXT("Waveファイルのオープンに失敗"), TEXT("Open"), MB_OK);
		return false;
	}

	//セカンダリ・バッファの作成
	DSBUFFERDESC	dsBufDesc;
	ZeroMemory(&dsBufDesc, sizeof(DSBUFFERDESC));
	dsBufDesc.dwSize = sizeof(DSBUFFERDESC);
	dsBufDesc.dwFlags = DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_GLOBALFOCUS | DSBCAPS_LOCDEFER |
		DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPAN | DSBCAPS_CTRLFREQUENCY;
	dsBufDesc.dwBufferBytes = waveFile.GetSize();
	dsBufDesc.lpwfxFormat = waveFile.GetFormat();
	
	//バッファの作成
	LPDIRECTSOUNDBUFFER		pDSBuf;
	if (FAILED(pDirectSound->CreateSoundBuffer(&dsBufDesc, &pDSBuf, NULL)))
	{
		MessageBox(NULL, TEXT("サウンドバッファの作成に失敗"), TEXT("CreateSoundBuf"), MB_OK);
		return false;
	}
	
	//SoundBufferのインターフェイスの取得
	HRESULT hr;
	hr = pDSBuf->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)&pDirectSoundBuf);
	SAFE_RELEASE(pDSBuf);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("SoundBufのインターフェイスの取得に失敗"), TEXT("QueryInterface"), MB_OK);
		return false;
	}
	
	//セカンダリ・バッファにWaveデータを書き込む
	LPVOID	lpvPtr1 = NULL;
	DWORD	dwByte1 = 0;
	LPVOID	lpvPtr2 = NULL;
	DWORD	dwByte2 = 0;

	hr = pDirectSoundBuf->Lock(0, waveFile.GetSize(), &lpvPtr1, &dwByte1, &lpvPtr2, &dwByte2, 0);
	
	//DSERR_BUFFERLOSTが返された場合、Restore()でバッファを復元
	if (hr == DSERR_BUFFERLOST)
	{
		pDirectSoundBuf->Restore();
		hr = pDirectSoundBuf->Lock(0, waveFile.GetSize(), &lpvPtr1, &dwByte1, &lpvPtr2, &dwByte2, 0);
	}
	if (SUCCEEDED(hr))
	{
		//バッファに書き込む
		DWORD	rsize;
		waveFile.Read((LPBYTE)lpvPtr1, dwByte1, &rsize);
		if (dwByte2 != 0) { waveFile.Read((LPBYTE)lpvPtr2, dwByte2, &rsize); }

		//書き込み終了後、Unlockする
		hr = pDirectSoundBuf->Unlock(lpvPtr1, dwByte1, lpvPtr2, dwByte2);
	}
	return true;
}



//10:サウンドメモリを共有するセカンダリバッファ
bool	Sound::DuplicateSoundBuf()
{
	LPDIRECTSOUNDBUFFER	pDSB = {};
	pDirectSound->DuplicateSoundBuffer(pDirectSoundBuf, &pNewSoundBuf);
	pDSB->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)&pNewSoundBuf);
	pDSB->Release();
	return true;
}



//11:サウンドの再生
bool	Sound::Play(bool loop)
{
	HRESULT hr;
	int flags = 0;
	if (loop) { flags = flags | DSBPLAY_LOOPING; }
	pDirectSoundBuf->SetCurrentPosition(0);	//先頭から再生
	
	hr = pDirectSoundBuf->Play(0, 0, flags);
	
	if(hr == DSERR_BUFFERLOST)
	{
		pDirectSoundBuf->Restore();		//失われたサウンドメモリを復元
		//サウンドバッファを設定しなおす
	}
	return true;
}

bool	Sound::Stop()
{
	pDirectSoundBuf->Stop();
	return true;
}



//ボリュームの設定
bool	Sound::SetVolume(LONG volume)
{
	pDirectSoundBuf->SetVolume(volume);
	return true;
}

//パンの設定
bool	Sound::SetPan(LONG pan)
{
	//パンの値を1/100dB単位で設定
	//右チャンネルが無音は[-10000]、左チャンネルが無音は[10000]
	pDirectSoundBuf->SetPan(pan);
	return true;
}


//周波数の設定
bool	Sound::SetFrequency(DWORD frequency)
{
	//再生する周波数をHz単位で設定
	//min(100)からmax(100000)までの値
	pDirectSoundBuf->SetFrequency(frequency);
	return true;
}

//オブジェクトの削除
void	Sound::BufRelease()
{
	if (pDirectSound != NULL) { pDirectSoundBuf->Release(); pDirectSound = NULL; }
}

void	Sound::InterfaceRelease()
{
	if (pDirectSound != NULL) { pDirectSoundBuf->Release(); pDirectSound = NULL; }
}





//------------------------------------------------------------------
//サウンドデバイスのシングルトンクラス
//------------------------------------------------------------------
SoundDevice::SoundDevice() : pDirectSound(NULL), pDSoundGuid(NULL)
{

}

//生成処理
SoundDevice*	SoundDevice::Instance()
{
	if (instance == NULL)
	{
		instance = new SoundDevice;
	}
	return instance;
}


//---------------------------------------------------------
//メンバ処理
//---------------------------------------------------------
//サウンド・デバイスの取得
bool	SoundDevice::DSoundEnumCallBack()
{

	//DirectSoundEnumerate((LPDSENUMCALLBACK)DSEnumProc, &hCombo);
	return true;
}
BOOL CALLBACK SoundDevice::DSEnumProc(LPGUID lpGUID, LPCTSTR lpszDesc, LPCTSTR lpszDrvName, LPVOID lpContext)
{
	HWND hCombo = (HWND)lpContext;
	LPGUID lpTemp = NULL;

	if (lpGUID != NULL)
	{
		if ((lpTemp = (LPGUID)malloc(sizeof(GUID))) == NULL)
		{
			return true;
		}
		memcpy(lpTemp, lpGUID, sizeof(GUID));
	}

	//ComboBox_AddString(hCombo, lpszDesc);
	//ComboBox_SetItemData(hCombo, ComboBox_FindString(hCombo, 0, lpszDesc), lpTemp);
	free(lpTemp);
	lpTemp = NULL;

	return true;
}


//2:DirectSoundオブジェクトの作成
bool	SoundDevice::DSoundCreate()
{
	if (FAILED(DirectSoundCreate8(
		NULL,		//デフォルトではNULL、GUIDを取得するならpDSoundGuid
		&pDirectSound,
		NULL
	)))
	{
		MessageBox(NULL, TEXT("DirectSoundオブジェクトの生成に失敗しました"), TEXT("DSoundCreate"), MB_OK);
		return false;
	}
	return true;
}



//3:協調レベルの設定
bool	SoundDevice::SetCooperativeLevel(HWND hWnd)
{
	if (FAILED(pDirectSound->SetCooperativeLevel(
		hWnd, DSSCL_PRIORITY
	)))
	{
		MessageBox(NULL, TEXT("協調レベルの設定に失敗しました"), TEXT("SetCooperativeLevel"), MB_OK);
		return false;
	}
	return true;
}




//4:デバイスの性能の調査
bool	SoundDevice::GetCaps()
{
	dsCaps.dwSize = sizeof(DSCAPS);	//必ず初期化

	if (FAILED(pDirectSound->GetCaps(&dsCaps)))
	{
		MessageBox(NULL, TEXT("デバイスの性能の取得に失敗しました"), TEXT("GetCaps"), MB_OK);
		return false;
	}
	return true;
}



//5:スピーカーの調査
bool	SoundDevice::GetSpeakerConfig()
{
	if (FAILED(pDirectSound->GetSpeakerConfig(&dwSpeakerConfig)))
	{
		MessageBox(NULL, TEXT("スピーカーの情報の取得に失敗しました"), TEXT("GetSpeakerConfig"), MB_OK);
		return false;
	}

	switch (DSSPEAKER_CONFIG(dwSpeakerConfig))
	{
	case DSSPEAKER_5POINT1:		//サブウーファ付きの5サラウンド・スピーカー
		break;
	case DSSPEAKER_DIRECTOUT:	//スピーカー用の構成は行われない
		break;
	case DSSPEAKER_HEADPHONE:	//ヘッドホン
		break;
	case DSSPEAKER_MONO:		//モノラル・スピーカー
		break;
	case DSSPEAKER_QUAD:		//4チャンネル・ステレオ・スピーカー
		break;
	case DSSPEAKER_STEREO:		//ステレオ・スピーカー

								//2つのスピーカーの配置
		switch (DSSPEAKER_GEOMETRY(dwSpeakerConfig))
		{
		case DSSPEAKER_GEOMETRY_WIDE:		//リスナーを中心として20度の角度
			break;
		case DSSPEAKER_GEOMETRY_NARROW:		//リスナーを中心として10度の角度
			break;
		case DSSPEAKER_GEOMETRY_MIN:		//リスナーを中心として5度の角度
			break;
		case DSSPEAKER_GEOMETRY_MAX:		//リスナーを中心として180度の角度
			break;
		}
		break;

	case DSSPEAKER_SURROUND:	//サラウンド・スピーカー
		break;
	case DSSPEAKER_7POINT1:		//サブウーファ付きの7サラウンド・スピーカー
		break;
	}
	return true;
}





////6:プライマリ・バッファの作成
//bool	SoundDevice::CreateSoundBuffer()
//{
//	//DSBUFFERDESC構造体を設定
//	ZeroMemory(&dsBufDesc, sizeof(DSBUFFERDESC));
//	dsBufDesc.dwSize = sizeof(DSBUFFERDESC);
//
//	//プライマリ・バッファを指定
//	dsBufDesc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_PRIMARYBUFFER;
//	dsBufDesc.dwBufferBytes = 0;
//	dsBufDesc.lpwfxFormat = NULL;
//
//
//	//バッファの作成
//	if (FAILED(pDirectSound->CreateSoundBuffer(
//		&dsBufDesc, &pDirectSoundBuf, NULL
//	)))
//	{
//		MessageBox(NULL, TEXT("バッファの作成に失敗しました"), TEXT("CreateSoundBuffer"), MB_OK);
//		return false;
//	}
//
//
//	//プライマリ・バッファのWaveフォーマットを設定
//	//優先協調レベル以上の協調レベルが設定されている必要がある
//	PCMWAVEFORMAT	pcmWF;
//	ZeroMemory(&pcmWF, sizeof(PCMWAVEFORMAT));
//	pcmWF.wf.wFormatTag = WAVE_FORMAT_PCM;		//Waveのフォーマット
//	pcmWF.wf.nChannels = 2;						//2チャンネル(ステレオ)
//	pcmWF.wf.nSamplesPerSec = 22050;			//サンプリング・レート	22kHz
//	pcmWF.wf.nBlockAlign = 4;
//	pcmWF.wf.nAvgBytesPerSec = pcmWF.wf.nSamplesPerSec * pcmWF.wf.nBlockAlign;	//固定
//	pcmWF.wBitsPerSample = 16;					//16ビット
//
//	pDirectSoundBuf->SetFormat((LPCWAVEFORMATEX)&pcmWF);	//バッファにフォーマットをセット
//
//	return true;
//}