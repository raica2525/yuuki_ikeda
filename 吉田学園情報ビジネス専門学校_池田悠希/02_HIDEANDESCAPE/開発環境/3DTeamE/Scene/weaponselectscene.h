//=============================================================================
//
// ����I����ʔw�i����[weaponselectscene.h]
// Author : ��K������
//
//=============================================================================
#ifndef _WEAPONSELECTSCENE_H_
#define _WEAPONSELECTSCENE_H_
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "object2d.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CWeaponSelectScene :public CObject2D
{
public:
	CWeaponSelectScene();
	~CWeaponSelectScene();
	static HRESULT Load(void);
	static void Unload(void);
	static CWeaponSelectScene * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		// �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3				m_pos;					// �|���S���̈ʒu
	D3DXVECTOR3				m_size;
	D3DCOLOR				m_col;
	D3DXVECTOR2 m_texpos[NUM_VERTEX];
};
#endif