#include "Input.h"

DGD*	dgd5 = DGD::Instance();

//コンストラクタ
Input::Input() :pDirectInput(NULL), pkeyboard(NULL), pMouse(NULL)
{
	
}

//デストラクタ
Input::~Input()
{
	if (pDirectInput != NULL) {	pDirectInput->Release(); pDirectInput = NULL; }
	if (pkeyboard != NULL) { pkeyboard->Release(); pkeyboard = NULL; }
	if (pMouse != NULL) { pMouse->Release(); pMouse = NULL; }
}


//---------------------------------------------------------
//DirectInputの初期化
//---------------------------------------------------------
HRESULT		Input::InitDirectInput(HWND hWnd, HINSTANCE hInstance)
{
	//変数とか
	HRESULT hr = S_OK;		//こけた時の結果返し
	
							//最初に初期化しておく
	KillTimer(hWnd, 0);
	

	//DirectInputオブジェクトの生成
	if (FAILED(hr = DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
		IID_IDirectInput8, (VOID**)&pDirectInput, NULL)))
	{
		MessageBox(NULL, TEXT("DirectInput8Create"), TEXT("DirectInput"), MB_OK);
		return hr;
	}

	if (FAILED(hr = SetKeyboard(hWnd))) { return hr; }
	//if (FAILED(hr = SetJoystick(hWnd))) { return hr; }
	if (FAILED(hr = SetMouse(hWnd)))	{ return hr; }
	
	return hr;
}


//---------------------------------------------------------
//DirectInput関係の解放処理
//---------------------------------------------------------
void		Input::ClearDirectInput()
{
	//DirectInputでキーボード、マウス、ジョイスティック
	//いずれか使用中なら、使用を終了
	if (pkeyboard) { pkeyboard->Unacquire(); }
	if (pJoystick) { pJoystick->Unacquire(); }
	if (pMouse)		{ pMouse->Unacquire(); }

	//デバイスの解放
	pkeyboard->Release();
	pJoystick->Release();
	pMouse->Release();

	//DirectInputの解放
	pDirectInput->Release();
}


//--------------------------------------------------------
//DirectInputでキーボードを使用可能にする
//--------------------------------------------------------
HRESULT		Input::SetKeyboard(HWND hWnd)
{
	//変数
	HRESULT	hr;		//こけたときの結果用

					//システムキーボードデバイスを探して確保
					//キーボードがない場合、は注意が必要
	if (FAILED(hr = pDirectInput->CreateDevice(GUID_SysKeyboard, &pkeyboard, NULL)))
	{
		return hr;
	}

	if (pkeyboard == NULL)
	{
		return S_OK;		//キーボードがない
	}

	//DirectInputから受け取るデータフォーマットをキーボードに設定
	//c_dfDIKeyboardは、DirectInputが用意したグローバル変数
	//const設定されて変数の値は変更できない
	if (FAILED(hr = pkeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return hr;
	}

	//システムや、ほかのDirectInputを利用したアプリケーションと
	//どのように連携すればよいか
	//DirectInputに通知するために、協調レベルをセット
	//(フォアグランド・直接入力・協調モード・Windowsキー無効に固定)
	if (FAILED(hr = pkeyboard->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND | DISCL_NOWINKEY)))
	{
		return hr;
	}

	//キーボードの入力を有効にする
	pkeyboard->Acquire();

	return S_OK;
}


