//=============================================================================
//
// �r���{�[�h [billboard.h]
// Author : ��K������
//
//=============================================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "model.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CBillboard :public CObject
{
public:
	CBillboard();
	~CBillboard();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPos(D3DXVECTOR3 pos);
	void SetSize(D3DXVECTOR3 size);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);
	void SetTex(float fTexX, float fTexY, float fTexX2, float fTexY2);
	void SetColor(D3DXCOLOR col);
private:
	LPDIRECT3DTEXTURE9		m_pTexture;		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX m_mtxWorld; //�s��v�Z�p
	D3DXVECTOR3 m_pos;

	D3DXVECTOR3 m_size;
	D3DXCOLOR m_col;
	float m_fTexX;
	float m_fTexY;
	float m_fTexX2;
	float m_fTexY2;
};
#endif