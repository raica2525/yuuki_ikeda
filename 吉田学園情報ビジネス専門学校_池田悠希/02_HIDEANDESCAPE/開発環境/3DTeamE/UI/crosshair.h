//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	crosshair.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#ifndef _CROSSHAIR_H_
#define _CROSSHAIR_H_

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "main.h"
#include "object.h"
#include "object2d.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//マクロ定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#define CROSSHAIR_PARTS_COUNT (4)
#define MIN_SPREAD_WALK (80)
#define MIN_SPREAD_STOP (30)
#define ADD_SPREAD_HG (35.0f)
#define ADD_SPREAD_AR (25.0f)

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CCrosshair : public CObject
{
public:
    CCrosshair();
    ~CCrosshair();

    HRESULT Init(void);    //初期化処理
    void Uninit(void);     //終了処理
    void Update(void);     //更新処理
    void Draw(void);       //描画処理

    static CCrosshair* Create(float fMinSpread);    //生成処理

    static void Load(void);      //テクスチャ読み込み処理
    static void Unload(void);    //テクスチャ破棄

    void AddSpread(float fValue);           //拡散追加
    void SetMinSpread(float fMinSpread);    //拡散最小値設定
    float GetSpread(void);                  //拡散取得

private:
    static LPDIRECT3DTEXTURE9 m_pTexture;              // テクスチャへのポインタ
    CObject2D* m_apObject2d[CROSSHAIR_PARTS_COUNT];    //クロスヘアのパーツへのポインタ
    float m_fSpread;                                   //拡散
    float m_fMinSpread;                                //拡散最小値
};

#endif
