//=============================================================================
//
// ���U���g���� [result.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "result.h"
#include "manager.h"
#include "camera.h"
#include "object.h"
#include "stage03.h"
#include "player.h"
#include "input.h"
#include "inputkeyboard.h"
#include "fade.h"
#include "goal.h"
#include "resultscene.h"
#include "sound.h"
#include "mission.h"
#include "clear.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CResult::CResult()
{
	m_pResultScene = NULL;
	m_pMission = NULL;
	m_pClear = NULL;
	m_nCount = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CResult::~CResult()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CResult::Init(void)
{
	//�T�E���h�̎擾
	CSound * pSound = CManager::GetSound();
	pSound->PlaySound(CSound::SOUND_LABEL_BGM_RESULT);
	while (ShowCursor(true)<0);
	m_pMission = CMission::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 -100, 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT - 100, 0.0f));
	m_pClear = CClear::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT / 2, 0.0f));
	m_nCount = 0;
	return S_OK;
}

//=============================================================================
// �X�V����
//=============================================================================
void CResult::Update(void)
{
	m_nCount++;

	if (m_nCount == 600)
	{
		CManager::GetFade()->SetFade(CManager::MODE_TITLE);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CResult::Draw(void)
{
}

//=============================================================================
// �I������
//=============================================================================
void CResult::Uninit(void)
{
	
}

