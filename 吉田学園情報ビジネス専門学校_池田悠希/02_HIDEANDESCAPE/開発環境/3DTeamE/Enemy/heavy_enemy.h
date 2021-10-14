//=============================================================================
//
// 重武装機 [heavy_enemy.h]
// Author : 吉田悠人 二階堂汰一
//
//=============================================================================
#ifndef _HEAVY_ENEMY_H_
#define _HEAVY_ENEMY_H_
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "enemy.h"
#include "model.h"
#include "animation.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 構造体定義
//*****************************************************************************
//*****************************************************************************
//前方宣言
//*****************************************************************************
class CAnimation;
//*****************************************************************************
// クラス定義
//*****************************************************************************
class CHeavyEnemy :public CEnemy
{
public:
	//パーツ
	typedef enum
	{
		PARTS_NONE = -1,
		PARTS_BODY,
		PARTS_RIGHT_THIGHS,
		PARTS_RIGHT_FOOT,
		PARTS_RIGHT_RIGHT,
		PARTS_LEFT_THIGHS,
		PARTS_LEFT_FOOT,
		PARTS_LEFT_RIGHT,
		PARTS_MAX
	}PARTS;

	//ステータス
	typedef enum
	{
		STATE_NONE = -1,
		STATE_MOVE,
		STATE_MAX
	}STATE;

	CHeavyEnemy();
	~CHeavyEnemy();
	static HRESULT Load(void);
	static void Unload(void);
	static CHeavyEnemy* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	void PartsUpdate(void);

	typedef struct
	{
		char *FileName;			//ファイルの名前
		int nParent;			//親パーツ
		D3DXVECTOR3 Partspos;	//パーツ座標
	}PARTS_DATA;

	static PARTS_DATA m_PartsData[PARTS_MAX];	//パーツ情報
	D3DXVECTOR3 m_Partsrot[PARTS_MAX];			//パーツrot情報
	D3DXVECTOR3 m_Partspos[PARTS_MAX];			//パーツpos情報
	static CAnimation *m_pAnimaSave;			//アニメーション保存ポインタ
	CAnimation *m_pAnime;						//アニメーションポインタ
	CAnimation::MOTION_HEAVY_ENEMY m_AnimaMotion;	//モーションセット

	static CModel::MODELDATA m_modeldata[PARTS_MAX];	//モデルデータ
	CModel* m_apModel[PARTS_MAX];

	int m_nLife;		//ライフ
	float m_fSpeed;		//スピード
	bool m_bSearch;		//捜してるかどうか
	int nWaryCoutn;		//警戒カウント
	bool m_bWary;		//?
	bool m_bDiscovery;	//!
};
#endif