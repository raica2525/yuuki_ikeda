//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	player.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#ifndef _PLAYER_H_
#define _PLAYER_H_

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "animation.h"
#include "main.h"
#include "manager.h"
#include "model.h"
#include "object.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//マクロ定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#define START_LIFE (100)
#define ASSAULT_RIFLE_RATE (5)
#define HANDGUN_RATE (5)
#define PLAYER_MODEL_COUNT (16)
#define PLAYER_MOVE_SPEED (1.0f)
#define PLAYER_MOVE_SPEED_SPRINT (1.5f)
#define PLAYER_MOVE_SPEED_AIM (0.75f)
#define PLAYER_MOVE_SPEED_CROUCH (0.5f)
#define COLLISION_RAY_COUNT (16)
#define PLAYER_COLLISION_HEIGHT (5.0f)
#define PLAYER_COLLISION_RADIUS (7.5f)
#define SENSI_RATE (0.01f)
#define START_SENSI (15.0f)
#define GAMEOVER_COUNT (180)
#define MAGAZINE_SIZE_AR (30)
#define MAGAZINE_SIZE_HG (16)
#define MAX_ITEM (5)
#define PLAYER_HEAD_HEIGHT (37.0f)
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//前方宣言
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CAnimation;
class CCrosshair;
class CInputKeyboard;
class CInputMouse;
class CDamage_ui;
class CBullet_ui;
class CItem_ui;
class CWeapons_ui;

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CPlayer : public CObject
{
public:
    typedef enum    //パーツ
    {
        PARTS_CHEST,             //胸
        PARTS_BELLY,             //腹
        PARTS_WAIST,             //腰
        PARTS_HEAD,              //頭
        PARTS_RIGHT_SHOULDER,    //右肩
        PARTS_RIGHT,             //右腕
        PARTS_RIGHT_HAND,        //右手
        PARTS_LEFT_SHOULDER,     //左肩
        PARTS_LEFT,              //左腕
        PARTS_LEFT_HAND,         //左手
        PARTS_RIGHT_THIGHS,      //右太もも
        PARTS_RIGHT_CALF,        //右ふくらはぎ
        PARTS_RIGHT_FOOT,        //右足
        PARTS_LEFT_THIGHS,       //左太もも
        PARTS_LEFT_CALF,         //左ふくらはぎ
        PARTS_LEFT_FOOT,         //左足
        PARTS_MAX
    } PLAYER_PARTS;

    typedef enum
    {
        STATE_STAND = 0,
        STATE_WALK,
        STATE_SPRINT,
        STATE_CROUCH,
        STATE_CROUCH_WALK,
        STATE_AIM,
        STATE_RELOAD,
        STATE_RELOAD_WALK,
        STATE_DEATH,
        STATE_MAX
    } STATE;

    CPlayer();
    ~CPlayer();

    HRESULT Init(void);    //初期化処理
    void Uninit(void);     //終了処理
    void Update(void);     //更新処理
    void Draw(void);       //描画処理

    static CPlayer* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);    //生成処理

    static void Load(void);      //ファイルデータ読み込み
    static void Unload(void);    //ファイルデータ破棄

    //ゲッター関数
    D3DXVECTOR3 GetPos(void);
    D3DXVECTOR3 GetPartsPos(int nParts);
    D3DXVECTOR3 GetCenter(void);
    D3DXVECTOR3 GetRot(void);
    STATE GetState(void);
    int GetLife(void);

    void AddLife(int Value);    //ライフ増加
    void AddItem(void);         //アイテム追加
private:
    typedef struct
    {
        char* FileName;          //ファイルの名前
        int nParent;             //親パーツ
        D3DXVECTOR3 Partspos;    //パーツ座標
    } PARTS_DATA;

    void PartsUpdate(void);                                                                                //パーツアップデート関数
    void AnimaControl(void);                                                                               //アニメーションコントロール関数
    BOOL CheckHitBullet(CModel::MODELDATA modeldata, BOOL* pHit, float* pDistance, D3DXVECTOR3 spread);    //弾丸(レイ)がモデルに当たっれいるかどうか
    CObject* GetHitObject(void);                                                                           //弾丸(レイ)が当たっているオブジェクト取得
    BOOL Collision(CModel::MODELDATA modeldata, D3DXVECTOR3* pHittedPolyNormal, int* pCountHit);           //壁との当たり判定
    void FindVerticesOnPoly(LPD3DXMESH pMesh, DWORD dwPolyIndex, D3DXVECTOR3* pvecVertices);               //メッシュ頂点座標取得
    D3DXVECTOR3 CalcWallScratchVector(D3DXVECTOR3 move, D3DXVECTOR3 nomal);                                //壁摺りベクトル計算
    float InputToAngle(CInputKeyboard* pInputKey);                                                         //キーボード入力を角度に変換
    float ChangeMoveSpeed(void);                                                                           //移動速度を変更
    void Move(CInputKeyboard* pInputKey);                                                                  //移動
    void UseItem(CSound* pSound);                                                                          //アイテム使用
    void BeginReload(CSound* pSound, bool bMove);                                                          //リロード開始
    void EndReload(CSound* pSound);                                                                        //リロード終了
    void ChangeState(CInputKeyboard* pInputKey, CInputMouse* pInputMou, CSound* pSound, bool bMove);       //ステート変更
    void Shot(int nBulletDamage, float fSpread, CSound* pSound);                                           //射撃

    D3DXVECTOR3 m_pos;     //位置
    D3DXVECTOR3 m_rot;     //向き
    D3DXVECTOR3 m_size;    //大きさ

    int m_nLife;             //ライフ
    int m_nRemainingAmmo;    //残弾数
    int m_nMagazineSize;     //最大弾数
    int m_nHaveItem;         //アイテム所持数

    float m_fMoveVector;           //移動方向
    static int m_nFrameCounter;    //フレームカウンター
    STATE m_state;                 //状態
    static int m_nSensi;           //マウス感度

    static PARTS_DATA m_PartsData[PARTS_MAX];                                  //パーツ情報
    static char* m_PartsWeapon[CManager::WEAPONS_MODE_MAX];                    //武器パーツの情報
    D3DXVECTOR3 m_Partsrot[PARTS_MAX];                                         //パーツrot情報
    D3DXVECTOR3 m_Partspos[PARTS_MAX];                                         //パーツpos情報
    D3DXVECTOR3 m_PartsSize[PARTS_MAX];                                        //パーツsize情報
    static CAnimation* m_pAnimaSave;                                           //アニメーション保存ポインタ
    CAnimation* m_pAnime;                                                      //アニメーションポインタ
    CAnimation::MOTION_PLAYER m_AnimaMotion;                                   //アニメーションパターン
    CModel* m_apModelWorld;                                                    //ワールド座標取得用モデル
    CModel* m_apModel[PARTS_MAX];                                              //モデルポインタ
    static CModel::MODELDATA m_modeldata[PARTS_MAX];                           //モデル情報
    static CModel::MODELDATA m_modelWeaponData[CManager::WEAPONS_MODE_MAX];    //モデルウェポン情報
    static D3DXMATERIAL* m_pMat;                                               //マテリアル情報

    CCrosshair* m_pCrosshair;                     //クロスヘアのポインタ
    CDamage_ui* m_pDamageUi;                      //ダメージUIのポインタ
    CBullet_ui* m_pBulletUi[MAGAZINE_SIZE_AR];    //残弾数UIのポインタ
    CItem_ui* m_apItemUI[MAX_ITEM];               //アイテムUIのポインタ
    CWeapons_ui* m_Weapons_UI;                    //武器UIのポインタ
};
#endif
