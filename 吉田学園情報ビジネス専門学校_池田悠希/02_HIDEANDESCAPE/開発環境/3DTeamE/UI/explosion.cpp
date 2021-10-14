//=============================================================================
//
// �������� [explosion.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "explosion.h"
#include "manager.h"
#include "renderer.h"
#include "billboard.h"
#include "sound.h"
//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CExplosion::m_pTexture = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CExplosion::CExplosion()
{
	m_pos = ZEROVECTOR3;
	m_rot = ZEROVECTOR3;
	m_size = ZEROVECTOR3;
	m_col = D3DCOLOR_RGBA(255, 255, 255, 255);
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CExplosion::~CExplosion()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CExplosion::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		EXPLOSION_TEXTURE,								// �t�@�C���̖��O
		&m_pTexture);								// �ǂݍ��ރ������[
	return S_OK;
}

//=============================================================================
// �e�N�X�`���j���֐�
//=============================================================================
void CExplosion::Unload(void)
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
CExplosion * CExplosion::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	CExplosion* pExplosion = NULL;
	pExplosion = new CExplosion;
	pExplosion->m_pos = pos;
	pExplosion->m_rot = rot;
	pExplosion->m_size = size;
	pExplosion->Init();

	return pExplosion;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CExplosion::Init(void)
{
	CSound* pSound = CManager::GetSound();
	CBillboard::Init();
	pSound->PlaySoundA(CSound::SOUND_LABEL_SE_TRAP);
	SetPos(m_pos);
	SetSize(m_size);
	SetColor(m_col);
	BindTexture(m_pTexture);
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CExplosion::Uninit(void)
{
	CBillboard::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CExplosion::Update(void)
{
	CBillboard::Update();
	//�J�E���g�C���N�������g
	m_nCounterAnim++;
	//�J�E���g��4�ȏ�ɂȂ����ꍇ
	if (m_nCounterAnim > 4)
	{
		//�J�E���g��0�ɂ���
		m_nCounterAnim = 0;

		//�p�^�[���̃C���N�������g
		m_nPatternAnim++;
		//�p�^�[����8�ɂȂ����ꍇ
		if (m_nPatternAnim > 8)
		{
			//�I��
			Uninit();
			return;
		}
	}
	//�e�N�X�`���Z�b�g
	SetTex(m_nPatternAnim * 0.125f,
		0.0f,
		m_nPatternAnim * 0.125f + 0.125f,
		1.0f);
}

//=============================================================================
// �`��֐�
//=============================================================================
void CExplosion::Draw(void)
{
	CBillboard::Draw();
}
