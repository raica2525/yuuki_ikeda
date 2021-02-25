//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
// チュートリアル処理 [tutorial.h]
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "gamemode.h"
#include "main.h"
//*****************************************************************************
//  前方宣言
//*****************************************************************************
class CCamera;
class CPlayer;
class CPolygon3D;
class CTutorialStage;
class CCrosshair;
class CWoodenBox;
class CComputer;
class CWeapons_ui;
class CTrap;
class CClothBox;
class CIronBox;
class CStage01;
class CStage02;
class CStage03;
class CTitleLogo;
class CItem_ui;
class CDamage_ui;
class CBullet_ui;
//*****************************************************************************
// クラス定義
//*****************************************************************************
class CTutorial : public CGamemode
{
  public:
    CTutorial();
    ~CTutorial();

    HRESULT Init(void);
    void Update(void);
    void Draw(void);
    void Uninit(void);
    static void Load(void);
    static void Unload(void);

  private:
    static LPDIRECT3DTEXTURE9 m_apTexture[13];    // テクスチャへのポインタ
    CWeapons_ui* m_pWeaponsUi;           //武器UIのポインタ
    CCamera* m_pCamera;                  //カメポインタ
    CPlayer* m_pPlayer;                  //プレイヤーポインタ
    CTutorialStage* m_pTutorialStage;    //ステージポインタ
    CCrosshair* m_pCrosshair;            //クロスヘッダーポインタ
    CWoodenBox* m_pWoodenBox;            //木箱ポインタ
    CClothBox* m_pClothBox;              //布付き箱ポインタ
    CComputer* m_pComputer;              //コンピュータポインタ
    CTrap* m_Trap;                       //トラップポインタ
    CIronBox* m_pIronBox;
    CStage01* m_pStage01;
    CStage02* m_pStage02;
    CStage03* m_pStage03;
    CTitleLogo* m_pTitleLogo;
    CItem_ui* m_pItemUi;        //回復アイテムUIのポインタ
    CDamage_ui* m_pDamageUi;    //ダメージUIのポインタ
    CBullet_ui* m_pBulletUi;    //弾UIのポインタ
};
#endif
