#pragma once
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

#include <dinput.h>
#include "../DGD.h"


//入力クラス
class Input
{
public:
	Input();
	~Input();

	//DirectInputの初期化
	HRESULT		InitDirectInput(HWND, HINSTANCE);

	//DirectInput関係の解放処理
	void		ClearDirectInput();

	//マウスの設定・取得
	HRESULT		SetMouse(HWND);
	HRESULT		GetMouseState(HWND, int* result);

	//ジョイスティックの設定・取得
	//HRESULT		SetJoystick(HWND);
	HRESULT		GetJoystickState(HWND, int* result);

	//キーボードの状態を取得
	HRESULT		SetKeyboard(HWND);
	int			GetKeyboardState();
	 char* GetKeyState();


	//コールバック関数
	BOOL CALLBACK	EnumJoysticksCallback(const DIDEVICEINSTANCE* pdidInstance, void* pContext);
	BOOL CALLBACK	EnumObjectsCallback(const DIDEVICEOBJECTINSTANCE* pdidoi, void* pContext);

	//定義
	//この値に度を掛けるとラジアンになる
	#define	kDEG_TO_RAD		( D3DX_PI * 2.0f / 360.0f)	

	#define	kPI_1FOURTH		( D3DX_PI / 4.0f )			// 45度
	#define	kPI_HALF		( D3DX_PI / 2.0f )			// 90度

	//　ジョイスティックで通常Aボタン、もしくはCボタンがOK、Bがキャンセルの意味を持つため
	#define kKEY_YES	(kKEY_Z | kKEY_ENTER | kKEY_SPACE | kKEY_C)
	#define	kKEY_NO		(kKEY_X)

	//　ジョイスティックの精度と感度
	#define	kJS_RESO	1000
	#define	kJS_DEAD	( kJS_RESO / 2 )

	//-----------------------------------------------------------------------------
	//　キーボード（ジョイスティック）の状態
	//　ジョイスティックの場合はLEFTとRIGHTなど相反するキー入力が同時に行われることはありえないが
	//　キーボードでは可能であることを注意する
	enum {
		kKEY_NONE = 0x00000,
		kDIR_LEFT = 0x00001,
		kDIR_RIGHT = 0x00002,
		kDIR_UP = 0x00004,
		kDIR_DOWN = 0x00008,

		kKEY_Z = 0x00020,// A
		kKEY_X = 0x00040,// B
		kKEY_C = 0x00080,// C
		kKEY_A = 0x01000,// X
		kKEY_S = 0x02000,// Y
		kKEY_D = 0x04000,// Z

		kKEY_L = 0x08000,// L
		kKEY_R = 0x10000,// R

		kKEY_SPACE = 0x00010,

		kKEY_ENTER = 0x00100,
		kKEY_TAB = 0x00200,
		kKEY_SHIFT = 0x00400,
		kKEY_DELBS = 0x00800,

		kKEY_ERR = 0x80000,
		kKEY_DIR_MASK = 0x0000f,
		kKEY_BUTTON_MASK = 0xffff0,
		kKEY_ALL_MASK = 0xfffff
	};

private:
	LPDIRECTINPUT8		pDirectInput;	//DirectInputオブジェクト

	LPDIRECTINPUTDEVICE8	pkeyboard;	//キーボードデバイス
	LPDIRECTINPUTDEVICE8	pJoystick;	//ジョイスティックデバイス
	LPDIRECTINPUTDEVICE8	pMouse;		//マウスデバイス

	char				keys[256];
};



//現段階では、キーボードのみ操作可能