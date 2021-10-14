//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	enemy.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

#ifndef _ENEMY_H_
#define _ENEMY_H_
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "main.h"
#include "scene2d.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CEnemy : public CScene2d
{
public:
    CEnemy();     //コンストラクタ
    ~CEnemy();    //デストラクタ
    typedef enum
    {
        TYPE_NORMAL = 0,
        TYPE_SPRINKLER,
        TYPE_CANON_UP,
        TYPE_CANON_DOWN,
        TYPE_MAX
    } TYPE;
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

    static void Create(D3DXVECTOR3 pos, TYPE type);    //ポリゴン生成処理
    void HitLaser(int nDamage);
    STATE GetState(void);

private:
    static LPDIRECT3DTEXTURE9 m_apTexture[TYPE_MAX];    // テクスチャへのポインタ
    int m_nLife;
    STATE m_state;
    int m_nShotCount;
    TYPE m_type;
    int m_nBulletRot;
};

#endif