//----------------------------------------------------------
//キーボードの状態を取得
//複数キーの入力を認識
//バッファを使い、データ入力を行う場合、変更の必要あり
//----------------------------------------------------------
int			Input::GetKeyboardState()
{
	int	result = kKEY_NONE;	//返り血用変数
	HRESULT	hr;
	BYTE	diks[256];		//DirectInputのキーボードステータスバッファ

							//キーボードデバイスがない場合、なめらかに去る
	if (NULL == pkeyboard) { return kKEY_ERR; }

	//入力デバイスの状態を確保し、配列に収める
	ZeroMemory(diks, sizeof(diks));
	hr = pkeyboard->GetDeviceState(sizeof(diks), diks);
	if (FAILED(hr))
	{
		//もじ入力が失われていた場合、確保し、維持を試みる
		hr = pkeyboard->Acquire();
		while (hr == DIERR_INPUTLOST) { hr = pkeyboard->Acquire(); }

		//エラー時は帰る
		if (FAILED(hr)) { return kKEY_ERR; }
	}

	//======================================================================
	//キーボードからの入力による
	if ((diks[0xcb] & 0x80) || (diks[0x4b] & 0x80))
	{
		result |= kDIR_LEFT;
	}                         // 左
	if ((diks[0xcd] & 0x80) || (diks[0x4d] & 0x80))
	{
		result |= kDIR_RIGHT;
	}                        // 右
	if ((diks[0xc8] & 0x80) || (diks[0x48] & 0x80))
	{
		result |= kDIR_UP;
	}                            // 上
	if ((diks[0xd0] & 0x80) || (diks[0x50] & 0x80))
	{
		result |= kDIR_DOWN;
	}                         // 下
							  //======================================================================

	if (diks[0x0f] & 0x80) { result |= kKEY_TAB; }       // Tab
	if (diks[0x2c] & 0x80) { result |= kKEY_Z; }         // Z
	if (diks[0x2d] & 0x80) { result |= kKEY_X; }         // X
	if (diks[0x2e] & 0x80) { result |= kKEY_C; }         // C
	if (diks[0x39] & 0x80) { result |= kKEY_SPACE; }     // Space
	if (diks[0x1c] & 0x80) { result |= kKEY_ENTER; }     // Enter
	if ((diks[0x0e] & 0x80) || (diks[0xd3] & 0x80))
	{
		result |= kKEY_DELBS;
	}                        // DelかBackSpace
	if ((diks[0x2a] & 0x80) || (diks[0x36] & 0x80))
	{
		result |= kKEY_SHIFT;
	}                        // Shift

	return(result);
}

//入力処理
char*		Input::GetKeyState()
{
	HRESULT hr = pkeyboard->Acquire();
	if ((hr == DI_OK) || (hr == S_FALSE))
	{
		pkeyboard->GetDeviceState(sizeof(keys), &keys);
		return keys;
	}
	return NULL;
}

//--------------------------------------------------------
//DirectInputでマウスを使用可能にする
//キーボードとマウスの中間の処理を行う
//直接入力を扱う
//バッファデータを扱いたい場合、バッファの設定などが必要になる
//--------------------------------------------------------
HRESULT		Input::SetMouse(HWND hWnd)
{

	HRESULT	hr = S_OK;

	//システムマウスデバイスを探して確保する
	if (FAILED(hr = pDirectInput->CreateDevice(GUID_SysMouse, &pMouse, NULL)))
	{
		return hr;
	}

	//ジョイスティックは確保できたか
	//ジョイスティックが接続されていなかった場合、後から接続しても認識しない
	if (NULL == pMouse)
	{
		MessageBox(NULL, TEXT("マウスが見つかりません"), TEXT("エラー"), MB_ICONERROR | MB_OK);
		return hr;
	}

	// DirectInputから受け取るデータフォーマットをマウス（拡張仕様）に設定する
	// c_dfDIMouse2はDirectInputが用意したグローバル変数でconst設定されていて
	// 変数の値は変更できない
	// この部分はJoystickの処理と同様
	// ただし複数のマウスがあることは考えられていない
	if (FAILED(hr = pMouse->SetDataFormat(&c_dfDIMouse2)))
	{
		return(hr);
	}

	// 他のデバイスと同様に協調レベルをセットする
	// ここではフォアグランド・排他的利用モードに固定
	// ゲームの操作のためにマウスを使う場合は、通常このモードでかまわない
	// しかし、このモードでは、マウスカーソルが見えなくなるため、
	// アプリケーション側でマウスカーソルを独自に表示させるなど工夫が
	// 必要になるので要注意
	if (FAILED(hr = pMouse->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND)))
	{
		ClearDirectInput();
		if (hr == DIERR_UNSUPPORTED)
		{
			MessageBox(NULL, TEXT("DirectInputがサポートしていない協調レベルです。"), TEXT("エラー"), MB_ICONERROR | MB_OK);
		}
		return(hr);
	}

	// マウスの入力を有効にする
	pMouse->Acquire();

	return S_OK;
}



