#include "Title.h"


//����������
void	Title::Inialize()
{
	font.Create(TEXT("MS �S�V�b�N"), 12, 12);
	titleImg.LoadTexture(TEXT("./data/Image/tex.bmp"));
}

//�I������
void	Title::Finalize()
{
	font.Destory();
	titleImg.Destroy();
	MessageBox(NULL, TEXT("�^�C�g����ʂ��I�����܂�"), TEXT("Title"), MB_OK);
}

//�X�V����
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

//�`�揈��
void	Title::Render()
{
	font.Render(TEXT("�^�C�g����ʂł�"), Box2D(0, 0, 200, 50), D3DXCOLOR(1, 1, 1, 1));

	titleImg.Render(Box2D(0, 0,64, 64), Box2D(0, 0, 64, 64));
}