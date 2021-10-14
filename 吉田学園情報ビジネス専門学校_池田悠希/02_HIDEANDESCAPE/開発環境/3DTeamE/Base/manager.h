//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	manager.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#ifndef _MANAGER_H_
#define _MANAGER_H_

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "main.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//マクロ定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#define ZEROVECTOR3 D3DXVECTOR3(0.0f, 0.0f, 0.0f)

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//前方宣言
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CRenderer;
class CInput;
class CCamera;
class CPlayer;
class CFade;
class CModel;
class CAnimation;
class CInputJoystick;
class ICGamemode;
class CWeaponSelect;
class CSound;
class CPause;
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CManager
{
public:
    //モードタイプ
    typedef enum
    {
        MODE_TITLE = 0,
        MODE_TUTORIAL,
        MODE_WEAPONSELECT,
        MODE_MAP01,
        MODE_MAP02,
        MODE_MAP03,
        MODE_MAP04,
        MODE_SELECT,
        MODE_RESULT,
        MODE_MAX
    } GAMEMODE;
    //ウェポンタイプ
    typedef enum
    {
        WEAPONS_MODE_NONE = -1,
        WEAPONS_MODE_AR,
        WEAPONS_MODE_HG,
        WEAPONS_MODE_MAX
    } WEAPONS_MODE;

    CManager();     //コンストラクタ
    ~CManager();    //デストラクタ

    HRESULT Init(HWND hWnd, bool bWindow, HINSTANCE hInstance);    //初期化関数
    void Uninit(void);                                             //終了関数
    void Update(void);                                             //更新関数
    void Draw(void);                                               //描画関数

    //ゲッター関数
    static CRenderer* GetRenderer(void);
    static CInput* GetInputKey(void);
    static CInput* GetInputMou(void);
    static CInputJoystick* GetInputJoystick(void);
    static CCamera* GetCamera(void);
    static CPlayer* GetPlayer(void);
    static CModel* GetStageModel(void);
    static WEAPONS_MODE GetWeaponsMode(void);
    static CSound* GetSound(void);
    static GAMEMODE GetMode(void);
    static CFade* GetFade(void);

    //セッター関数
    static void SetWeaponsMode(WEAPONS_MODE WeaponsMode);
    static void SetStageModel(CModel* pModel);
    static void SetPlayer(CPlayer* pPlayer);
    static void BindCamera(CCamera* pCamera);
    static void SetMode(GAMEMODE mode);

    static void LoadFile(void);
    static void UnloadFile(void);
    static void EndPause(void);

private:
    //オブジェクト保持用ポインタ
    static CRenderer* m_pRenderer;
    static CInput* m_pInputKey;
    static CInput* m_pInputMou;
    static CCamera* m_pCamera;
    static CPlayer* m_pPlayer;
    static CSound* m_pSound;
    static CModel* m_pStageModel;
    static ICGamemode* m_pGamemode;
    static CAnimation* m_pAnimation;
    static CInputJoystick* m_pInputJoystick;
    static CPause* m_pPause;
    static CFade* m_pFade;

    static GAMEMODE m_mode;               //ゲームモード
    static WEAPONS_MODE m_WeaponsMode;    //ウェポンタイプ
};

#endif
