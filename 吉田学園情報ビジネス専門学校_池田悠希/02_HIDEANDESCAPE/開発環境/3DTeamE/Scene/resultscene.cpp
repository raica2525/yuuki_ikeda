//=============================================================================
//
// ���U���g��ʔw�i���� [resultscene.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "resultscene.h"
#include "manager.h"
#include "renderer.h"
#include "fade.h"
#include "input.h"
#include "inputkeyboard.h"

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CResultScene::m_pTexture = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CResultScene::CResultScene()
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
CResultScene::~CResultScene()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CResultScene::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		"Data/Texture/result.png",								// �t�@�C���̖��O
		&m_pTexture);								// �ǂݍ��ރ������[
	return S_OK;
}

//=============================================================================
// �e�N�X�`���j���֐�
//=============================================================================
void CResultScene::Unload(void)
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
CResultScene * CResultScene::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CResultScene* pResultScene = NULL;
	pResultScene = new CResultScene;
	pResultScene->m_pos = pos;
	pResultScene->m_size = size;
	pResultScene->Init();

	return pResultScene;
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CResultScene::Init(void)
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
void CResultScene::Uninit(void)
{
	CObject2D::Uninit();
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CResultScene::Update(void)
{
	CInputKeyboard* pInputKeyboard;
	pInputKeyboard = (CInputKeyboard*)CManager::GetInputKey();

	if (pInputKeyboard->GetKeyTrigger(DIK_RETURN))
	{
		CManager::GetFade()->SetFade(CManager::MODE_TITLE);
	}
}

//=============================================================================
// �`��֐�
//=============================================================================
void CResultScene::Draw(void)
{
	CObject2D::Draw();
}
