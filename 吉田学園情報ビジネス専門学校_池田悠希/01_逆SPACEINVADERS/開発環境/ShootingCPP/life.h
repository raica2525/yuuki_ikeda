//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	life.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

#ifndef _LIFE_H_
#define _LIFE_H_
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "main.h"
#include "scene.h"

class CPolygon;
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CLife : public CScene
{
public:
    CLife();     //コンストラクタ
    ~CLife();    //デストラクタ

    static CLife* Create();    //ポリゴン生成処理

    HRESULT Init();       //初期化処理
    void Uninit(void);    //終了処理
    void Update(void);    //更新処理
    void Draw(void);      //描画処理

    void AddLife(int nLife);
    int GetLife(void);
    static HRESULT Load(void);
    static void Unload(void);

private:
    CPolygon* m_apPolygon[NUM_GAUGE_LAYER];
    int m_nLife;
    static LPDIRECT3DTEXTURE9 m_pTexture;
};

#endif
