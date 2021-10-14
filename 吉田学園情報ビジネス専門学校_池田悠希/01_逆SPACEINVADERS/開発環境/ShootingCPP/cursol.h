//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	cursol.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

#ifndef _CURSOL_H_
#define _CURSOL_H_
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "main.h"
#include "scene.h"

class CPolygon;
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CCursol : public CScene
{
public:
    CCursol();     //コンストラクタ
    ~CCursol();    //デストラクタ

    static CCursol* Create();    //ポリゴン生成処理

    HRESULT Init();       //初期化処理
    void Uninit(void);    //終了処理
    void Update(void);    //更新処理
    void Draw(void);      //描画処理
    static HRESULT Load(void);
    static void Unload(void);

private:
    CPolygon* m_pPolygon;
    static LPDIRECT3DTEXTURE9 m_pTexture;
};

#endif
