#include "SoundManager.h"

SoundDevice* sd = SoundDevice::Instance();

//サウンドデバイスの生成
bool	SoundManager::Create(HWND hWnd)
{
	//1:サウンドデバイスの列挙

	//2:IDirectSound8インターフェイスの取得
	sound.DSoundCreate();

	//3:協調レベルの設定
	sound.SetCooperativeLevel(hWnd);

	//4:デバイスの性能の調査
	sound.GetCaps();

	//5:スピーカの調査
	sound.GetSpeakerConfig();

	//6:プライマリバッファの生成
	sound.CreateSoundBuffer();

	return true;
}


//セカンダリバッファの作成
void	SoundManager::LoadSound(LPTSTR fileName)
{
	if (fileName == sound.waveFileName)
	{
		sound.DuplicateSoundBuf();
	}
	sound.SecondarySetFormat(fileName);
}

//セカンダリバッファの再生
void	SoundManager::Play(bool loop)
{
	sound.Play(loop);
}

//セカンダリバッファの停止
void	SoundManager::Stop()
{
	sound.Stop();
}

//ボリュームの設定
void	SoundManager::SetVolume(LONG valume)
{
	sound.SetVolume(valume);
}

//パンの設定
void	SoundManager::SetPan(LONG pan)
{
	sound.SetPan(pan);
}

//再生周波数の設定
void	SoundManager::SetFrequency(DWORD frequency)
{
	sound.SetFrequency(frequency);
}







namespace SE2
{
	//サウンドデバイスの生成
	bool	Create(HWND hWnd)
	{
		//1:サウンドデバイスの列挙

		//2:IDirectSound8インターフェイスの取得
		se.DSoundCreate();

		//3:協調レベルの設定
		se.SetCooperativeLevel(hWnd);

		//4:デバイスの性能の調査
		se.GetCaps();

		//5:スピーカの調査
		se.GetSpeakerConfig();

		//6:プライマリバッファの生成
		se.CreateSoundBuffer();

		return true;
	}


	//セカンダリバッファの作成
	void	LoadSound(LPTSTR fileName)
	{
		if (fileName == se.waveFileName)
		{
			se.DuplicateSoundBuf();
		}
		se.SecondarySetFormat(fileName);
	}

	//セカンダリバッファの再生
	void	Play(bool loop)
	{
		se.Play(loop);
	}

	//セカンダリバッファの停止
	void	Stop()
	{
		se.Stop();
	}

	//ボリュームの設定
	void	SetVolume(LONG valume)
	{
		se.SetVolume(valume);
	}

	//パンの設定
	void	SetPan(LONG pan)
	{
		se.SetPan(pan);
	}

	//再生周波数の設定
	void	SetFrequency(DWORD frequency)
	{
		se.SetFrequency(frequency);
	}

}







//---------------------------------------------------------------------------------------------
//サウンドデバイスのシングルトンクラスを利用したセカンダリサウンド
//---------------------------------------------------------------------------------------------

//コンストラクタ
Sounds::Sounds() : pDirectSoundBuf(NULL), pNewSoundBuf(NULL)
{

}

//デストラクタ
Sounds::~Sounds()
{
	if (pDirectSoundBuf != NULL) { pDirectSoundBuf->Release(); pDirectSoundBuf = NULL; }
	if (pNewSoundBuf != NULL) { pNewSoundBuf->Release(); pNewSoundBuf = NULL; }
}

//9:セカンダリバッファのフォーマットの設定
bool	Sounds::SecondarySetFormat(LPTSTR fileName)
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
	if (FAILED(sd->pDirectSound->CreateSoundBuffer(&dsBufDesc, &pDSBuf, NULL)))
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
bool	Sounds::DuplicateSoundBuf()
{
	LPDIRECTSOUNDBUFFER	pDSB = NULL;
	sd->pDirectSound->DuplicateSoundBuffer(pDirectSoundBuf, &pNewSoundBuf);
	pDSB->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)&pNewSoundBuf);
	pDSB->Release();
	return true;
}



