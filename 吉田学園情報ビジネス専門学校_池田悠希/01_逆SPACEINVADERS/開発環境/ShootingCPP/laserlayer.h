//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	laserlayer.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

#ifndef _LASERLAYER_H_
#define _LASERLAYER_H_
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "main.h"
#include "polygon.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CLaserLayer : public CPolygon
{
public:
    CLaserLayer();     //コンストラクタ
    ~CLaserLayer();    //デストラクタ

    HRESULT Init(void);    //初期化処理
    void Uninit(void);     //終了処理
    void Update(void);     //更新処理
    void Draw(void);       //描画処理
    static HRESULT Load(void);
    static void Unload(void);

    static CLaserLayer* Create(D3DXVECTOR3 pos, D3DCOLOR col, int nWidth, int Length, float fRot);    //ポリゴン生成処理

private:
    static LPDIRECT3DTEXTURE9 m_pTexture;    // テクスチャへのポインタ
};

#endif
