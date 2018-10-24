#include "Model.h"



//�R���X�g���N�^
Model::Model() : m_pMesh(0), m_pMtrlBuf(0), m_texture(nullptr)
{
	pos = D3DXVECTOR3(0, 0, 0);
	angle = D3DXVECTOR3(0, 0, 0);
	size = D3DXVECTOR3(1, 1, 1);
}
//�f�X�g���N�^
Model::~Model()
{
	Erase();
}

//���f���̓ǂݍ���
void	Model::Load(LPCWSTR fileName)
{
	LibModel::Load(fileName, &m_pMtrlBuf, &m_MtrlNum, &m_pMesh);
}

void	Model::Load(LPCSTR fileName)
{
	LibModel::Load(fileName, &m_pMtrlBuf, &m_MtrlNum, &m_pMesh);
}

//���f���̉��
void	Model::Erase()
{
	if (m_pMesh != nullptr) { m_pMesh->Release(); m_pMesh = nullptr; }
	if (m_pMtrlBuf != nullptr) { m_pMtrlBuf->Release(); m_pMtrlBuf = nullptr; }

}

//���f���̕`��
void	Model::Render()
{
	D3DMATERIAL9	mMaterial;

	//�}�e���A���������o��
	D3DXMATERIAL*	mD3DXMaterials = (D3DXMATERIAL*)m_pMtrlBuf->GetBufferPointer();
	m_texture = new LPDIRECT3DTEXTURE9[m_MtrlNum];	//�e�N�X�`�����}�e���A���̐������p��

	for (DWORD i = 0; i < m_MtrlNum; i++)
	{
		mMaterial = mD3DXMaterials[i].MatD3D;	//�}�e���A���̃R�s�[
		LibModel::SetMaterial(&mMaterial);		//�}�e���A���̃Z�b�g
		m_texture[i] = NULL;					//�e�N�X�`���Ȃ�

		//�g�p���Ă���e�N�X�`��������Γǂݍ���
		if (mD3DXMaterials[i].pTextureFilename != NULL && lstrlenA(mD3DXMaterials[i].pTextureFilename) > 0)
		{
			LibTexture::Create(mD3DXMaterials[i].pTextureFilename, &m_texture[i]);
			LibDGD::SetTexture(0, m_texture[i]);	//�e�N�X�`�����Z�b�g����
		}
		if (m_texture[i] != NULL) { m_texture[i]->Release(); m_texture[i] = NULL; }
		delete m_texture[i];

		m_pMesh->DrawSubset(i);					//�`��

		LibDGD::SetTexture(0, NULL);			//�e�N�X�`���̐ݒ�����Ƃɖ߂�
	}
}

void	Model::ZTexRender(ZTexture* zTex)
{
	D3DMATERIAL9	mMaterial;

	//�}�e���A���������o��
	D3DXMATERIAL*	mD3DXMaterials = (D3DXMATERIAL*)m_pMtrlBuf->GetBufferPointer();
	m_texture = new LPDIRECT3DTEXTURE9[m_MtrlNum];	//�e�N�X�`�����}�e���A���̐������p��

	for (DWORD i = 0; i < m_MtrlNum; i++)
	{
		mMaterial = mD3DXMaterials[i].MatD3D;	//�}�e���A���̃R�s�[
		LibModel::SetMaterial(&mMaterial);		//�}�e���A���̃Z�b�g
		m_texture[i] = NULL;					//�e�N�X�`���Ȃ�

		//�g�p���Ă���e�N�X�`��������Γǂݍ���
		if (mD3DXMaterials[i].pTextureFilename != NULL && lstrlenA(mD3DXMaterials[i].pTextureFilename) > 0)
		{
			LibTexture::Create(mD3DXMaterials[i].pTextureFilename, &m_texture[i]);
			LibDGD::SetTexture(0, m_texture[i]);	//�e�N�X�`�����Z�b�g����
		}
		if (m_texture[i] != NULL) { m_texture[i]->Release(); m_texture[i] = NULL; }
		delete m_texture[i];

		zTex->SetEffectParam();
		zTex->BeginPass();
		m_pMesh->DrawSubset(i);					//�`��
		zTex->EndPass();

		LibDGD::SetTexture(0, NULL);			//�e�N�X�`���̐ݒ�����Ƃɖ߂�
	}
}

