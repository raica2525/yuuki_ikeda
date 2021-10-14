//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	result.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

#ifndef _RESULT_H_
#define _RESULT_H_
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "main.h"
#include "polygon.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CResult : public CPolygon
{
public:
    CResult();     //コンストラクタ
    ~CResult();    //デストラクタ

    HRESULT Init(void);    //初期化処理
    void Uninit(void);     //終了処理
    void Draw(void);       //描画処理
    static HRESULT Load(void);
    static void Unload(void);

    static CResult* Create();    //ポリゴン生成処理
    void DrawRanking(void);
    void UpdateRanking(void);

private:
    static LPDIRECT3DTEXTURE9 m_pTexture;    // テクスチャへのポインタ
    LPD3DXFONT m_pFont;
    int m_nTopScore[MAX_RANKING];
    int m_nRank;
};

#endif
