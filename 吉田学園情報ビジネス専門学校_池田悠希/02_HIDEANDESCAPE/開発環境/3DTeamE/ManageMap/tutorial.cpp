//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	tutorial.cpp
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "tutorial.h"

#include "camera.h"
#include "goal.h"
#include "item.h"
#include "light_enemy.h"
#include "manager.h"
#include "player.h"
#include "polygon3d.h"
#include "sound.h"
#include "titlelogo.h"
#include "trap.h"
#include "tutorialstage.h"
#include "uav.h"
#include "renderer.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�ÓI�����o�ϐ��錾
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
LPDIRECT3DTEXTURE9 CTutorial::m_apTexture[GUIDE_NUM] = {};

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�R���X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CTutorial::CTutorial()
{
    //����������
    m_pCamera        = NULL;
    m_pPlayer        = NULL;
    m_pTutorialStage = NULL;
    m_Trap           = NULL;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�f�X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CTutorial::~CTutorial()
{
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�������֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
HRESULT CTutorial::Init(void)
{
    CLightEnemy* pEnemy           = NULL;
    CUav* pUav                    = NULL;
    CPolygon3D* pGuide[GUIDE_NUM] = {};
    ZeroMemory(pGuide, sizeof(pGuide));
    //�T�E���h�Đ�
    CSound* pSound = CManager::GetSound();
    pSound->StopSound();
    pSound->PlaySound(CSound::SOUND_LABEL_BGM_MAP);
    //�J�[�\���ʒu���Z�b�g
    SetCursorPos(((int)SCREEN_WIDTH / 2), ((int)SCREEN_HEIGHT / 2));

    //�J��������
    m_pCamera = new CCamera;
    m_pCamera->Init();

    //�`���[�g���A������
    m_pTutorialStage = CTutorialStage::Create(ZEROVECTOR3, ZEROVECTOR3, D3DXVECTOR3(2.0f, 1.75f, 2.0f));

    //�v���C���[����
    m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, -800.0f), D3DXVECTOR3(45, 180, 0), D3DXVECTOR3(0.2f, 0.2f, 0.2f));

    //�G�l�~�[����
    pEnemy = CLightEnemy::Create(D3DXVECTOR3(90.0f, 0.0f, 375.0f), ZEROVECTOR3);
    pEnemy->SetTour(1, D3DXVECTOR3(90.0f, 0.0f, 375.0f));
    pEnemy->SetTour(2, D3DXVECTOR3(-90.0f, 0.0f, 375.0f));

    pUav = CUav::Create(D3DXVECTOR3(0.0f, 0.0f, -175.0f), ZEROVECTOR3);
    pUav->SetTour(1, D3DXVECTOR3(90.0f, 0.0f, -175.0f));
    pUav->SetTour(2, D3DXVECTOR3(-90.0f, 0.0f, -175.0f));

    //�K�C�h�|���S������
	pGuide[0] = CPolygon3D::Create(D3DXVECTOR3(-50.0f, 60.0f, -700.0f), D3DXVECTOR3(180.0f, -90.0f, 0.0f), D3DXVECTOR3(50.0f, 20.0f, 0.0f));
	pGuide[1] = CPolygon3D::Create(D3DXVECTOR3(-50.0f, 60.0f, -600.0f), D3DXVECTOR3(180.0f, -90.0f, 0.0f), D3DXVECTOR3(50.0f, 20.0f, 0.0f));
	pGuide[2] = CPolygon3D::Create(D3DXVECTOR3(-50.0f, 60.0f, -500.0f), D3DXVECTOR3(180.0f, -90.0f, 0.0f), D3DXVECTOR3(50.0f, 20.0f, 0.0f));
	pGuide[3] = CPolygon3D::Create(D3DXVECTOR3(50.0f, 60.0f, -700.0f), D3DXVECTOR3(180.0f, 90.0f, 0.0f), D3DXVECTOR3(50.0f, 20.0f, 0.0f));
	pGuide[4] = CPolygon3D::Create(D3DXVECTOR3(50.0f, 60.0f, -600.0f), D3DXVECTOR3(180.0f, 90.0f, 0.0f), D3DXVECTOR3(50.0f, 20.0f, 0.0f));
	pGuide[5] = CPolygon3D::Create(D3DXVECTOR3(50.0f, 60.0f, -500.0f), D3DXVECTOR3(180.0f, 90.0f, 0.0f), D3DXVECTOR3(50.0f, 20.0f, 0.0f));
	pGuide[6] = CPolygon3D::Create(D3DXVECTOR3(0.0f, 60.0f, -450.0f), D3DXVECTOR3(180.0f, 0.0f, 0.0f), D3DXVECTOR3(30.0f, 20.0f, 0.0f));
	pGuide[7] = CPolygon3D::Create(D3DXVECTOR3(0.0f, 60.0f, -175.0f), D3DXVECTOR3(180.0f, 0.0f, 0.0f), D3DXVECTOR3(30.0f, 20.0f, 0.0f));
	pGuide[8] = CPolygon3D::Create(D3DXVECTOR3(0.0f, 60.0f, 375.0f), D3DXVECTOR3(180.0f, 0.0f, 0.0f), D3DXVECTOR3(30.0f, 20.0f, 0.0f));
	pGuide[9] = CPolygon3D::Create(D3DXVECTOR3(-50.0f, 60.0f, -50.0f), D3DXVECTOR3(180.0f, -90.0f, 0.0f), D3DXVECTOR3(50.0f, 20.0f, 0.0f));
	pGuide[10] = CPolygon3D::Create(D3DXVECTOR3(-370.0f, 60.0f, 320.0f), D3DXVECTOR3(180.0f, 180.0f, 0.0f), D3DXVECTOR3(30.0f, 20.0f, 0.0f));
	pGuide[11] = CPolygon3D::Create(D3DXVECTOR3(-370.0f, 30.0f, 310.0f), D3DXVECTOR3(180.0f, 180.0f, 0.0f), D3DXVECTOR3(50.0f, 20.0f, 0.0f));
	pGuide[12] = CPolygon3D::Create(D3DXVECTOR3(-370.0f, 35.0f, 460.0f), D3DXVECTOR3(180.0f, 0.0f, 0.0f), D3DXVECTOR3(40.0f, 50.0f, 0.0f));
    //�K�C�h�|���S���Ƀe�N�X�`������
    for(int nCount = 0; nCount < GUIDE_NUM; nCount++)
    {
        pGuide[nCount]->BindTexture(m_apTexture[nCount]);
    }
    //�A�C�e������
    CItem::Create(D3DXVECTOR3(-370, 25, 320), ZEROVECTOR3);
    m_Trap = CTrap::Create(D3DXVECTOR3(60.0f, 35.0f, -400.0f), D3DXVECTOR3(-60.0f, 35.0f, -400.0f));
    CGoal::Create(D3DXVECTOR3(-500.0f, 50.0f, 390.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR3(100.0f, 100.0f, 100.0f), D3DXCOLOR(1.0f, 0.1f, 0.1f, 0.0f), CManager::MODE_TITLE);

    return S_OK;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�X�V�֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CTutorial::Update(void)
{
    if(m_pCamera != NULL)
    {
        m_pCamera->Update();
    }
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�`��֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CTutorial::Draw(void)
{
    if(m_pCamera != NULL)
    {
        m_pCamera->SetCamera();
    }
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�I���֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CTutorial::Uninit(void)
{
    CObject::ReleaseAll();
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�e�N�X�`���ǂݍ��݊֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CTutorial::Load(void)
{
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

    // �e�N�X�`���̐���
    D3DXCreateTextureFromFile(pDevice, "Data/Texture/WASD.png", &m_apTexture[0]);
    D3DXCreateTextureFromFile(pDevice, "Data/Texture/Shift.png", &m_apTexture[1]);
    D3DXCreateTextureFromFile(pDevice, "Data/Texture/Ctrl.png", &m_apTexture[2]);
    D3DXCreateTextureFromFile(pDevice, "Data/Texture/Mouse.png", &m_apTexture[3]);
    D3DXCreateTextureFromFile(pDevice, "Data/Texture/RClick.png", &m_apTexture[4]);
    D3DXCreateTextureFromFile(pDevice, "Data/Texture/LClick.png", &m_apTexture[5]);
    D3DXCreateTextureFromFile(pDevice, "Data/Texture/Trap.png", &m_apTexture[6]);
    D3DXCreateTextureFromFile(pDevice, "Data/Texture/teisatsuki.png", &m_apTexture[7]);
    D3DXCreateTextureFromFile(pDevice, "Data/Texture/chugataki.png", &m_apTexture[8]);
    D3DXCreateTextureFromFile(pDevice, "Data/Texture/R_Key.png", &m_apTexture[9]);
    D3DXCreateTextureFromFile(pDevice, "Data/Texture/recovery.png", &m_apTexture[10]);
    D3DXCreateTextureFromFile(pDevice, "Data/Texture/F_Key.png", &m_apTexture[11]);
    D3DXCreateTextureFromFile(pDevice, "Data/Texture/mission.png", &m_apTexture[12]);
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�e�N�X�`���j���֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CTutorial::Unload(void)
{
    for(int nCount = 0; nCount < GUIDE_NUM; nCount++)
    {
        if(m_apTexture[nCount] != NULL)
        {
            m_apTexture[nCount]->Release();
            m_apTexture[nCount] = NULL;
        }
    }
}
