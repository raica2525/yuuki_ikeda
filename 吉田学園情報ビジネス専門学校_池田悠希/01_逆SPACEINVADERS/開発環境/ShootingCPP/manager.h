//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	manager.h
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�O���錾
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CRenderer;
class CInputKeyboard;
class CInputMouse;
class CSound;
class CNumber;
class CLife;
class CTitle;
class CFade;
class CResult;
class CCursol;
class CTutorial;
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���X��`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CManager
{
public:
    CManager();     //�R���X�g���N�^
    ~CManager();    //�f�X�g���N�^

    typedef enum
    {
        GAMEMODE_TITLE = 0,
        GAMEMODE_TUTORIAL,
        GAMEMODE_MAIN,
        GAMEMODE_RESULT,
        GAMEMODE_MAX
    } GAMEMODE;

    HRESULT Init(HWND hWnd, bool bWindow, HINSTANCE hInstance);    //�������֐�
    void Uninit(void);                                             //�I���֐�
    void Update(void);                                             //�X�V�֐�
    void Draw(void);                                               //�`��֐�
    static CRenderer* GetRenderer(void);                           //�Q�b�^�[
    static CInputKeyboard* GetInputKey(void);
    static CInputMouse* GetInputMouse(void);
    static CSound* GetSound(void);
    static void LoadTextures(void);
    static void UnloadTextures(void);
    static GAMEMODE GetGamemode(void);
    static CTitle* GetTitle(void);
    static void SetGamemode(GAMEMODE nextMode);
    static CFade* GetFade(void);
    static CResult* GetResult(void);
    static void KillFade(void);
    static void GameOver(void);
    static bool GetAlive(void);
    static void SetAlive(bool bAlive);
    static CTutorial* GetTutorial(void);

private:
    static CRenderer* m_pRenderer;    //�����_���̃|�C���^
    static GAMEMODE m_gamemode;
    static LPDIRECT3DTEXTURE9 m_pTextureGameOver[2];
    static CInputKeyboard* m_pInputKey;    //�C���v�b�g�̃|�C���^
    static CInputMouse* m_pInputMouse;
    static CSound* m_pSound;
    static CLife* m_pLife;
    static CTitle* m_pTitle;
    static CFade* m_pFade;
    static CResult* m_pResult;
    static int m_FrameCount;
    static int m_nCountSpawn;
    static bool m_bAlive;
    static CTutorial* m_pTutorial;
};

#endif
