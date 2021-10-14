//=============================================================================
//
// ����UI���� [weapons_ui.cpp]
// Author : �g�c�I�l
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "weapons_ui.h"
#include "manager.h"
#include "renderer.h"
#include "billboard.h"
#include "manager.h"
//*****************************************************************************
//�@�ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CWeapons_ui::m_pTexture[WEAPONS_TEXTURE_MAX] = {};
char *CWeapons_ui::m_cFileName[WEAPONS_TEXTURE_MAX]=
{
	WEAPONS_UI_AR_TEXTURE,
	WEAPONS_UI_HG_TEXTURE
};
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CWeapons_ui::CWeapons_ui() : CObject2D(2)
{
	m_pos = ZEROVECTOR3;
	m_frot = 0.0f;
	m_size = ZEROVECTOR3;
	m_col = D3DCOLOR_RGBA(255, 255, 255, 255);
	nCountCol = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CWeapons_ui::~CWeapons_ui()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CWeapons_ui::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	for (int nTexture=0;nTexture<WEAPONS_TEXTURE_MAX;nTexture++)
	{
		D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
			m_cFileName[nTexture],						// �t�@�C���̖��O
			&m_pTexture[nTexture]);								// �ǂݍ��ރ������[

	}
	return S_OK;
}

//=============================================================================
// �e�N�X�`���j���֐�
//=============================================================================
void CWeapons_ui::Unload(void)
{
	// �e�N�X�`���̔j��
	for (int nTexture = 0; nTexture < WEAPONS_TEXTURE_MAX; nTexture++)
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
CWeapons_ui * CWeapons_ui::Create(void)
{
	CWeapons_ui* pWeaponsUi = NULL;
	pWeaponsUi = new CWeapons_ui;

	pWeaponsUi->Init();

	return pWeaponsUi;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CWeapons_ui::Init(void)
{
	//�I�u�W�F�N�g2D������
	CObject2D::Init();
	//�T�C�Y����
	m_size = D3DXVECTOR3(250, 150, 0);
	//�ʒu�ݒ�
	m_pos = D3DXVECTOR3(SCREEN_WIDTH - (m_size.x/2), SCREEN_HEIGHT - (m_size.y+25), 0);

	//�Z�b�g
	SetPos(m_pos);
	SetRot(m_frot);
	SetSize(m_size);
	SetCol(m_col);
	//SetCol(D3DCOLOR_RGBA(255, 255, 0, 255));

	//�e�N�X�`���ݒ�
	BindTexture(m_pTexture[CManager::GetWeaponsMode()]);
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CWeapons_ui::Uninit(void)
{
	CObject2D::Uninit();
	
}

//=============================================================================
// �X�V����
//=============================================================================
void CWeapons_ui::Update(void)
{
	CObject2D::Update();
	if (nCountCol >= 0)
	{
		nCountCol--;
	}
	if (nCountCol == 0)
	{
		SetCol(D3DCOLOR_RGBA(255, 255, 255, 255));
	}
}

//=============================================================================
// �`��֐�
//=============================================================================
void CWeapons_ui::Draw(void)
{
	CObject2D::Draw();
}

//=============================================================================
// ����֐�
//=============================================================================
void CWeapons_ui::Gleams(void)
{
	nCountCol = 5;
	SetCol(D3DCOLOR_RGBA(255, 241, 86, 255));

}
