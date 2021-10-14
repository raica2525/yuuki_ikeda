//=============================================================================
//
// �A�C�e��UI���� [item_ui.h]
// Author : ��R�@���H
//
//=============================================================================
#ifndef _ITEM_UI_H_
#define _ITEM_UI_H_
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "model.h"
#include "object2d.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define ITEM_UI_TEXTURE 	"Data/Texture/HealItem.png"	//�ǂݍ��ޗp�̃A�C�e���e�N�X�`��
#define TEXTURE_MAX 1
//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CItem_ui :public CObject2D
{
public:
	CItem_ui();
	~CItem_ui();
	static HRESULT Load(void);
	static void Unload(void);
	static CItem_ui * Create(D3DXVECTOR3 pos);//(D3DXVECTOR3 pos, float frot, D3DXVECTOR3 size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		// �e�N�X�`���ւ̃|�C���^
	static char *m_cFileName;			//�t�@�C���̖��O

	D3DXVECTOR3 m_pos;
	float m_frot;
	D3DXVECTOR3 m_size;
	D3DCOLOR m_col;

};
#endif