//=============================================================================
//
// ����I������ [weaponselect.h]
// Author : ��K������
//
//=============================================================================
#ifndef _WEAPONSELECT_H_
#define _WEAPONSELECT_H_
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "gamemode.h"
#include "main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �O���錾
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
// �N���X��`
//*****************************************************************************
class CWeaponSelect : public ICGamemode
{
public:
	CWeaponSelect();
	~CWeaponSelect();
	HRESULT Init(void);
	void Update(void);
	void Draw(void);
	void Uninit(void);
private:
	CCamera* m_pCamera;					//�J���|�C���^
	CStage01* m_pStage01;
	CTitleLogo* m_pTitleLogo;
	CTutorialButton* m_pTutorialButton;
	CStartButton* m_pStartButton;
	CAssaultButton* m_pAssaultButton;
	CHandgunButton* m_pHandgunButton;
	CWeaponSelectScene* m_pWeaponSelectScene;
};
#endif