//--------------------------------------------------------
//マウスの状態を取得
//バッファを使って、データ入力を行いたい場合、変更の必要がある
//--------------------------------------------------------
HRESULT		Input::GetMouseState(HWND hWnd, int* result)
{
	HRESULT       hr;             // システムリザルト
	DIMOUSESTATE2 aMouseState;    // DirectInputのマウス情報構造体

								  // マウスがない場合は、なめらかに去る
	if (NULL == pMouse) { return S_OK; }

	// 入力機器の状態を確保し、配列に納める
	// キーボードとよく似ている
	ZeroMemory(&aMouseState, sizeof(DIMOUSESTATE2));

	hr = pMouse->GetDeviceState(sizeof(DIMOUSESTATE2), &aMouseState);
	if (FAILED(hr))
	{
		// もし入力が失われていた場合、再確保を試みる
		hr = pMouse->Acquire();
		while (hr == DIERR_INPUTLOST) { hr = pMouse->Acquire(); }

		// エラー時は他のアプリケーションがフォアグランドに
		// なっていたりするので何もしないで帰る
		if (FAILED(hr))
		{
			*result = kKEY_ERR;
			return(S_OK);
		}
	}

	//======================================================================
	// マウスボタンの読み取り
	if (aMouseState.rgbButtons[0x00] & 0x80) { *result |= kKEY_Z; }    // Z
	if (aMouseState.rgbButtons[0x01] & 0x80) { *result |= kKEY_X; }    // X
	if (aMouseState.rgbButtons[0x02] & 0x80) { *result |= kKEY_C; }    // C
	if (aMouseState.rgbButtons[0x03] & 0x80) { *result |= kKEY_A; }    // A
	if (aMouseState.rgbButtons[0x04] & 0x80) { *result |= kKEY_S; }    // S
	if (aMouseState.rgbButtons[0x05] & 0x80) { *result |= kKEY_D; }    // D
	if (aMouseState.rgbButtons[0x06] & 0x80) { *result |= kKEY_L; }    // L
	if (aMouseState.rgbButtons[0x07] & 0x80) { *result |= kKEY_R; }    // R


																	   //======================================================================
																	   // 移動方向の読み取り
	if ((aMouseState.lX != 0) || (aMouseState.lY != 0))
	{
		const double kPI_1EIGHTH = kPI_1FOURTH / 2.0f;    // 8分の１

		double aTheta = atan2((double)aMouseState.lX, (double)aMouseState.lY);

		if ((aTheta < kPI_1EIGHTH * 3.0f) && (aTheta > kPI_1EIGHTH * -3.0f))
		{
			*result |= kDIR_DOWN;
		}
		else
			if ((aTheta > kPI_1EIGHTH * 5.0f) || (aTheta < kPI_1EIGHTH * -5.0f))
			{
				*result |= kDIR_UP;
			}

		if ((aTheta > kPI_1EIGHTH * 1.0f) && (aTheta < kPI_1EIGHTH * 7.0f))
		{
			*result |= kDIR_RIGHT;
		}
		else
			if ((aTheta < kPI_1EIGHTH * -1.0f) && (aTheta > kPI_1EIGHTH * -7.0f))
			{
				*result |= kDIR_LEFT;
			}
	}

	return(S_OK);
}


