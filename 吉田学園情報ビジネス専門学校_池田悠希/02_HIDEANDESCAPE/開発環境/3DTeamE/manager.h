//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	manager.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//前方宣言
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CRenderer;
class CInput;
class CCamera;
class CPlayer;
class CTutorialStage;
class CFade;
class CTitle;
class CTutorial;
class CGamemain;
class CModel;
class CAnimation;
class CInputJoystick;
class CMap01;
class CMap02;
class CMap03;
class CMap04;
class CResult;
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
    } MODE;
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
    static CRenderer* GetRenderer(void);                           //ゲッター
    static CInput* GetInputKey(void);
    static CInput* GetInputMou(void);
    static CInputJoystick* GetInputJoystick(void);
    static CCamera* GetCamera(void);
    static CPlayer* GetPlayer(void);
    static CModel* GetStageModel(void);
    static WEAPONS_MODE GetWeaponsMode(void);    //ウェポンステート取得
    static CSound* GetSound(void)
    {
        return m_pSound;
    }
    static void SetWeaponsMode(WEAPONS_MODE WeaponsMode);    //ウェポンステートセット
    static void SetStageModel(CModel* pModel);
    static void SetPlayer(CPlayer* pPlayer);
    static void BindCamera(CCamera* pCamera);
    static void LoadFile(void);
    static void UnloadFiles(void);
    static void SetMode(MODE mode);    // モード切替
    static MODE GetMode(void);
    static CFade* GetFade(void)
    {
        return m_pFade;
    }    // フェードの取得
    static void EndPause(void);

private:
    static CRenderer* m_pRenderer;    //レンダラのポインタ
    static CInput* m_pInputKey;       //インプットのポインタ
    static CInput* m_pInputMou;
    static CCamera* m_pCamera;
    static CPlayer* m_pPlayer;
    static CSound* m_pSound;
    static CModel* m_pStageModel;
    static CFade* m_pFade;            // フェードのポインタ
    static MODE m_mode;               // モードの変数
    static CTitle* m_pTitle;          // タイトルのポインタ
    static CGamemain* m_pGamemain;    // ゲームメインへのポインタ
    static CTutorial* m_pTutorial;    // チュートリアルのポインタ
    static CMap01* m_pMap01;
    static CMap02* m_pMap02;
    static CMap03* m_pMap03;
	static CMap04* m_pMap04;
    static CResult* m_pResult;
    static CWeaponSelect* m_pWeaponSelect;
    static CAnimation* m_pAnimation;
    static CInputJoystick* m_pInputJoystick;
    static WEAPONS_MODE m_WeaponsMode;    //ウェポンタイプ保存
    static CPause* m_pPause;
};

#endif
