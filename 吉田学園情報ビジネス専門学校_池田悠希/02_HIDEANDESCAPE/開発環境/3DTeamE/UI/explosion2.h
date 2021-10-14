//=============================================================================
//
// ����(�p�[�e�B�N��) [explosion2.h]
// Author : ��K������
//
//=============================================================================
#ifndef _EXPLOSION2_H_
#define _EXPLOSION2_H_
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "model.h"
#include "billboard.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define EXPLOSION2_TEXTURE 	"Data/Texture/explosion2.png"	//�����e�N�X�`���̕ۑ���
//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CExplosion2 :public CBillboard
{
public:
	CExplosion2();
	~CExplosion2();
	static HRESULT Load(void);
	static void Unload(void);
	static CExplosion2 * Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		// �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_size;
	D3DCOLOR m_col;
};
#endif