//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	player.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "player.h"
#include "inputkeyboard.h"
#include "inputmouse.h"
#include "manager.h"
#include "bullet.h"
#include "renderer.h"
#include "sound.h"
#include "laser.h"
#include "life.h"
#include "energy.h"
#include "stdio.h"
#include "number.h"
#include "cursol.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//静的メンバ変数宣言
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture   = NULL;
LPDIRECT3DTEXTURE9 CPlayer::m_pTextureUI = NULL;

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//コンストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CPlayer::CPlayer() : CScene2d(2)
{
    m_pLife       = NULL;
    m_state       = STATE_NORMAL;
    LaserType     = CLaser::LASERTYPE_STRONG_STRAIGHT;
    m_nStateCount = 0;
    m_nCountFrame = 0;
    m_pPolygon    = NULL;
    m_CountNumber = NULL;
    m_pCursol     = NULL;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//デストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CPlayer::~CPlayer()
{
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//初期化処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
HRESULT CPlayer::Init(void)
{
    CScene2d::Init();
    BindTexture(m_pTexture);

    return S_OK;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//終了処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CPlayer::Uninit(void)
{
    if(m_pPolygon != NULL)
    {
        m_pPolygon->Uninit();
    }
    CManager::SetAlive(false);
    CScene2d::Uninit();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//更新処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CPlayer::Update(void)
{
    CInput* pInputKey    = CManager::GetInputKey();
	CInput* pInputMouse = CManager::GetInputMouse();
    D3DXVECTOR3 WorldPos = GetWorldPos();
    D3DXVECTOR3 move;
    bool bGameOver = false;

    //キー入力処理
    if(((CInputKeyboard*)pInputKey)->GetKeyPress(DIK_W))
    {
        m_nMoveVector = -90;
    }
    if(((CInputKeyboard*)pInputKey)->GetKeyPress(DIK_S))
    {
        m_nMoveVector = 90;
    }
    if(((CInputKeyboard*)pInputKey)->GetKeyPress(DIK_A))
    {
        m_nMoveVector = 180;

        if(((CInputKeyboard*)pInputKey)->GetKeyPress(DIK_W))
        {
            m_nMoveVector = -135;
        }
        else if(((CInputKeyboard*)pInputKey)->GetKeyPress(DIK_S))
        {
            m_nMoveVector = 135;
        }
    }
    if(((CInputKeyboard*)pInputKey)->GetKeyPress(DIK_D))
    {
        m_nMoveVector = 0;
        if(((CInputKeyboard*)pInputKey)->GetKeyPress(DIK_W))
        {
            m_nMoveVector = -45;
        }
        else if(((CInputKeyboard*)pInputKey)->GetKeyPress(DIK_S))
        {
            m_nMoveVector = 45;
        }
    }
    if(((CInputKeyboard*)pInputKey)->GetKeyPress(DIK_LSHIFT) && !m_bOverHeat)
    {
        move = D3DXVECTOR3(PLAYER_MOVE_RATE_SPRINT * cosf(D3DXToRadian(m_nMoveVector)), PLAYER_MOVE_RATE_SPRINT * sinf(D3DXToRadian(m_nMoveVector)), 0);
        m_pEnergy->ReduceEnergy(1);
    }
    else
    {
        move = D3DXVECTOR3(PLAYER_MOVE_RATE * cosf(D3DXToRadian(m_nMoveVector)), PLAYER_MOVE_RATE * sinf(D3DXToRadian(m_nMoveVector)), 0);
    }

    if(((CInputKeyboard*)pInputKey)->GetKeyPress(DIK_D) && ((CInputKeyboard*)pInputKey)->GetKeyPress(DIK_A))
    {
        move.x = 0;
    }
    if(((CInputKeyboard*)pInputKey)->GetKeyPress(DIK_W) && ((CInputKeyboard*)pInputKey)->GetKeyPress(DIK_S))
    {
        move.y = 0;
    }
    if(((CInputKeyboard*)pInputKey)->GetKeyPress(DIK_W) || ((CInputKeyboard*)pInputKey)->GetKeyPress(DIK_A) || ((CInputKeyboard*)pInputKey)->GetKeyPress(DIK_S)
       || ((CInputKeyboard*)pInputKey)->GetKeyPress(DIK_D))
    {
        WorldPos += move;
    }
    CScene** pScene = CScene::GetScene();
    for(int nCount = 0; nCount < MAX_SCENE * PRIORITY_MAX; nCount++)
    {
        if((*(pScene + nCount)) != NULL)
        {
            if((*(pScene + nCount))->GetObjType() == OBJTYPE_MAP_TILE || (*(pScene + nCount))->GetObjType() == OBJTYPE_MAP_TILE_BRAKABLE)
            {
                D3DXVECTOR3 TilePos = ((CScene2d*)(*(pScene + nCount)))->GetWorldPos();

                if(WorldPos.x + (PLAYER_SIZE_X / 2) > TilePos.x - (MAP_TILE_SIZE / 2) && WorldPos.x - (PLAYER_SIZE_X / 2) < TilePos.x + (MAP_TILE_SIZE / 2)
                   && WorldPos.y + (PLAYER_SIZE_Y / 2) > TilePos.y - (MAP_TILE_SIZE / 2) && WorldPos.y - (PLAYER_SIZE_Y / 2) < TilePos.y + (MAP_TILE_SIZE / 2))
                {
                    D3DXVECTOR3 TileVtxPos[4];
                    TileVtxPos[0] = D3DXVECTOR3(TilePos.x - (MAP_TILE_SIZE / 2), TilePos.y - (MAP_TILE_SIZE / 2), 0);
                    TileVtxPos[1] = D3DXVECTOR3(TilePos.x + (MAP_TILE_SIZE / 2), TilePos.y - (MAP_TILE_SIZE / 2), 0);
                    TileVtxPos[2] = D3DXVECTOR3(TilePos.x - (MAP_TILE_SIZE / 2), TilePos.y + (MAP_TILE_SIZE / 2), 0);
                    TileVtxPos[3] = D3DXVECTOR3(TilePos.x + (MAP_TILE_SIZE / 2), TilePos.y + (MAP_TILE_SIZE / 2), 0);
                    int Side      = CheckSide(TileVtxPos);
                    char str[256] = {};
                    sprintf(str, "%d\n", Side);
                    OutputDebugString(str);
                    if(Side == 1 || Side == 4)
                    {
                        WorldPos.y = m_posOld.y;
                    }
                    if(Side == 2 || Side == 3)
                    {
                        WorldPos.x = m_posOld.x;
                    }
                }
            }
        }
    }
    D3DXVECTOR3 ScreenPos = GetPos();
    if(ScreenPos.x < 0 || ScreenPos.x > SCREEN_WIDTH || ScreenPos.y < 0 || ScreenPos.y > SCREEN_HEIGHT)
    {
        if(m_pPolygon == NULL)
        {
            m_pPolygon = CPolygon::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_WIDTH, 0), 0, OBJTYPE_UI);
            m_pPolygon->BindTexture(m_pTextureUI);
        }
        if(m_CountNumber == NULL)
        {
            m_CountNumber = CNumber::Create(LOST_FLAME / 60, D3DXVECTOR3(SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 3) * 2, 0), D3DXVECTOR3(200, 400, 0), D3DCOLOR_RGBA(255, 0, 0, 255));
        }

        m_nCountFrame++;
        if(m_CountNumber != NULL)
        {
            m_CountNumber->SetValue((int)((LOST_FLAME - m_nCountFrame) / 60));
        }
        if(m_nCountFrame > LOST_FLAME)
        {
            if(m_pPolygon != NULL)
            {
                m_pPolygon->Uninit();
                m_pPolygon = NULL;
            }
            if(m_CountNumber != NULL)
            {
                m_CountNumber->Uninit();
                m_CountNumber = NULL;
            }
            CManager::GameOver();
            bGameOver = true;
        }
    }
    else
    {
        m_nCountFrame = 0;
        if(m_pPolygon != NULL)
        {
            m_pPolygon->Uninit();
            m_pPolygon = NULL;
        }
        if(m_CountNumber != NULL)
        {
            m_CountNumber->Uninit();
            m_CountNumber = NULL;
        }
    }
    //位置設定
    SetWorldPos(WorldPos);
    if(!m_bOverHeat && ((CInputMouse*)pInputMouse)->GetKeyPress(0))
    {
        D3DXVECTOR3 ScreenPos = GetPos();
        switch(LaserType)
        {
            case CLaser::LASERTYPE_STRONG_STRAIGHT:

                CLaser::Create(ScreenPos, D3DCOLOR_RGBA(255, 0, 0, 255), LASER_WIDTH, 0, 5, true);
                m_pEnergy->ReduceEnergy(3);
                break;
            case CLaser::LASERTYPE_WEEK_DIAGONAL:
                POINT point;
                GetCursorPos(&point);
                ScreenToClient(FindWindow(CLASS_NAME, NULL), &point);
                CLaser::Create(ScreenPos, D3DCOLOR_RGBA(0, 0, 255, 255), LASER_WIDTH / 2, atan2f(point.y - ScreenPos.y, point.x - ScreenPos.x), 5, false);
                m_pEnergy->ReduceEnergy(2);
                break;
            default:
                break;
        }
    }
    if(((CInputMouse*)pInputMouse)->GetKeyTrigger(1))
    {
        LaserType = (CLaser::LASERTYPE)(LaserType + 1);

        if(LaserType == CLaser::LASERTYPE_MAX)
        {
            LaserType = CLaser::LASERTYPE_STRONG_STRAIGHT;
        }
        if(LaserType == CLaser::LASERTYPE_WEEK_DIAGONAL)
        {
            if(m_pCursol == NULL)
            {
                m_pCursol = CCursol::Create();
            }
        }
        else
        {
            if(m_pCursol != NULL)
            {
                m_pCursol->Uninit();
                m_pCursol = NULL;
            }
        }
    }
    m_posOld = WorldPos;
    CScene2d::Update();
    if(m_CountNumber != NULL)
    {
        m_CountNumber->Update();
    }
    if(bGameOver)
    {
        Uninit();
    }
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//描画処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CPlayer::Draw(void)
{
    CScene2d::Draw();
    if(m_pPolygon != NULL)
    {
        m_pPolygon->Draw();
    }
    if(m_CountNumber != NULL)
    {
        m_CountNumber->Draw();
    }
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クリエイト関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CPlayer::Create(D3DXVECTOR3 pos)
{
    CPlayer* pPlayer = new CPlayer();     
    pPlayer->SetPos(pos);
    pPlayer->SetWorldPos(pos);
    pPlayer->Init();
    pPlayer->SetSize(D3DXVECTOR3(PLAYER_SIZE_X, PLAYER_SIZE_Y, 0.0f));
    pPlayer->SetObjType(OBJTYPE_PLAYER);
    pPlayer->m_pLife   = CLife::Create();
    pPlayer->m_pEnergy = CEnergy::Create();
    CManager::SetAlive(true);
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//ファイル読み込み関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
HRESULT CPlayer::Load(void)
{
    D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "Resources\\backtocombat.png", &m_pTextureUI);
    D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "Resources\\player.png", &m_pTexture);
    return S_OK;
}

void CPlayer::Unload(void)
{
    if(m_pTexture != NULL)
    {
        m_pTexture->Release();
        m_pTexture = NULL;
    }
}

void CPlayer::HitBullet(void)
{
    m_state = STATE_DAMAGE;

    m_pLife->AddLife(-10);
    if(m_pLife->GetLife() <= 0)
    {
        //ゲームオーバー
        CManager::GameOver();
        Uninit();
    }
}

CLife* CPlayer::GetLife(void)
{
    return m_pLife;
}
void CPlayer::SetOverHeat(bool bOverHeat)
{
    m_bOverHeat = bOverHeat;
}

int CPlayer::CheckSide(D3DXVECTOR3* pObjVtx)
{
    D3DXVECTOR3 worldPos = GetWorldPos();
	D3DXVECTOR3 nullvec;
    if((*D3DXVec3Cross(&nullvec, &(pObjVtx[3] - pObjVtx[0]), &(worldPos - pObjVtx[0]))).z < 0)
    {
		
        if((*D3DXVec3Cross(&nullvec, &(pObjVtx[1] - pObjVtx[2]), &(worldPos - pObjVtx[2]))).z < 0)
        {
            return 1;
        }
        else
        {
            return 2;
        }
    }
    else
    {
        if((*D3DXVec3Cross(&nullvec, &(pObjVtx[1] - pObjVtx[2]), &(worldPos - pObjVtx[2]))).z < 0)
        {
            return 3;
        }
        else
        {
            return 4;
        }
    }
}
