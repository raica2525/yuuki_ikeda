//=============================================================================
//
// �^�C�g�����S���� [titlelogo.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "titlelogo.h"
#include "manager.h"
#include "renderer.h"

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CTitleLogo::m_pTexture = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTitleLogo::CTitleLogo() : CObject2D(2)
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
CTitleLogo::~CTitleLogo()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CTitleLogo::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		"Data/Texture/titlelogo.png",								// �t�@�C���̖��O
		&m_pTexture);								// �ǂݍ��ރ������[
	return S_OK;
}

//=============================================================================
// �e�N�X�`���j���֐�
//=============================================================================
void CTitleLogo::Unload(void)
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
CTitleLogo * CTitleLogo::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CTitleLogo* pTitleLogo = NULL;
	pTitleLogo = new CTitleLogo;
	pTitleLogo->m_pos = pos;
	pTitleLogo->m_size = size;
	pTitleLogo->Init();

	return pTitleLogo;
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CTitleLogo::Init(void)
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
void CTitleLogo::Uninit(void)
{
	CObject2D::Uninit();
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CTitleLogo::Update(void)
{
	////�J�E���g�C���N�������g
	//m_nCounterAnim++;
	////�J�E���g��4�ȏ�ɂȂ����ꍇ
	//if (m_nCounterAnim > 4)
	//{
	//	//�J�E���g��0�ɂ���
	//	m_nCounterAnim = 0;

	//	//�p�^�[���̃C���N�������g
	//	m_nPatternAnim++;
	//	//�p�^�[����8�ɂȂ����ꍇ
	//	if (m_nPatternAnim > 8)
	//	{
	//		//�I��
	//		Uninit();
	//		return;
	//	}
	//}

	//m_texpos[0] = D3DXVECTOR2(m_nPatternAnim * 0.125f, 0.0f);
	//m_texpos[1] = D3DXVECTOR2(m_nPatternAnim * 0.125f + 0.125f, 0.0f);
	//m_texpos[2] = D3DXVECTOR2(m_nPatternAnim * 0.125f, 1.0f);
	//m_texpos[3] = D3DXVECTOR2(m_nPatternAnim * 0.125f + 0.125f, 1.0f);

	//SetTexPos(m_texpos);
}

//=============================================================================
// �`��֐�
//=============================================================================
void CTitleLogo::Draw(void)
{
	CObject2D::Draw();
}