/*
//--------------------------------------------------------
//DirectInputでジョイスティックを使用可能にする
//複数の場合、ここで初期化処理を変更させる
//--------------------------------------------------------
HRESULT		Input::SetJoystick(HWND hWnd)
{
	HRESULT hr;    // ずっこけたときの結果返し用

				   // ジョイスティックを探して確保する
				   // （ジョイスティックは複数ある可能性がある）
				   // EnumJoysticksCallbackはデバイスごとに呼び出されるコールバック関数
				   // デバイスの数だけ呼び出される
				   // DI8DEVCLASS_GAMECTRLはすべてのゲーム用コントローラを探し出すための定数
				   // DIEDFL_ATTACHEDONLYはアタッチ状態にあり、インストールずみのデバイスのみ 
	if (FAILED(hr = pDirectInput->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback, NULL, DIEDFL_ATTACHEDONLY)))
	{
		return(hr);
	}

	// ジョイスティックは確保できた？
	// ジョイスティックが接続されていなかった場合、あとから接続しても認識しない
	if (NULL == pJoystick)
	{
		MessageBox(NULL, TEXT("ジョイスティックが発見できませんでした。"), TEXT("ジョイスティック確保できない"), MB_ICONERROR | MB_OK);
		return(S_OK);    // ここで帰ってしまう
	}

	// DirectInputから受け取るデータフォーマットを
	// ジョイスティック（拡張仕様）に設定する
	// c_dfDIJoystick2はDirectInputが用意したグローバル変数
	// const設定されていて変数の値は変更できない
	// この部分は普通のジョイパッドを使う限りは定型句に近いが、
	// 複数のジョイスティックがある場合、それぞれに対して
	// データフォーマットを設定する必要があることに注意する
	if (FAILED(hr = pJoystick->SetDataFormat(&c_dfDIJoystick2)))
	{
		return(hr);
	}

	// システムや、他のDirectInputを利用したアプリケーションと、
	// どのように連携すればよいのか
	// DirectInputに通知するために、協調レベルをセットする
	// これも複数のジョイスティックを使う場合は
	// それぞれに対して設定する必要がある
	// ここではフォアグランド・排他的利用モードに固定
	// 普通、ジョイスティック使う場合はこの設定のままでかまわない
	if (FAILED(hr = pJoystick->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND)))
	{
		return(hr);
	}

	// EnumDevicesメソッドで探し出されたジョイスティック上にあるオブジェクト、
	// つまり操作するためのボタンや方向キーを
	// 1つ1つ確認していく
	// EnumObjectsCallbackはディバイス上にオブジェクトが見つかるたびに
	// 呼び出されるコールバック関数
	// DIDFT_ALLはデバイス上の全ての入出力オブジェクトを列挙するための定数
	if (FAILED(hr = pJoystick->EnumObjects(EnumObjectsCallback, (VOID*)hWnd, DIDFT_ALL)))
	{
		return(hr);
	}

	// ジョイスティックの入力を有効にする
	pJoystick->Acquire();

	return(S_OK);
}
*/


//--------------------------------------------------------
//ジョイスティックの状態を取得する
//バッファを使った入力を行うなら、変更の必要がある
//--------------------------------------------------------
HRESULT		Input::GetJoystickState(HWND hWnd, int* result)
{
	HRESULT  hr = S_OK;
	//  TCHAR strText[512];    // デバイスの状態を取得するバッファ（特にボタン）
	DIJOYSTATE2 aJoystickState;    // ジョイスティックの状態を取得する
								   //  TCHAR* str;

								   // もし、ジョイスティックデバイスが初期化されていなかった場合は
								   // 何もせずに帰る
	if (NULL == pJoystick)
	{
		*result = kKEY_ERR;
		return (S_OK);
	}

	// デバイスの現在の状況を取得する
	hr = pJoystick->Poll();
	if (FAILED(hr))
	{
		// DirectInputはPollメソッドが呼び出された時点での
		// 入力ストリームの状態を伝えるが
		// 入力機器がなんらかの原因で失われたとしても
		// それをメソッドが返すエラー以外で知ることはできない
		// また、デバイスをリセットする手段もない
		// そのため、デバイスを再取得することを試みる
		hr = pJoystick->Acquire();
		while (hr == DIERR_INPUTLOST) { hr = pJoystick->Acquire(); }

		// それ以外のエラーは、他のアプリケーションがフォアグランドになっているか
		// アプリケーション自体が最小化されてデータが取得できない場合がほとんど
		// こうした場合は、何もせずに帰って後で再取得を試みる
		return(S_OK);
	}

	// ジョイスティックの状態を取得する
	// ここで取得できる状態は、先のPoll()メソッドを呼び出した時点のもの
	// GetDeviceStateの呼び出しが遅れれば、当然それだけ古い情報になってしまう
	// ここがエラーを返す場合、ジョイスティックが引き抜かれた可能性が高い
	if (FAILED(hr = pJoystick->GetDeviceState(sizeof(DIJOYSTATE2), &aJoystickState)))
	{
		return(hr);
	}


	// 方向ボタンの検出（Z軸は見ていない）
	if (aJoystickState.lX > kJS_DEAD) { *result |= kDIR_RIGHT; }
	else if (aJoystickState.lX < -kJS_DEAD) { *result |= kDIR_LEFT; }
	if (aJoystickState.lY > kJS_DEAD) { *result |= kDIR_DOWN; }
	else if (aJoystickState.lY < -kJS_DEAD) { *result |= kDIR_UP; }

	// どのボタンが押されたか確認する
	// rgbButtonsは押されたボタンに対応した配列の最上位ビットが1になる
	if (aJoystickState.rgbButtons[0x00] & 0x80) { *result |= kKEY_Z; }     // A
	if (aJoystickState.rgbButtons[0x01] & 0x80) { *result |= kKEY_X; }     // B
	if (aJoystickState.rgbButtons[0x02] & 0x80) { *result |= kKEY_C; }     // C

	if (aJoystickState.rgbButtons[0x03] & 0x80) { *result |= kKEY_A; }     // X
	if (aJoystickState.rgbButtons[0x04] & 0x80) { *result |= kKEY_S; }     // Y
	if (aJoystickState.rgbButtons[0x05] & 0x80) { *result |= kKEY_D; }     // Z

	if (aJoystickState.rgbButtons[0x06] & 0x80) { *result |= kKEY_L; }     // L
	if (aJoystickState.rgbButtons[0x07] & 0x80) { *result |= kKEY_R; }     // R
	if (aJoystickState.rgbButtons[0x08] & 0x80) { *result |= kKEY_ENTER; } // Start

	return(hr);
}