void	Model::DepthRender(DepthTexture* depTex)
{
	D3DMATERIAL9	mMaterial;

	//�}�e���A���������o��
	D3DXMATERIAL*	mD3DXMaterials = (D3DXMATERIAL*)m_pMtrlBuf->GetBufferPointer();
	m_texture = new LPDIRECT3DTEXTURE9[m_MtrlNum];	//�e�N�X�`�����}�e���A���̐������p��

	for (DWORD i = 0; i < m_MtrlNum; i++)
	{
		mMaterial = mD3DXMaterials[i].MatD3D;	//�}�e���A���̃R�s�[
		LibModel::SetMaterial(&mMaterial);		//�}�e���A���̃Z�b�g
		m_texture[i] = NULL;					//�e�N�X�`���Ȃ�

												//�g�p���Ă���e�N�X�`��������Γǂݍ���
		if (mD3DXMaterials[i].pTextureFilename != NULL && lstrlenA(mD3DXMaterials[i].pTextureFilename) > 0)
		{
			LibTexture::Create(mD3DXMaterials[i].pTextureFilename, &m_texture[i]);
			LibDGD::SetTexture(0, m_texture[i]);	//�e�N�X�`�����Z�b�g����
		}
		if (m_texture[i] != NULL) { m_texture[i]->Release(); m_texture[i] = NULL; }
		delete m_texture[i];

		depTex->SetMaterialDiffuse(D3DXVECTOR4(mMaterial.Diffuse.r, mMaterial.Diffuse.g, mMaterial.Diffuse.b, mMaterial.Diffuse.a));
		depTex->SetEffectParam();
		depTex->BeginPass();
		m_pMesh->DrawSubset(i);					//�`��
		depTex->EndPass();

		LibDGD::SetTexture(0, NULL);			//�e�N�X�`���̐ݒ�����Ƃɖ߂�
	}
}




//��--------------------
bool	Model::BoundingBox()
{
	DWORD numv, stride;
	LPDIRECT3DVERTEXBUFFER9	vb;
	BYTE*		pvertices;
	HRESULT		hr = S_OK;
	D3DXVECTOR3	lmin, lmax;

	numv = m_pMesh->GetNumVertices();		//���_��
	stride = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	//���_�o�b�t�@�̎擾
	if (FAILED(m_pMesh->GetVertexBuffer(&vb)))
	{
		MessageBox(NULL, TEXT("���b�V���̒��_�o�b�t�@�擾�Ɏ��s���܂���"), TEXT("GetVertexBuf"), MB_OK);
		return false;
	}

	vb->Lock(0, 0, (VOID**)&pvertices, 0);	//���_�o�b�t�@�̃��b�N
	if (FAILED(D3DXComputeBoundingBox((D3DXVECTOR3*)pvertices,
		numv, stride, &lmin, &lmax)))
	{
		MessageBox(NULL, TEXT("�o�E���f�B���O�{�b�N�X�̍쐬�Ɏ��s���܂���"), TEXT("ComputBound"), MB_OK);
		return false;
	}

	LPD3DXMESH		tempMesh;
	//�}�e���A���̃N���[��
	m_pMesh->CloneMeshFVF(m_pMesh->GetOptions(), m_pMesh->GetFVF(), *LibDEV::GetDevice(), &tempMesh);

	minB = pos + lmin;
	maxB = pos + lmax;
	vb->Unlock();

	return true;
}


//�N���[�����b�V���̐���
bool	Model::CloneModel()
{
	//���_�錾
	const D3DVERTEXELEMENT9 vertexDecl[] =
	{
		{0, 0,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_POSITION,0},
		{0, 12,D3DDECLTYPE_FLOAT2,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_TEXCOORD,0},
		{0, 20,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_NORMAL,0},
		{ 0,32,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_TANGENT,0 },
		{ 0,44,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_BINORMAL,0 },
		D3DDECL_END()
	};

	//�N���[�����b�V���̐���
	if (FAILED(m_pMesh->CloneMesh(m_pMesh->GetOptions(), vertexDecl, *LibDEV::GetDevice(), &cloneMesh)))
	{
		MessageBoxA(NULL, "�N���[�����b�V���̐����Ɏ��s", "CloneMesh", MB_OK);
		return false;
	}
	return true;
}


//�ݒ菈��
void		Model::SetPos(const D3DXVECTOR3& pos)
{
	this->pos = pos;
}
void		Model::SetAngle(const D3DXVECTOR3& angle)
{
	this->angle = angle;
}
void		Model::SetSize(const D3DXVECTOR3& size)
{
	this->size = size;
}

//�擾����
D3DXVECTOR3	Model::GetPos()
{
	return D3DXVECTOR3(pos.x,pos.y,pos.z);
}
D3DXVECTOR3	Model::GetAngle()
{
	return D3DXVECTOR3(angle.x, angle.y, angle.z);
}
D3DXVECTOR3	Model::GetSize()
{
	return D3DXVECTOR3(size.x, size.y, size.z);
}
