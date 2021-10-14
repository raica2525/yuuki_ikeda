//=============================================================================
//
// �g���b�v [trap.h]
// Author : �g�c�I�l
//
//=============================================================================
#ifndef _TRAP_H_
#define _TRAP_H_
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "model.h"
#include "meshfield_cylinder.h"
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
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CTrap :public CMeshCylinder
{
public:
	CTrap();
	~CTrap();

	static CTrap* Create(D3DXVECTOR3 Startpos,D3DXVECTOR3 Endpos);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	BOOL Search(CModel::MODELDATA modeldata, float &fDistanve);
private:

	LPDIRECT3DTEXTURE9		m_pTexture;		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;		//�C���f�b�N�X�o�b�t�@�ւ̃|�C���g
	D3DXMATRIX m_mtxWorld;					//�s��v�Z�p
	CMesh_Cylinder *m_pMeshCylinder;		//���b�V���t�B�[���h�~���̃|�C���g
	D3DXVECTOR3 m_Startpos;					//�X�^�[�g��pos
	D3DXVECTOR3 m_Endpos;					//�I����pos
};
#endif