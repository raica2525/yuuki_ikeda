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

#include "animation.h"
#include "bullet_ui.h"
#include "camera.h"
#include "crosshair.h"
#include "damage_ui.h"
#include "debug.h"
#include "enemy.h"
#include "fade.h"
#include "gameoveroverlay.h"
#include "inputkeyboard.h"
#include "inputmouse.h"
#include "manager.h"
#include "model.h"
#include "object.h"
#include "object3d.h"
#include "polygon3d.h"
#include "renderer.h"
#include "sound.h"
#include "tutorialstage.h"
#include "item_ui.h"
#include "weapons_ui.h"
#include "blood.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//マクロ定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#define AR_DAMAGE (15)
#define HG_DAMAGE (10)
#define AR_MOVE_RATE (0.75f)
#define HG_MOVE_RATE (1.25f)
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//静的メンバ変数宣言
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CModel::MODELDATA CPlayer::m_modeldata[PARTS_MAX]                        = {};
CModel::MODELDATA CPlayer::m_modelWeaponData[CManager::WEAPONS_MODE_MAX] = {};
D3DXMATERIAL* CPlayer::m_pMat                                            = NULL;
CAnimation* CPlayer::m_pAnimaSave                                        = NULL;
int CPlayer::m_nSensi                                                    = START_SENSI;
int CPlayer::m_nFrameCounter                                             = 0;
char* CPlayer::m_PartsWeapon[CManager::WEAPONS_MODE_MAX]                 = {
  "Data/Model/Player/06_RightHandandAsult.x",
  "Data/Model/Player/06_HandGun.x",
};

