//=============================================================================
//
// �eUI���� [bullet_ui.cpp]
// Author : ��R�@���H
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "bullet_ui.h"
#include "manager.h"
#include "renderer.h"
#include "billboard.h"
#include "manager.h"
//*****************************************************************************
//�@�ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBullet_ui::m_pTexture[BULLET_TEXTURE_MAX] = {};
char *CBullet_ui::m_cFileName[BULLET_TEXTURE_MAX] =
{
	BULLET_UI_TEXTURE,
};
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBullet_ui::CBullet_ui() :CObject2D(2)
{
	m_pos = ZEROVECTOR3;
	m_frot = 0.0f;
	m_size = ZEROVECTOR3;
	m_col = D3DCOLOR_RGBA(255, 255, 255, 255);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBullet_ui::~CBullet_ui()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CBullet_ui::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	for (int nTexture = 0; nTexture<BULLET_TEXTURE_MAX; nTexture++)
	{
		D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
			m_cFileName[nTexture],						// �t�@�C���̖��O
			&m_pTexture[nTexture]);						// �ǂݍ��ރ������[

	}
	return S_OK;
}

//=============================================================================
// �e�N�X�`���j���֐�
//=============================================================================
void CBullet_ui::Unload(void)
{
	// �e�N�X�`���̔j��
	for (int nTexture = 0; nTexture < BULLET_TEXTURE_MAX; nTexture++)
	{
		if (m_pTexture[nTexture] != NULL)
		{
			m_pTexture[nTexture]->Release();
			m_pTexture[nTexture] = NULL;
		}

	}
}

//=============================================================================
// �����֐�
//=============================================================================
CBullet_ui * CBullet_ui::Create(D3DXVECTOR3 pos)
{
	CBullet_ui* pBulletUi = NULL;
	pBulletUi = new CBullet_ui;
	//�e�̏����l��ݒ�
	pBulletUi->m_pos = pos;
	pBulletUi->m_size = BULLET_UI_SIZE;
	pBulletUi->Init();

	return pBulletUi;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CBullet_ui::Init(void)
{
	//�Z�b�g
	SetPos(m_pos);
	SetRot(m_frot);
	SetSize(m_size);
	SetCol(m_col);

	//�e�N�X�`���ݒ�
	BindTexture(m_pTexture[0]);
	//�I�u�W�F�N�g2D������
	CObject2D::Init();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CBullet_ui::Uninit(void)
{
	CObject2D::Uninit();

}

//=============================================================================
// �X�V����
//=============================================================================
void CBullet_ui::Update(void)
{
	CObject2D::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CBullet_ui::Draw(void)
{
	CObject2D::Draw();
}