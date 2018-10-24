#pragma once
#include "../../../Library9/Function.h"


//------------------------------------------
//�|���S�����b�V���̃f�[�^��`
//------------------------------------------
class SkinAnim
{
public:


private:

	//���_���
	struct Vertex
	{
		D3DXVECTOR3		coord;
		D3DXVECTOR3		weight;
		unsigned char matrixIndex[4];
	};

	void	VertexDeclaration();		//���_�錾


	//�{�[��
	struct Bone
	{
		int id;
		Bone*	firstChild;
		Bone*	sibling;

		D3DXMATRIX offsetMat;
		D3DXMATRIX initMat;
		D3DXMATRIX	boneMat;
		D3DXMATRIX* combMatArray;
	};

	void	CreateBone();	//�{�[���̐���
};