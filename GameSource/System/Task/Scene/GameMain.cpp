#include "GameMain.h"

#include <time.h>


//----------------------------------------------------
//�Q�[�����C���̏�����
//----------------------------------------------------
void	GameMain::Initailize()
{
	srand((unsigned int)time(0));

	cameraMan.Initialize();
	LightInit();

	LibDGD::SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	LibDGD::SetRenderState(D3DRS_ZENABLE, TRUE);
	LibDGD::SetRenderState(D3DRS_DITHERENABLE, TRUE);
	LibDGD::SetRenderState(D3DRS_LIGHTING, TRUE);
	LibDGD::SetRenderState(D3DRS_AMBIENT, D3DXCOLOR(1, 1, 1, 1));

	
	map.Initialize();
	

	player.Initialize();
	samp.Initialize();
	//object.Initialize();
	obj.Initialize();

	D3DXMATRIX	lightV,lightP;
	D3DXMatrixPerspectiveFovLH(&lightP, D3DXToRadian(120), 1.0f, 40.0f, 700.0f);
	D3DXMatrixLookAtLH(&lightV, &D3DXVECTOR3(100, 500, 100), &D3DXVECTOR3(0, -60, 0), &D3DXVECTOR3(0, 1, 0));
	
	//Z�l�e�N�X�`���̏�����
	zTexture.Initialize();
	zTexture.SetViewMatrix(&lightV);		//���C�g�̃r���[
	zTexture.SetProjMatrix(&lightP);		//���C�g�̎ˉe

	//�[�x�o�b�t�@�̏�����
	depthTexture.SetTexture(zTexture.GetTexture());	//�e�N�X�`���̏���n��
	depthTexture.Initialize();
	depthTexture.GetLightProjMatrix(&lightP);		//���C�g�̎ˉe
	depthTexture.GetLightViewMatrix(&lightV);		//���C�g�̃r���[
	depthTexture.SetCameraProjMatrix(&cameraMan.PassProjMatrix());	//�J�����̎ˉe

}


//----------------------------------------------------
//�Q�[�����C���̏I��
//----------------------------------------------------
void	GameMain::Finalize()
{
	MessageBox(NULL, TEXT("�Q�[�����C�����I�����܂�"), TEXT("GameMain"), MB_OK);
}


//----------------------------------------------------
//�Q�[�����C���̍X�V
//----------------------------------------------------
Task	GameMain::UpDate()
{
	key = input.GetKeyState();
	
	//�J�����}���̍X�V
	cameraMan.GetKeyboard(input.GetKeyState());
	cameraMan.CircleMove(&player);
	cameraMan.UpDate();

	//���C�g�̍X�V
	for (int i = 0; i < 4; ++i)
	{
		light[i].UpDate();
	}

	//�X�|�b�g���C�g�̍X�V
	light[1].SetPosition(D3DXVECTOR3(player.model.pos.x,player.model.pos.y + 10,player.model.pos.z));

	//�ǉ�---------
	
	map.UpDate();

	player.GetKeyboard(input.GetKeyState());
	player.GetCameraManAngle(cameraMan.angle);

	//�v���C���[�ƃ}�b�v�Ƃ̓����蔻��
	player.Move(&map);
	player.UpDate();


	samp.BoxHitCheck(player.hitBox);
	samp.UpDate();

	obj.UpDate();

	//object.UpDate();


	//�^�X�N�̑J��
	Task	nextTask = Task::GameMain;
	if (key[DIK_V] & 0x80)
	{
		nextTask = Task::End;
	}

	return nextTask;
}


