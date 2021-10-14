//=============================================================================
//
// ��@�@���� [uav.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "monitor.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "countdown.h"

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CMonitor::m_pTexture = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMonitor::CMonitor() :CObject2D(3)
{
	D3DXVECTOR3	m_pos = ZEROVECTOR3;
	D3DXVECTOR3	m_size = ZEROVECTOR3;
	D3DCOLOR	m_col = D3DCOLOR_RGBA(255, 255, 255, 255);
	m_nCounterAnim = 0;				//�A�j���J�E���^
	m_nPatternAnim = 0;				//�A�j���p�^�[��
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_texpos[nCount] = D3DXVECTOR2(0.0f, 0.0f);
	}
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMonitor::~CMonitor()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CMonitor::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		"Data/Texture/monitor.png",								// �t�@�C���̖��O
		&m_pTexture);								// �ǂݍ��ރ������[
	return S_OK;
}

//=============================================================================
// �e�N�X�`���j���֐�
//=============================================================================
void CMonitor::Unload(void)
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
CMonitor * CMonitor::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CMonitor* pMonitor = NULL;
	pMonitor = new CMonitor;
	pMonitor->m_pos = pos;
	pMonitor->m_size = size;
	pMonitor->Init();

	return pMonitor;
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CMonitor::Init(void)
{
	SetPos(m_pos);
	SetSize(m_size);
	BindTexture(m_pTexture);	//�e�N�X�`���̊��蓖��
	//�T�E���h�̎擾
	CSound * pSound = CManager::GetSound();
	pSound->StopSound();
	pSound->PlaySound(CSound::SOUND_LABEL_SE_KEYBOARD);
	CObject2D::Init();
	return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CMonitor::Uninit(void)
{
	CObject2D::Uninit();
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CMonitor::Update(void)
{
	//�T�E���h�̎擾
	CSound * pSound = CManager::GetSound();
	//�J�E���g�C���N�������g
	m_nCounterAnim++;

	//�J�E���g��4�ȏ�ɂȂ����ꍇ
	if (m_nCounterAnim > 20)
	{
		//�J�E���g��0�ɂ���
		m_nCounterAnim = 0;

		//�p�^�[���̃C���N�������g
		m_nPatternAnim++;
		//�p�^�[����13�ɂȂ����ꍇ
		if (m_nPatternAnim > 9)
		{
			pSound->StopSound();
			pSound->PlaySound(CSound::SOUND_LABEL_SE_MAPEXPLOSION);
			pSound->PlaySound(CSound::SOUND_LABEL_SE_ALARM);
			pSound->PlaySound(CSound::SOUND_LABEL_BGM_LASTMAP);
			CCountDown::Create(60, D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 - 200, 0.0f), D3DXVECTOR3(200.0f, 100.0f, 100.0f));
			//�I��
			Uninit();
			return;
		}
	}

	m_texpos[0] = D3DXVECTOR2(m_nPatternAnim * 0.1f, 0.0f);
	m_texpos[1] = D3DXVECTOR2(m_nPatternAnim * 0.1f + 0.1f, 0.0f);
	m_texpos[2] = D3DXVECTOR2(m_nPatternAnim * 0.1f, 1.0f);
	m_texpos[3] = D3DXVECTOR2(m_nPatternAnim * 0.1f + 0.1f, 1.0f);

	SetTexPos(m_texpos);
}

//=============================================================================
// �`��֐�
//=============================================================================
void CMonitor::Draw(void)
{
	CObject2D::Draw();
}

