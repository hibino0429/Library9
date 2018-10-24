#pragma once
#pragma comment(lib,"dsound.lib")


#include <dsound.h>
#include <dmusicc.h>
#include <objbase.h>
#include "WaveFile.h"

//サウンドクラス
class Sound
{
public:
	Sound();
	~Sound();
public:

	//1:サウンド・デバイスの列挙
	bool	DSoundEnumCallBack();
	BOOL CALLBACK DSEnumProc(LPGUID lpGUID, LPCTSTR lpszDesc, LPCTSTR lpszDrvName, LPVOID lpContext);

	//2:DirectSoundオブジェクトの作成
	bool	DSoundCreate();

	//3:協調レベルの設定
	bool	SetCooperativeLevel(HWND hWnd);

	//4:デバイスの性能の調査
	bool	GetCaps();

	//5:スピーカーの調査
	bool	GetSpeakerConfig();

	//6:プライマリ・バッファの作成
	bool	CreateSoundBuffer();

	//7:セカンダリ・バッファの作成
	bool	CreateSecondaryBuffer();

	//8:セカンダリ・バッファへの書き込み
	bool	WriteSecondaryBuffer();

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

	//13:オブジェクトの削除
	void	BufRelease();
	void	InterfaceRelease();

private:

	LPGUID			pDSoundGuid;	//取得したGUID(デフォルトはNULL)
	LPDIRECTSOUND8	pDirectSound;	//サウンドを扱うインターフェイス

	DSCAPS			dsCaps;				//デバイスの性能情報
	DWORD			dwSpeakerConfig;	//スピーカーの情報

	LPDIRECTSOUNDBUFFER		pDirectSoundBuf;	//プライマリバッファのインターフェイス
	DSBUFFERDESC			dsBufDesc;			//サウンドバッファ

	LPDIRECTSOUNDBUFFER		pNewSoundBuf;

public:
	LPTSTR					waveFileName;
};



//---------------------------------------------------------
//サウンドデバイスのシングルトンクラス
//---------------------------------------------------------
class SoundDevice
{
public:
	static SoundDevice* Instance();

protected:
	SoundDevice();

private:
	static SoundDevice* instance;

public:
	//メンバ変数
	LPGUID				pDSoundGuid;		//サウンドGUID
	LPDIRECTSOUND8		pDirectSound;		//サウンドデバイス

	DSCAPS				dsCaps;				//デバイスの性能情報
	DWORD				dwSpeakerConfig;	//スピーカーの情報

	LPDIRECTSOUNDBUFFER		pDirectSoundBuf;	//プライマリバッファのインターフェイス
	LPDIRECTSOUNDBUFFER		pNewSoundBuf;

	DSBUFFERDESC			dsBufDesc;			//サウンドバッファ

public:
	//メンバ関数
	
	//1:サウンド・デバイスの列挙
	bool	DSoundEnumCallBack();
	BOOL CALLBACK DSEnumProc(LPGUID lpGUID, LPCTSTR lpszDesc, LPCTSTR lpszDrvName, LPVOID lpContext);

	//2:DirectSoundオブジェクトの作成
	bool	DSoundCreate();

	//3:協調レベルの設定
	bool	SetCooperativeLevel(HWND hWnd);

	//4:デバイスの性能の調査
	bool	GetCaps();

	//5:スピーカーの調査
	bool	GetSpeakerConfig();

	//6:プライマリ・バッファの作成
	//bool	CreateSoundBuffer();
};