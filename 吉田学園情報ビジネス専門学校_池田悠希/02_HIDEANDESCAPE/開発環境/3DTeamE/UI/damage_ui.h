//=============================================================================
//
// �_���[�WUi���� [damage_ui.h]
// Author : ��R�@���H
//
//=============================================================================
#ifndef _DAMAGE_UI_H_
#define _DAMAGE_UI_H_
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "model.h"
#include "object2d.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define DAMAGE_UI_TEXTURE 	"Data/Texture/Blood.png"	//�ǂݍ��ޗp�̃_���[�W�e�N�X�`��
#define TEXTURE_MAX 1
//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CDamage_ui :public CObject2D
{
public:
	CDamage_ui();
	~CDamage_ui();
	static HRESULT Load(void);
	static void Unload(void);
	static CDamage_ui * Create(void);//(D3DXVECTOR3 pos, float frot, D3DXVECTOR3 size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetDamageUi(int nlife);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		// �e�N�X�`���ւ̃|�C���^
	static char *m_cFileName;			//�t�@�C���̖��O

	D3DXVECTOR3 m_pos;
	float m_frot;
	D3DXVECTOR3 m_size;
	D3DCOLOR m_col;


};
#endif