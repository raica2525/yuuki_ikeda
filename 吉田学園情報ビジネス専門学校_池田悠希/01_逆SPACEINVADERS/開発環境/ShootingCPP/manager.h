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
class CInputKeyboard;
class CInputMouse;
class CSound;
class CNumber;
class CLife;
class CTitle;
class CFade;
class CResult;
class CCursol;
class CTutorial;
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CManager
{
public:
    CManager();     //コンストラクタ
    ~CManager();    //デストラクタ

    typedef enum
    {
        GAMEMODE_TITLE = 0,
        GAMEMODE_TUTORIAL,
        GAMEMODE_MAIN,
        GAMEMODE_RESULT,
        GAMEMODE_MAX
    } GAMEMODE;

    HRESULT Init(HWND hWnd, bool bWindow, HINSTANCE hInstance);    //初期化関数
    void Uninit(void);                                             //終了関数
    void Update(void);                                             //更新関数
    void Draw(void);                                               //描画関数
    static CRenderer* GetRenderer(void);                           //ゲッター
    static CInputKeyboard* GetInputKey(void);
    static CInputMouse* GetInputMouse(void);
    static CSound* GetSound(void);
    static void LoadTextures(void);
    static void UnloadTextures(void);
    static GAMEMODE GetGamemode(void);
    static CTitle* GetTitle(void);
    static void SetGamemode(GAMEMODE nextMode);
    static CFade* GetFade(void);
    static CResult* GetResult(void);
    static void KillFade(void);
    static void GameOver(void);
    static bool GetAlive(void);
    static void SetAlive(bool bAlive);
    static CTutorial* GetTutorial(void);

private:
    static CRenderer* m_pRenderer;    //レンダラのポインタ
    static GAMEMODE m_gamemode;
    static LPDIRECT3DTEXTURE9 m_pTextureGameOver[2];
    static CInputKeyboard* m_pInputKey;    //インプットのポインタ
    static CInputMouse* m_pInputMouse;
    static CSound* m_pSound;
    static CLife* m_pLife;
    static CTitle* m_pTitle;
    static CFade* m_pFade;
    static CResult* m_pResult;
    static int m_FrameCount;
    static int m_nCountSpawn;
    static bool m_bAlive;
    static CTutorial* m_pTutorial;
};

#endif
