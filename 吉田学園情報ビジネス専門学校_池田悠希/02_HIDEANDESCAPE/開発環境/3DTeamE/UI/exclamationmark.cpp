//=============================================================================
//
// !�}�[�N���� [exclamationmark.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "exclamationmark.h"
#include "renderer.h"
#include "manager.h"

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CExclamationMark::m_pTexture = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CExclamationMark::CExclamationMark()
{
	m_pos = ZEROVECTOR3;
	m_rot = ZEROVECTOR3;
	m_size = ZEROVECTOR3;
	m_col = D3DCOLOR_RGBA(255, 255, 255, 255);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CExclamationMark::~CExclamationMark()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CExclamationMark::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		EXCLAMATIONMARK_TEXTURE,								// �t�@�C���̖��O
		&m_pTexture);								// �ǂݍ��ރ������[
	return S_OK;
}

//=============================================================================
// �e�N�X�`���j���֐�
//=============================================================================
void CExclamationMark::Unload(void)
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
CExclamationMark * CExclamationMark::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	CExclamationMark* pExclamationMark = NULL;
	pExclamationMark = new CExclamationMark;
	pExclamationMark->m_pos = pos;
	pExclamationMark->m_rot = rot;
	pExclamationMark->m_size = size;
	pExclamationMark->Init();

	return pExclamationMark;
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CExclamationMark::Init(void)
{
	CBillboard::Init();
	SetPos(m_pos);
	SetSize(m_size);
	SetColor(m_col);
	BindTexture(m_pTexture);
	return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CExclamationMark::Uninit(void)
{
	CBillboard::Uninit();
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CExclamationMark::Update(void)
{
	CBillboard::Update();

	//�e�N�X�`���̃Z�b�g
	SetTex(
		0.0f,
		0.0f,
		1.0f,
		1.0f);
}

//=============================================================================
// �`��֐�
//=============================================================================
void CExclamationMark::Draw(void)
{
	CBillboard::Draw();
}