//----------------------------------------------------
//�Q�[�����C���̕`��
//----------------------------------------------------
void	GameMain::Render()
{
	LibDGD::ZBufClear();

	//���C�g�̕`��
	for (int i = 0; i < 5; ++i)
	{
		light[i].Render();
	}
	//�J�����̃}���̕`��
	cameraMan.Render();


	//--------------------------------------------------
	//�`��̊J�n
	zTexture.Begin();

	//�I�u�W�F�N�g�̕`��
	player.ZRendere(&zTexture);
	//object.ZTexRender(&zTexture);
	samp.ZTexRender(&zTexture);
	map.ZTexRender(&zTexture);

	obj.Render(&zTexture);

	//�`��̏I��
	zTexture.End();
	//--------------------------------------------------

	//�J�����̃r���[�E�ˉe�s��̃Z�b�g
	depthTexture.SetCameraViewMatrix(&cameraMan.PassViewMatrix());
	depthTexture.SetCameraProjMatrix(&cameraMan.PassProjMatrix());

	//--------------------------------------------------
	//�[�x�V���h�E�o�b�t�@�̕`��
	depthTexture.Begin(0, 0);
	
	//�I�u�W�F�N�g�̕`��
	//object.DepthRender(&depthTexture);
	samp.DepthRender(&depthTexture);
	map.DepthRender(&depthTexture);
	player.DepthRender(&depthTexture);

	obj.Render(&depthTexture);

	//�`��̏I��
	depthTexture.End();
	//--------------------------------------------------

	

	//�@���}�b�v�̃I�u�W�F�N�g
	/*object.normalMap.SetViewMatrix(&cameraMan.PassViewMatrix());
	object.normalMap.SetProjMatrix(&cameraMan.PassProjMatrix());
	D3DXVECTOR3 cameraVec = cameraMan.camera.GetTarget() - cameraMan.camera.GetPos();
	object.normalMap.SetCameraVec(cameraVec);
	object.normalMap.SetLightDir(light[0].direction);
	object.Render();*/
}



//���C�g�̏�����
void	GameMain::LightInit()
{
	//���C�g0
	light[0].SetNumber(0);
	light[0].SetUse(true);
	//�f�B���N�V���i�����C�g
	//�K�v�Ȃ���
	//�^�C�v�E�f�B�t���[�Y�F�E�����E�X�y�L�����[�F
	light[0].SetType(D3DLIGHT_DIRECTIONAL);
	light[0].SetDiffuse(D3DXCOLOR(1, 1, 1, 1));
	light[0].SetSpecular(D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.1f));
	light[0].SetDirection(D3DXVECTOR3(-5.0f, -5.0f, 10.0f));
	light[0].position = D3DXVECTOR3(0, 100, 0);

	//���C�g1
	light[1].SetNumber(1);
	light[1].SetUse(true);
	//�|�C���g���C�g
	//�K�v�Ȃ���
	//�^�C�v�E�ʒu�E���̗L�������E���̌����E�f�B�t���[�Y�F, (�X�y�L�����[�F)
	light[1].SetType(D3DLIGHT_POINT);
	light[1].SetDiffuse(D3DXCOLOR(1.0f, 0.2f, 0, 1));
	light[1].SetSpecular(D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f));
	light[1].SetPosition(D3DXVECTOR3(600, 10, -150));
	light[1].SetAttenuation((1.0f / 755.0f) * (1.0f / 755.0f));
	light[1].SetRange(850.0f);


	//���C�g2
	light[2].SetNumber(2);
	light[2].SetUse(false);

	//���C�g3
	light[3].SetNumber(3);
	light[3].SetUse(false);


	light[0].Initalize();
	light[1].Initalize();
	light[2].Initalize();
	light[3].Initalize();
}


//���C�g�̍X�V
void	GameMain::LightUpDate()
{

}

//���C�g�̎ˉe�ϊ����Z�b�g
void	GameMain::SetLightView(D3DXMATRIX* mat,D3DXVECTOR3& pos)
{
	D3DXMatrixLookAtLH(mat, 
		&D3DXVECTOR3(pos.x + 50,pos.y + 200,pos.z + 100), 
		&D3DXVECTOR3(pos.x,pos.y-50,pos.z),
		&D3DXVECTOR3(0, 1, 0)
	);
}