//11:サウンドの再生
bool	Sounds::Play(bool loop)
{
	HRESULT hr;
	int flags = 0;
	if (loop) { flags = flags | DSBPLAY_LOOPING; }
	pDirectSoundBuf->SetCurrentPosition(0);	//先頭から再生

	hr = pDirectSoundBuf->Play(0, 0, flags);

	if (hr == DSERR_BUFFERLOST)
	{
		pDirectSoundBuf->Restore();		//失われたサウンドメモリを復元
										//サウンドバッファを設定しなおす
	}
	return true;
}

bool	Sounds::Stop()
{
	pDirectSoundBuf->Stop();
	return true;
}



//ボリュームの設定
bool	Sounds::SetVolume(LONG volume)
{
	pDirectSoundBuf->SetVolume(volume);
	return true;
}

//パンの設定
bool	Sounds::SetPan(LONG pan)
{
	//パンの値を1/100dB単位で設定
	//右チャンネルが無音は[-10000]、左チャンネルが無音は[10000]
	pDirectSoundBuf->SetPan(pan);
	return true;
}


//周波数の設定
bool	Sounds::SetFrequency(DWORD frequency)
{
	//再生する周波数をHz単位で設定
	//min(100)からmax(100000)までの値
	pDirectSoundBuf->SetFrequency(frequency);
	return true;
}




bool	Sounds::LoadSound(LPTSTR fileName)
{
	CreateSoundBuffer();

	if (fileName == waveFileName)
	{
		//DuplicateSoundBuf();
		return false;
	}
	SecondarySetFormat(fileName);

	return true;
}


