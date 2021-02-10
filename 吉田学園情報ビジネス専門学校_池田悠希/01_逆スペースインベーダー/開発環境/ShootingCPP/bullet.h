//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	bullet.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

#ifndef _BULLET_H_
#define _BULLET_H_
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "main.h"
#include "scene2d.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CBullet : public CScene2d
{
public:
    CBullet();     //コンストラクタ
    ~CBullet();    //デストラクタ

    HRESULT Init(void);    //初期化処理
    void Uninit(void);     //終了処理
    void Update(void);     //更新処理
    void Draw(void);       //描画処理
    static HRESULT Load(void);
    static void Unload(void);

    static void Create(D3DXVECTOR3 pos, D3DXVECTOR3 move);    //ポリゴン生成処理

private:
    static LPDIRECT3DTEXTURE9 m_pTexture;    // テクスチャへのポインタ
    bool m_bHit;
    D3DXVECTOR3 m_move;
};

#endif
