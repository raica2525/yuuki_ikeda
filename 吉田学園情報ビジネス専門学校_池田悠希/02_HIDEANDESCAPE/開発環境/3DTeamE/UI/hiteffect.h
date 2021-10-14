//=============================================================================
//
// �q�b�g�G�t�F�N�g [hiteffect.h]
// Author : ��K������
//
//=============================================================================
#ifndef _HITEFFECT_H_
#define _HITEFFECT_H_
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "model.h"
#include "billboard.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define HITEFFECT_TEXTURE 	"Data/Texture/hiteffect.png"	//�����e�N�X�`���̕ۑ���
#define HITEFFECT_SPEED 2.5f
//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CHitEffect :public CBillboard
{
public:
	CHitEffect();
	~CHitEffect();
	static HRESULT Load(void);
	static void Unload(void);
	static CHitEffect * Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void HitEffectCreate(D3DXVECTOR3 pos,D3DXVECTOR3 size, D3DCOLOR col);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		// �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_size;
	D3DCOLOR m_col;
	int m_nLife;
};
#endif