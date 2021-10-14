//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//　tutorial
//　Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "gamemode.h"
#include "main.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//マクロ定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#define GUIDE_NUM (13)

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//前方宣言
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CCamera;
class CPlayer;
class CTutorialStage;
class CTrap;

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CTutorial : public ICGamemode
{
public:
    CTutorial();
    ~CTutorial();

    HRESULT Init(void);    //初期化処理
    void Update(void);     //更新処理
    void Draw(void);       //描画処理
    void Uninit(void);     //終了処理

    static void Load(void);      //テクスチャ読み込み
    static void Unload(void);    //テクスチャ破棄

private:
    static LPDIRECT3DTEXTURE9 m_apTexture[GUIDE_NUM];    //テクスチャへのポインタ
    CCamera* m_pCamera;                                  //カメポインタ
    CPlayer* m_pPlayer;                                  //プレイヤーポインタ
    CTutorialStage* m_pTutorialStage;                    //ステージポインタ
    CTrap* m_Trap;                                       //トラップポインタ
};
#endif
