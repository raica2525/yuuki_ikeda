//=============================================================================
//
//  �S�[�� [goal.h]
// Author : �g�c�I�l
//
//=============================================================================
#ifndef _GOAL_H_
#define _GOAL_H_
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "model.h"
#include "meshfield_cylinder.h"
#include "manager.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CModel;
class CMesh_Cylinder;
class CManager;
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CGoal :public CMeshCylinder
{
public:
	CGoal();
	~CGoal();

	static CGoal* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, CManager::GAMEMODE Mode);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void HitGoal(void);
private:

	LPDIRECT3DTEXTURE9		m_pTexture;		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;		//�C���f�b�N�X�o�b�t�@�ւ̃|�C���g
	D3DXMATRIX m_mtxWorld;					//�s��v�Z�p
	CMesh_Cylinder *m_pMeshCylinder;		//���b�V���t�B�[���h�~���̃|�C���g
	CManager::GAMEMODE m_GameMode;
};
#endif