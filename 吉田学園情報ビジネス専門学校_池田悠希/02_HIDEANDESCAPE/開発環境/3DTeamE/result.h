//=============================================================================
//
// リザルト [result.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_
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
class CResultScene;
class CMission;
class CClear;
//*****************************************************************************
// クラス定義
//*****************************************************************************
class CResult : public CGamemode
{
public:
	CResult();
	~CResult();
	HRESULT Init(void);
	void Update(void);
	void Draw(void);
	void Uninit(void);
private:
	CResultScene* m_pResultScene;
	CMission* m_pMission;
	CClear* m_pClear;
	int m_nCount;
};
#endif
