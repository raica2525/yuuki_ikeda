//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	exprosion.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "main.h"
#include "scene2d.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CExplosion : public CScene2d
{
public:
    CExplosion();     //コンストラクタ
    ~CExplosion();    //デストラクタ

    HRESULT Init(void);    //初期化処理
    void Uninit(void);     //終了処理
    void Update(void);     //更新処理
    void Draw(void);       //描画処理

    static HRESULT Load(void);
    static void Unload(void);

    static CExplosion* Create(D3DXVECTOR3 pos, D3DCOLOR col);    //ポリゴン生成処理

private:
    static LPDIRECT3DTEXTURE9 m_pTexture;    // テクスチャへのポインタ
    int m_nLife;
};

#endif
