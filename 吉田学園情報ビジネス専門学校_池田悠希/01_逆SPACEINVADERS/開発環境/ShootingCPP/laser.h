//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	laser.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

#ifndef _LASER_H_
#define _LASER_H_
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "main.h"
#include "scene.h"
#include "polygon.h"
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//前方宣言
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

class CLaserLayer;
class CScene2d;
class CEnemy;
class CScore;
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CLaser : public CScene
{
public:
    CLaser();     //コンストラクタ
    ~CLaser();    //デストラクタ

    typedef enum
    {
        LASERTYPE_STRONG_STRAIGHT = 0,
        LASERTYPE_WEEK_DIAGONAL,
        LASERTYPE_MAX
    } LASERTYPE;

    HRESULT Init(void);    //初期化処理
    void Uninit(void);     //終了処理
    void Update(void);     //更新処理
    void Draw(void);       //描画処理

    static void Create(D3DXVECTOR3 pos, D3DCOLOR col, int nWidth, float fRot, int nDamage, bool bPenetrate);    //ポリゴン生成処理
	

private:
    bool CheckCollision(D3DXVECTOR3* pObjVtx);	//当たり判定
	void GetHittedObject(CScene** pScene, CEnemy** apHitEnemy, int* pHitEnemyCount, CEnemy** pClosestEnemy, CScene2d** pClosestTile);	//レーザーがあたったオブジェクトを取得
	void HitTile(CScene2d* pTile, CScore* pScore);	//タイルにあたったときの処理
	void SetLaserSize(D3DXVECTOR3 size);			//大きさ設定
    CPolygon* m_pPolygon;							//レーザーの本体
    CLaserLayer* m_pLaserLayer;						//レーザーの色変更用ポリゴン
    int m_nDamage;									//レーザーのダメージ
    D3DXVECTOR3 m_pos;								//座標
    D3DCOLOR m_col;									//色
    int m_nWidth;									//太さ
    float m_fRot;									//角度
    bool m_bHit;									//あたっているか
    D3DXVECTOR3 m_vtxPos[NUM_VERTEX];				//頂点座標
    bool m_bPenetrate;								//貫通属性
};

#endif