//--------------------------------------------------------
//EnumDevicesメソッドで設定
//ジョイスティック1つにつき1回呼び出されるコールバック関数
//列挙を続けるなら、DIENUM_CONTINUE
//見つかったなら、DIENUM_STOP
//--------------------------------------------------------
BOOL CALLBACK Input::EnumJoysticksCallback(const DIDEVICEINSTANCE* pdidInstance, void* pContext)
{
	HRESULT hr;

	// 列挙されたジョイスティックへのインターフェイスを獲得する
	// g_pJoystickに確保された情報を納めるので、
	// 複数のジョイスティックを認識させたい場合は
	// その数だけLPDIRECTINPUTDEVICE8型の変数を用意しておく
	hr = Input::pDirectInput->CreateDevice(pdidInstance->guidInstance, &pJoystick, NULL);

	// 失敗していた場合、そのジョイスティックは使えない。
	// デバイスを列挙している途中でユーザーが
	// ジョイスティックを外した可能性が高い
	// ここでは、ジョイスティックが1つ見つかればそれでいいので、
	// 失敗したときにかぎって再度検索するようにしている
	if (SUCCEEDED(hr))
	{
		return(DIENUM_STOP);
	}
	else { return(DIENUM_CONTINUE); }
}



//---------------------------------------------------------
//EnumObjectsメソッドで設定
//ジョイスティックの角度、ボタン、方向コントローラーを
//1つ1つ調べていくコールバック関数
//---------------------------------------------------------
BOOL CALLBACK Input::EnumObjectsCallback(const DIDEVICEOBJECTINSTANCE* pdidoi, void* pContext)
{
	HWND hWnd = (HWND)pContext;

	// 列挙されたオブジェクトが角度コントローラだった場合
	// 角度コントローラにDIPROP_RANGEをセットして最大最小値を設定する
	if (pdidoi->dwType & DIDFT_AXIS)
	{
		DIPROPRANGE diprg;
		// 必ずこう初期化しなければならない
		diprg.diph.dwSize = sizeof(DIPROPRANGE);
		// 必ずこう初期化しなければならない
		diprg.diph.dwHeaderSize = sizeof(DIPROPHEADER);
		// dwObj メンバの解釈方法を指定する
		// 詳細については、dwObjメンバに関する下の説明を参照すること
		diprg.diph.dwHow = DIPH_BYID;
		// dwHow メンバが DIPH_BYID の場合、このメンバは、
		// 設定または取得されるプロパティを持つオブジェクトの識別子とする
		diprg.diph.dwObj = pdidoi->dwType;
		diprg.lMin = -kJS_RESO;    // 角度デバイスの最小値
		diprg.lMax = +kJS_RESO;    // 角度デバイスの最大値

		MessageBox(NULL, TEXT("絶対値か相対値を出力するディバイスを確認しました。\n最大値、最小値を設定します。"), TEXT("デバイスの確認"), MB_ICONEXCLAMATION | MB_OK);

		// 検出角度の範囲を設定する
		// DIPROP_RANGEで設定を行うが、一部のデバイスでは、
		// これは読み取り専用であるため、失敗する場合もある
		// 一部のデバイスでは、これは読み取り専用になっている
		// 失敗した場合は、角度ディバイスがどんな値を出力してくるか
		// わからないので列挙を止める
		if (FAILED(pJoystick->SetProperty(DIPROP_RANGE, &diprg.diph)))
		{
			return(DIENUM_STOP);
		}
	}

	return(DIENUM_CONTINUE);
}