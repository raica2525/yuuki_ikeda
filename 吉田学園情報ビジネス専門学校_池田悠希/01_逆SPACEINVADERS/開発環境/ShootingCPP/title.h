//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	laserlayer.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

#ifndef _TITLE_H_
#define _TITLE_H_
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "main.h"
#include "polygon.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CTitle : public CPolygon
{
public:
    CTitle();     //コンストラクタ
    ~CTitle();    //デストラクタ

    HRESULT Init(void);    //初期化処理
    static HRESULT Load(void);
    static void Unload(void);

    static CTitle* Create();    //ポリゴン生成処理

private:
    static LPDIRECT3DTEXTURE9 m_pTexture;    // テクスチャへのポインタ
};

#endif
