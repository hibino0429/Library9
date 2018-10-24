#include "Title.h"


//初期化処理
void	Title::Inialize()
{
	font.Create(TEXT("MS ゴシック"), 12, 12);
	titleImg.LoadTexture(TEXT("./data/Image/tex.bmp"));
}

//終了処理
void	Title::Finalize()
{
	font.Destory();
	titleImg.Destroy();
	MessageBox(NULL, TEXT("タイトル画面が終了します"), TEXT("Title"), MB_OK);
}

//更新処理
Task	Title::UpDate()
{
	key = input.GetKeyState();

	Task	nextTask = Task::Title;
	if (key[DIK_V] & 0x80)
	{
		nextTask = Task::GameMain;
	}
	return nextTask;
}

//描画処理
void	Title::Render()
{
	font.Render(TEXT("タイトル画面です"), Box2D(0, 0, 200, 50), D3DXCOLOR(1, 1, 1, 1));

	titleImg.Render(Box2D(0, 0,64, 64), Box2D(0, 0, 64, 64));
}