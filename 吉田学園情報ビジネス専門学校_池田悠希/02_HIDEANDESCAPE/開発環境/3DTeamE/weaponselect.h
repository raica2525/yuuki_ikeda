//=============================================================================
//
// 武器選択処理 [weaponselect.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _WEAPONSELECT_H_
#define _WEAPONSELECT_H_
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
class CStage01;
class CTitleLogo;
class CStartButton;
class CTutorialButton;
class CAssaultButton;
class CHandgunButton;
class CWeaponSelectScene;
//*****************************************************************************
// クラス定義
//*****************************************************************************
class CWeaponSelect : public CGamemode
{
public:
	CWeaponSelect();
	~CWeaponSelect();
	HRESULT Init(void);
	void Update(void);
	void Draw(void);
	void Uninit(void);
private:
	CCamera* m_pCamera;					//カメポインタ
	CStage01* m_pStage01;
	CTitleLogo* m_pTitleLogo;
	CTutorialButton* m_pTutorialButton;
	CStartButton* m_pStartButton;
	CAssaultButton* m_pAssaultButton;
	CHandgunButton* m_pHandgunButton;
	CWeaponSelectScene* m_pWeaponSelectScene;
};
#endif
