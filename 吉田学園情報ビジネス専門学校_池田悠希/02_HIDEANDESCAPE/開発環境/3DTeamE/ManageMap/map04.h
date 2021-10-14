//=============================================================================
//
// マップ04 [map04.h]
// Author : 二階堂汰一・吉田悠人
//
//=============================================================================
#ifndef _MAP04_H_
#define _MAP04_H_
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "gamemode.h"
#include "main.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CCamera;
class CStage04;
class CPlayer;
class CObstacle;
class CLightEnemy;
class CHeavyEnemy;
class CObstacle;
//*****************************************************************************
// クラス定義
//*****************************************************************************
class CMap04 : public ICGamemode
{
public:
	CMap04();
	~CMap04();
	HRESULT Init(void);
	void Update(void);
	void Draw(void);
	void Uninit(void);
private:
	CCamera* m_pCamera;			//カメポインタ
	CPlayer* m_pPlayer;			//プレイヤーポインタ		
	CStage04* m_pStage04;		//マップモデルポインタ
	CObstacle* m_pObstacle;		//障害物ポインタ
	CLightEnemy *m_pLightEnemy[6];		//軽装エネミーポインタ
	CHeavyEnemy *m_pHeavyEnemy[1];		//重装エネミーポインタ
	bool bCollEnemy[3];					//エネミーが増えているか

};
#endif
