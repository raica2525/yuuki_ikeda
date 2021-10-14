//=============================================================================
//
// 敵 [enemy.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "model.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TOUR_MAX 8	//巡回する最大位置
//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CQuestion;
class CExclamationMark;
//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CEnemy :public CObject
{
public:

	//状態タイプ
	typedef enum
	{
		ENEMY_NONE = -1,
		ENEMY_TOUR,		//通常・巡回
		ENEMY_WARY,			//警戒
		ENEMY_FOUND,		//プレイヤー発見
		ENEMY_MAX
	} ENEMY_MODE;

	typedef enum
	{
		STATE_NONE = -1,
		STATE_NORMAL,		//通常
		STATE_DAMAGE,		//ダメージを食らう
		STATE_DEATH,		//破壊される
		STATE_MAX
	} ENEMY_STATE;

	CEnemy();
	virtual ~CEnemy();
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	void SetPos(D3DXVECTOR3(pos));
	void SetRot(D3DXVECTOR3(rot));
	void SetSize(D3DXVECTOR3(size));
	void SetTour(int nTour, D3DXVECTOR3(pos));
	void SetMode(ENEMY_MODE mode);
	void SetLife(int nLife);
	void SetState(ENEMY_STATE state);

	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }

	void Hit(int nDamage);
	void Attack(int nDamage);
	
	bool Tour(void);
	
	void Direction(D3DXVECTOR3(pos));	
	bool Search(const float fRangeDistance, const float fViesswingAngle);
	bool Found(void);
	BOOL CheckSearch(CModel::MODELDATA modeldata,float *fDistance);
	CModel *GetWorld(void) { return m_pModel; }
	ENEMY_MODE GetMode(void){ return m_Mode; }
	ENEMY_STATE GetState(void) { return m_State; }
	void SetQuestion(CQuestion * pQuestion);
	CQuestion *GetQuestion(void) { return m_pQuestion; }
	void SetExclamation(CExclamationMark * pExclamation);
	CExclamationMark *GetExclamation(void) { return m_pExclamation; }
private:
	void SubLife(int nSublife);	//体力セット
	CModel* m_pModel;			//モデルポインタ
	D3DXVECTOR3 m_pos;			//位置
	D3DXVECTOR3 m_move;			//移動量
	D3DXVECTOR3 m_rot;			//向き
	D3DXVECTOR3 m_size;			//サイズ
	int m_nLife;				//体力
	ENEMY_MODE m_Mode;			//エネミーモード
	ENEMY_STATE m_State;		//ステータ状態

	D3DXVECTOR3	m_TourPos[TOUR_MAX];			//巡回位置
	int m_TourMax;								//巡回する位置の最大数
	int m_TourCount;							//現在の巡回位置
	CQuestion * m_pQuestion;
	CExclamationMark * m_pExclamation;
	int m_nAttack_SE;
};
#endif