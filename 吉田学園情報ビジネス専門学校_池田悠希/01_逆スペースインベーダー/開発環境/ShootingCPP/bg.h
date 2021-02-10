//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	bg.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

#ifndef _BG_H_
#define _BG_H_
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "main.h"
#include "scene.h"

class CScene2d;
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CBg : public CScene
{
public:
    CBg();     //コンストラクタ
    ~CBg();    //デストラクタ

    static HRESULT Load(void);
    static void Unload(void);
    static CBg* Create();    //ポリゴン生成処理

    HRESULT Init();       //初期化処理
    void Uninit(void);    //終了処理
    void Update(void);    //更新処理
    void Draw(void);      //描画処理

private:
    CScene2d* m_apScene2d[NUM_BG_LAYER];
    static LPDIRECT3DTEXTURE9 m_apTexture[NUM_BG_LAYER];    // テクスチャへのポインタ
    D3DXVECTOR2 m_TexPos[NUM_BG_LAYER][NUM_VERTEX];
};

#endif
