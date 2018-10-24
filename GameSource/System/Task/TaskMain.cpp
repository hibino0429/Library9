#include "TaskMain.h"


//------------------------------------------------------------
//タスクの初期化処理
//------------------------------------------------------------
void	TaskMain::Inialize()
{
	task.nowTask = Task::None;
	task.nextTask = Task::Title;
}


//------------------------------------------------------------
//タスクの解放処理
//------------------------------------------------------------
void	TaskMain::Finalize()
{

}


//------------------------------------------------------------
//タスクの更新処理
//------------------------------------------------------------
void	TaskMain::UpDate()
{
	//次のタスクが、現在のタスクと一致しない場合
	if (task.nowTask != task.nextTask)
	{
		//今実行中のタスクの終了処理を呼び出す
		switch (task.nowTask) {
		case Task::Title:		title.Finalize();	 break;
		case Task::GameMain:	gameMain.Finalize(); break;
		case Task::End:			ending.Finalize();	 break;
		}
		//次のタスクへ
		task.nowTask = task.nextTask;
		//次のタスクの初期化処理を呼ぶ
		switch (task.nowTask) {
		case Task::Title:		title.Inialize();		break;
		case Task::GameMain:	gameMain.Initailize();	break;
		case Task::End:			ending.Initialize();	break;
		}
	}
	//現在のタスクの実行・更新処理を呼び出す
	switch (task.nowTask) {
	case Task::Title:		task.nextTask = title.UpDate();		break;
	case Task::GameMain:	task.nextTask = gameMain.UpDate();	break;
	case Task::End:			task.nextTask = ending.UpDate();	break;
	}
	
}


//------------------------------------------------------------
//タスクの描画処理
//------------------------------------------------------------
void	TaskMain::Render()
{
	switch (task.nowTask) {
	case Task::Title:		title.Render();		break;
	case Task::GameMain:	gameMain.Render();	break;
	case Task::End:			ending.Render();	break;
	}
}






//---------------------------------------------------------------/
//タスクメイン処理
//---------------------------------------------------------------/
HRESULT	TaskMain::Create(HWND hWnd, HINSTANCE hInst, BOOL isFullScreen, int clientWidth, int clientHeight)
{
	//DirectInputの初期化
	if (FAILED(InputInit(hWnd, hInst)))
	{
		MessageBox(NULL, TEXT("失敗しました"), TEXT("失敗"), MB_OKCANCEL);
		return E_FAIL;
	}

	//DirectSoundの初期化
	/*if (!SE::Create(hWnd))
	{
		MessageBox(NULL, TEXT("サウンドの初期化に失敗しました"), TEXT("SE::Create"), MB_OKCANCEL);
		return E_FAIL;
	}*/

	//Audioの初期化
	if (!Audio::CreateSoundDevice(hWnd))
	{
		MessageBox(NULL, TEXT("Audioの生成に失敗しました"), TEXT("これは大いなる一歩だ"),MB_OK);
		return E_FAIL;
	}
	

	//Direct3Dの初期化
	if (FAILED(LibDEV::InitDevice(hWnd, isFullScreen, clientWidth, clientHeight)))
	{
		MessageBox(NULL, TEXT("Direct3Dデバイスの生成に失敗しました"), TEXT("InitDevice"), MB_OK);
		return E_FAIL;
	}

	//ゲームの初期化
	this->Inialize();

	return S_OK;
}

//--------------------------------------------------------------/
//ゲームの破棄処理
//--------------------------------------------------------------/
void	TaskMain::Destroy()
{
	//ゲームの解放
	this->Finalize();

	LibDEV::FinalDevice();
}

//--------------------------------------------------------------/
//ゲームメインの更新
//--------------------------------------------------------------/
void	TaskMain::SceneUpDate()
{
	//ゲームの更新
	this->UpDate();
}

//---------------------------------------------------------------/
//ゲームメインの描画
//---------------------------------------------------------------/
void	TaskMain::SceneRender()
{
	if (!LibDGD::ViewAndStencilClear()) { return; }

	if (LibDGD::BeginRender())
	{
		//ゲームの描画
		this->Render();

		LibDGD::EndRender();
	}
	LibDGD::PresentRender();
}


//---------------------------------------------------------------/
//デストラクタ
//---------------------------------------------------------------/
TaskMain::~TaskMain()
{
	Destroy();
}


//----------------------------------------------------------------
//入力処理の初期化処理
//----------------------------------------------------------------
HRESULT		TaskMain::InputInit(HWND hWnd, HINSTANCE hInst)
{
	//Titleの入力処理の初期化
	if (FAILED(title.input.InitDirectInput(hWnd, hInst)))
	{
		return E_FAIL;
	}
	//GameMainの入力処理
	if (FAILED(gameMain.input.InitDirectInput(hWnd, hInst)))
	{
		return E_FAIL;
	}
	//Endingの入力処理
	if (FAILED(ending.input.InitDirectInput(hWnd, hInst)))
	{
		return E_FAIL;
	}
	return S_OK;
}