CPlayer::PARTS_DATA CPlayer::m_PartsData[PARTS_MAX] = {
  {
    "Data/Model/Player/00_Mune.x",
    -1,
    D3DXVECTOR3(0.0f, 140.0f, 0.0f),
  },
  {
    "Data/Model/Player/01_Onaka.x",
    0,
    D3DXVECTOR3(0.0f, -10.0f, 0.0f),
  },
  {
    "Data/Model/Player/02_Kosi.x",
    1,
    D3DXVECTOR3(0.0f, 5.0f, 0.0f),
  },
  {
    "Data/Model/Player/03_Head.x",
    0,
    D3DXVECTOR3(0.0f, 20.0f, 0.0f),
  },
  {
    "Data/Model/Player/04_RighJouwan.x",
    0,
    D3DXVECTOR3(-10.0f, 30.0f, 0.0f),
  },
  {
    "Data/Model/Player/05_RightZenwan.x",
    4,
    D3DXVECTOR3(-30.0f, -17.0f, 0.0f),
  },
  {
    "Data/Model/Player/06_RightHandandAsult.x",
    5,
    D3DXVECTOR3(-35.0f, -18.0f, 2.0f),
  },
  {
    "Data/Model/Player/07_LeftJouwan.x",
    0,
    D3DXVECTOR3(10.0f, 30.0f, 0.0f),
  },
  {
    "Data/Model/Player/08_LeftZenwan.x",
    7,
    D3DXVECTOR3(30.0f, -17.0f, 0.0f),
  },
  {
    "Data/Model/Player/09_LeftHand.x",
    8,
    D3DXVECTOR3(35.0f, -16.0f, 0.0f),
  },
  {
    "Data/Model/Player/10_RightHutomomo.x",
    2,
    D3DXVECTOR3(-5.75f, -20.0f, 0.0f),
  },
  {
    "Data/Model/Player/11_RightHukurahagi.x",
    10,
    D3DXVECTOR3(-6.0f, -40.0f, 2.0f),
  },
  {
    "Data/Model/Player/12_RightFoot.x",
    11,
    D3DXVECTOR3(0.0f, -50.0f, 5.0f),
  },
  {
    "Data/Model/Player/13_LeftHutomomo.x",
    2,
    D3DXVECTOR3(5.75f, -20.0f, 0.0f),
  },
  {
    "Data/Model/Player/14_LeftHukurahagi.x",
    13,
    D3DXVECTOR3(6.0f, -40.0f, 2.0f),
  },
  {
    "Data/Model/Player/15_LeftFoot.x",
    14,
    D3DXVECTOR3(0.0f, -50.0f, 5.0f),
  },
};
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//コンストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CPlayer::CPlayer()
{
	static_assert(sizeof(m_PartsWeapon) / sizeof(m_PartsWeapon[0]) == CManager::WEAPONS_MODE_MAX, "配列範囲エラー");
	static_assert(sizeof(m_PartsData) / sizeof(m_PartsData[0]) == PARTS_MAX, "配列範囲エラー");
    m_nFrameCounter = 0;                                    //フレームカウンター
    m_AnimaMotion   = CAnimation::MOTION_PLAYER_NEUTRAL;    //初期モーション設定
    m_pCrosshair    = NULL;                                 //クロスヘアポインタ
    m_pAnime        = NULL;                                 //アニメポインタ
    m_pDamageUi     = NULL;                                 //ダメージUIポインタ
    ZeroMemory(m_apItemUI, sizeof(m_apItemUI));             //回復アイテムのUI
    m_nLife       = START_LIFE;                             //初期ライフ
    m_pos         = ZEROVECTOR3;                            //座標
    m_rot         = ZEROVECTOR3;                            //初期向き
    m_size        = D3DXVECTOR3(1.0f, 1.0f, 1.0f);          //大きさ
    m_state       = STATE_STAND;                            //初期状態
    m_fMoveVector = 0.0f;                                   //移動方向
    ZeroMemory(m_apModel, sizeof(m_apModel));               //モデルのポインタゼロクリア
    SetObjType(CObject::OBJTYPE_PLAYER);                    //オブジェクトタイプ設定
    m_fMoveVector = 0.0f;                                   //進行方向
    m_nHaveItem   = 0;                                      //アイテム所持数
    m_Weapons_UI  = NULL;                                   //ウェポンUIポインタ
    memset(m_Partsrot, NULL, sizeof(m_Partsrot));           //パーツの初期向き
    memset(m_Partspos, NULL, sizeof(m_Partspos));           //パーツの初期位置
    for(int nCount = 0; nCount < PARTS_MAX; nCount++)
    {
        m_PartsSize[nCount] = D3DXVECTOR3(1.0f, 1.0f, 1.0f);    //パーツの初期大きさ
    }
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
    CManager::WEAPONS_MODE weaponMode = CManager::GetWeaponsMode();
    //アニメーション生成
    if(weaponMode == CManager::WEAPONS_MODE_AR)
    {
        m_pAnimaSave     = CAnimation::Create(CAnimation::ANIMATION_PLAYER_AR);
        m_nRemainingAmmo = MAGAZINE_SIZE_AR;
        m_nMagazineSize  = MAGAZINE_SIZE_AR;
    }
    else
    {
        m_pAnimaSave     = CAnimation::Create(CAnimation::ANIMATION_PLAYER_HG);
        m_nRemainingAmmo = MAGAZINE_SIZE_HG;
        m_nMagazineSize  = MAGAZINE_SIZE_HG;
    }
    while(ShowCursor(false) >= 0);    //マウスカーソル無効化

    //ワールドマトリクス用
    m_apModelWorld = CModel::Create(NULL, this, {}, m_pos, m_rot, m_size);

    //ウェポンモデルに切り替え
    if(weaponMode != CManager::WEAPONS_MODE_NONE)
    {
        m_modeldata[PARTS_RIGHT_HAND] = m_modelWeaponData[weaponMode];
    }

    //モデル生成
    for(int nCount = 0; nCount < PARTS_MAX; nCount++)
    {
        if(m_PartsData[nCount].nParent == -1)
        {
            m_apModel[nCount] = CModel::Create(m_apModelWorld, this, m_modeldata[nCount], m_PartsData[nCount].Partspos, m_Partsrot[nCount], m_PartsSize[nCount]);
        }
        else
        {
            m_apModel[nCount] = CModel::Create(m_apModel[m_PartsData[nCount].nParent], this, m_modeldata[nCount], m_PartsData[nCount].Partspos, m_Partsrot[nCount], m_PartsSize[nCount]);
        }
    }
    //ウェポンUI生成
    m_Weapons_UI = CWeapons_ui::Create();
    //ダメージUIの生成
    m_pDamageUi = CDamage_ui::Create();

    //バレットの初期値の数だけCreateする
    for(int nCountBullet = 0; nCountBullet < m_nMagazineSize; nCountBullet++)
    {
        // nCountBulletの数字が増えるごとに横に展開していく処理
        m_pBulletUi[nCountBullet] = CBullet_ui::Create(D3DXVECTOR3((SCREEN_WIDTH - (BULLET_UI_SIZE.x + (BULLET_UI_SIZE.x * nCountBullet))), (SCREEN_HEIGHT - 70.0f), 0.0f));
    }
    //マネージャーにポインタ保存
    CManager::SetPlayer(this);

    //アニメ保存
    m_pAnime = m_pAnimaSave;

    //アニメションセット
    m_pAnime->SetAnimation(CAnimation::MOTION_PLAYER_NEUTRAL);

    return S_OK;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//終了処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CPlayer::Uninit(void)
{
    //モデル破棄
    for(int nCount = 0; nCount < PARTS_MAX; nCount++)
    {
        m_apModel[nCount]->Uninit();
		m_apModel[nCount] = NULL;
    }
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//更新処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CPlayer::Update(void)
{
    CInputKeyboard* pInputKeyboard = nullptr;                     //キーボード入力用
    CInputMouse* pInputMouse       = nullptr;                     //マウス入力用
    CSound* pSound                 = CManager::GetSound();        //サウンドの取得
    POINT point;                                                  //マウスポインタの位置取得用
    bool bMove     = false;                                       //移動しているかどうか
    pInputKeyboard = (CInputKeyboard*)CManager::GetInputKey();    //キーボード入力取得
    pInputMouse    = (CInputMouse*)CManager::GetInputMou();       //マウス入力取得
    GetCursorPos(&point);                                         //マウス位置取得
	//プレイヤーが死んでいなければ
    if(m_state != STATE_DEATH)
    {
        SetCursorPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);                             //マウス位置を中央に固定
        m_rot.y -= (point.x - (SCREEN_WIDTH / 2)) * (float)(SENSI_RATE * m_nSensi);    //プレイヤーの回転量にマウス位置を反映
        m_rot.x += (point.y - (SCREEN_HEIGHT / 2)) * (float)(SENSI_RATE * m_nSensi);

        // ジンバルロック回避用
        if(m_rot.x > 90.0f)
        {
            m_rot.x = 89.0f;
        }
        else if(m_rot.x < -90.0f)
        {
            m_rot.x = -89.0f;
        }

        if(m_rot.y < 0.0f)
        {
            m_rot.y += 360.0f;
        }
        if(m_rot.y > 360.0f)
        {
            m_rot.y -= 360.0f;
        }

        CManager::GetCamera()->SetRot(m_rot);    //カメラを向きに合わせる

        //マウス感度調整
        if(pInputKeyboard->GetKeyTrigger(DIK_LBRACKET))
        {
            m_nSensi++;
        }
        if(pInputKeyboard->GetKeyTrigger(DIK_RBRACKET))
        {
            m_nSensi--;
            if(m_nSensi <= 0)
            {
                m_nSensi = 1;
            }
        }

        //移動処理
        if(pInputKeyboard->GetKeyPress(DIK_W) || pInputKeyboard->GetKeyPress(DIK_A) || pInputKeyboard->GetKeyPress(DIK_S) || pInputKeyboard->GetKeyPress(DIK_D))
        {
            bMove = true;
            Move(pInputKeyboard);
        }

        //アイテム使用
        if(m_nHaveItem > 0 && pInputKeyboard->GetKeyTrigger(DIK_F))
        {
            UseItem(pSound);
        }

        m_pDamageUi->SetDamageUi(m_nLife);    //ダメージUIの設定

        //空砲音処理
        if(m_nRemainingAmmo <= 0 && pInputMouse->GetKeyTrigger(CInputMouse::MOUSE_BUTTON_LEFT) && m_state == STATE_AIM)
        {
            pSound->PlaySoundA(CSound::SOUND_LABEL_SE_AIR);
        }

        //リロード処理
        if(pInputKeyboard->GetKeyTrigger(DIK_R) && m_state != STATE_RELOAD && m_state != STATE_RELOAD_WALK && m_nRemainingAmmo < m_nMagazineSize)
        {
            BeginReload(pSound, bMove);
        }

        //リロード完了処理
        if(m_pAnime->GetAnimeEnd() == false)
        {
            EndReload(pSound);
        }

        //プレイヤーの状態変更
        ChangeState(pInputKeyboard, pInputMouse, pSound, bMove);

        // AIM時に正面を向く処理
        if(m_state == STATE_AIM)
        {
            m_fMoveVector = m_rot.y - 90.0f;

            //射撃処理
            if(pInputMouse->GetKeyPress(CInputMouse::MOUSE_BUTTON_LEFT) && m_nFrameCounter++ > ASSAULT_RIFLE_RATE && CManager::GetWeaponsMode() == CManager::WEAPONS_MODE_AR && m_nRemainingAmmo-- > 0)
            {
                // AR
                m_nFrameCounter = 0;
                Shot(AR_DAMAGE, ADD_SPREAD_AR, pSound);
            }
            else if(pInputMouse->GetKeyTrigger(CInputMouse::MOUSE_BUTTON_LEFT) && m_nFrameCounter++ > HANDGUN_RATE && CManager::GetWeaponsMode() == CManager::WEAPONS_MODE_HG && m_nRemainingAmmo-- > 0)
            {
                // HG
                m_nFrameCounter = 0;
                Shot(HG_DAMAGE, ADD_SPREAD_HG, pSound);
            }
        }
        else
        {
            // AIM中以外はクロスヘアを消す
            if(m_pCrosshair != NULL)
            {
                m_pCrosshair->Uninit();
                m_pCrosshair = NULL;
            }
        }

        //クロスヘアが存在していれば拡散の最小値を設定
        if(m_pCrosshair != NULL)
        {
            if(bMove)
            {
                m_pCrosshair->SetMinSpread(MIN_SPREAD_WALK);
            }
            else
            {
                m_pCrosshair->SetMinSpread(MIN_SPREAD_STOP);
            }
        }

        //死亡
        if(m_nLife <= 0)
        {
            pSound->PlaySoundA(CSound::SOUND_LABEL_SE_SCREAM);
            m_state         = STATE_DEATH;
            m_nFrameCounter = 0;
        }
        //モデルの位置を設定
        m_apModelWorld->SetPos(m_pos);
        //モデルの向きを設定
        m_apModelWorld->SetRot(-D3DXToRadian(D3DXVECTOR3(0, m_fMoveVector + 90, 0)));
    }
    else //死亡後
    {
        //死んだ場合の処理
        if(m_nFrameCounter == GAMEOVER_COUNT)    //死んでから一定時間立ったらゲームオーバー画面を出す
        {
			CGameoverOverlay::Create();
        }
		m_nFrameCounter++;
    }
    //アニメーションコントロール処理
    AnimaControl();
    //アニメーション処理
    m_pAnime->SetAnimation(m_AnimaMotion);
    //アニメーション用関数
    PartsUpdate();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//描画処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CPlayer::Draw(void)
{
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//生成関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CPlayer* CPlayer::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 size)
{
    CPlayer* pPlayer = new CPlayer;
    pPlayer->m_pos   = pos;
    pPlayer->m_rot   = rot;
    pPlayer->m_size  = size;
    pPlayer->Init();

    return pPlayer;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//ファイル読み込み
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CPlayer::Load(void)
{
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

    //プレイヤーモデルロード
    for(int nCount = 0; nCount < PARTS_MAX ; nCount++)
    {
        D3DXLoadMeshFromX(m_PartsData[nCount].FileName, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_modeldata[nCount].pBuffMat, NULL, &m_modeldata[nCount].nNumMat, &m_modeldata[nCount].pMesh);
        m_pMat = (D3DXMATERIAL*)m_modeldata[nCount].pBuffMat->GetBufferPointer();

        for(int nCountMat = 0; nCountMat < (int)m_modeldata[nCount].nNumMat; nCountMat++)
        {
            D3DXCreateTextureFromFile(pDevice, m_pMat[nCountMat].pTextureFilename, &m_modeldata[nCount].pTexture[nCountMat]);
        }
    }

    //ウェポンモデルロード
    for(int nCount = 0; nCount < CManager::WEAPONS_MODE_MAX; nCount++)
    {
        D3DXLoadMeshFromX(m_PartsWeapon[nCount], D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_modelWeaponData[nCount].pBuffMat, NULL, &m_modelWeaponData[nCount].nNumMat, &m_modelWeaponData[nCount].pMesh);
        m_pMat = (D3DXMATERIAL*)m_modelWeaponData[nCount].pBuffMat->GetBufferPointer();
        for(int nCountMat = 0; nCountMat < (int)m_modelWeaponData[nCount].nNumMat; nCountMat++)
        {
            D3DXCreateTextureFromFile(pDevice, m_pMat[nCountMat].pTextureFilename, &m_modelWeaponData[nCount].pTexture[nCountMat]);
        }
    }
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//ファイル破棄
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CPlayer::Unload(void)
{
    //プレイヤーモデルアンロード
    for(int nCount = 0; nCount < PARTS_MAX; nCount++)
    {
        if(m_modeldata[nCount].pBuffMat != NULL)
        {
            m_modeldata[nCount].pBuffMat->Release();
        }

        if(m_modeldata[nCount].pMesh != NULL)
        {
            m_modeldata[nCount].pMesh->Release();
        }

        for(int nCountTex = 0; nCountTex < MAX_MATERIAL; nCountTex++)
        {
            if(m_modeldata[nCount].pTexture[nCountTex] != NULL)
            {
                m_modeldata[nCount].pTexture[nCountTex]->Release();
            }
        }
    }
	ZeroMemory(&m_modeldata, sizeof(m_modeldata));
    //ウェポンモデルアンロード
    for(int nCount = 0; nCount < CManager::WEAPONS_MODE_MAX; nCount++)
    {
        if(m_modelWeaponData[nCount].pBuffMat != NULL)
        {
            m_modelWeaponData[nCount].pBuffMat->Release();
        }

        if(m_modelWeaponData[nCount].pMesh != NULL)
        {
            m_modelWeaponData[nCount].pMesh->Release();
        }

        for(int nCountTex = 0; nCountTex < MAX_MATERIAL; nCountTex++)
        {
            if(m_modelWeaponData[nCount].pTexture[nCountTex] != NULL)
            {
                m_modelWeaponData[nCount].pTexture[nCountTex]->Release();
            }
        }
    }
	ZeroMemory(&m_modelWeaponData, sizeof(m_modelWeaponData));
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//ゲッター関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
D3DXVECTOR3 CPlayer::GetPos(void)
{
    return m_pos;
}
D3DXVECTOR3 CPlayer::GetPartsPos(const int nParts)
{
    return m_PartsData[nParts].Partspos;
}

D3DXVECTOR3 CPlayer::GetCenter(void)
{
    return (m_pos + (m_PartsData[PARTS_CHEST].Partspos * 0.2f)) + (m_Partspos[PARTS_CHEST] * 0.2f);
}

D3DXVECTOR3 CPlayer::GetRot(void)
{
    return m_rot;
}

CPlayer::STATE CPlayer::GetState(void)
{
    return m_state;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//弾丸(レイ)がモデルに当たったか判定
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
BOOL CPlayer::CheckHitBullet(const CModel::MODELDATA modeldata, BOOL* pHit, float* pDistance, const D3DXVECTOR3 spread)
{
    D3DXVECTOR3 TransformedPos, TranceformedVec, NormalizedVec, PosR;
    PosR = CManager::GetCamera()->GetPosR();                                                                            //注視点
    D3DXVec3Normalize(&NormalizedVec, &((PosR + spread) - (m_pos + D3DXVECTOR3(0, PLAYER_HEAD_HEIGHT, 0))));            //プレイヤーから注視点へのベクトルを単位ベクトルに変換
	D3DXMATRIX InversedWorldMatrix;
    D3DXMatrixInverse(&InversedWorldMatrix, NULL, &modeldata.mtxWorld);                                                 //逆行列生成
    D3DXVec3TransformCoord(&TransformedPos, &(m_pos + D3DXVECTOR3(0, PLAYER_HEAD_HEIGHT, 0)), &InversedWorldMatrix);    //逆行列で変換
    D3DXVec3TransformNormal(&TranceformedVec, &NormalizedVec, &InversedWorldMatrix);
	BOOL bHit;
    D3DXIntersect(modeldata.pMesh, &TransformedPos, &TranceformedVec, &bHit, NULL, NULL, NULL, pDistance, NULL, NULL);    //当たり判定を確認
    pHit = &bHit;
    return bHit;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//弾丸(レイ)が当たったモデル取得
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CObject* CPlayer::GetHitObject(void)
{
    CObject* pTop[PRIORITY_MAX] = {};      //オブジェクト取得用
    CObject* pNext              = NULL;    //次チェックするオブジェクトのポインタ
    D3DXVECTOR3 RandomSpread;              //銃弾のブレ
    for(int nCount = 0; nCount < PRIORITY_MAX; nCount++)
    {
        pTop[nCount] = *(CObject::GetTop() + nCount);    // topのアドレスを取得
    }
    float fDistance        = 0.0f;       //銃弾(レイ)が当たった距離
    float fClosestDistance = 0.0f;       //銃弾(レイ)が当たった距離の中で一番近い物
    CObject* ClosestObject = NULL;		//↑のオブジェクトのポインタ
    //銃弾のブレを生成
    RandomSpread = D3DXVECTOR3((float)(rand() % (int)(m_pCrosshair->GetSpread() + 1)), (float)(rand() % (int)(m_pCrosshair->GetSpread() + 1)), (float)(rand() % (int)(m_pCrosshair->GetSpread() + 1)));
    //銃弾のブレを中央に補正
	float fSpread = m_pCrosshair->GetSpread();
    RandomSpread.x -= fSpread / 4.0f;
    RandomSpread.y -= fSpread / 4.0f;
    RandomSpread.z -= fSpread / 4.0f;

    //オブジェクト探査
    for(int nCount = 0; nCount < PRIORITY_MAX; nCount++)
    {
		if (pTop[nCount] == NULL)
		{
			continue;
		}
        //その描画優先度のオブジェクトがなくなるまでループ
        for(pNext = pTop[nCount];pNext != NULL;pNext = pNext->GetNext())
        {
			if (pNext->GetObjType() != OBJTYPE_MODEL)    //オブジェクトのタイプがモデルなら
			{
				continue;
			}
			CModel* pModel = (CModel*)pNext;
			if (pModel->GetParentObject() == NULL)    //親オブジェクトが存在するなら
			{
				continue;
			}
			if (!pModel->GetParentObject()->GetCollisionBullet())    //銃弾に対する当たり判定をするかチェック
			{
				continue;
			}
			if (!CheckHitBullet(((CModel*)pNext)->GetModelData(), NULL, &fDistance, RandomSpread))    //当たり判定をチェック
			{
				continue;
			}
            if(ClosestObject == NULL || fClosestDistance > fDistance)    //現状一番近いオブジェクトが存在しないかそれまでで一番近ければ
            {
                //一番近いオブジェクトを更新
                ClosestObject    = pNext;
                fClosestDistance = fDistance;
            }
        }
    }
    return ClosestObject;    //一番近いオブジェクトを返す
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
// HP加算(負の数指定で減らす)
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CPlayer::AddLife(const int Value)
{
    m_nLife += Value;
    //現在のライフの値をダメージUIに入れる
    if(m_nLife > START_LIFE)
    {
        m_nLife = START_LIFE;
    }
    if(m_nLife < 0)
    {
        m_nLife = 0;
    }
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
// HPゲット関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
int CPlayer::GetLife(void)
{
    return m_nLife;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//壁との当たり判定取得用関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
BOOL CPlayer::Collision(const CModel::MODELDATA modeldata, D3DXVECTOR3* pHittedPolyNormal, int* pHitCount)
{
    int HitCount = 0;                                              //プレイヤーが接しているメッシュの数
    BOOL bHit    = false;                                          //プレイヤーが出しているレイがメッシュに当たっているか
    D3DXMATRIX InversedWorldMatrix;                                //ワールド変換行列の逆行列
    D3DXVECTOR3 TransformedPos, TranceformedVec, NormalizedVec;    //各変換後のベクトル
    float fRayRot               = 0.0f;                               //レイを飛ばす方向
    float fDistance             = 0.0f;                               //レイがヒットした距離
    DWORD dwPolyIndex           = 0;                               //当たったメッシュのインデックス
    DWORD HittedPolyIndex[1024] = {};

    for(int nCount = 0; nCount < COLLISION_RAY_COUNT; nCount++)
    {
        bool bAlreadyChecked = false;
        fRayRot              = (float)nCount * (360 / COLLISION_RAY_COUNT);                                                      //レイを均等な角度で飛ばす
        D3DXVec3Normalize(&NormalizedVec, &(D3DXVECTOR3(cosf(D3DXToRadian(fRayRot)), 0.0f, sinf(D3DXToRadian(fRayRot)))));          //プレイヤーから注視点へのベクトルを単位ベクトルに変換
        D3DXMatrixInverse(&InversedWorldMatrix, NULL, &modeldata.mtxWorld);                                                      //逆行列生成
        D3DXVec3TransformCoord(&TransformedPos, &(m_pos + D3DXVECTOR3(0.0f, PLAYER_COLLISION_HEIGHT, 0.0f)), &InversedWorldMatrix);    //逆行列で変換
        D3DXVec3TransformNormal(&TranceformedVec, &NormalizedVec, &InversedWorldMatrix);
        D3DXIntersect(modeldata.pMesh, &TransformedPos, &TranceformedVec, &bHit, &dwPolyIndex, NULL, NULL, &fDistance, NULL, NULL);    //当たり判定を確認

        for(int nCountPoly = 0; nCountPoly < HitCount; nCountPoly++)
        {
            if(HittedPolyIndex[nCountPoly] == dwPolyIndex)
            {
                bAlreadyChecked = true;
            }
        }

        if(bHit && fDistance < PLAYER_COLLISION_RADIUS && !bAlreadyChecked)    //レイがヒットかつ距離がプレイヤーの当たり判定のサイズ以下なら
        {
            D3DXVECTOR3 vertex[3];                                       //レイがヒットしたメッシュの頂点座標
            D3DXPLANE plane;                                             //メッシュの平面
            FindVerticesOnPoly(modeldata.pMesh, dwPolyIndex, vertex);    //メッシュの頂点を取得

            //その頂点から平面方程式を得る
            D3DXPlaneFromPoints(&plane, &vertex[0], &vertex[1], &vertex[2]);
            //法線を計算
            pHittedPolyNormal[HitCount].x = plane.a;
            pHittedPolyNormal[HitCount].y = plane.b;
            pHittedPolyNormal[HitCount].z = plane.c;
            D3DXVec3Normalize(&pHittedPolyNormal[HitCount], &pHittedPolyNormal[HitCount]);
            HittedPolyIndex[HitCount] = dwPolyIndex;
			assert(sizeof(HittedPolyIndex) / sizeof(HittedPolyIndex[0]) < 1024);
            HitCount++;    //当たったメッシュの数を増やす
        }
    }
    *pHitCount = HitCount;

	return HitCount > 0;

}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//メッシュの頂点座標を取得
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CPlayer::FindVerticesOnPoly(const LPD3DXMESH pMesh, const DWORD dwPolyIndex, D3DXVECTOR3* pvecVertices)
{
    DWORD dwStride = pMesh->GetNumBytesPerVertex();
    WORD* pwPoly   = NULL;
    pMesh->LockIndexBuffer(D3DLOCK_READONLY, (VOID**)&pwPoly);
    BYTE* pbVertices           = NULL;
    FLOAT* pfVetices           = NULL;
    LPDIRECT3DVERTEXBUFFER9 VB = NULL;
    pMesh->GetVertexBuffer(&VB);
    if(SUCCEEDED(VB->Lock(0, 0, (VOID**)&pbVertices, 0)))
    {
        for(int nCount = 0; nCount < 3; nCount++)
        {
            pfVetices              = (FLOAT*)&pbVertices[dwStride * pwPoly[dwPolyIndex * 3 + nCount]];
            pvecVertices[nCount].x = pfVetices[0];
            pvecVertices[nCount].y = pfVetices[1];
            pvecVertices[nCount].z = pfVetices[2];
        }
        pMesh->UnlockIndexBuffer();
        VB->Unlock();
    }
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//壁ずりベクトル生成
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
D3DXVECTOR3 CPlayer::CalcWallScratchVector(const D3DXVECTOR3 move, const D3DXVECTOR3 nomal)
{
    return move - ((D3DXVec3Dot(&nomal, &move)) / (float)(pow(D3DXVec3Length(&nomal), 2))) * nomal;
}

//=============================================================================
// パーツアップデート関数
//=============================================================================
void CPlayer::PartsUpdate(void)
{
    if(m_pAnime != NULL)
    {
        for(int nCount = 0; nCount < PARTS_MAX /*(読み込んだモデル数分)*/; nCount++)
        {
            m_apModel[nCount]->SetAnimationRot(m_Partsrot[nCount]);
            m_apModel[nCount]->SetAnimationPos(m_Partspos[nCount]);
        }
        m_pAnime->Update();
        for(int nCount = 0; nCount < PARTS_MAX /*(読み込んだモデル数分)*/; nCount++)
        {
            m_Partsrot[nCount] = m_pAnime->GetAnimeRot(nCount);
            m_Partspos[nCount] = m_pAnime->GetAnimePos(nCount);
            m_pAnime->SetAnimeRot(nCount, m_Partsrot[nCount]);
            m_pAnime->SetAnimePos(nCount, m_Partspos[nCount]);
        }
    }
}

//=============================================================================
// アニメーションコントロール関数
//=============================================================================
void CPlayer::AnimaControl(void)
{
    //ステートスイッチ
    switch(m_state)
    {
            //ニュートラル
        case STATE_STAND:
            m_AnimaMotion = CAnimation::MOTION_PLAYER_NEUTRAL;
            break;
            //歩き
        case STATE_WALK:
            m_AnimaMotion = CAnimation::MOTION_PLAYER_MOVE;
            break;
            //走り
        case STATE_SPRINT:
            m_AnimaMotion = CAnimation::MOTION_PLAYER_SPRINT;
            break;
            //しゃがみ
        case STATE_CROUCH:
            m_AnimaMotion = CAnimation::MOTION_PLAYER_CROUCHING;
            break;
            //しゃがみ歩き
        case STATE_CROUCH_WALK:
            m_AnimaMotion = CAnimation::MOTION_PLAYER_CROUCHING_MOVE;
            break;
            //エイム
        case STATE_AIM:
            m_AnimaMotion = CAnimation::MOTION_PLAYER_AIM;
            break;
            //リロード
        case STATE_RELOAD:
            m_AnimaMotion = CAnimation::MOTION_PLAYER_RELOAD;
            break;
            //リロード歩き
        case STATE_RELOAD_WALK:
            m_AnimaMotion = CAnimation::MOTION_PLAYER_RELOAD_MOVE;
            break;
            //死
        case STATE_DEATH:
            m_AnimaMotion = CAnimation::MOTION_PLAYER_DEATH;
            break;
        default:
			assert(false);
            break;
    }
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//アイテムを追加
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CPlayer::AddItem(void)
{
    m_apItemUI[m_nHaveItem] = CItem_ui::Create(D3DXVECTOR3(SCREEN_WIDTH - 100.0f, SCREEN_HEIGHT - 300.0f - m_nHaveItem * 100.0f, 0.0f));
    m_nHaveItem++;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//入力を方向に変換
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
float CPlayer::InputToAngle(CInputKeyboard* const pInputKey)
{
    //移動
    if(pInputKey->GetKeyPress(DIK_W))
    {
        //移動方向指定
        m_fMoveVector = 270.0f;
    }
    if(pInputKey->GetKeyPress(DIK_S))
    {
        //移動方向指定
        m_fMoveVector = 90.0f;
    }
    if(pInputKey->GetKeyPress(DIK_A))
    {
        //移動方向指定
        m_fMoveVector = 0.0f;
        //同時押しの処理
        if(pInputKey->GetKeyPress(DIK_W))
        {
            m_fMoveVector = 315.0f;
        }
        else if(pInputKey->GetKeyPress(DIK_S))
        {
            m_fMoveVector = 45.0f;
        }
    }
    if(pInputKey->GetKeyPress(DIK_D))
    {
        //移動方向指定
        m_fMoveVector = 180.0f;
        //同時押しの処理
        if(pInputKey->GetKeyPress(DIK_W))
        {
            m_fMoveVector = 225.0f;
        }
        else if(pInputKey->GetKeyPress(DIK_S))
        {
            m_fMoveVector = 135.0f;
        }
    }
    return m_fMoveVector;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//移動速度変更
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
float CPlayer::ChangeMoveSpeed(void)
{
    float fMoveSpeed = NULL;
    //それぞれの状態に割り当てられた移動速度を代入
    switch(m_state)
    {
        case STATE_SPRINT:
            fMoveSpeed = PLAYER_MOVE_SPEED_SPRINT;
            break;
        case STATE_CROUCH_WALK:
            fMoveSpeed = PLAYER_MOVE_SPEED_CROUCH;
            break;
        case STATE_AIM:
            fMoveSpeed = PLAYER_MOVE_SPEED_AIM;
            break;
        case STATE_RELOAD:
            fMoveSpeed = 0.0f;
            break;
        case STATE_RELOAD_WALK:
            fMoveSpeed = PLAYER_MOVE_SPEED_AIM;
            break;
        case STATE_DEATH:
            fMoveSpeed = 0.0f;
            break;
        default:
            fMoveSpeed = PLAYER_MOVE_SPEED;
            break;
    }

	//武器ごとの移動速度の倍率を設定
	float fMoveRate = 0.0f;
	switch (CManager::GetWeaponsMode())
	{
	case CManager::WEAPONS_MODE_AR:
		fMoveRate = AR_MOVE_RATE;
		break;
	case CManager::WEAPONS_MODE_HG:
		fMoveRate = HG_MOVE_RATE;
		break;
	default:
		assert(false);
		break;
	}
    return fMoveSpeed *= fMoveRate;;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//移動
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CPlayer::Move(CInputKeyboard* const pInputKey)
{
    D3DXVECTOR3 move = ZEROVECTOR3;                       //移動量
    D3DXVECTOR3 HittedPolyNormal[COLLISION_RAY_COUNT];    //レイが当たったメッシュの法線
    int nCountHit = 0;                                    //当たったメッシュの数

    m_fMoveVector = InputToAngle(pInputKey);
    m_fMoveVector += m_rot.y;
    if(m_fMoveVector < 0)
    {
        m_fMoveVector += 360;
    }
    if(m_fMoveVector > 360)
    {
        m_fMoveVector -= 360;
    }

    //移動速度設定
    float fMoveSpeed = ChangeMoveSpeed();

    //代入された移動速度をもとに移動するベクトルを生成
    move = D3DXVECTOR3(fMoveSpeed * cosf(D3DXToRadian(m_fMoveVector)), 0, fMoveSpeed * sinf(D3DXToRadian(m_fMoveVector)));

    if(Collision(CManager::GetStageModel()->GetModelData(), HittedPolyNormal, &nCountHit))    //壁に触れた場合
    {
        for(int nCount = 0; nCount < nCountHit; nCount++)
        {
            float NormalRot            = D3DXToDegree(atan2f(HittedPolyNormal[nCount].z, HittedPolyNormal[nCount].x));
            float CollisionRotRange[2] = {};
            CollisionRotRange[0]       = NormalRot - 90;
            CollisionRotRange[1]       = NormalRot + 90;
            for(int nCountRange = 0; nCountRange < 2; nCountRange++)
            {
                if(CollisionRotRange[nCountRange] < 0)
                {
                    CollisionRotRange[nCountRange] += 360;
                }
                if(CollisionRotRange[nCountRange] > 360)
                {
                    CollisionRotRange[nCountRange] -= 360;
                }
            }
            if(CollisionRotRange[0] > CollisionRotRange[1])
            {
                if(CollisionRotRange[0] > m_fMoveVector && CollisionRotRange[1] < m_fMoveVector)
                {
                    move = CalcWallScratchVector(move, HittedPolyNormal[nCount]);    //壁ずりベクトルを計算
                }
            }
            else
            {
                if(CollisionRotRange[0] > m_fMoveVector || CollisionRotRange[1] < m_fMoveVector)
                {
                    move = CalcWallScratchVector(move, HittedPolyNormal[nCount]);    //壁ずりベクトルを計算
                }
            }
        }
    }
    //位置に移動量を足す
    m_pos += move;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//アイテム使用
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CPlayer::UseItem(CSound* const pSound)
{
    pSound->PlaySoundA(CSound::SOUND_LABEL_SE_HEAL);
    m_nHaveItem--;
    m_apItemUI[m_nHaveItem]->Uninit();
    m_apItemUI[m_nHaveItem] = NULL;
    m_nLife                 = START_LIFE;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//リロード開始処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CPlayer::BeginReload(CSound* const pSound, const bool bMove)
{
    pSound->PlaySoundA(CSound::SOUND_LABEL_SE_MAGAZINEOUT);
    if(bMove)
    {
        m_state = STATE_RELOAD_WALK;
    }
    else
    {
        m_state = STATE_RELOAD;
    }
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//リロード終了処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CPlayer::EndReload(CSound* const pSound)
{
    if(m_state == STATE_RELOAD || m_state == STATE_RELOAD_WALK)
    {
        //残弾数が0以下の場合、0に戻す
        if(m_nRemainingAmmo <= 0)
        {
            m_nRemainingAmmo = 0;
        }
        //リロードした時にBulletUIを再クリエイト
        for(int nCountBullet = m_nRemainingAmmo; nCountBullet < m_nMagazineSize; nCountBullet++)
        {
            m_pBulletUi[nCountBullet] = CBullet_ui::Create(D3DXVECTOR3((SCREEN_WIDTH - (15.0f + (15.0f * nCountBullet))), (SCREEN_HEIGHT - 70.0f), 0.0f));
        }

        m_nRemainingAmmo = m_nMagazineSize;
        m_state          = STATE_STAND;
        pSound->PlaySoundA(CSound::SOUND_LABEL_SE_MAGAZINESET);
    }
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//状態変更
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CPlayer::ChangeState(CInputKeyboard* const pInputKey, CInputMouse* const pInputMou, CSound* const pSound, const bool bMove)
{
    //リロード時の歩きと立ち止まりの切り替え
    if(m_state == STATE_RELOAD && bMove)
    {
        m_state = STATE_RELOAD_WALK;
    }
    else if(m_state == STATE_RELOAD_WALK && bMove == false)
    {
        m_state = STATE_RELOAD;
    }

    if(m_state != STATE_RELOAD && m_state != STATE_RELOAD_WALK)
    {
        if(pInputMou->GetKeyTrigger(CInputMouse::MOUSE_BUTTON_RIGHT))    //右クリック時はAIM
        {
            pSound->PlaySoundA(CSound::SOUND_LABEL_SE_AIM);
        }
        if(pInputMou->GetKeyPress(CInputMouse::MOUSE_BUTTON_RIGHT))    //右クリック時はAIM
        {
            m_state = STATE_AIM;
            //クロスヘアが無い場合はクロスヘアを生成する
            if(m_pCrosshair == NULL)
            {
                m_pCrosshair = CCrosshair::Create(30.0f);
            }
        }
        else if(pInputKey->GetKeyPress(DIK_LSHIFT) && bMove)    // LSHIFTが押下されているかつ移動中ならスプリント
        {
            m_state = STATE_SPRINT;
        }
        else if(pInputKey->GetKeyPress(DIK_LCONTROL) && bMove)
        {
            m_state = STATE_CROUCH_WALK;
        }
        else if(pInputKey->GetKeyPress(DIK_LCONTROL) && bMove == false)    // LCONTROLが押下されているされている場合はしゃがみ
        {
            m_state = STATE_CROUCH;
        }
        else if(bMove)
        {
            m_state = STATE_WALK;
        }
        else    //上記のどれにも当てはまらない場合通常
        {
            m_state = STATE_STAND;
        }
    }
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//銃を撃つ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CPlayer::Shot(const int nBulletDamage, const float fSpread, CSound* const pSound)
{
    pSound->PlaySoundA(CSound::SOUND_LABEL_SE_ASSAULT);
    CObject* pHitObject = GetHitObject();    //当たり判定されたオブジェクトを取得
    m_Weapons_UI->Gleams();
    //バレットUIが存在するなら弾が消費されたタイミングでUninitする
    if(m_pBulletUi[m_nRemainingAmmo] != NULL && m_nRemainingAmmo >= 0)
    {
        m_pBulletUi[m_nRemainingAmmo]->Uninit();
    }
    if(pHitObject != NULL)
    {
        if(((CModel*)pHitObject)->GetParentObject() != NULL)
        {
            switch(((CModel*)pHitObject)->GetParentObject()->GetObjType())    //当たったモデルの親オブジェクトのタイプによって処理を変える
            {
                case OBJTYPE_ENEMY:
                    ((CEnemy*)((CModel*)pHitObject)->GetParentObject())->Hit(nBulletDamage);
                    break;
                case OBJTYPE_STAGE:
                    break;
                default:
                    ((CModel*)pHitObject)->GetParentObject()->Uninit();
                    break;
            }
        }
    }
    m_pCrosshair->AddSpread(fSpread);    //クロスヘアの拡散を増やす
}
