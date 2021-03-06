//=============================================================================
//
// スタートボタン処理[startbutton.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _STARTBUTTON_H_
#define _STARTBUTTON_H_
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "button.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CStartButton :public CButton
{
public:
	CStartButton();
	~CStartButton();
	static HRESULT Load(void);
	static void Unload(void);
	static CStartButton * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Push(void);
	void Select(void);
	void Unselect(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		// テクスチャへのポインタ
	D3DXVECTOR3 m_DefaultSize;
};
#endif