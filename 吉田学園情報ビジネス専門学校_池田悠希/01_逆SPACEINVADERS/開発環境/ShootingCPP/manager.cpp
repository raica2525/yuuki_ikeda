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
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"
#include "input.h"
#include "inputkeyboard.h"
#include "player.h"
#include "bullet.h"
#include "explosion.h"
#include "sound.h"
#include "bg.h"
#include "enemy.h"
#include "number.h"
#include "score.h"
#include "laser.h"
#include "laserlayer.h"
#include "life.h"
#include "title.h"
#include "fade.h"
#include "result.h"
#include "energy.h"
#include "map.h"
#include "item.h"
#include "inputmouse.h"
#include "cursol.h"
#include "tutorial.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//静的メンバ変数宣言
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CRenderer* CManager::m_pRenderer                   = NULL;
CInputKeyboard* CManager::m_pInputKey              = NULL;
CInputMouse* CManager::m_pInputMouse               = NULL;
CSound* CManager::m_pSound                         = NULL;
CLife* CManager::m_pLife                           = NULL;
CTitle* CManager::m_pTitle                         = NULL;
CFade* CManager::m_pFade                           = NULL;
CResult* CManager::m_pResult                       = NULL;
CTutorial* CManager::m_pTutorial                   = NULL;
CManager::GAMEMODE CManager::m_gamemode            = GAMEMODE_TITLE;
LPDIRECT3DTEXTURE9 CManager::m_pTextureGameOver[2] = {};
int CManager::m_FrameCount                         = 0;
int CManager::m_nCountSpawn                        = 0;
bool CManager::m_bAlive                            = 0;

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//コンストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CManager::CManager()
{
    m_pRenderer = NULL;
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

    m_pSound = new CSound;	//サウンド初期化
    m_pSound->Init(hWnd);
    m_pSound->Play(CSound::BGM);	//BGM再生

    m_pInputKey = new CInputKeyboard;	//キーボード初期化
    m_pInputKey->Init(hInstance, hWnd);
    m_pInputMouse = new CInputMouse;	//マウス初期化
    m_pInputMouse->Init(hInstance, hWnd);
    LoadTextures();						//テクスチャ読込
    m_pTitle  = CTitle::Create();		//タイトル画面生成
	m_pTutorial = CTutorial::Create();	//チュートリアル生成
    m_pResult = CResult::Create();		//リザルト画面生成
    return hResult;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//終了関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CManager::Uninit(void)
{
    CScene::ReleaseAll();    //ポリゴンの終了

    m_pInputKey->Uninit();	//キーボード入力の終了
    delete m_pInputKey;		
    m_pInputKey = NULL;

	m_pInputMouse->Uninit();	//マウス入力の終了
	delete m_pInputMouse;
	m_pInputMouse = NULL;

    m_pRenderer->Uninit();    //レンダラの終了
    delete m_pRenderer;
    m_pRenderer = NULL;

    m_pSound->Uninit();		//サウンドの終了
    delete m_pSound;
    m_pSound = NULL;

	m_pTitle->Uninit();		//タイトル画面終了
	delete m_pTitle;
	m_pTitle = NULL;

	m_pTutorial->Uninit();	//チュートリアル終了
	delete m_pTutorial;
	m_pTutorial = NULL;

	m_pResult->Uninit();	//リザルトの終了
	delete m_pResult;
	m_pResult = NULL;

	if (m_pFade != NULL)
	{
		m_pFade->Uninit();
	}

	

    UnloadTextures();		//テクスチャアンロード
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//更新関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CManager::Update(void)
{
    m_pInputKey->Update();
    m_pInputMouse->Update();
    if(CMap::GetGoal())	//ゴール後の敵のランダムスポーン
    {
        if(m_nCountSpawn++ % ENEMY_SPAWN_CYCLE == 0)
        {
            CEnemy::Create(D3DXVECTOR3((float)SCREEN_WIDTH, (rand() % 7 + 2.5f) * MAP_TILE_SIZE, 0), (CEnemy::TYPE)(rand() % (CEnemy::TYPE_SPRINKLER + 1)));
        }
    }

    if(((CInputKeyboard*)m_pInputKey)->GetKeyTrigger(DIK_RETURN))	//ENTERキーの画面遷移
    {
        switch(m_gamemode)
        {
            case GAMEMODE_TITLE:
                if(!CFade::GetUse())
                {
                    m_nCountSpawn = 0;	//敵のランダムスポーン用のカウンタ
                    CBg::Create();		//背景生成
                    CMap::Create();		//マップ生成
                    CPlayer::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0));	//プレイヤー生成
                    CScore::Create();	//スコア生成
                    m_pFade = CFade::Create(GAMEMODE_TUTORIAL);	//フェード
                }
                break;
            case GAMEMODE_TUTORIAL:
				if (!CFade::GetUse())
				{
					m_pFade = CFade::Create(GAMEMODE_MAIN);//フェード
				}
				break;
            case GAMEMODE_RESULT:
                if(!CFade::GetUse())
                {
                    m_pFade = CFade::Create(GAMEMODE_TITLE);//フェード
                    CScene::ReleaseAll();					//CScene管理しているオブジェクトをすべて破棄
                }
				break;
        }
    }
    if(m_FrameCount > 0)	//ゲームオーバー後のフレーム数カウント
    {
        m_FrameCount++;
        if(m_FrameCount == 300)	//5秒(300フレーム後)にリザルト画面に遷移する
        {
            m_pResult->UpdateRanking();
            m_pFade      = CFade::Create(GAMEMODE_RESULT);
            m_FrameCount = 0;
        }
    }

    m_pRenderer->Update();    //レンダラの更新

#ifdef _DEBUG
	//デバッグモードで敵をスポーンさせる関数
    if(((CInputKeyboard*)m_pInputKey)->GetKeyTrigger(DIK_P))
    {
        POINT point;
        GetCursorPos(&point);
        ScreenToClient(FindWindow(CLASS_NAME, NULL), &point);
        CEnemy::Create(D3DXVECTOR3((float)point.x, (float)point.y, 0), CEnemy::TYPE_NORMAL);
    }
    else if(((CInputKeyboard*)m_pInputKey)->GetKeyTrigger(DIK_O))
    {
        POINT point;
        GetCursorPos(&point);
        ScreenToClient(FindWindow(CLASS_NAME, NULL), &point);
        CEnemy::Create(D3DXVECTOR3((float)point.x, (float)point.y, 0), CEnemy::TYPE_SPRINKLER);
    }

#endif
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//描画関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CManager::Draw(void)
{
    m_pRenderer->Draw();    //レンダラの描画
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//ゲッター関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

CRenderer* CManager::GetRenderer(void)
{
    return m_pRenderer;
}

CInputKeyboard* CManager::GetInputKey(void)
{
    return m_pInputKey;
}

CInputMouse* CManager::GetInputMouse(void)
{
    return m_pInputMouse;
}

CSound* CManager::GetSound(void)
{
    return m_pSound;
}

CTitle* CManager::GetTitle(void)
{
    return m_pTitle;
}

CFade* CManager::GetFade(void)
{
    return m_pFade;
}

CResult* CManager::GetResult(void)
{
	return m_pResult;
}

CManager::GAMEMODE CManager::GetGamemode(void)
{
	return m_gamemode;
}

bool CManager::GetAlive(void)
{
	return m_bAlive;
}

CTutorial* CManager::GetTutorial(void)
{
	return m_pTutorial;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//セッター関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CManager::SetGamemode(GAMEMODE nextMode)
{
	m_gamemode = nextMode;
}

void CManager::SetAlive(bool bAlive)
{
	m_bAlive = bAlive;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//ファイル読み込み関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CManager::LoadTextures(void)
{
    D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "Resources\\gameover.png", &m_pTextureGameOver[0]);
    D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "Resources\\saved.png", &m_pTextureGameOver[1]);
    CExplosion::Load();
    CBullet::Load();
    CPlayer::Load();
    CBg::Load();
    CEnemy::Load();
    CNumber::Load();
    CLaserLayer::Load();
    CTitle::Load();
    CResult::Load();
    CLife::Load();
    CEnergy::Load();
    CMap::Load();
    CItem::Load();
    CCursol::Load();
    CTutorial::Load();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//読み込みデータ破棄処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CManager::UnloadTextures(void)
{
    CBullet::Unload();
    CPlayer::Unload();
    CExplosion::Unload();
    CBg::Unload();
    CEnemy::Unload();
    CNumber::Unload();
    CLaserLayer::Unload();
    CTitle::Unload();
    CResult::Unload();
    CLife::Unload();
    CEnergy::Unload();
    CMap::Unload();
    CItem::Unload();
    CCursol::Unload();
    CTutorial::Unload();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//フェード破棄処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CManager::KillFade(void)
{
	delete m_pFade;
    m_pFade = NULL;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//ゲームオーバー処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CManager::GameOver(void)
{
    CScene2d* pScene2d = CScene2d::Create(4);
    pScene2d->Init();
    if(CMap::GetGoal())	//ゴールしているかいないかで表示するテクスチャを変更
    {
        pScene2d->BindTexture(m_pTextureGameOver[1]);
    }
    else
    {
        pScene2d->BindTexture(m_pTextureGameOver[0]);
    }
    CMap::SetGoal(false);	//ゴールフラグをfalseに
    pScene2d->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0));
    pScene2d->SetSize(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0));
    m_FrameCount = 1;	//リザルトに遷移するまでのカウントスタート
}