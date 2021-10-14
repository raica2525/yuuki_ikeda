//=============================================================================
//
// !�}�[�N [exclamationmark.h]
// Author : ��K������
//
//=============================================================================
#ifndef _EXCLAMATIONMARK_H_
#define _EXCLAMATIONMARK_H_
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "model.h"
#include "billboard.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define EXCLAMATIONMARK_TEXTURE 	"Data/Texture/bikkuri.png"	//�����e�N�X�`���̕ۑ���
//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CExclamationMark :public CBillboard
{
public:
	CExclamationMark();
	~CExclamationMark();
	static HRESULT Load(void);
	static void Unload(void);
	static CExclamationMark * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		// �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_size;
	D3DCOLOR m_col;
};
#endif