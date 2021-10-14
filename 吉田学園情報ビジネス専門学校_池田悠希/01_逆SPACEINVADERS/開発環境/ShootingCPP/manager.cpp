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
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"
#include "input.h"
#include "inputkeyboard.h"
#include "player.h"
#include "bullet.h"
#include "explosion.h"
#include "sound.h"
#include "bg.h"
#include "enemy.h"
#include "number.h"
#include "score.h"
#include "laser.h"
#include "laserlayer.h"
#include "life.h"
#include "title.h"
#include "fade.h"
#include "result.h"
#include "energy.h"
#include "map.h"
#include "item.h"
#include "inputmouse.h"
#include "cursol.h"
#include "tutorial.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�ÓI�����o�ϐ��錾
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CRenderer* CManager::m_pRenderer                   = NULL;
CInputKeyboard* CManager::m_pInputKey              = NULL;
CInputMouse* CManager::m_pInputMouse               = NULL;
CSound* CManager::m_pSound                         = NULL;
CLife* CManager::m_pLife                           = NULL;
CTitle* CManager::m_pTitle                         = NULL;
CFade* CManager::m_pFade                           = NULL;
CResult* CManager::m_pResult                       = NULL;
CTutorial* CManager::m_pTutorial                   = NULL;
CManager::GAMEMODE CManager::m_gamemode            = GAMEMODE_TITLE;
LPDIRECT3DTEXTURE9 CManager::m_pTextureGameOver[2] = {};
int CManager::m_FrameCount                         = 0;
int CManager::m_nCountSpawn                        = 0;
bool CManager::m_bAlive                            = 0;

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�R���X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CManager::CManager()
{
    m_pRenderer = NULL;
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

    m_pSound = new CSound;	//�T�E���h������
    m_pSound->Init(hWnd);
    m_pSound->Play(CSound::BGM);	//BGM�Đ�

    m_pInputKey = new CInputKeyboard;	//�L�[�{�[�h������
    m_pInputKey->Init(hInstance, hWnd);
    m_pInputMouse = new CInputMouse;	//�}�E�X������
    m_pInputMouse->Init(hInstance, hWnd);
    LoadTextures();						//�e�N�X�`���Ǎ�
    m_pTitle  = CTitle::Create();		//�^�C�g����ʐ���
	m_pTutorial = CTutorial::Create();	//�`���[�g���A������
    m_pResult = CResult::Create();		//���U���g��ʐ���
    return hResult;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�I���֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CManager::Uninit(void)
{
    CScene::ReleaseAll();    //�|���S���̏I��

    m_pInputKey->Uninit();	//�L�[�{�[�h���͂̏I��
    delete m_pInputKey;		
    m_pInputKey = NULL;

	m_pInputMouse->Uninit();	//�}�E�X���͂̏I��
	delete m_pInputMouse;
	m_pInputMouse = NULL;

    m_pRenderer->Uninit();    //�����_���̏I��
    delete m_pRenderer;
    m_pRenderer = NULL;

    m_pSound->Uninit();		//�T�E���h�̏I��
    delete m_pSound;
    m_pSound = NULL;

	m_pTitle->Uninit();		//�^�C�g����ʏI��
	delete m_pTitle;
	m_pTitle = NULL;

	m_pTutorial->Uninit();	//�`���[�g���A���I��
	delete m_pTutorial;
	m_pTutorial = NULL;

	m_pResult->Uninit();	//���U���g�̏I��
	delete m_pResult;
	m_pResult = NULL;

	if (m_pFade != NULL)
	{
		m_pFade->Uninit();
	}

	

    UnloadTextures();		//�e�N�X�`���A�����[�h
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�X�V�֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CManager::Update(void)
{
    m_pInputKey->Update();
    m_pInputMouse->Update();
    if(CMap::GetGoal())	//�S�[����̓G�̃����_���X�|�[��
    {
        if(m_nCountSpawn++ % ENEMY_SPAWN_CYCLE == 0)
        {
            CEnemy::Create(D3DXVECTOR3((float)SCREEN_WIDTH, (rand() % 7 + 2.5f) * MAP_TILE_SIZE, 0), (CEnemy::TYPE)(rand() % (CEnemy::TYPE_SPRINKLER + 1)));
        }
    }

    if(((CInputKeyboard*)m_pInputKey)->GetKeyTrigger(DIK_RETURN))	//ENTER�L�[�̉�ʑJ��
    {
        switch(m_gamemode)
        {
            case GAMEMODE_TITLE:
                if(!CFade::GetUse())
                {
                    m_nCountSpawn = 0;	//�G�̃����_���X�|�[���p�̃J�E���^
                    CBg::Create();		//�w�i����
                    CMap::Create();		//�}�b�v����
                    CPlayer::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0));	//�v���C���[����
                    CScore::Create();	//�X�R�A����
                    m_pFade = CFade::Create(GAMEMODE_TUTORIAL);	//�t�F�[�h
                }
                break;
            case GAMEMODE_TUTORIAL:
				if (!CFade::GetUse())
				{
					m_pFade = CFade::Create(GAMEMODE_MAIN);//�t�F�[�h
				}
				break;
            case GAMEMODE_RESULT:
                if(!CFade::GetUse())
                {
                    m_pFade = CFade::Create(GAMEMODE_TITLE);//�t�F�[�h
                    CScene::ReleaseAll();					//CScene�Ǘ����Ă���I�u�W�F�N�g�����ׂĔj��
                }
				break;
        }
    }
    if(m_FrameCount > 0)	//�Q�[���I�[�o�[��̃t���[�����J�E���g
    {
        m_FrameCount++;
        if(m_FrameCount == 300)	//5�b(300�t���[����)�Ƀ��U���g��ʂɑJ�ڂ���
        {
            m_pResult->UpdateRanking();
            m_pFade      = CFade::Create(GAMEMODE_RESULT);
            m_FrameCount = 0;
        }
    }

    m_pRenderer->Update();    //�����_���̍X�V

#ifdef _DEBUG
	//�f�o�b�O���[�h�œG���X�|�[��������֐�
    if(((CInputKeyboard*)m_pInputKey)->GetKeyTrigger(DIK_P))
    {
        POINT point;
        GetCursorPos(&point);
        ScreenToClient(FindWindow(CLASS_NAME, NULL), &point);
        CEnemy::Create(D3DXVECTOR3((float)point.x, (float)point.y, 0), CEnemy::TYPE_NORMAL);
    }
    else if(((CInputKeyboard*)m_pInputKey)->GetKeyTrigger(DIK_O))
    {
        POINT point;
        GetCursorPos(&point);
        ScreenToClient(FindWindow(CLASS_NAME, NULL), &point);
        CEnemy::Create(D3DXVECTOR3((float)point.x, (float)point.y, 0), CEnemy::TYPE_SPRINKLER);
    }

#endif
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�`��֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CManager::Draw(void)
{
    m_pRenderer->Draw();    //�����_���̕`��
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�Q�b�^�[�֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

CRenderer* CManager::GetRenderer(void)
{
    return m_pRenderer;
}

CInputKeyboard* CManager::GetInputKey(void)
{
    return m_pInputKey;
}

CInputMouse* CManager::GetInputMouse(void)
{
    return m_pInputMouse;
}

CSound* CManager::GetSound(void)
{
    return m_pSound;
}

CTitle* CManager::GetTitle(void)
{
    return m_pTitle;
}

CFade* CManager::GetFade(void)
{
    return m_pFade;
}

CResult* CManager::GetResult(void)
{
	return m_pResult;
}

CManager::GAMEMODE CManager::GetGamemode(void)
{
	return m_gamemode;
}

bool CManager::GetAlive(void)
{
	return m_bAlive;
}

CTutorial* CManager::GetTutorial(void)
{
	return m_pTutorial;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�Z�b�^�[�֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CManager::SetGamemode(GAMEMODE nextMode)
{
	m_gamemode = nextMode;
}

void CManager::SetAlive(bool bAlive)
{
	m_bAlive = bAlive;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�t�@�C���ǂݍ��݊֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CManager::LoadTextures(void)
{
    D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "Resources\\gameover.png", &m_pTextureGameOver[0]);
    D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "Resources\\saved.png", &m_pTextureGameOver[1]);
    CExplosion::Load();
    CBullet::Load();
    CPlayer::Load();
    CBg::Load();
    CEnemy::Load();
    CNumber::Load();
    CLaserLayer::Load();
    CTitle::Load();
    CResult::Load();
    CLife::Load();
    CEnergy::Load();
    CMap::Load();
    CItem::Load();
    CCursol::Load();
    CTutorial::Load();
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�ǂݍ��݃f�[�^�j������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CManager::UnloadTextures(void)
{
    CBullet::Unload();
    CPlayer::Unload();
    CExplosion::Unload();
    CBg::Unload();
    CEnemy::Unload();
    CNumber::Unload();
    CLaserLayer::Unload();
    CTitle::Unload();
    CResult::Unload();
    CLife::Unload();
    CEnergy::Unload();
    CMap::Unload();
    CItem::Unload();
    CCursol::Unload();
    CTutorial::Unload();
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�t�F�[�h�j������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CManager::KillFade(void)
{
	delete m_pFade;
    m_pFade = NULL;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�Q�[���I�[�o�[����
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CManager::GameOver(void)
{
    CScene2d* pScene2d = CScene2d::Create(4);
    pScene2d->Init();
    if(CMap::GetGoal())	//�S�[�����Ă��邩���Ȃ����ŕ\������e�N�X�`����ύX
    {
        pScene2d->BindTexture(m_pTextureGameOver[1]);
    }
    else
    {
        pScene2d->BindTexture(m_pTextureGameOver[0]);
    }
    CMap::SetGoal(false);	//�S�[���t���O��false��
    pScene2d->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0));
    pScene2d->SetSize(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0));
    m_FrameCount = 1;	//���U���g�ɑJ�ڂ���܂ł̃J�E���g�X�^�[�g
}