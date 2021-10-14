//=============================================================================
//
// 偵察機 [uav.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _UAV_H_
#define _UAV_H_
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "enemy.h"
#include "model.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CUav :public CEnemy
{
public:
	typedef enum
	{
		STATE_NONE = -1,
		STATE_MOVE,
		STATE_MAX
	}STATE;
	CUav();
	 ~CUav();
	static HRESULT Load(void);
	static void Unload(void);
	static CUav* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool EnemyCall(void);
private:
	static CModel::MODELDATA m_modeldata;
	static D3DXMATERIAL *m_pMat;
	CModel* m_pModel;
	int m_nLife;		//ライフ
	float m_fSpeed;		//スピード
	bool m_bSearch;		//捜してるかどうか
	int nWaryCoutn;		//警戒カウント
	bool m_bWary;		//?
	bool m_bDiscovery;	//!
	int m_nFly;			//飛ぶカウント

	bool bCall;			//発見したとき敵を呼び出したか
};
#endif