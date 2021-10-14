//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	laserlayer.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "main.h"
#include "polygon.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CTutorial : public CPolygon
{
public:
	CTutorial();		//コンストラクタ
	~CTutorial();	//デストラクタ

	HRESULT Init(void);	//初期化処理
	static HRESULT Load(void);
	static void Unload(void);

	static CTutorial* Create();	//ポリゴン生成処理

private:
	static LPDIRECT3DTEXTURE9		m_pTexture;		// テクスチャへのポインタ
};

#endif