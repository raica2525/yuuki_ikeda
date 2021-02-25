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
//・・・・・・・・x・・・・・・・・・・・・・・・・・・・
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
#define START_SENSI (15)
#define GAMEOVER_COUNT (180)
#define MAGAZINE_SIZE_AR (30)
#define MAGAZINE_SIZE_HG (16)
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//前方宣言
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CAnimation;
class CCrosshair;
class CInputKeyboard;
class CDamage_ui;
class CBullet_ui;
class CItem_ui;
class CWeapons_ui;
//*****************************************************************************
// クラス定義
//*****************************************************************************
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
    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    void Draw(void);
    static CPlayer* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);
    static void Load(void);
    static void Unload(void);

    D3DXVECTOR3 GetPos(void);
    D3DXVECTOR3 GetPartsPos(int nParts);
	D3DXVECTOR3 GetCenter(void);
    D3DXVECTOR3 GetRot(void);
    STATE GetState(void);

    void AddLife(int Value);
    int GetLife(void);
	void AddItem(void);
private:
    typedef struct
    {
        char* FileName;          //ファイルの名前
        int nParent;             //親パーツ
        D3DXVECTOR3 Partspos;    //パーツ座標
    } PARTS_DATA;

    void PartsUpdate(void);     //パーツアップデート関数
    void AnimaControl(void);    //アニメーションコントロール関数
    BOOL CheckHitBullet(CModel::MODELDATA modeldata, BOOL* pHit, float* pDistance, D3DXVECTOR3 spread);
    CObject* GetHitObject(void);
    BOOL Collision(CModel::MODELDATA modeldata, D3DXVECTOR3* pHittedPolyNormal, int* pCountHit);
    void FindVerticesOnPoly(LPD3DXMESH pMesh, DWORD dwPolyIndex, D3DXVECTOR3* pvecVertices);
    D3DXVECTOR3 CalcWallScratchVector(D3DXVECTOR3 move, D3DXVECTOR3 nomal);

    static PARTS_DATA m_PartsData[PARTS_MAX];                                  //パーツ情報
    static char* m_PattsWeapon[CManager::WEAPONS_MODE_MAX];                    //武器パーツの情報
    D3DXVECTOR3 m_Partsrot[PARTS_MAX];                                         //パーツrot情報
    D3DXVECTOR3 m_Partspos[PARTS_MAX];                                         //パーツpos情報
    D3DXVECTOR3 m_Partssize[PARTS_MAX];                                        //パーツsize情報
    static CAnimation* m_pAnimaSave;                                           //アニメーション保存ポインタ
    CAnimation* m_pAnima;                                                      //アニメーションポインタ
    CAnimation::MOTION_PLAYER m_AnimaMotion;                                   //アニメーションパターン
    CModel* m_apModelWorld;                                                    //ワールド座標取得用モデル
    CModel* m_apModel[PARTS_MAX];                                              //モデルポインタ
    static CModel::MODELDATA m_modeldata[PARTS_MAX];                           //モデル情報
    static CModel::MODELDATA m_modelWeaponData[CManager::WEAPONS_MODE_MAX];    //モデルウェポン情報
    static D3DXMATERIAL* m_pMat;
    D3DXVECTOR3 m_pos;    //位置
    D3DXVECTOR3 m_rot;         //向き
    D3DXVECTOR3 m_AnimaRot;    //アニメーション向き
    float m_fMoveVector;       //移動方向
    D3DXVECTOR3 m_size;
    STATE m_state;
    int m_nLife;
    CCrosshair* m_pCrosshair;
    static int m_nSensi;
    CDamage_ui* m_pDamageUi;    //ダメージUIのポインタ
    CBullet_ui* m_pBulletUi[MAGAZINE_SIZE_AR];
	int m_nRemainingAmmo;
	int m_nMagazineSize;		//最大弾数
	int m_nHaveItem;
	CItem_ui* m_apItemUI[5];
	CWeapons_ui *m_Weapons_UI;
};
#endif
