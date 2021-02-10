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
#include "main.h"
#include "scene2d.h"
#include "laser.h"
class CLife;
class CEnergy;
class CNumber;
class CCursol;
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CPlayer : public CScene2d
{
public:
    CPlayer();     //コンストラクタ
    ~CPlayer();    //デストラクタ

    typedef enum
    {
        STATE_NORMAL = 0,
        STATE_DAMAGE,
        STATE_MAX
    } STATE;

    HRESULT Init(void);    //初期化処理
    void Uninit(void);     //終了処理
    void Update(void);     //更新処理
    void Draw(void);       //描画処理
    static HRESULT Load(void);
    static void Unload(void);
    void HitBullet(void);
    static void Create(D3DXVECTOR3 pos);    //ポリゴン生成処理
    void SetOverHeat(bool bOverHeat);
    int CheckSide(D3DXVECTOR3* pObjVtx);
    CLife* GetLife(void);

private:
    CPolygon* m_pPolygon;
    CNumber* m_CountNumber;
    int m_nMoveVector;
    CLife* m_pLife;
    CEnergy* m_pEnergy;
    static LPDIRECT3DTEXTURE9 m_pTexture;    // テクスチャへのポインタ
    static LPDIRECT3DTEXTURE9 m_pTextureUI;
    STATE m_state;
    int m_nStateCount;
    bool m_bOverHeat;
    D3DXVECTOR3 m_posOld;
    CLaser::LASERTYPE LaserType;
    int m_nCountFrame;
    CCursol* m_pCursol;
};

#endif
