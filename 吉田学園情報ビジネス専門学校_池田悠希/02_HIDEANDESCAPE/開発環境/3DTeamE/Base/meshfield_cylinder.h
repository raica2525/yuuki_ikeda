//=============================================================================
//
// ���b�V���t�B�[���h_�~�� [meshfield_cylinder.h]
// Author : �g�c�I�l
//
//=============================================================================
#ifndef _MESHFIELD_CYLINDER_H_
#define _MESHFIELD_CYLINDER_H_
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "model.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MESH_X_BLOCK 8				//X�����̃u���b�N��
#define MESH_Y_BLOCK 10				//Y�����̃u���b�N��
#define MESH_VERTEX_NUM ((MESH_X_BLOCK+1)*(MESH_Y_BLOCK+1))								//���_								
#define MESH_INDEX_NUM (((MESH_X_BLOCK+1)*2)*MESH_Y_BLOCK+(MESH_Y_BLOCK-1)*2)	//�C���f�b�N�X
#define MESH_PRIMITIVE_NUM (MESH_X_BLOCK*MESH_Y_BLOCK*2)+((MESH_Y_BLOCK-1)*4)			//�|���S��


//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CMeshCylinder :public CObject
{
public:
	CMeshCylinder();
	~CMeshCylinder();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPos(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);
	void SetSize(D3DXVECTOR3 size);
	void SetColor(D3DXCOLOR col,int fMeshY);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);

	D3DXCOLOR GetColor(int fMeshY);
	D3DXVECTOR3 GetPos(void);
	D3DXVECTOR3 GetRot(void);
	D3DXVECTOR3 GetSize(void);

	void ColorAnimation(void);
private:
	LPDIRECT3DTEXTURE9		m_pTexture;		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;//�C���f�b�N�X�o�b�t�@�ւ̃|�C���g
	D3DXMATRIX m_mtxWorld; //�s��v�Z�p
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_size;
	D3DXCOLOR m_col[MESH_Y_BLOCK+1];
	bool m_bColAnima[MESH_Y_BLOCK+1];
};
#endif