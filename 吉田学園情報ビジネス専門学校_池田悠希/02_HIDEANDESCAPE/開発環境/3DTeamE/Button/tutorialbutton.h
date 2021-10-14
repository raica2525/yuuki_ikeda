//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	tutorialbutton.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#ifndef _TUTORIALBUTTON_H_
#define _TUTORIALBUTTON_H_

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "button.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CTutorialButton :public CButton
{
public:
	CTutorialButton();
	~CTutorialButton();

	HRESULT Init(void);	//初期化処理

	static CTutorialButton* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	//生成処理

	static HRESULT Load(void);	//テクスチャ読込処理
	static void Unload(void);	//テクスチャ破棄処理

	void Push(void);	//押されたときの処理
	void Select(void);	//選ばれたときの処理
	void Unselect(void);//選ばれていないときの処理

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		// テクスチャへのポインタ
	D3DXVECTOR3 m_DefaultSize;					//デフォルトの大きさ
};
#endif