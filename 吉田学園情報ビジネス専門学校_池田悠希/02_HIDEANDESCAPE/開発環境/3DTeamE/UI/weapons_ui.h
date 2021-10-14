//=============================================================================
//
// 武装UI処理 [weapons_ui.h]
// Author : 吉田　悠人
//
//=============================================================================
#ifndef _WEAPONS_UI_H_
#define _WEAPONS_UI_H_
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "object2d.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define WEAPONS_UI_AR_TEXTURE 	"Data/Texture/AR_UI.png"	//読み込む用のAR武器テクスチャ
#define WEAPONS_UI_HG_TEXTURE	"Data/Texture/HG_UI.png"	//読み込む用のHG武器テクスチャ
#define WEAPONS_TEXTURE_MAX 2
//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CWeapons_ui :public CObject2D
{
public:
	CWeapons_ui();
	~CWeapons_ui();
	static HRESULT Load(void);
	static void Unload(void);
	static CWeapons_ui * Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Gleams(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture[WEAPONS_TEXTURE_MAX];		// テクスチャへのポインタ
	static char *m_cFileName[WEAPONS_TEXTURE_MAX];			//ファイルの名前

	D3DXVECTOR3 m_pos;
	float m_frot;
	D3DXVECTOR3 m_size;
	D3DCOLOR m_col;
	int nCountCol;
};
#endif