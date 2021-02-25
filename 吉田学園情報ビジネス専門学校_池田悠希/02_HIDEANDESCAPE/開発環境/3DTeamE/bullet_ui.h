//=============================================================================
//
// 弾Ui処理 [bullet_ui.h]
// Author : 若山　言稀
//
//=============================================================================
#ifndef _BULLET_UI_H_
#define _BULLET_UI_H_
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "model.h"
#include "object2d.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BULLET_UI_TEXTURE 	"Data/Texture/bullet2.png"	//読み込む用の弾テクスチャ
#define BULLET_TEXTURE_MAX 1
//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CBullet_ui :public CObject2D
{
public:
	CBullet_ui();
	~CBullet_ui();
	static HRESULT Load(void);
	static void Unload(void);
	static CBullet_ui * Create(D3DXVECTOR3 pos);//(D3DXVECTOR3 pos, float frot, D3DXVECTOR3 size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture[BULLET_TEXTURE_MAX];		// テクスチャへのポインタ
	static char *m_cFileName[BULLET_TEXTURE_MAX];			//ファイルの名前

	D3DXVECTOR3 m_pos;
	float m_frot;
	D3DXVECTOR3 m_size;
	D3DCOLOR m_col;

};
#endif