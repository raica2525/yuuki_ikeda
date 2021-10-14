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
    m_LaserType   = CLaser::LASERTYPE_STRONG_STRAIGHT;
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
		delete m_pPolygon;
		m_pPolygon = NULL;
    }

	if (m_CountNumber != NULL)
	{
		m_CountNumber->Uninit();
		delete m_CountNumber;
		m_CountNumber = NULL;
	}

	//死んだことをManagerに教える
    CManager::SetAlive(false);

    CScene2d::Uninit();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//更新処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CPlayer::Update(void)
{
	//移動
	D3DXVECTOR3 WorldPos = Move();

	//タイルとの当たり判定
	CollisionTile(&WorldPos);

	//画面外判定
	bool bGameOver = OutOfScreen();

    //位置設定
    SetWorldPos(WorldPos);
	
	//レーザー発射
	ShotLaser();

	//レーザータイプ設定
	ChangeLaserType();

	//posOld設定
    m_posOld = WorldPos;

    CScene2d::Update();

	//時間制限の数字更新
    if(m_CountNumber != NULL)
    {
        m_CountNumber->Update();
    }

	//ゲームオーバーになったら殺す
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

	//画面外に出たときのUIを消す
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

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//テクスチャ破棄関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CPlayer::Unload(void)
{
    if(m_pTexture != NULL)
    {
        m_pTexture->Release();
        m_pTexture = NULL;
    }
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//被弾処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CPlayer::HitBullet(void)
{
    m_pLife->AddLife(-10);
    if(m_pLife->GetLife() <= 0)
    {
        //ゲームオーバー
        CManager::GameOver();
        Uninit();
    }
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//ゲッター関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CLife* CPlayer::GetLife(void)
{
    return m_pLife;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//セッター関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CPlayer::SetOverHeat(bool bOverHeat)
{
    m_bOverHeat = bOverHeat;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//タイルからみたプレイヤーの方向を取得
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
int CPlayer::CheckSide(D3DXVECTOR3* pObjVtx)
{
    D3DXVECTOR3 worldPos = GetWorldPos();	//ワールド座標の取得
	D3DXVECTOR3 nullvec;	//引数廃棄用変数

	//タイルのポリゴンの対角線の左右判定を利用して方向を取得
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

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//入力を角度に変換
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
int CPlayer::InputToAngle(void)
{
	CInputKeyboard* pInputKey = CManager::GetInputKey();
	int vec = 0;
	//キーボード入力を角度に変換する
	if (pInputKey->GetKeyPress(DIK_W))
	{
		vec = -90;
	}
	if (pInputKey->GetKeyPress(DIK_S))
	{
		vec = 90;
	}
	if (pInputKey->GetKeyPress(DIK_A))
	{
		vec = 180;

		if (pInputKey->GetKeyPress(DIK_W))
		{
			vec = -135;
		}
		else if (pInputKey->GetKeyPress(DIK_S))
		{
			vec = 135;
		}
	}
	if (pInputKey->GetKeyPress(DIK_D))
	{
		vec = 0;
		if (((CInputKeyboard*)pInputKey)->GetKeyPress(DIK_W))
		{
			vec = -45;
		}
		else if (pInputKey->GetKeyPress(DIK_S))
		{
			vec = 45;
		}
	}
	return vec;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//移動
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
D3DXVECTOR3 CPlayer::Move(void)
{
	D3DXVECTOR3 move;
	CInputKeyboard* pInputKey = CManager::GetInputKey();
	D3DXVECTOR3 WorldPos = GetWorldPos();
	//キー入力処理
	m_nMoveVector = InputToAngle();

	if (pInputKey->GetKeyPress(DIK_LSHIFT) && !m_bOverHeat)	//スプリント移動
	{
		move = D3DXVECTOR3(PLAYER_MOVE_RATE_SPRINT * cosf(D3DXToRadian(m_nMoveVector)), PLAYER_MOVE_RATE_SPRINT * sinf(D3DXToRadian(m_nMoveVector)), 0);
		m_pEnergy->ReduceEnergy(1);
	}
	else	//通常移動
	{
		move = D3DXVECTOR3(PLAYER_MOVE_RATE * cosf(D3DXToRadian(m_nMoveVector)), PLAYER_MOVE_RATE * sinf(D3DXToRadian(m_nMoveVector)), 0);
	}

	//逆キー同時押ししたときの処理
	if (pInputKey->GetKeyPress(DIK_D) && ((CInputKeyboard*)pInputKey)->GetKeyPress(DIK_A))
	{
		move.x = 0;
	}
	if (pInputKey->GetKeyPress(DIK_W) && ((CInputKeyboard*)pInputKey)->GetKeyPress(DIK_S))
	{
		move.y = 0;
	}

	//キーを押しているときだけ移動
	if (pInputKey->GetKeyPress(DIK_W) || pInputKey->GetKeyPress(DIK_A) || pInputKey->GetKeyPress(DIK_S) || pInputKey->GetKeyPress(DIK_D))
	{
		return WorldPos + move;
	}
	else
	{
		return WorldPos;
	}
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//画面外に出たときの処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
bool CPlayer::OutOfScreen(void)
{
	//画面外判定
	D3DXVECTOR3 ScreenPos = GetPos();
	if (ScreenPos.x < 0 || ScreenPos.x > SCREEN_WIDTH || ScreenPos.y < 0 || ScreenPos.y > SCREEN_HEIGHT)
	{
		if (m_pPolygon == NULL)
		{
			m_pPolygon = CPolygon::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_WIDTH, 0), 0, OBJTYPE_UI);
			m_pPolygon->BindTexture(m_pTextureUI);
		}
		if (m_CountNumber == NULL)
		{
			m_CountNumber = CNumber::Create(LOST_FLAME / 60, D3DXVECTOR3(SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 3) * 2, 0), D3DXVECTOR3(200, 400, 0), D3DCOLOR_RGBA(255, 0, 0, 255));
		}

		m_nCountFrame++;
		if (m_CountNumber != NULL)
		{
			m_CountNumber->SetValue((int)((LOST_FLAME - m_nCountFrame) / 60));
		}
		if (m_nCountFrame > LOST_FLAME)
		{
			if (m_pPolygon != NULL)
			{
				m_pPolygon->Uninit();
				delete m_pPolygon;
				m_pPolygon = NULL;
			}
			if (m_CountNumber != NULL)
			{
				m_CountNumber->Uninit();
				delete m_CountNumber;
				m_CountNumber = NULL;
			}
			CManager::GameOver();
			return true;
		}
	}
	else
	{
		m_nCountFrame = 0;
		if (m_pPolygon != NULL)
		{
			m_pPolygon->Uninit();
			delete m_pPolygon;
			m_pPolygon = NULL;
		}
		if (m_CountNumber != NULL)
		{
			m_CountNumber->Uninit();
			delete m_CountNumber;
			m_CountNumber = NULL;
		}
	}
	return false;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//タイルとの当たり判定
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CPlayer::CollisionTile(D3DXVECTOR3* pWorldPos)
{
	//タイルとの当たり判定
	CScene** pScene = CScene::GetScene();
	//タイルを探す
	for (int nCount = 0; nCount < MAX_SCENE * PRIORITY_MAX; nCount++)
	{
		if ((*(pScene + nCount)) != NULL)
		{
			
			if ((*(pScene + nCount))->GetObjType() == OBJTYPE_MAP_TILE || (*(pScene + nCount))->GetObjType() == OBJTYPE_MAP_TILE_BRAKABLE)
			{
				//タイルの座標を取得
				D3DXVECTOR3 TilePos = ((CScene2d*)(*(pScene + nCount)))->GetWorldPos();
				//タイルとの当たり判定
				if (pWorldPos->x + (PLAYER_SIZE_X / 2) > TilePos.x - (MAP_TILE_SIZE / 2) && pWorldPos->x - (PLAYER_SIZE_X / 2) < TilePos.x + (MAP_TILE_SIZE / 2)
					&& pWorldPos->y + (PLAYER_SIZE_Y / 2) > TilePos.y - (MAP_TILE_SIZE / 2) && pWorldPos->y - (PLAYER_SIZE_Y / 2) < TilePos.y + (MAP_TILE_SIZE / 2))
				{
					//タイルの頂点座標を取得
					D3DXVECTOR3 TileVtxPos[4];
					TileVtxPos[0] = D3DXVECTOR3(TilePos.x - (MAP_TILE_SIZE / 2), TilePos.y - (MAP_TILE_SIZE / 2), 0);
					TileVtxPos[1] = D3DXVECTOR3(TilePos.x + (MAP_TILE_SIZE / 2), TilePos.y - (MAP_TILE_SIZE / 2), 0);
					TileVtxPos[2] = D3DXVECTOR3(TilePos.x - (MAP_TILE_SIZE / 2), TilePos.y + (MAP_TILE_SIZE / 2), 0);
					TileVtxPos[3] = D3DXVECTOR3(TilePos.x + (MAP_TILE_SIZE / 2), TilePos.y + (MAP_TILE_SIZE / 2), 0);

					//タイルの頂点座標からプレイヤーとタイルの位置関係を取得
					int Side = CheckSide(TileVtxPos);	
					
					//プレイヤーとタイルの位置関係によってプレイヤーの座標を補正
					if (Side == 1 || Side == 4)
					{
						pWorldPos->y = m_posOld.y;
					}
					if (Side == 2 || Side == 3)
					{
						pWorldPos->x = m_posOld.x;
					}
				}
			}
		}
	}
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//レーザー発射
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CPlayer::ShotLaser(void)
{
	CInputMouse* pInputMouse = CManager::GetInputMouse();
	//レーザー発射
	if (!m_bOverHeat && pInputMouse->GetKeyPress(0))
	{
		D3DXVECTOR3 ScreenPos = GetPos();
		//現在のレーザータイプによって発射するレーザーを変更
		switch (m_LaserType)
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
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//レーザーの種類設定
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CPlayer::ChangeLaserType(void)
{
	CInputMouse* pInputMouse = CManager::GetInputMouse();
	//右クリックされた時にレーザーの種類を変更
	if (pInputMouse->GetKeyTrigger(1))
	{
		m_LaserType = (CLaser::LASERTYPE)(m_LaserType + 1);

		//レーザーの種類が最大値になったときに戻す
		if (m_LaserType == CLaser::LASERTYPE_MAX)
		{
			m_LaserType = CLaser::LASERTYPE_STRONG_STRAIGHT;
		}
		//レーザーの種類によってカーソルの表示非表示を変更
		if (m_LaserType == CLaser::LASERTYPE_WEEK_DIAGONAL)
		{
			if (m_pCursol == NULL)
			{
				m_pCursol = CCursol::Create();
			}
		}
		else
		{
			if (m_pCursol != NULL)
			{
				m_pCursol->Uninit();
				m_pCursol = NULL;
			}
		}
	}
}