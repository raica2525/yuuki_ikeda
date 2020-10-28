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

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CLaser : public CScene
{
public:
	CLaser();		//コンストラクタ
	~CLaser();	//デストラクタ

	typedef enum
	{
		LASERTYPE_STRONG_STRAIGHT = 0,
		LASERTYPE_WEEK_DIAGONAL,
		LASERTYPE_MAX
	}LASERTYPE;

	HRESULT Init(void);	//初期化処理
	void Uninit(void);		//終了処理
	void Update(void);		//更新処理
	void Draw(void);		//描画処理

	static void Create(D3DXVECTOR3 pos, D3DCOLOR col, int nWidth, float fRot, int nDamage, bool bPenetrate);	//ポリゴン生成処理

private:
	bool CheckCollision(D3DXVECTOR3* pObjVtx);
	int CheckSide(D3DXVECTOR3* pObjVtx);
	CPolygon* m_pPolygon;
	CLaserLayer* m_pLaserLayer;
	int m_nDamage;
	D3DXVECTOR3 m_pos;
	D3DCOLOR m_col;
	int m_nWidth;
	float m_fRot;
	bool m_bHit;
	D3DXVECTOR3 m_vtxPos[NUM_VERTEX];
	bool m_bPenetrate;
};

#endif