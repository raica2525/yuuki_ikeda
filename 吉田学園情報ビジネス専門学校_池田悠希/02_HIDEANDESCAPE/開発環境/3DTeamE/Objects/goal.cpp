//=============================================================================
//
// �S�[������ [trap.cpp]
// Author : �g�c�I�l
//
//=============================================================================


//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "goal.h"
#include "explosion.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "fade.h"
#include "sound.h"

//*****************************************************************************
//�@�ÓI�����o�ϐ��̏�����
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGoal::CGoal()
{
	m_GameMode = {};
	m_pTexture = NULL;
	SetObjType(OBJTYPE_NONE);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGoal::~CGoal()
{
}

//=============================================================================
// �����֐�
//=============================================================================
CGoal * CGoal::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, CManager::GAMEMODE Mode)
{
	CGoal* pGoal = NULL;
	pGoal = new CGoal;
	pGoal->SetPos(pos);
	pGoal->SetRot(rot);
	pGoal->SetSize(size);
	pGoal->m_GameMode = Mode;
	for (int nMesh = 0; nMesh < MESH_Y_BLOCK + 1; nMesh++)
	{
		pGoal->SetColor(D3DXCOLOR(col.r, col.g, col.b, nMesh*0.1f), nMesh);
	}

	pGoal->Init();
	return pGoal;
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CGoal::Init(void)
{
	CMeshCylinder::Init();
	return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CGoal::Uninit(void)
{
	CMeshCylinder::Uninit();
	Release();
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CGoal::Update(void)
{
	//���b�V���̃J���[�ύX
	CMeshCylinder::ColorAnimation();
	//�S�[������
	HitGoal();
	//���b�V���̃A�b�v�f�[�g
	CMeshCylinder::Update();
}

//=============================================================================
// �`��֐�
//=============================================================================
void CGoal::Draw(void)
{
	CMeshCylinder::Draw();
}

void CGoal::HitGoal(void)
{
	D3DXVECTOR3 Playerpos = CManager::GetPlayer()->GetPos();
	if (GetPos().x+(GetSize().x/2)>Playerpos.x
		&&GetPos().x - (GetSize().x / 2)<Playerpos.x
		&&GetPos().z + (GetSize().z / 2)> Playerpos.z
		&&GetPos().z - (GetSize().z / 2)< Playerpos.z)
	{
		//�T�E���h�̎擾
		CSound * pSound = CManager::GetSound();
		pSound->StopSound();
		CManager::GetFade()->SetFade(m_GameMode);
		Uninit();
	}
}

