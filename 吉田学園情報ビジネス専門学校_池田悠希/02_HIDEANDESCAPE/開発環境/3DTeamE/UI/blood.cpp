//=============================================================================
//
// ������ [blood.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "blood.h"
#include "manager.h"
#include "renderer.h"

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBlood::m_pTexture = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBlood::CBlood()
{
	m_pos = ZEROVECTOR3;
	m_move = ZEROVECTOR3;
	m_rot = ZEROVECTOR3;
	m_size = ZEROVECTOR3;
	m_col = D3DCOLOR_RGBA(255, 255, 255, 255);
	m_nLife = 30;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBlood::~CBlood()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CBlood::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		HITEFFECT_TEXTURE,								// �t�@�C���̖��O
		&m_pTexture);								// �ǂݍ��ރ������[
	return S_OK;
}

//=============================================================================
// �e�N�X�`���j���֐�
//=============================================================================
void CBlood::Unload(void)
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
CBlood * CBlood::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col)
{
	CBlood* pBlood = NULL;
	pBlood = new CBlood;
	pBlood->m_pos = pos;
	pBlood->m_move = move;
	pBlood->m_rot = rot;
	pBlood->m_size = size;
	pBlood->m_col = col;
	pBlood->Init();

	return pBlood;
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CBlood::Init(void)
{
	CBillboard::Init();
	SetPos(m_pos);
	SetSize(m_size);
	SetColor(m_col);
	BindTexture(m_pTexture);
	SetTex(0.0f, 0.0f, 1.0f, 1.0f);
	return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CBlood::Uninit(void)
{
	CBillboard::Uninit();
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CBlood::Update(void)
{
	CBillboard::Update();

	m_move.y -= 0.1f;

	m_pos += m_move;
	SetPos(m_pos);
	m_nLife--;

	if (m_nLife <= 0)
	{
		Uninit();
	}
	SetColor(m_col);
}

//=============================================================================
// �`��֐�
//=============================================================================
void CBlood::Draw(void)
{
	//D3DMATERIAL9 material;
	//ZeroMemory(&material, sizeof(D3DMATERIAL9));
	//material.Ambient = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	//pDevice->SetMaterial(&material);
	//pDevice->SetRenderState(D3DRS_AMBIENT, 0x44444444);
	CBillboard::Draw();
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

void CBlood::BloodCreate(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DCOLOR col)
{
	int nRandSeed = 0;//�����_���V�[�h�l�i���Ԗ��ύX�ł͂Ȃ��N���b�N���ύX�ɂ��邽�߁j
	nRandSeed = rand() % 255;
	srand((unsigned int)time(NULL)*nRandSeed);

	for (int nCount = 0; nCount < 10; nCount++)
	{
		float fRandRotX = float(rand() % 360 + -360);
		float fRandRotY = float(rand() % 360);
		float fRandRotZ = float(rand() % 360);
		float fRandSize = float(rand() % SPLACH_BLOOD_SIZE_X);
		float fRandSpeed = float(rand() % int(BLOOD_SPEED * 10));//�\�{�ɂ��ă����_���ɂ���
																	 //���̒l�̔{���ɖ߂�
		fRandSpeed = fRandSpeed / 10;
		CBlood::Create(pos, D3DXVECTOR3(cosf(D3DXToRadian(fRandRotX)) * fRandSpeed, sinf(D3DXToRadian(fRandRotY)) * -(fRandSpeed), cosf(D3DXToRadian(fRandRotZ))*fRandSpeed), ZEROVECTOR3, D3DXVECTOR3(fRandSize, fRandSize, 0.0f), D3DCOLOR_RGBA(255, 0, 0, 255));
	}
}
