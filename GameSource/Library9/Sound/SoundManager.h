#pragma once
#include "DSound.h"

#include "SoundListener.h"
#include "SoundSource.h"

//----------------------------------------------------
//サウンド管理クラス
//----------------------------------------------------
class SoundManager
{
public:
	//処理の手順

	//1:サウンド・デバイスの列挙

	//2:IDirectSound8インターフェイスの取得

	//3:協調レベルの設定

	//4:デバイスの性能の調査

	//5:スピーカの調査

	//6:プライマリバッファの作成

	//7:セカンダリバッファの作成

	//8:セカンダリバッファへの書き込み

	//9:セカンダリバッファの再生


	bool	Create(HWND hWnd);	//サウンドの生成

	void	LoadSound(LPTSTR fileName);

	void	Play(bool loop);
	void	Stop();

	void	SetVolume(LONG volume);
	void	SetPan(LONG pan);
	void	SetFrequency(DWORD frequency);

private:
	Sound	sound;

};



//名前空間にのみ格納する
namespace SE2
{
	bool	Create(HWND hWnd);	//サウンドの生成

	void	LoadSound(LPTSTR fileName);

	void	Play(bool loop);
	void	Stop();

	void	SetVolume(LONG volume);
	void	SetPan(LONG pan);
	void	SetFrequency(DWORD frequency);

	static Sound	se;
}



//------------------------------------------------------
//サウンドの管理クラス
//------------------------------------------------------
//セカンダリバッファを使用して、サウンドの再生などの処理をする

class Sounds
{
public:

	Sounds();
	~Sounds();

	//9:バッファのフォーマットの設定
	bool	SecondarySetFormat(LPTSTR fileName);

	//10:サウンドメモリを共有するセカンダリバッファ
	bool	DuplicateSoundBuf();

	//11:セカンダリバッファの再生・停止
	bool	Play(bool loop);
	bool	Stop();

	//12:ボリューム・パン・再生周波数の設定
	bool	SetVolume(LONG);
	bool	SetPan(LONG);
	bool	SetFrequency(DWORD);

	
	//サウンドファイルの読み込み
	bool	LoadSound(LPTSTR fileName);


	//プライマリバッファの作成
	bool	CreateSoundBuffer();

public:
	LPTSTR		waveFileName;

	LPDIRECTSOUNDBUFFER		pDirectSoundBuf;	//プライマリバッファのインターフェイス
	LPDIRECTSOUNDBUFFER		pNewSoundBuf;

	DSBUFFERDESC			dsBufDesc;			//サウンドバッファ
};



//サウンドデバイスの処理
namespace SE
{
	//サウンドデバイスの生成
	bool	Create(HWND hWnd);

}



//-----------------------------------------------------------------
//ストリーム再生
//XXX:現在改良中
//-----------------------------------------------------------------
class StreamSound
{
public:
	bool	CreateNotify(LPTSTR fileName);	//通知イベントを発行

	bool	CreateThreadNotify();				//スレッドの作成

	void	Block_Copy(UINT i);			//サウンドバッファへコピー


	StreamSound();
	~StreamSound();

	static DWORD WINAPI MyThreadFunc(LPVOID param);

public:
	LPDIRECTSOUNDBUFFER8	pDirectSoundData;	//サウンドバッファ
	LPDIRECTSOUNDNOTIFY8	pDirectSoundNotify;	//通知イベントデバイス

	HANDLE		hEvent[3];		//イベントハンドル
	HANDLE		hThreadHandle;	//スレッド・ハンドル
	DWORD		dwThreadID;		//スレッドID
	DWORD		dwBlockSize;	//サウンドバッファのサイズ
	DWORD		dwPlayAdd;		//現在の再生位置
	
	CWaveFile	waveFile;		//WAVEファイル
};




//-----------------------------------------------------
//3Dサウンド
//-----------------------------------------------------
class Sound3D
{
public:

	Sound3D();
	~Sound3D();

	bool	CreatePrimary(LPTSTR fileName);		//プライマリバッファの作成
	

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


	//仮-----------------
	//プライマリバッファ
	bool	PrimaryBufCreate();
	bool	SecondaryBufCreate(LPTSTR fileName);

public:

public:
	LPDIRECTSOUND3DBUFFER8		pSource;			//音源(ソース)
	LPDIRECTSOUND3DLISTENER8	pListener;			//リスナー

	LPDIRECTSOUNDBUFFER8		pDSBuf8;
	LPDIRECTSOUNDBUFFER			pPrimaryBuf;		//サウンドバッファ(プライマリ)

	DSBUFFERDESC				dsBufDesc;


};


//3Dサウンド
namespace Audio
{
	bool	CreateSoundDevice(HWND hWnd);

	bool	CreateAudio(LPTSTR fileName,LPDIRECTSOUNDBUFFER* pBuf);

	bool	CreateSoundBuf(DSBUFFERDESC* desBufDesc,LPDIRECTSOUNDBUFFER* pBuf);

	bool	QueryInterface();

	LPDIRECTSOUND8*	GetDirectSound();
}