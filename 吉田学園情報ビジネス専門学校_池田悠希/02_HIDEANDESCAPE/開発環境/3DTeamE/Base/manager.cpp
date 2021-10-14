//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	manager.cpp
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "manager.h"

#include "animation.h"
#include "assaultbutton.h"
#include "bullet_ui.h"
#include "camera.h"
#include "clear.h"
#include "continuebutton.h"
#include "crosshair.h"
#include "damage_ui.h"
#include "debug.h"
#include "exclamationmark.h"
#include "explosion.h"
#include "explosion2.h"
#include "fade.h"
#include "handgunbutton.h"
#include "heavy_enemy.h"
#include "hiteffect.h"
#include "input.h"
#include "inputkeyboard.h"
#include "inputmouse.h"
#include "item.h"
#include "item_ui.h"
#include "light.h"
#include "light_enemy.h"
#include "map01.h"
#include "map02.h"
#include "map03.h"
#include "map04.h"
#include "mission.h"
#include "model.h"
#include "monitor.h"
#include "object.h"
#include "object2d.h"
#include "object3d.h"
#include "pause.h"
#include "player.h"
#include "polygon3d.h"
#include "question.h"
#include "renderer.h"
#include "result.h"
#include "resultscene.h"
#include "retrybutton.h"
#include "returntitlebutton.h"
#include "sound.h"
#include "stage01.h"
#include "stage02.h"
#include "stage03.h"
#include "stage04.h"
#include "startbutton.h"
#include "title.h"
#include "titlelogo.h"
#include "trap.h"
#include "tutorial.h"
#include "tutorialbutton.h"
#include "tutorialstage.h"
#include "uav.h"
#include "weapons_ui.h"
#include "weaponselect.h"
#include "weaponselectscene.h"
#include "number.h"
#include "countdown.h"
#include "blood.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�ÓI�����o�ϐ��錾
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CRenderer* CManager::m_pRenderer               = NULL;
CInput* CManager::m_pInputKey                  = NULL;
CInput* CManager::m_pInputMou                  = NULL;
CCamera* CManager::m_pCamera                   = NULL;
CPlayer* CManager::m_pPlayer                   = NULL;
CModel* CManager::m_pStageModel                = NULL;
CFade* CManager::m_pFade                       = NULL;
CManager::GAMEMODE CManager::m_mode            = {};
CSound* CManager::m_pSound                     = NULL;
ICGamemode* CManager::m_pGamemode              = NULL;
CManager::WEAPONS_MODE CManager::m_WeaponsMode = WEAPONS_MODE_NONE;
CInputJoystick* CManager::m_pInputJoystick     = NULL;
CPause* CManager::m_pPause                     = NULL;

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�R���X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CManager::CManager()
{
    m_pRenderer   = NULL;
    m_WeaponsMode = WEAPONS_MODE_AR;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�f�X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CManager::~CManager()
{
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�������֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
HRESULT CManager::Init(HWND hWnd, bool bWindow, HINSTANCE hInstance)
{
    HRESULT hResult = NULL;
    m_pRenderer     = new CRenderer;                    //�����_���𐶐�
    hResult         = m_pRenderer->Init(hWnd, true);    //�����_����������

    //���C�g�̐���
    CLight* pLight = NULL;
    pLight         = new CLight;
    pLight->Init();

    //�L�[�{�[�h����
    m_pInputKey = new CInputKeyboard;
    m_pInputKey->Init(hInstance, hWnd);

    //�}�E�X����
    m_pInputMou = new CInputMouse;
    m_pInputMou->Init(hInstance, hWnd);

    //�����̃V�[�h�l�ݒ�
    srand((unsigned int)time(0));

    //�T�E���h�̐���
    if(m_pSound == NULL)
    {
        m_pSound = new CSound;
    }

    //�T�E���h�̏�����
    m_pSound->Init(hWnd);

    //�t�F�[�h����
    m_pFade = CFade::Create();

    //�t�@�C���ǂݍ���
	LoadFile();

    CDebug::Init();         //�f�o�b�O���̏���������
    SetMode(MODE_TITLE);    //���[�h�ݒ�

    return hResult;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�I���֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CManager::Uninit(void)
{
    //�V�[���̏I��
    CObject::ReleaseAll();

    //�f�o�b�O���̏I��
    CDebug::Uninit();

    //�Q�[�����[�h�I��
    if(m_pGamemode != NULL)
    {
        m_pGamemode->Uninit();
		SAFE_DELETE(m_pGamemode);
    }

    //�t�F�[�h�I��
    if(m_pFade != NULL)
    {
        m_pFade->Uninit();
		SAFE_DELETE(m_pFade);
    }

    //���͂̏I��
    if(m_pInputKey != NULL)
    {
        m_pInputKey->Uninit();
		SAFE_DELETE(m_pInputKey);
    }
    if(m_pInputMou != NULL)
    {
        m_pInputMou->Uninit();
		SAFE_DELETE(m_pInputMou);
    }

    //�J�����̏I��
    if(m_pCamera != NULL)
    {
        m_pCamera->Uninit();
		SAFE_DELETE(m_pCamera);
    }

	//�����_���̏I��
    if(m_pRenderer != NULL)
    {
        m_pRenderer->Uninit();
		SAFE_DELETE(m_pRenderer);
    }

    //�T�E���h�̔j��
    if(m_pSound != NULL)
    {
        m_pSound->Uninit();
		SAFE_DELETE(m_pSound);
    }

    //�ǂݍ��񂾃t�@�C���̃A�����[�h
    UnloadFile();
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�X�V�֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CManager::Update(void)
{
    //���͂̍X�V
    if(m_pInputKey != NULL)
    {
        m_pInputKey->Update();
    }

    if(m_pInputMou != NULL)
    {
        m_pInputMou->Update();
    }

    //�����_���̍X�V
    if(m_pRenderer != NULL && m_pPause == NULL)
    {
        m_pRenderer->Update();
    }

    //�t�F�[�h�X�V
    if(m_pFade != NULL)
    {
        m_pFade->Update();
    }

    if(((CInputKeyboard*)m_pInputKey)->GetKeyTrigger(DIK_ESCAPE))
    {
        //�|�[�Y�ł���Ƃ��̓|�[�Y�A�|�[�Y���Ȃ�|�[�Y�I���A�ǂ���ł��Ȃ��Ƃ��̓A�v���P�[�V�������I������
        if(m_mode != MODE_TITLE && m_mode != MODE_WEAPONSELECT && m_mode != MODE_RESULT && m_pPause == NULL)
        {
            if(m_pPlayer->GetLife() > 0)
            {
                m_pPause = CPause::Create();
            }
        }
        else if(m_pPause != NULL)
        {
            EndPause();
        }
        else
        {
            DestroyWindow(FindWindow(CLASS_NAME, NULL));
        }
    }

    //�|�[�Y����Ă���Ƃ��̓|�[�Y��ʍX�V�@�����łȂ��Ƃ��̓��C���̃Q�[�����[�h���X�V
    if(m_pPause != NULL)
    {
        m_pPause->Update();
    }
    else
    {
        m_pGamemode->Update();
    }
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�`��֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CManager::Draw(void)
{
    //���C���̃Q�[�����[�h�̕`�揈��
    m_pGamemode->Draw();

    //�����_���̕`��
    if(m_pRenderer != NULL)
    {
        m_pRenderer->Draw();
    }
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�Q�b�^�[�֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CRenderer* CManager::GetRenderer(void)
{
    return m_pRenderer;
}

CInput* CManager::GetInputKey(void)
{
    return m_pInputKey;
}

CInput* CManager::GetInputMou(void)
{
    return m_pInputMou;
}

CInputJoystick* CManager::GetInputJoystick(void)
{
    return m_pInputJoystick;
}

CCamera* CManager::GetCamera(void)
{
    return m_pCamera;
}

CPlayer* CManager::GetPlayer(void)
{
    return m_pPlayer;
}

CModel* CManager::GetStageModel(void)
{
    return m_pStageModel;
}

CManager::WEAPONS_MODE CManager::GetWeaponsMode(void)
{
    return m_WeaponsMode;
}

CFade* CManager::GetFade(void)
{
    return m_pFade;
}

CManager::GAMEMODE CManager::GetMode(void)
{
    return m_mode;
}

CSound* CManager::GetSound(void)
{
    return m_pSound;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�Z�b�^�[�֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CManager::SetWeaponsMode(const WEAPONS_MODE WeaponsMode)
{
    m_WeaponsMode = WeaponsMode;
}

void CManager::SetStageModel(CModel* const pModel)
{
    m_pStageModel = pModel;
}

void CManager::SetPlayer(CPlayer* const pPlayer)
{
    m_pPlayer = pPlayer;
}

void CManager::BindCamera(CCamera* const pCamera)
{
    m_pCamera = pCamera;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�t�@�C���̃��[�h
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CManager::LoadFile(void)
{
    CWeapons_ui::Load();
    CPlayer::Load();
    CCrosshair::Load();
    CLightEnemy::Load();
    CTutorialStage::Load();
    CItem::Load();
    CAnimation::Load();
    CExplosion::Load();
    CExplosion2::Load();
    CMonitor::Load();
    CExclamationMark::Load();
    CQuestion::Load();
    CUav::Load();
    CStage01::Load();
    CStage02::Load();
    CStage03::Load();
    CStage04::Load();
    CTitleLogo::Load();
    CHeavyEnemy::Load();
    CHitEffect::Load();
    CItem_ui::Load();
    CDamage_ui::Load();
    CBullet_ui::Load();
    CStartButton::Load();
    CTutorialButton::Load();
    CAssaultButton::Load();
    CHandgunButton::Load();
    CWeaponSelectScene::Load();
    CResultScene::Load();
    CReturnTitleButton::Load();
    CRetryButton::Load();
    CMission::Load();
    CClear::Load();
    CContinueButton::Load();
    CNumber::Load();
    CCountDown::Load();
    CTutorial::Load();
    CBlood::Load();
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�t�@�C���̃A�����[�h
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CManager::UnloadFile(void)
{
    CWeapons_ui::Unload();
    CPlayer::Unload();
    CLightEnemy::Unload();
    CTutorialStage::Unload();
    CItem::Unload();
    CExplosion::Unload();
    CExplosion2::Unload();
    CMonitor::Unload();
    CExclamationMark::Unload();
    CQuestion::Unload();
    CUav::Unload();
    CStage01::Unload();
    CStage02::Unload();
    CStage03::Unload();
    CStage04::Unload();
    CTitleLogo::Unload();
    CHeavyEnemy::Unload();
    CHitEffect::Unload();
    CItem_ui::Unload();
    CDamage_ui::Unload();
    CBullet_ui::Unload();
    CStartButton::Unload();
    CTutorialButton::Unload();
    CAssaultButton::Unload();
    CHandgunButton::Unload();
    CWeaponSelectScene::Unload();
    CResultScene::Unload();
    CReturnTitleButton::Unload();
    CRetryButton::Unload();
    CMission::Unload();
    CClear::Unload();
    CContinueButton::Unload();
    CNumber::Unload();
    CCountDown::Unload();
    CCrosshair::Unload();
    CTutorial::Unload();
    CBlood::Unload();
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//���[�h�ؑ�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CManager::SetMode(const GAMEMODE mode)
{
    //�|�[�Y���Ȃ�|�[�Y���I��
    EndPause();

    //�T�E���h�I��
    CManager::GetSound()->StopSound();

    //�Q�[�����[�h�����łɐ�������Ă���ΏI��
    if(m_pGamemode != NULL)
    {
        //�I������
        m_pGamemode->Uninit();
		SAFE_DELETE(m_pGamemode);
    }

    //�����o�ϐ��ɑ��
    m_mode = mode;

    //�؂�ւ���̃Q�[�����[�h��ݒ�
    switch(m_mode)
    {
        case MODE_TITLE:
            m_pGamemode = new CTitle;
            break;
        case MODE_TUTORIAL:
            m_pGamemode = new CTutorial;
            break;
        case MODE_WEAPONSELECT:
            m_pGamemode = new CWeaponSelect;
            break;
        case MODE_MAP01:
            m_pGamemode = new CMap01;
            break;
        case MODE_MAP02:
            m_pGamemode = new CMap02;
            break;
        case MODE_MAP03:
            m_pGamemode = new CMap03;
            break;
        case MODE_MAP04:
            m_pGamemode = new CMap04;
            break;
        case MODE_RESULT:
            m_pGamemode = new CResult;
            break;
    }
    //���������Q�[�����[�h�̏�����
    m_pGamemode->Init();
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�|�[�Y�I������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CManager::EndPause(void)
{
    //�|�[�Y���Ȃ�|�[�Y�I��
    if(m_pPause != NULL)
    {
        m_pPause->Uninit();
		SAFE_DELETE(m_pPause);
    }
}
