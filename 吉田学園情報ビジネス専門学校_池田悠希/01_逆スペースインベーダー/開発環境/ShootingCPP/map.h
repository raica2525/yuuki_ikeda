//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	map.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

#ifndef _MAP_H_
#define _MAP_H_
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "main.h"
#include "scene.h"

class CScene2d;
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CMap : public CScene
{
public:
    CMap();     //コンストラクタ
    ~CMap();    //デストラクタ

    typedef enum
    {
        TILE_TYPE_NONE = 0,
        TILE_TYPE_BLOCK,
        TILE_TYPE_BRAKABLE_BLOCK,
        TILE_TYPE_ENEMY_CANON_UP,
        TILE_TYPE_ENEMY_CANON_DOWN,
        TILE_TYPE_ENEMY_SPLINKLER,
        TILE_TYPE_ENEMY,
        TILE_TYPE_MAX
    } TILE_TYPE;

    static HRESULT Load(void);
    static void Unload(void);
    static CMap* Create();    //ポリゴン生成処理

    HRESULT Init();       //初期化処理
    void Uninit(void);    //終了処理
    void Update(void);    //更新処理
    void Draw(void);      //描画処理
    static int GetLength(void);
    static void SetGoal(bool bGoal);
    static bool GetGoal(void);

private:
    CScene2d* m_apScene2d[MAX_MAP_HEIGHT * MAX_MAP_WIDTH];
    static LPDIRECT3DTEXTURE9 m_apTexture[TILE_TYPE_MAX];    // テクスチャへのポインタ
    TILE_TYPE m_mapData[MAX_MAP_HEIGHT][MAX_MAP_WIDTH];
    static D3DXVECTOR2 m_mapSize;
    static bool m_bGoal;
};

#endif
