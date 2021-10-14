//=============================================================================
//
// ����I����ʔw�i���� [weaponselectscene.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "weaponselectscene.h"
#include "manager.h"
#include "renderer.h"
#include "fade.h"

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CWeaponSelectScene::m_pTexture = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CWeaponSelectScene::CWeaponSelectScene()
{
	D3DXVECTOR3	m_pos = ZEROVECTOR3;
	D3DXVECTOR3	m_size = ZEROVECTOR3;
	D3DCOLOR	m_col = D3DCOLOR_RGBA(255, 255, 255, 255);
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_texpos[nCount] = D3DXVECTOR2(0.0f, 0.0f);
	}
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CWeaponSelectScene::~CWeaponSelectScene()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CWeaponSelectScene::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		"Data/Texture/selectscene.png",								// �t�@�C���̖��O
		&m_pTexture);								// �ǂݍ��ރ������[
	return S_OK;
}

//=============================================================================
// �e�N�X�`���j���֐�
//=============================================================================
void CWeaponSelectScene::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// �����֐�
//=============================================================================
CWeaponSelectScene * CWeaponSelectScene::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CWeaponSelectScene* pWeaponSelectScene = NULL;
	pWeaponSelectScene = new CWeaponSelectScene;
	pWeaponSelectScene->m_pos = pos;
	pWeaponSelectScene->m_size = size;
	pWeaponSelectScene->Init();

	return pWeaponSelectScene;
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CWeaponSelectScene::Init(void)
{
	SetPos(m_pos);
	SetSize(m_size);
	SetCol(m_col);
	BindTexture(m_pTexture);	//�e�N�X�`���̊��蓖��
	CObject2D::Init();
	return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CWeaponSelectScene::Uninit(void)
{
	CObject2D::Uninit();
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CWeaponSelectScene::Update(void)
{
}

//=============================================================================
// �`��֐�
//=============================================================================
void CWeaponSelectScene::Draw(void)
{
	CObject2D::Draw();
}
