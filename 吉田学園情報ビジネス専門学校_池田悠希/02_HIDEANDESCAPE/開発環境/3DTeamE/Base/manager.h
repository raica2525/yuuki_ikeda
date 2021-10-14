//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	manager.h
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#ifndef _MANAGER_H_
#define _MANAGER_H_

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "main.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�}�N����`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#define ZEROVECTOR3 D3DXVECTOR3(0.0f, 0.0f, 0.0f)

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�O���錾
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CRenderer;
class CInput;
class CCamera;
class CPlayer;
class CFade;
class CModel;
class CAnimation;
class CInputJoystick;
class ICGamemode;
class CWeaponSelect;
class CSound;
class CPause;
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���X��`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CManager
{
public:
    //���[�h�^�C�v
    typedef enum
    {
        MODE_TITLE = 0,
        MODE_TUTORIAL,
        MODE_WEAPONSELECT,
        MODE_MAP01,
        MODE_MAP02,
        MODE_MAP03,
        MODE_MAP04,
        MODE_SELECT,
        MODE_RESULT,
        MODE_MAX
    } GAMEMODE;
    //�E�F�|���^�C�v
    typedef enum
    {
        WEAPONS_MODE_NONE = -1,
        WEAPONS_MODE_AR,
        WEAPONS_MODE_HG,
        WEAPONS_MODE_MAX
    } WEAPONS_MODE;

    CManager();     //�R���X�g���N�^
    ~CManager();    //�f�X�g���N�^

    HRESULT Init(HWND hWnd, bool bWindow, HINSTANCE hInstance);    //�������֐�
    void Uninit(void);                                             //�I���֐�
    void Update(void);                                             //�X�V�֐�
    void Draw(void);                                               //�`��֐�

    //�Q�b�^�[�֐�
    static CRenderer* GetRenderer(void);
    static CInput* GetInputKey(void);
    static CInput* GetInputMou(void);
    static CInputJoystick* GetInputJoystick(void);
    static CCamera* GetCamera(void);
    static CPlayer* GetPlayer(void);
    static CModel* GetStageModel(void);
    static WEAPONS_MODE GetWeaponsMode(void);
    static CSound* GetSound(void);
    static GAMEMODE GetMode(void);
    static CFade* GetFade(void);

    //�Z�b�^�[�֐�
    static void SetWeaponsMode(WEAPONS_MODE WeaponsMode);
    static void SetStageModel(CModel* pModel);
    static void SetPlayer(CPlayer* pPlayer);
    static void BindCamera(CCamera* pCamera);
    static void SetMode(GAMEMODE mode);

    static void LoadFile(void);
    static void UnloadFile(void);
    static void EndPause(void);

private:
    //�I�u�W�F�N�g�ێ��p�|�C���^
    static CRenderer* m_pRenderer;
    static CInput* m_pInputKey;
    static CInput* m_pInputMou;
    static CCamera* m_pCamera;
    static CPlayer* m_pPlayer;
    static CSound* m_pSound;
    static CModel* m_pStageModel;
    static ICGamemode* m_pGamemode;
    static CAnimation* m_pAnimation;
    static CInputJoystick* m_pInputJoystick;
    static CPause* m_pPause;
    static CFade* m_pFade;

    static GAMEMODE m_mode;               //�Q�[�����[�h
    static WEAPONS_MODE m_WeaponsMode;    //�E�F�|���^�C�v
};

#endif
