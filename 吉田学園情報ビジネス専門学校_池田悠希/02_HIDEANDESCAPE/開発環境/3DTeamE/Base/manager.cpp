//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	manager.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "manager.h"

#include "animation.h"
#include "assaultbutton.h"
#include "bullet_ui.h"
#include "camera.h"
#include "clear.h"
#include "continuebutton.h"
#include "crosshair.h"
#include "damage_ui.h"
#include "debug.h"
#include "exclamationmark.h"
#include "explosion.h"
#include "explosion2.h"
#include "fade.h"
#include "handgunbutton.h"
#include "heavy_enemy.h"
#include "hiteffect.h"
#include "input.h"
#include "inputkeyboard.h"
#include "inputmouse.h"
#include "item.h"
#include "item_ui.h"
#include "light.h"
#include "light_enemy.h"
#include "map01.h"
#include "map02.h"
#include "map03.h"
#include "map04.h"
#include "mission.h"
#include "model.h"
#include "monitor.h"
#include "object.h"
#include "object2d.h"
#include "object3d.h"
#include "pause.h"
#include "player.h"
#include "polygon3d.h"
#include "question.h"
#include "renderer.h"
#include "result.h"
#include "resultscene.h"
#include "retrybutton.h"
#include "returntitlebutton.h"
#include "sound.h"
#include "stage01.h"
#include "stage02.h"
#include "stage03.h"
#include "stage04.h"
#include "startbutton.h"
#include "title.h"
#include "titlelogo.h"
#include "trap.h"
#include "tutorial.h"
#include "tutorialbutton.h"
#include "tutorialstage.h"
#include "uav.h"
#include "weapons_ui.h"
#include "weaponselect.h"
#include "weaponselectscene.h"
#include "number.h"
#include "countdown.h"
#include "blood.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//静的メンバ変数宣言
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CRenderer* CManager::m_pRenderer               = NULL;
CInput* CManager::m_pInputKey                  = NULL;
CInput* CManager::m_pInputMou                  = NULL;
CCamera* CManager::m_pCamera                   = NULL;
CPlayer* CManager::m_pPlayer                   = NULL;
CModel* CManager::m_pStageModel                = NULL;
CFade* CManager::m_pFade                       = NULL;
CManager::GAMEMODE CManager::m_mode            = {};
CSound* CManager::m_pSound                     = NULL;
ICGamemode* CManager::m_pGamemode              = NULL;
CManager::WEAPONS_MODE CManager::m_WeaponsMode = WEAPONS_MODE_NONE;
CInputJoystick* CManager::m_pInputJoystick     = NULL;
CPause* CManager::m_pPause                     = NULL;

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//コンストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CManager::CManager()
{
    m_pRenderer   = NULL;
    m_WeaponsMode = WEAPONS_MODE_AR;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//デストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CManager::~CManager()
{
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//初期化関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
HRESULT CManager::Init(HWND hWnd, bool bWindow, HINSTANCE hInstance)
{
    HRESULT hResult = NULL;
    m_pRenderer     = new CRenderer;                    //レンダラを生成
    hResult         = m_pRenderer->Init(hWnd, true);    //レンダラを初期化

    //ライトの生成
    CLight* pLight = NULL;
    pLight         = new CLight;
    pLight->Init();

    //キーボード入力
    m_pInputKey = new CInputKeyboard;
    m_pInputKey->Init(hInstance, hWnd);

    //マウス入力
    m_pInputMou = new CInputMouse;
    m_pInputMou->Init(hInstance, hWnd);

    //乱数のシード値設定
    srand((unsigned int)time(0));

    //サウンドの生成
    if(m_pSound == NULL)
    {
        m_pSound = new CSound;
    }

    //サウンドの初期化
    m_pSound->Init(hWnd);

    //フェード生成
    m_pFade = CFade::Create();

    //ファイル読み込み
	LoadFile();

    CDebug::Init();         //デバッグ情報の初期化処理
    SetMode(MODE_TITLE);    //モード設定

    return hResult;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//終了関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CManager::Uninit(void)
{
    //シーンの終了
    CObject::ReleaseAll();

    //デバッグ情報の終了
    CDebug::Uninit();

    //ゲームモード終了
    if(m_pGamemode != NULL)
    {
        m_pGamemode->Uninit();
		SAFE_DELETE(m_pGamemode);
    }

    //フェード終了
    if(m_pFade != NULL)
    {
        m_pFade->Uninit();
		SAFE_DELETE(m_pFade);
    }

    //入力の終了
    if(m_pInputKey != NULL)
    {
        m_pInputKey->Uninit();
		SAFE_DELETE(m_pInputKey);
    }
    if(m_pInputMou != NULL)
    {
        m_pInputMou->Uninit();
		SAFE_DELETE(m_pInputMou);
    }

    //カメラの終了
    if(m_pCamera != NULL)
    {
        m_pCamera->Uninit();
		SAFE_DELETE(m_pCamera);
    }

	//レンダラの終了
    if(m_pRenderer != NULL)
    {
        m_pRenderer->Uninit();
		SAFE_DELETE(m_pRenderer);
    }

    //サウンドの破棄
    if(m_pSound != NULL)
    {
        m_pSound->Uninit();
		SAFE_DELETE(m_pSound);
    }

    //読み込んだファイルのアンロード
    UnloadFile();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//更新関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CManager::Update(void)
{
    //入力の更新
    if(m_pInputKey != NULL)
    {
        m_pInputKey->Update();
    }

    if(m_pInputMou != NULL)
    {
        m_pInputMou->Update();
    }

    //レンダラの更新
    if(m_pRenderer != NULL && m_pPause == NULL)
    {
        m_pRenderer->Update();
    }

    //フェード更新
    if(m_pFade != NULL)
    {
        m_pFade->Update();
    }

    if(((CInputKeyboard*)m_pInputKey)->GetKeyTrigger(DIK_ESCAPE))
    {
        //ポーズできるときはポーズ、ポーズ中ならポーズ終了、どちらでもないときはアプリケーションを終了する
        if(m_mode != MODE_TITLE && m_mode != MODE_WEAPONSELECT && m_mode != MODE_RESULT && m_pPause == NULL)
        {
            if(m_pPlayer->GetLife() > 0)
            {
                m_pPause = CPause::Create();
            }
        }
        else if(m_pPause != NULL)
        {
            EndPause();
        }
        else
        {
            DestroyWindow(FindWindow(CLASS_NAME, NULL));
        }
    }

    //ポーズされているときはポーズ画面更新　そうでないときはメインのゲームモードを更新
    if(m_pPause != NULL)
    {
        m_pPause->Update();
    }
    else
    {
        m_pGamemode->Update();
    }
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//描画関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CManager::Draw(void)
{
    //メインのゲームモードの描画処理
    m_pGamemode->Draw();

    //レンダラの描画
    if(m_pRenderer != NULL)
    {
        m_pRenderer->Draw();
    }
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//ゲッター関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CRenderer* CManager::GetRenderer(void)
{
    return m_pRenderer;
}

CInput* CManager::GetInputKey(void)
{
    return m_pInputKey;
}

CInput* CManager::GetInputMou(void)
{
    return m_pInputMou;
}

CInputJoystick* CManager::GetInputJoystick(void)
{
    return m_pInputJoystick;
}

CCamera* CManager::GetCamera(void)
{
    return m_pCamera;
}

CPlayer* CManager::GetPlayer(void)
{
    return m_pPlayer;
}

CModel* CManager::GetStageModel(void)
{
    return m_pStageModel;
}

CManager::WEAPONS_MODE CManager::GetWeaponsMode(void)
{
    return m_WeaponsMode;
}

CFade* CManager::GetFade(void)
{
    return m_pFade;
}

CManager::GAMEMODE CManager::GetMode(void)
{
    return m_mode;
}

CSound* CManager::GetSound(void)
{
    return m_pSound;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//セッター関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CManager::SetWeaponsMode(const WEAPONS_MODE WeaponsMode)
{
    m_WeaponsMode = WeaponsMode;
}

void CManager::SetStageModel(CModel* const pModel)
{
    m_pStageModel = pModel;
}

void CManager::SetPlayer(CPlayer* const pPlayer)
{
    m_pPlayer = pPlayer;
}

void CManager::BindCamera(CCamera* const pCamera)
{
    m_pCamera = pCamera;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//ファイルのロード
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CManager::LoadFile(void)
{
    CWeapons_ui::Load();
    CPlayer::Load();
    CCrosshair::Load();
    CLightEnemy::Load();
    CTutorialStage::Load();
    CItem::Load();
    CAnimation::Load();
    CExplosion::Load();
    CExplosion2::Load();
    CMonitor::Load();
    CExclamationMark::Load();
    CQuestion::Load();
    CUav::Load();
    CStage01::Load();
    CStage02::Load();
    CStage03::Load();
    CStage04::Load();
    CTitleLogo::Load();
    CHeavyEnemy::Load();
    CHitEffect::Load();
    CItem_ui::Load();
    CDamage_ui::Load();
    CBullet_ui::Load();
    CStartButton::Load();
    CTutorialButton::Load();
    CAssaultButton::Load();
    CHandgunButton::Load();
    CWeaponSelectScene::Load();
    CResultScene::Load();
    CReturnTitleButton::Load();
    CRetryButton::Load();
    CMission::Load();
    CClear::Load();
    CContinueButton::Load();
    CNumber::Load();
    CCountDown::Load();
    CTutorial::Load();
    CBlood::Load();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//ファイルのアンロード
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CManager::UnloadFile(void)
{
    CWeapons_ui::Unload();
    CPlayer::Unload();
    CLightEnemy::Unload();
    CTutorialStage::Unload();
    CItem::Unload();
    CExplosion::Unload();
    CExplosion2::Unload();
    CMonitor::Unload();
    CExclamationMark::Unload();
    CQuestion::Unload();
    CUav::Unload();
    CStage01::Unload();
    CStage02::Unload();
    CStage03::Unload();
    CStage04::Unload();
    CTitleLogo::Unload();
    CHeavyEnemy::Unload();
    CHitEffect::Unload();
    CItem_ui::Unload();
    CDamage_ui::Unload();
    CBullet_ui::Unload();
    CStartButton::Unload();
    CTutorialButton::Unload();
    CAssaultButton::Unload();
    CHandgunButton::Unload();
    CWeaponSelectScene::Unload();
    CResultScene::Unload();
    CReturnTitleButton::Unload();
    CRetryButton::Unload();
    CMission::Unload();
    CClear::Unload();
    CContinueButton::Unload();
    CNumber::Unload();
    CCountDown::Unload();
    CCrosshair::Unload();
    CTutorial::Unload();
    CBlood::Unload();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//モード切替
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CManager::SetMode(const GAMEMODE mode)
{
    //ポーズ中ならポーズを終了
    EndPause();

    //サウンド終了
    CManager::GetSound()->StopSound();

    //ゲームモードがすでに生成されていれば終了
    if(m_pGamemode != NULL)
    {
        //終了処理
        m_pGamemode->Uninit();
		SAFE_DELETE(m_pGamemode);
    }

    //メンバ変数に代入
    m_mode = mode;

    //切り替え先のゲームモードを設定
    switch(m_mode)
    {
        case MODE_TITLE:
            m_pGamemode = new CTitle;
            break;
        case MODE_TUTORIAL:
            m_pGamemode = new CTutorial;
            break;
        case MODE_WEAPONSELECT:
            m_pGamemode = new CWeaponSelect;
            break;
        case MODE_MAP01:
            m_pGamemode = new CMap01;
            break;
        case MODE_MAP02:
            m_pGamemode = new CMap02;
            break;
        case MODE_MAP03:
            m_pGamemode = new CMap03;
            break;
        case MODE_MAP04:
            m_pGamemode = new CMap04;
            break;
        case MODE_RESULT:
            m_pGamemode = new CResult;
            break;
    }
    //生成したゲームモードの初期化
    m_pGamemode->Init();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//ポーズ終了処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CManager::EndPause(void)
{
    //ポーズ中ならポーズ終了
    if(m_pPause != NULL)
    {
        m_pPause->Uninit();
		SAFE_DELETE(m_pPause);
    }
}
