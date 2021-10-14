//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//�@tutorial
//�@Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "gamemode.h"
#include "main.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�}�N����`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#define GUIDE_NUM (13)

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�O���錾
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CCamera;
class CPlayer;
class CTutorialStage;
class CTrap;

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���X��`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CTutorial : public ICGamemode
{
public:
    CTutorial();
    ~CTutorial();

    HRESULT Init(void);    //����������
    void Update(void);     //�X�V����
    void Draw(void);       //�`�揈��
    void Uninit(void);     //�I������

    static void Load(void);      //�e�N�X�`���ǂݍ���
    static void Unload(void);    //�e�N�X�`���j��

private:
    static LPDIRECT3DTEXTURE9 m_apTexture[GUIDE_NUM];    //�e�N�X�`���ւ̃|�C���^
    CCamera* m_pCamera;                                  //�J���|�C���^
    CPlayer* m_pPlayer;                                  //�v���C���[�|�C���^
    CTutorialStage* m_pTutorialStage;                    //�X�e�[�W�|�C���^
    CTrap* m_Trap;                                       //�g���b�v�|�C���^
};
#endif