//6:プライマリ・バッファの作成
bool	Sounds::CreateSoundBuffer()
{
	//DSBUFFERDESC構造体を設定
	ZeroMemory(&dsBufDesc, sizeof(DSBUFFERDESC));
	dsBufDesc.dwSize = sizeof(DSBUFFERDESC);

	//プライマリ・バッファを指定
	dsBufDesc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_PRIMARYBUFFER;
	dsBufDesc.dwBufferBytes = 0;
	dsBufDesc.lpwfxFormat = NULL;


	//バッファの作成
	if (FAILED(sd->pDirectSound->CreateSoundBuffer(
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






namespace SE
{
	//サウンドデバイスの生成
	bool	Create(HWND hWnd)
	{
		//1:サウンドデバイスの列挙

		//2:IDirectSound8インターフェイスの取得
		sd->DSoundCreate();

		//3:協調レベルの設定
		sd->SetCooperativeLevel(hWnd);

		//4:デバイスの性能の調査
		sd->GetCaps();

		//5:スピーカの調査
		sd->GetSpeakerConfig();

		//6:プライマリバッファの生成
		//sd->CreateSoundBuffer();

		return true;
	}

}



////////////////////////////////////////////////////////////////////////
//コンストラクタ
StreamSound::StreamSound() : pDirectSoundData(NULL),pDirectSoundNotify(NULL),
hThreadHandle(NULL),dwThreadID(0),dwBlockSize(0),dwPlayAdd(0)
{
	for (int i = 0; i < 3; ++i) { hEvent[i] = NULL; }
}

//デストラクタ
StreamSound::~StreamSound()
{
	if (pDirectSoundData != NULL) { pDirectSoundData->Release(); pDirectSoundData = NULL; }
	if (pDirectSoundNotify != NULL) { pDirectSoundNotify->Release(); pDirectSoundNotify = NULL; }
	if (hThreadHandle != NULL) { hThreadHandle = NULL; }
	dwThreadID = 0;
	dwBlockSize = 0;
	dwPlayAdd = 0;
	for (int i = 0; i < 3; ++i) { hEvent[i] = NULL; }
}


//ストリーム再生
bool	StreamSound::CreateNotify(LPTSTR fileName)
{
	CWaveFile	waveFile;
	waveFile.Open(fileName, NULL, WAVEFILE_READ);

	//1:Notifyインターフェイスの取得
	if (FAILED(pDirectSoundNotify->QueryInterface(
		IID_IDirectSoundNotify8,
		(LPVOID*)&pDirectSoundNotify)))
	{
		MessageBox(NULL, TEXT("Notify8の作成に失敗しました"), TEXT("pDirectNotifyQueryInterface"), MB_OK);
		return false;
	}

	//2:通知イベントのオブジェクトの作成
	HANDLE	hEvent[3];
	//引数1:デフォルト。セキュリティ属性
	//引数2:自動リセット(FALSE)
	//引数3:初期状態 - 非シグナル(FALSE)
	//引数4:名前
	hEvent[0] = CreateEvent(NULL, FALSE, FALSE, NULL);
	hEvent[1] = CreateEvent(NULL, FALSE, FALSE, NULL);
	hEvent[2] = CreateEvent(NULL, FALSE, FALSE, NULL);

	
	//3:通知位置の設定
	DSBPOSITIONNOTIFY	posNotify[3];

	posNotify[0].dwOffset = 0;		//0秒目
	posNotify[0].hEventNotify = hEvent[0];
	posNotify[1].dwOffset = 1;		//1秒目
	posNotify[1].hEventNotify = hEvent[1];
	posNotify[2].dwOffset = DSBPN_OFFSETSTOP;		//再生停止
	posNotify[2].hEventNotify = hEvent[2];

	//停止位置の設定
	//引数1:構造体の数
	//引数2:構造体のポインタ
	if (FAILED(pDirectSoundNotify->SetNotificationPositions(3, posNotify)))
	{
		MessageBox(NULL, TEXT("停止位置の設定に失敗しました"), TEXT("SetNotifyPos"), MB_OK);
		return false;
	}
	return true;
}


//スレッドの作成
bool	StreamSound::CreateThreadNotify()
{
	HANDLE hThreadHandle;		//スレッドのハンドル
	DWORD	dwThreadID;			//スレッドのID
	hThreadHandle = CreateThread(NULL, 0,MyThreadFunc, NULL, 0, &dwThreadID);
	if (hThreadHandle == NULL)
	{
		MessageBox(NULL, TEXT("スレッドの生成に失敗しました"), TEXT("CreateThread"), MB_OK);
		return false;
	}
	return true;
}


//サウンドバッファへコピーする
void	StreamSound::Block_Copy(UINT i)
{
	//一度更新するデータサイズ(サウンドバッファの半分)
	UINT dsize = (UINT)dwBlockSize / 2;

	//バッファをロック
	LPBYTE	blockAdd1, blockAdd2;
	DWORD	blockSize1, blockSize2;

	if (FAILED(pDirectSoundData->Lock(dsize * i, dsize,
		(LPVOID*)&blockAdd1, &blockSize1,
		(LPVOID*)&blockAdd2, &blockSize2, 0)))
	{
		MessageBox(NULL, TEXT("バッファのロックに失敗しました"), TEXT("Block_Copy"), MB_OK);
		return;
	}

	//バッファの前半にデータをコピー
	UINT rsize, asize;
	for (asize = 0; asize < blockSize1; asize += rsize)
	{
		waveFile.Read((BYTE*)blockSize1 - asize, (DWORD)blockAdd1 + asize, (DWORD*)&rsize);
		if (rsize == 0) { break; }
		if (blockSize1 - asize != rsize)
		{
			waveFile.ResetFile();	//ファイルを巻き戻す
		}
	}

	//バッファの後半にデータをコピー
	for (asize = 0; asize < blockSize2; asize += rsize)
	{
		waveFile.Read((BYTE*)blockSize2 - asize, (DWORD)blockAdd2 + asize, (DWORD*)&rsize);
		if (rsize == 0) { break; }
		if (blockSize2 - asize != rsize)
		{
			waveFile.ResetFile();	//ファイルを巻き戻す
		}
	}

	//バッファのアンロック
	pDirectSoundData->Unlock(blockAdd1, blockSize1, blockAdd2, blockSize2);
}


DWORD	WINAPI	StreamSound::MyThreadFunc(LPVOID param)
{
	////バッファの1番目のブロックにデータを書き込む
	//Block_Copy(0);
	//
	//pDirectSoundData->Play(0, 0, DSBPLAY_LOOPING);

	////データを書き込む無限ループに入る
	//while (true)
	//{
	//	//DirectSoundBufferからのイベント通知を待つ
	//	DWORD i = WaitForMultipleObjects(3, StreamSound::hEvent, FALSE, INFINITE);
	//	//イベントがきたら、これから再生されるブロックの次のブロックに書き込む
	//	switch (i)
	//	{
	//	case WAIT_OBJECT_0:
	//		//２番目のブロックに書き込む
	//		Block_Copy(1);
	//		break;
	//	case WAIT_OBJECT_0 + 1:
	//		Block_Copy(0);
	//		break;
	//	case WAIT_OBJECT_0 + 2:
	//	default:
	//		//再生終了時に、スレッドを終了する
	//		ExitThread(TRUE);
	//	}
	//}
	return 0L;
}






//------------------------------------------------------
//3Dサウンド
//------------------------------------------------------

//コンストラクタ
Sound3D::Sound3D() : pPrimaryBuf(NULL)
{

}

//デストラクタ
Sound3D::~Sound3D()
{
	if (pPrimaryBuf != NULL) { pPrimaryBuf->Release(); pPrimaryBuf = NULL; }
}


//プライマリ・バッファの作成
bool	Sound3D::CreatePrimary(LPTSTR fileName)
{
	sd->DSoundCreate();
	CWaveFile	waveFile;
	if (FAILED(waveFile.Open(fileName, NULL, WAVEFILE_READ)))
	{
		MessageBox(NULL, TEXT("Waveファイルのオープンに失敗しました"), TEXT("Open"), MB_OK);
		return false;
	}

	DSBUFFERDESC	dsBufDesc;
	dsBufDesc.dwSize = sizeof(DSBUFFERDESC);
	dsBufDesc.dwFlags = DSBCAPS_CTRL3D | DSBCAPS_PRIMARYBUFFER;
	dsBufDesc.dwBufferBytes = 0;
	dsBufDesc.lpwfxFormat = NULL;


	//サウンドバッファを作成
	if (FAILED(sd->pDirectSound->CreateSoundBuffer(&dsBufDesc, &pPrimaryBuf, NULL)))
	{
		MessageBox(NULL, TEXT("サウンドバッファの作成に失敗しました"), TEXT("CreateSoundBuf"), MB_OK);
		return false;
	}


	//サウンドバッファの作成
	LPDIRECTSOUNDBUFFER		pDSBuf = {};
	//SoundBufferのインターフェイスの取得
	HRESULT hr = S_OK;
	hr = pDSBuf->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)&pPrimaryBuf);
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
bool	Sound3D::CreateSource()
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
void	Sound3D::SetMinDistance(float minDist, DWORD apply)
{
	pSource->SetMinDistance(minDist, apply);
}
//最大距離
void	Sound3D::SetMaxDistance(float maxDist, DWORD apply)
{
	pSource->SetMaxDistance(maxDist, apply);
}

//3Dサウンド処理モードの設定
void	Sound3D::SetMode(DWORD mode, DWORD apply)
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
void	Sound3D::SetPositionSource(float x, float y, float z, DWORD apply)
{
	pSource->SetPosition(x, y, z, apply);
}
void	Sound3D::SetVelocitySource(float vx, float vy, float vz, DWORD apply)
{
	pSource->SetVelocity(vx, vy, vz, apply);
}

//サウンドコーンの設定
void	Sound3D::SetConeAngle(DWORD insideConeAngle, DWORD outsideConeAngle, DWORD apply)
{
	pSource->SetConeAngles(insideConeAngle, outsideConeAngle, apply);
}

//コーンの向きの設定
void	Sound3D::SetConeOrientation(float x, float y, float z, DWORD apply)
{
	pSource->SetConeOrientation(x, y, z, apply);
}

//外部コーンの音量の設定
void	Sound3D::SetConeOutsideVolume(LONG coneOutsideVolume, DWORD apply)
{
	pSource->SetConeOutsideVolume(coneOutsideVolume, apply);
}

//音源から音を鳴らす
void	Sound3D::Play(bool loop)
{
	int flags = 0;
	if (loop) { flags = flags | DSBPLAY_LOOPING; }
	pDSBuf8->Play(0, 0, flags);
}


//仮-------------------------
bool	Sound3D::PrimaryBufCreate()
{
	//DSBUFFERDESC構造体を設定
	ZeroMemory(&dsBufDesc, sizeof(DSBUFFERDESC));
	dsBufDesc.dwSize = sizeof(DSBUFFERDESC);

	//バッファの中身の設定
	dsBufDesc.dwSize = sizeof(DSBUFFERDESC);
	dsBufDesc.dwFlags = DSBCAPS_CTRL3D | DSBCAPS_PRIMARYBUFFER;
	dsBufDesc.dwBufferBytes = 0;
	dsBufDesc.lpwfxFormat = NULL;

	//プライマリバッファの作成
	if (FAILED(sd->pDirectSound->CreateSoundBuffer(&dsBufDesc, &pPrimaryBuf, NULL)))
	{
		MessageBox(NULL, TEXT("プライマリバッファの作成に失敗しました"), TEXT("CreateSoundBuffer"), MB_OK);
		return false;
	}
	

	//リスナーの作成
	if (FAILED(pPrimaryBuf->QueryInterface(IID_IDirectSound3DListener8, (LPVOID*)&pListener)))
	{
		MessageBox(NULL, TEXT("リスナーの作成に失敗"), TEXT("Error"), MB_OK);
		return false;
	}
	pListener->SetPosition(0, 0, 0, DS3D_IMMEDIATE);
	pListener->SetVelocity(0, 0, 0, DS3D_IMMEDIATE);
	pListener->SetOrientation(0, 0, 1.0f, 0, 1.0f, 0, DS3D_IMMEDIATE);
	pListener->SetRolloffFactor(1.0f, DS3D_IMMEDIATE);
	pListener->SetDopplerFactor(DS3D_MAXDOPPLERFACTOR, DS3D_IMMEDIATE);

	return true;
}


//仮のSecond
bool	Sound3D::SecondaryBufCreate(LPTSTR fileName)
{
	CWaveFile	waveFile;
	if (FAILED(waveFile.Open(fileName, NULL, WAVEFILE_READ)))
	{
		MessageBox(NULL, TEXT("プライマリバッファの作成に失敗しました"), TEXT("CreateSoundBuffer"), MB_OK);
		return false;
	}

	//セカンダリバッファの作成
	//DSBUFFERDESC dsbdesc;
	//ZeroMemory(&dsbdesc, sizeof(DSBUFFERDESC));
	//dsbdesc.dwSize = sizeof(DSBUFFERDESC);
	//dsbdesc.dwFlags = DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_GLOBALFOCUS | DSBCAPS_LOCDEFER | DSBCAPS_CTRL3D;
	//dsbdesc.dwBufferBytes = waveFile.GetSize();
	//dsbdesc.lpwfxFormat = waveFile.GetFormat();
	//dsbdesc.guid3DAlgorithm = DS3DALG_HRTF_FULL;	// とりあえず高音質のアルゴリズムを要求しておく

	dsBufDesc.dwSize = sizeof(DSBUFFERDESC);
	dsBufDesc.dwFlags = DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_GLOBALFOCUS | DSBCAPS_LOCDEFER |
		DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPAN | DSBCAPS_CTRLFREQUENCY ;
	dsBufDesc.dwBufferBytes = waveFile.GetSize();
	dsBufDesc.lpwfxFormat = waveFile.GetFormat();

	//セカンダリバッファの作成
	LPDIRECTSOUNDBUFFER		pDSBuf;
	if (FAILED(sd->pDirectSound->CreateSoundBuffer(&dsBufDesc, &pDSBuf, NULL)))
	{
		MessageBox(NULL, TEXT("セカンダリバッファの作成に失敗しました"), TEXT("CreateSoundBuf"), MB_OK);
		return false;
	}
	
	if (FAILED(pDSBuf->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)&pDSBuf8)))
	{
		MessageBox(NULL, TEXT("Sound3Dインターフェイスの取得に失敗しました"), TEXT("Query"), MB_OK);
		return false;
	}
	if (pDSBuf != NULL) { pDSBuf->Release(); pDSBuf = NULL; }

	if (FAILED(pDSBuf8->QueryInterface(IID_IDirectSound3DBuffer8, (LPVOID*)&pSource)))
	{
		MessageBox(NULL, TEXT("3Dバッファの作成に失敗しました"), TEXT("Error"), MB_OK);
		return false;
	}
	
	//セカンダリバッファにWaveデータを書き込む
	HRESULT hr;
	LPVOID lpvPtr1; 	// 最初のブロックのポインタ
	DWORD dwBytes1; 	// 最初のブロックのサイズ
	LPVOID lpvPtr2; 	// ２番目のブロックのポインタ
	DWORD dwBytes2; 	// ２番目のブロックのサイズ

	hr = pDSBuf8->Lock(0, waveFile.GetSize(), &lpvPtr1, &dwBytes1, &lpvPtr2, &dwBytes2, 0);

	// DSERR_BUFFERLOSTが返された場合，Restoreメソッドを使ってバッファを復元する
	if (DSERR_BUFFERLOST == hr)
	{
		pDSBuf8->Restore();
		hr = pDSBuf8->Lock(0, waveFile.GetSize(), &lpvPtr1, &dwBytes1, &lpvPtr2, &dwBytes2, 0);
	}
	if (SUCCEEDED(hr))
	{
		// ロック成功

		// ここで，バッファに書き込む
		// バッファにデータをコピーする
		DWORD rsize;
		waveFile.Read((LPBYTE)lpvPtr1, dwBytes1, &rsize);
		if (0 != dwBytes2)
			waveFile.Read((LPBYTE)lpvPtr2, dwBytes2, &rsize);

		// 書き込みが終わったらすぐにUnlockする．
		hr = pDSBuf8->Unlock(lpvPtr1, dwBytes1, lpvPtr2, dwBytes2);
	}

	pSource->SetMinDistance(1.0f, DS3D_IMMEDIATE);
	pSource->SetMaxDistance(10.0f, DS3D_IMMEDIATE);
	pSource->SetPosition(1, 0, 0, DS3D_IMMEDIATE);
	pSource->SetVelocity(2, 2, 2, DS3D_IMMEDIATE);
	pSource->SetConeOutsideVolume(100, DS3D_IMMEDIATE);

	pDSBuf8->Play(0, 0, DSBPLAY_LOOPING);

	return true;
}


/////////////////////////////////////////////////////

//サウンド
namespace Audio
{
	bool	CreateSoundDevice(HWND hWnd)
	{
		//1:IDirectSound8インターフェイスの取得
		if (!sd->DSoundCreate())
		{
			return false;
		}

		//2:協調レベルの設定
		sd->SetCooperativeLevel(hWnd);

		//3:デバイスの性能の調査
		sd->GetCaps();

		//4:スピーカの調査
		sd->GetSpeakerConfig();
		return true;
	}

	//サウンドの作成
	bool	CreateAudio(LPTSTR fileName,LPDIRECTSOUNDBUFFER* pBuf)
	{
		CWaveFile	waveFile;
		if (FAILED(waveFile.Open(fileName, NULL, WAVEFILE_READ)))
		{
			MessageBox(NULL, TEXT("Waveファイルのオープンに失敗しました"), TEXT("Open"), MB_OK);
			return false;
		}

		DSBUFFERDESC	dsBufDesc;
		dsBufDesc.dwSize = sizeof(DSBUFFERDESC);
		dsBufDesc.dwFlags = DSBCAPS_CTRL3D | DSBCAPS_PRIMARYBUFFER;
		dsBufDesc.dwBufferBytes = 0;
		dsBufDesc.lpwfxFormat = NULL;


		//サウンドバッファを作成
		if (FAILED(sd->pDirectSound->CreateSoundBuffer(&dsBufDesc, pBuf, NULL)))
		{
			MessageBox(NULL, TEXT("サウンドバッファの作成に失敗しました"), TEXT("CreateSoundBuf"), MB_OK);
			return false;
		}


		//サウンドバッファの作成
		LPDIRECTSOUNDBUFFER		pDSBuf = {};
		//SoundBufferのインターフェイスの取得
		HRESULT hr = S_OK;
		hr = pDSBuf->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)&pBuf);
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

		hr = (*pBuf)->Lock(0, waveFile.GetSize(), &lpvPtr1, &dwByte1, &lpvPtr2, &dwByte2, 0);

		//DSERR_BUFFERLOSTが返された場合、Restore()でバッファを復元
		if (hr == DSERR_BUFFERLOST)
		{
			(*pBuf)->Restore();
			hr = (*pBuf)->Lock(0, waveFile.GetSize(), &lpvPtr1, &dwByte1, &lpvPtr2, &dwByte2, 0);
		}
		if (SUCCEEDED(hr))
		{
			//バッファに書き込む
			DWORD	rsize;
			waveFile.Read((LPBYTE)lpvPtr1, dwByte1, &rsize);
			if (dwByte2 != 0) { waveFile.Read((LPBYTE)lpvPtr2, dwByte2, &rsize); }

			//書き込み終了後、Unlockする
			hr = (*pBuf)->Unlock(lpvPtr1, dwByte1, lpvPtr2, dwByte2);
		}

		return true;
	}


	//サウンドバッファの生成
	bool	CreateSoundBuf(DSBUFFERDESC* dsBufDesc, LPDIRECTSOUNDBUFFER* pBuf)
	{
		DSBUFFERDESC	dsBufDesc2;
		dsBufDesc2.dwSize = sizeof(DSBUFFERDESC);
		dsBufDesc2.dwFlags = DSBCAPS_CTRL3D | DSBCAPS_PRIMARYBUFFER;
		dsBufDesc2.dwBufferBytes = 0;
		dsBufDesc2.lpwfxFormat = NULL;

		//サウンドバッファを作成
		if (FAILED(sd->pDirectSound->CreateSoundBuffer(dsBufDesc,pBuf, NULL)))
		{
			MessageBox(NULL, TEXT("サウンドバッファの作成に失敗しました"), TEXT("CreateSoundBuf"), MB_OK);
			return false;
		}
		MessageBox(NULL, TEXT("デバイスの確保には成功しました"), TEXT("サウンドデバイス"), MB_OK);
		return true;
	}

	//サウンドバッファのインターフェイスの取得
	bool	QueryInterface()
	{
		LPDIRECTSOUNDBUFFER		pDSBuf = {};
		if (FAILED(pDSBuf->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)sd->pDirectSound)))
		{
			MessageBox(NULL, TEXT("サウンドバッファのインターフェイスの取得に失敗しました"), TEXT("QueryInterface"), MB_OK);
			return false;
		}
		SAFE_RELEASE(pDSBuf);
		return true;
	}

	LPDIRECTSOUND8*	GetDirectSound()
	{
		return &sd->pDirectSound;
	}

}