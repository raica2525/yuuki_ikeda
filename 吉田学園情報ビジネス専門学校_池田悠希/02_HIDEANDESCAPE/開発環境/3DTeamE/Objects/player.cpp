//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	player.cpp
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "player.h"

#include "animation.h"
#include "bullet_ui.h"
#include "camera.h"
#include "crosshair.h"
#include "damage_ui.h"
#include "debug.h"
#include "enemy.h"
#include "fade.h"
#include "gameoveroverlay.h"
#include "inputkeyboard.h"
#include "inputmouse.h"
#include "manager.h"
#include "model.h"
#include "object.h"
#include "object3d.h"
#include "polygon3d.h"
#include "renderer.h"
#include "sound.h"
#include "tutorialstage.h"
#include "item_ui.h"
#include "weapons_ui.h"
#include "blood.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�}�N����`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#define AR_DAMAGE (15)
#define HG_DAMAGE (10)
#define AR_MOVE_RATE (0.75f)
#define HG_MOVE_RATE (1.25f)
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�ÓI�����o�ϐ��錾
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CModel::MODELDATA CPlayer::m_modeldata[PARTS_MAX]                        = {};
CModel::MODELDATA CPlayer::m_modelWeaponData[CManager::WEAPONS_MODE_MAX] = {};
D3DXMATERIAL* CPlayer::m_pMat                                            = NULL;
CAnimation* CPlayer::m_pAnimaSave                                        = NULL;
int CPlayer::m_nSensi                                                    = START_SENSI;
int CPlayer::m_nFrameCounter                                             = 0;
char* CPlayer::m_PartsWeapon[CManager::WEAPONS_MODE_MAX]                 = {
  "Data/Model/Player/06_RightHandandAsult.x",
  "Data/Model/Player/06_HandGun.x",
};

CPlayer::PARTS_DATA CPlayer::m_PartsData[PARTS_MAX] = {
  {
    "Data/Model/Player/00_Mune.x",
    -1,
    D3DXVECTOR3(0.0f, 140.0f, 0.0f),
  },
  {
    "Data/Model/Player/01_Onaka.x",
    0,
    D3DXVECTOR3(0.0f, -10.0f, 0.0f),
  },
  {
    "Data/Model/Player/02_Kosi.x",
    1,
    D3DXVECTOR3(0.0f, 5.0f, 0.0f),
  },
  {
    "Data/Model/Player/03_Head.x",
    0,
    D3DXVECTOR3(0.0f, 20.0f, 0.0f),
  },
  {
    "Data/Model/Player/04_RighJouwan.x",
    0,
    D3DXVECTOR3(-10.0f, 30.0f, 0.0f),
  },
  {
    "Data/Model/Player/05_RightZenwan.x",
    4,
    D3DXVECTOR3(-30.0f, -17.0f, 0.0f),
  },
  {
    "Data/Model/Player/06_RightHandandAsult.x",
    5,
    D3DXVECTOR3(-35.0f, -18.0f, 2.0f),
  },
  {
    "Data/Model/Player/07_LeftJouwan.x",
    0,
    D3DXVECTOR3(10.0f, 30.0f, 0.0f),
  },
  {
    "Data/Model/Player/08_LeftZenwan.x",
    7,
    D3DXVECTOR3(30.0f, -17.0f, 0.0f),
  },
  {
    "Data/Model/Player/09_LeftHand.x",
    8,
    D3DXVECTOR3(35.0f, -16.0f, 0.0f),
  },
  {
    "Data/Model/Player/10_RightHutomomo.x",
    2,
    D3DXVECTOR3(-5.75f, -20.0f, 0.0f),
  },
  {
    "Data/Model/Player/11_RightHukurahagi.x",
    10,
    D3DXVECTOR3(-6.0f, -40.0f, 2.0f),
  },
  {
    "Data/Model/Player/12_RightFoot.x",
    11,
    D3DXVECTOR3(0.0f, -50.0f, 5.0f),
  },
  {
    "Data/Model/Player/13_LeftHutomomo.x",
    2,
    D3DXVECTOR3(5.75f, -20.0f, 0.0f),
  },
  {
    "Data/Model/Player/14_LeftHukurahagi.x",
    13,
    D3DXVECTOR3(6.0f, -40.0f, 2.0f),
  },
  {
    "Data/Model/Player/15_LeftFoot.x",
    14,
    D3DXVECTOR3(0.0f, -50.0f, 5.0f),
  },
};
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�R���X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CPlayer::CPlayer()
{
	static_assert(sizeof(m_PartsWeapon) / sizeof(m_PartsWeapon[0]) == CManager::WEAPONS_MODE_MAX, "�z��͈̓G���[");
	static_assert(sizeof(m_PartsData) / sizeof(m_PartsData[0]) == PARTS_MAX, "�z��͈̓G���[");
    m_nFrameCounter = 0;                                    //�t���[���J�E���^�[
    m_AnimaMotion   = CAnimation::MOTION_PLAYER_NEUTRAL;    //�������[�V�����ݒ�
    m_pCrosshair    = NULL;                                 //�N���X�w�A�|�C���^
    m_pAnime        = NULL;                                 //�A�j���|�C���^
    m_pDamageUi     = NULL;                                 //�_���[�WUI�|�C���^
    ZeroMemory(m_apItemUI, sizeof(m_apItemUI));             //�񕜃A�C�e����UI
    m_nLife       = START_LIFE;                             //�������C�t
    m_pos         = ZEROVECTOR3;                            //���W
    m_rot         = ZEROVECTOR3;                            //��������
    m_size        = D3DXVECTOR3(1.0f, 1.0f, 1.0f);          //�傫��
    m_state       = STATE_STAND;                            //�������
    m_fMoveVector = 0.0f;                                   //�ړ�����
    ZeroMemory(m_apModel, sizeof(m_apModel));               //���f���̃|�C���^�[���N���A
    SetObjType(CObject::OBJTYPE_PLAYER);                    //�I�u�W�F�N�g�^�C�v�ݒ�
    m_fMoveVector = 0.0f;                                   //�i�s����
    m_nHaveItem   = 0;                                      //�A�C�e��������
    m_Weapons_UI  = NULL;                                   //�E�F�|��UI�|�C���^
    memset(m_Partsrot, NULL, sizeof(m_Partsrot));           //�p�[�c�̏�������
    memset(m_Partspos, NULL, sizeof(m_Partspos));           //�p�[�c�̏����ʒu
    for(int nCount = 0; nCount < PARTS_MAX; nCount++)
    {
        m_PartsSize[nCount] = D3DXVECTOR3(1.0f, 1.0f, 1.0f);    //�p�[�c�̏����傫��
    }
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�f�X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CPlayer::~CPlayer()
{
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//����������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
HRESULT CPlayer::Init(void)
{
    CManager::WEAPONS_MODE weaponMode = CManager::GetWeaponsMode();
    //�A�j���[�V��������
    if(weaponMode == CManager::WEAPONS_MODE_AR)
    {
        m_pAnimaSave     = CAnimation::Create(CAnimation::ANIMATION_PLAYER_AR);
        m_nRemainingAmmo = MAGAZINE_SIZE_AR;
        m_nMagazineSize  = MAGAZINE_SIZE_AR;
    }
    else
    {
        m_pAnimaSave     = CAnimation::Create(CAnimation::ANIMATION_PLAYER_HG);
        m_nRemainingAmmo = MAGAZINE_SIZE_HG;
        m_nMagazineSize  = MAGAZINE_SIZE_HG;
    }
    while(ShowCursor(false) >= 0);    //�}�E�X�J�[�\��������

    //���[���h�}�g���N�X�p
    m_apModelWorld = CModel::Create(NULL, this, {}, m_pos, m_rot, m_size);

    //�E�F�|�����f���ɐ؂�ւ�
    if(weaponMode != CManager::WEAPONS_MODE_NONE)
    {
        m_modeldata[PARTS_RIGHT_HAND] = m_modelWeaponData[weaponMode];
    }

    //���f������
    for(int nCount = 0; nCount < PARTS_MAX; nCount++)
    {
        if(m_PartsData[nCount].nParent == -1)
        {
            m_apModel[nCount] = CModel::Create(m_apModelWorld, this, m_modeldata[nCount], m_PartsData[nCount].Partspos, m_Partsrot[nCount], m_PartsSize[nCount]);
        }
        else
        {
            m_apModel[nCount] = CModel::Create(m_apModel[m_PartsData[nCount].nParent], this, m_modeldata[nCount], m_PartsData[nCount].Partspos, m_Partsrot[nCount], m_PartsSize[nCount]);
        }
    }
    //�E�F�|��UI����
    m_Weapons_UI = CWeapons_ui::Create();
    //�_���[�WUI�̐���
    m_pDamageUi = CDamage_ui::Create();

    //�o���b�g�̏����l�̐�����Create����
    for(int nCountBullet = 0; nCountBullet < m_nMagazineSize; nCountBullet++)
    {
        // nCountBullet�̐����������邲�Ƃɉ��ɓW�J���Ă�������
        m_pBulletUi[nCountBullet] = CBullet_ui::Create(D3DXVECTOR3((SCREEN_WIDTH - (BULLET_UI_SIZE.x + (BULLET_UI_SIZE.x * nCountBullet))), (SCREEN_HEIGHT - 70.0f), 0.0f));
    }
    //�}�l�[�W���[�Ƀ|�C���^�ۑ�
    CManager::SetPlayer(this);

    //�A�j���ۑ�
    m_pAnime = m_pAnimaSave;

    //�A�j���V�����Z�b�g
    m_pAnime->SetAnimation(CAnimation::MOTION_PLAYER_NEUTRAL);

    return S_OK;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�I������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CPlayer::Uninit(void)
{
    //���f���j��
    for(int nCount = 0; nCount < PARTS_MAX; nCount++)
    {
        m_apModel[nCount]->Uninit();
		m_apModel[nCount] = NULL;
    }
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�X�V����
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CPlayer::Update(void)
{
    CInputKeyboard* pInputKeyboard = nullptr;                     //�L�[�{�[�h���͗p
    CInputMouse* pInputMouse       = nullptr;                     //�}�E�X���͗p
    CSound* pSound                 = CManager::GetSound();        //�T�E���h�̎擾
    POINT point;                                                  //�}�E�X�|�C���^�̈ʒu�擾�p
    bool bMove     = false;                                       //�ړ����Ă��邩�ǂ���
    pInputKeyboard = (CInputKeyboard*)CManager::GetInputKey();    //�L�[�{�[�h���͎擾
    pInputMouse    = (CInputMouse*)CManager::GetInputMou();       //�}�E�X���͎擾
    GetCursorPos(&point);                                         //�}�E�X�ʒu�擾
	//�v���C���[������ł��Ȃ����
    if(m_state != STATE_DEATH)
    {
        SetCursorPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);                             //�}�E�X�ʒu�𒆉��ɌŒ�
        m_rot.y -= (point.x - (SCREEN_WIDTH / 2)) * (float)(SENSI_RATE * m_nSensi);    //�v���C���[�̉�]�ʂɃ}�E�X�ʒu�𔽉f
        m_rot.x += (point.y - (SCREEN_HEIGHT / 2)) * (float)(SENSI_RATE * m_nSensi);

        // �W���o�����b�N���p
        if(m_rot.x > 90.0f)
        {
            m_rot.x = 89.0f;
        }
        else if(m_rot.x < -90.0f)
        {
            m_rot.x = -89.0f;
        }

        if(m_rot.y < 0.0f)
        {
            m_rot.y += 360.0f;
        }
        if(m_rot.y > 360.0f)
        {
            m_rot.y -= 360.0f;
        }

        CManager::GetCamera()->SetRot(m_rot);    //�J�����������ɍ��킹��

        //�}�E�X���x����
        if(pInputKeyboard->GetKeyTrigger(DIK_LBRACKET))
        {
            m_nSensi++;
        }
        if(pInputKeyboard->GetKeyTrigger(DIK_RBRACKET))
        {
            m_nSensi--;
            if(m_nSensi <= 0)
            {
                m_nSensi = 1;
            }
        }

        //�ړ�����
        if(pInputKeyboard->GetKeyPress(DIK_W) || pInputKeyboard->GetKeyPress(DIK_A) || pInputKeyboard->GetKeyPress(DIK_S) || pInputKeyboard->GetKeyPress(DIK_D))
        {
            bMove = true;
            Move(pInputKeyboard);
        }

        //�A�C�e���g�p
        if(m_nHaveItem > 0 && pInputKeyboard->GetKeyTrigger(DIK_F))
        {
            UseItem(pSound);
        }

        m_pDamageUi->SetDamageUi(m_nLife);    //�_���[�WUI�̐ݒ�

        //��C������
        if(m_nRemainingAmmo <= 0 && pInputMouse->GetKeyTrigger(CInputMouse::MOUSE_BUTTON_LEFT) && m_state == STATE_AIM)
        {
            pSound->PlaySoundA(CSound::SOUND_LABEL_SE_AIR);
        }

        //�����[�h����
        if(pInputKeyboard->GetKeyTrigger(DIK_R) && m_state != STATE_RELOAD && m_state != STATE_RELOAD_WALK && m_nRemainingAmmo < m_nMagazineSize)
        {
            BeginReload(pSound, bMove);
        }

        //�����[�h��������
        if(m_pAnime->GetAnimeEnd() == false)
        {
            EndReload(pSound);
        }

        //�v���C���[�̏�ԕύX
        ChangeState(pInputKeyboard, pInputMouse, pSound, bMove);

        // AIM���ɐ��ʂ���������
        if(m_state == STATE_AIM)
        {
            m_fMoveVector = m_rot.y - 90.0f;

            //�ˌ�����
            if(pInputMouse->GetKeyPress(CInputMouse::MOUSE_BUTTON_LEFT) && m_nFrameCounter++ > ASSAULT_RIFLE_RATE && CManager::GetWeaponsMode() == CManager::WEAPONS_MODE_AR && m_nRemainingAmmo-- > 0)
            {
                // AR
                m_nFrameCounter = 0;
                Shot(AR_DAMAGE, ADD_SPREAD_AR, pSound);
            }
            else if(pInputMouse->GetKeyTrigger(CInputMouse::MOUSE_BUTTON_LEFT) && m_nFrameCounter++ > HANDGUN_RATE && CManager::GetWeaponsMode() == CManager::WEAPONS_MODE_HG && m_nRemainingAmmo-- > 0)
            {
                // HG
                m_nFrameCounter = 0;
                Shot(HG_DAMAGE, ADD_SPREAD_HG, pSound);
            }
        }
        else
        {
            // AIM���ȊO�̓N���X�w�A������
            if(m_pCrosshair != NULL)
            {
                m_pCrosshair->Uninit();
                m_pCrosshair = NULL;
            }
        }

        //�N���X�w�A�����݂��Ă���Ίg�U�̍ŏ��l��ݒ�
        if(m_pCrosshair != NULL)
        {
            if(bMove)
            {
                m_pCrosshair->SetMinSpread(MIN_SPREAD_WALK);
            }
            else
            {
                m_pCrosshair->SetMinSpread(MIN_SPREAD_STOP);
            }
        }

        //���S
        if(m_nLife <= 0)
        {
            pSound->PlaySoundA(CSound::SOUND_LABEL_SE_SCREAM);
            m_state         = STATE_DEATH;
            m_nFrameCounter = 0;
        }
        //���f���̈ʒu��ݒ�
        m_apModelWorld->SetPos(m_pos);
        //���f���̌�����ݒ�
        m_apModelWorld->SetRot(-D3DXToRadian(D3DXVECTOR3(0, m_fMoveVector + 90, 0)));
    }
    else //���S��
    {
        //���񂾏ꍇ�̏���
        if(m_nFrameCounter == GAMEOVER_COUNT)    //����ł����莞�ԗ�������Q�[���I�[�o�[��ʂ��o��
        {
			CGameoverOverlay::Create();
        }
		m_nFrameCounter++;
    }
    //�A�j���[�V�����R���g���[������
    AnimaControl();
    //�A�j���[�V��������
    m_pAnime->SetAnimation(m_AnimaMotion);
    //�A�j���[�V�����p�֐�
    PartsUpdate();
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�`�揈��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CPlayer::Draw(void)
{
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�����֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CPlayer* CPlayer::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 size)
{
    CPlayer* pPlayer = new CPlayer;
    pPlayer->m_pos   = pos;
    pPlayer->m_rot   = rot;
    pPlayer->m_size  = size;
    pPlayer->Init();

    return pPlayer;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�t�@�C���ǂݍ���
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CPlayer::Load(void)
{
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

    //�v���C���[���f�����[�h
    for(int nCount = 0; nCount < PARTS_MAX ; nCount++)
    {
        D3DXLoadMeshFromX(m_PartsData[nCount].FileName, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_modeldata[nCount].pBuffMat, NULL, &m_modeldata[nCount].nNumMat, &m_modeldata[nCount].pMesh);
        m_pMat = (D3DXMATERIAL*)m_modeldata[nCount].pBuffMat->GetBufferPointer();

        for(int nCountMat = 0; nCountMat < (int)m_modeldata[nCount].nNumMat; nCountMat++)
        {
            D3DXCreateTextureFromFile(pDevice, m_pMat[nCountMat].pTextureFilename, &m_modeldata[nCount].pTexture[nCountMat]);
        }
    }

    //�E�F�|�����f�����[�h
    for(int nCount = 0; nCount < CManager::WEAPONS_MODE_MAX; nCount++)
    {
        D3DXLoadMeshFromX(m_PartsWeapon[nCount], D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_modelWeaponData[nCount].pBuffMat, NULL, &m_modelWeaponData[nCount].nNumMat, &m_modelWeaponData[nCount].pMesh);
        m_pMat = (D3DXMATERIAL*)m_modelWeaponData[nCount].pBuffMat->GetBufferPointer();
        for(int nCountMat = 0; nCountMat < (int)m_modelWeaponData[nCount].nNumMat; nCountMat++)
        {
            D3DXCreateTextureFromFile(pDevice, m_pMat[nCountMat].pTextureFilename, &m_modelWeaponData[nCount].pTexture[nCountMat]);
        }
    }
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�t�@�C���j��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CPlayer::Unload(void)
{
    //�v���C���[���f���A�����[�h
    for(int nCount = 0; nCount < PARTS_MAX; nCount++)
    {
        if(m_modeldata[nCount].pBuffMat != NULL)
        {
            m_modeldata[nCount].pBuffMat->Release();
        }

        if(m_modeldata[nCount].pMesh != NULL)
        {
            m_modeldata[nCount].pMesh->Release();
        }

        for(int nCountTex = 0; nCountTex < MAX_MATERIAL; nCountTex++)
        {
            if(m_modeldata[nCount].pTexture[nCountTex] != NULL)
            {
                m_modeldata[nCount].pTexture[nCountTex]->Release();
            }
        }
    }
	ZeroMemory(&m_modeldata, sizeof(m_modeldata));
    //�E�F�|�����f���A�����[�h
    for(int nCount = 0; nCount < CManager::WEAPONS_MODE_MAX; nCount++)
    {
        if(m_modelWeaponData[nCount].pBuffMat != NULL)
        {
            m_modelWeaponData[nCount].pBuffMat->Release();
        }

        if(m_modelWeaponData[nCount].pMesh != NULL)
        {
            m_modelWeaponData[nCount].pMesh->Release();
        }

        for(int nCountTex = 0; nCountTex < MAX_MATERIAL; nCountTex++)
        {
            if(m_modelWeaponData[nCount].pTexture[nCountTex] != NULL)
            {
                m_modelWeaponData[nCount].pTexture[nCountTex]->Release();
            }
        }
    }
	ZeroMemory(&m_modelWeaponData, sizeof(m_modelWeaponData));
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�Q�b�^�[�֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
D3DXVECTOR3 CPlayer::GetPos(void)
{
    return m_pos;
}
D3DXVECTOR3 CPlayer::GetPartsPos(const int nParts)
{
    return m_PartsData[nParts].Partspos;
}

D3DXVECTOR3 CPlayer::GetCenter(void)
{
    return (m_pos + (m_PartsData[PARTS_CHEST].Partspos * 0.2f)) + (m_Partspos[PARTS_CHEST] * 0.2f);
}

D3DXVECTOR3 CPlayer::GetRot(void)
{
    return m_rot;
}

CPlayer::STATE CPlayer::GetState(void)
{
    return m_state;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�e��(���C)�����f���ɓ�������������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
BOOL CPlayer::CheckHitBullet(const CModel::MODELDATA modeldata, BOOL* pHit, float* pDistance, const D3DXVECTOR3 spread)
{
    D3DXVECTOR3 TransformedPos, TranceformedVec, NormalizedVec, PosR;
    PosR = CManager::GetCamera()->GetPosR();                                                                            //�����_
    D3DXVec3Normalize(&NormalizedVec, &((PosR + spread) - (m_pos + D3DXVECTOR3(0, PLAYER_HEAD_HEIGHT, 0))));            //�v���C���[���璍���_�ւ̃x�N�g����P�ʃx�N�g���ɕϊ�
	D3DXMATRIX InversedWorldMatrix;
    D3DXMatrixInverse(&InversedWorldMatrix, NULL, &modeldata.mtxWorld);                                                 //�t�s�񐶐�
    D3DXVec3TransformCoord(&TransformedPos, &(m_pos + D3DXVECTOR3(0, PLAYER_HEAD_HEIGHT, 0)), &InversedWorldMatrix);    //�t�s��ŕϊ�
    D3DXVec3TransformNormal(&TranceformedVec, &NormalizedVec, &InversedWorldMatrix);
	BOOL bHit;
    D3DXIntersect(modeldata.pMesh, &TransformedPos, &TranceformedVec, &bHit, NULL, NULL, NULL, pDistance, NULL, NULL);    //�����蔻����m�F
    pHit = &bHit;
    return bHit;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�e��(���C)�������������f���擾
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CObject* CPlayer::GetHitObject(void)
{
    CObject* pTop[PRIORITY_MAX] = {};      //�I�u�W�F�N�g�擾�p
    CObject* pNext              = NULL;    //���`�F�b�N����I�u�W�F�N�g�̃|�C���^
    D3DXVECTOR3 RandomSpread;              //�e�e�̃u��
    for(int nCount = 0; nCount < PRIORITY_MAX; nCount++)
    {
        pTop[nCount] = *(CObject::GetTop() + nCount);    // top�̃A�h���X���擾
    }
    float fDistance        = 0.0f;       //�e�e(���C)��������������
    float fClosestDistance = 0.0f;       //�e�e(���C)���������������̒��ň�ԋ߂���
    CObject* ClosestObject = NULL;		//���̃I�u�W�F�N�g�̃|�C���^
    //�e�e�̃u���𐶐�
    RandomSpread = D3DXVECTOR3((float)(rand() % (int)(m_pCrosshair->GetSpread() + 1)), (float)(rand() % (int)(m_pCrosshair->GetSpread() + 1)), (float)(rand() % (int)(m_pCrosshair->GetSpread() + 1)));
    //�e�e�̃u���𒆉��ɕ␳
	float fSpread = m_pCrosshair->GetSpread();
    RandomSpread.x -= fSpread / 4.0f;
    RandomSpread.y -= fSpread / 4.0f;
    RandomSpread.z -= fSpread / 4.0f;

    //�I�u�W�F�N�g�T��
    for(int nCount = 0; nCount < PRIORITY_MAX; nCount++)
    {
		if (pTop[nCount] == NULL)
		{
			continue;
		}
        //���̕`��D��x�̃I�u�W�F�N�g���Ȃ��Ȃ�܂Ń��[�v
        for(pNext = pTop[nCount];pNext != NULL;pNext = pNext->GetNext())
        {
			if (pNext->GetObjType() != OBJTYPE_MODEL)    //�I�u�W�F�N�g�̃^�C�v�����f���Ȃ�
			{
				continue;
			}
			CModel* pModel = (CModel*)pNext;
			if (pModel->GetParentObject() == NULL)    //�e�I�u�W�F�N�g�����݂���Ȃ�
			{
				continue;
			}
			if (!pModel->GetParentObject()->GetCollisionBullet())    //�e�e�ɑ΂��铖���蔻������邩�`�F�b�N
			{
				continue;
			}
			if (!CheckHitBullet(((CModel*)pNext)->GetModelData(), NULL, &fDistance, RandomSpread))    //�����蔻����`�F�b�N
			{
				continue;
			}
            if(ClosestObject == NULL || fClosestDistance > fDistance)    //�����ԋ߂��I�u�W�F�N�g�����݂��Ȃ�������܂łň�ԋ߂����
            {
                //��ԋ߂��I�u�W�F�N�g���X�V
                ClosestObject    = pNext;
                fClosestDistance = fDistance;
            }
        }
    }
    return ClosestObject;    //��ԋ߂��I�u�W�F�N�g��Ԃ�
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
// HP���Z(���̐��w��Ō��炷)
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CPlayer::AddLife(const int Value)
{
    m_nLife += Value;
    //���݂̃��C�t�̒l���_���[�WUI�ɓ����
    if(m_nLife > START_LIFE)
    {
        m_nLife = START_LIFE;
    }
    if(m_nLife < 0)
    {
        m_nLife = 0;
    }
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
// HP�Q�b�g�֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
int CPlayer::GetLife(void)
{
    return m_nLife;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�ǂƂ̓����蔻��擾�p�֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
BOOL CPlayer::Collision(const CModel::MODELDATA modeldata, D3DXVECTOR3* pHittedPolyNormal, int* pHitCount)
{
    int HitCount = 0;                                              //�v���C���[���ڂ��Ă��郁�b�V���̐�
    BOOL bHit    = false;                                          //�v���C���[���o���Ă��郌�C�����b�V���ɓ������Ă��邩
    D3DXMATRIX InversedWorldMatrix;                                //���[���h�ϊ��s��̋t�s��
    D3DXVECTOR3 TransformedPos, TranceformedVec, NormalizedVec;    //�e�ϊ���̃x�N�g��
    float fRayRot               = 0.0f;                               //���C���΂�����
    float fDistance             = 0.0f;                               //���C���q�b�g��������
    DWORD dwPolyIndex           = 0;                               //�����������b�V���̃C���f�b�N�X
    DWORD HittedPolyIndex[1024] = {};

    for(int nCount = 0; nCount < COLLISION_RAY_COUNT; nCount++)
    {
        bool bAlreadyChecked = false;
        fRayRot              = (float)nCount * (360 / COLLISION_RAY_COUNT);                                                      //���C���ϓ��Ȋp�x�Ŕ�΂�
        D3DXVec3Normalize(&NormalizedVec, &(D3DXVECTOR3(cosf(D3DXToRadian(fRayRot)), 0.0f, sinf(D3DXToRadian(fRayRot)))));          //�v���C���[���璍���_�ւ̃x�N�g����P�ʃx�N�g���ɕϊ�
        D3DXMatrixInverse(&InversedWorldMatrix, NULL, &modeldata.mtxWorld);                                                      //�t�s�񐶐�
        D3DXVec3TransformCoord(&TransformedPos, &(m_pos + D3DXVECTOR3(0.0f, PLAYER_COLLISION_HEIGHT, 0.0f)), &InversedWorldMatrix);    //�t�s��ŕϊ�
        D3DXVec3TransformNormal(&TranceformedVec, &NormalizedVec, &InversedWorldMatrix);
        D3DXIntersect(modeldata.pMesh, &TransformedPos, &TranceformedVec, &bHit, &dwPolyIndex, NULL, NULL, &fDistance, NULL, NULL);    //�����蔻����m�F

        for(int nCountPoly = 0; nCountPoly < HitCount; nCountPoly++)
        {
            if(HittedPolyIndex[nCountPoly] == dwPolyIndex)
            {
                bAlreadyChecked = true;
            }
        }

        if(bHit && fDistance < PLAYER_COLLISION_RADIUS && !bAlreadyChecked)    //���C���q�b�g���������v���C���[�̓����蔻��̃T�C�Y�ȉ��Ȃ�
        {
            D3DXVECTOR3 vertex[3];                                       //���C���q�b�g�������b�V���̒��_���W
            D3DXPLANE plane;                                             //���b�V���̕���
            FindVerticesOnPoly(modeldata.pMesh, dwPolyIndex, vertex);    //���b�V���̒��_���擾

            //���̒��_���畽�ʕ������𓾂�
            D3DXPlaneFromPoints(&plane, &vertex[0], &vertex[1], &vertex[2]);
            //�@�����v�Z
            pHittedPolyNormal[HitCount].x = plane.a;
            pHittedPolyNormal[HitCount].y = plane.b;
            pHittedPolyNormal[HitCount].z = plane.c;
            D3DXVec3Normalize(&pHittedPolyNormal[HitCount], &pHittedPolyNormal[HitCount]);
            HittedPolyIndex[HitCount] = dwPolyIndex;
			assert(sizeof(HittedPolyIndex) / sizeof(HittedPolyIndex[0]) < 1024);
            HitCount++;    //�����������b�V���̐��𑝂₷
        }
    }
    *pHitCount = HitCount;

	return HitCount > 0;

}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//���b�V���̒��_���W���擾
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CPlayer::FindVerticesOnPoly(const LPD3DXMESH pMesh, const DWORD dwPolyIndex, D3DXVECTOR3* pvecVertices)
{
    DWORD dwStride = pMesh->GetNumBytesPerVertex();
    WORD* pwPoly   = NULL;
    pMesh->LockIndexBuffer(D3DLOCK_READONLY, (VOID**)&pwPoly);
    BYTE* pbVertices           = NULL;
    FLOAT* pfVetices           = NULL;
    LPDIRECT3DVERTEXBUFFER9 VB = NULL;
    pMesh->GetVertexBuffer(&VB);
    if(SUCCEEDED(VB->Lock(0, 0, (VOID**)&pbVertices, 0)))
    {
        for(int nCount = 0; nCount < 3; nCount++)
        {
            pfVetices              = (FLOAT*)&pbVertices[dwStride * pwPoly[dwPolyIndex * 3 + nCount]];
            pvecVertices[nCount].x = pfVetices[0];
            pvecVertices[nCount].y = pfVetices[1];
            pvecVertices[nCount].z = pfVetices[2];
        }
        pMesh->UnlockIndexBuffer();
        VB->Unlock();
    }
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�ǂ���x�N�g������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
D3DXVECTOR3 CPlayer::CalcWallScratchVector(const D3DXVECTOR3 move, const D3DXVECTOR3 nomal)
{
    return move - ((D3DXVec3Dot(&nomal, &move)) / (float)(pow(D3DXVec3Length(&nomal), 2))) * nomal;
}

//=============================================================================
// �p�[�c�A�b�v�f�[�g�֐�
//=============================================================================
void CPlayer::PartsUpdate(void)
{
    if(m_pAnime != NULL)
    {
        for(int nCount = 0; nCount < PARTS_MAX /*(�ǂݍ��񂾃��f������)*/; nCount++)
        {
            m_apModel[nCount]->SetAnimationRot(m_Partsrot[nCount]);
            m_apModel[nCount]->SetAnimationPos(m_Partspos[nCount]);
        }
        m_pAnime->Update();
        for(int nCount = 0; nCount < PARTS_MAX /*(�ǂݍ��񂾃��f������)*/; nCount++)
        {
            m_Partsrot[nCount] = m_pAnime->GetAnimeRot(nCount);
            m_Partspos[nCount] = m_pAnime->GetAnimePos(nCount);
            m_pAnime->SetAnimeRot(nCount, m_Partsrot[nCount]);
            m_pAnime->SetAnimePos(nCount, m_Partspos[nCount]);
        }
    }
}

//=============================================================================
// �A�j���[�V�����R���g���[���֐�
//=============================================================================
void CPlayer::AnimaControl(void)
{
    //�X�e�[�g�X�C�b�`
    switch(m_state)
    {
            //�j���[�g����
        case STATE_STAND:
            m_AnimaMotion = CAnimation::MOTION_PLAYER_NEUTRAL;
            break;
            //����
        case STATE_WALK:
            m_AnimaMotion = CAnimation::MOTION_PLAYER_MOVE;
            break;
            //����
        case STATE_SPRINT:
            m_AnimaMotion = CAnimation::MOTION_PLAYER_SPRINT;
            break;
            //���Ⴊ��
        case STATE_CROUCH:
            m_AnimaMotion = CAnimation::MOTION_PLAYER_CROUCHING;
            break;
            //���Ⴊ�ݕ���
        case STATE_CROUCH_WALK:
            m_AnimaMotion = CAnimation::MOTION_PLAYER_CROUCHING_MOVE;
            break;
            //�G�C��
        case STATE_AIM:
            m_AnimaMotion = CAnimation::MOTION_PLAYER_AIM;
            break;
            //�����[�h
        case STATE_RELOAD:
            m_AnimaMotion = CAnimation::MOTION_PLAYER_RELOAD;
            break;
            //�����[�h����
        case STATE_RELOAD_WALK:
            m_AnimaMotion = CAnimation::MOTION_PLAYER_RELOAD_MOVE;
            break;
            //��
        case STATE_DEATH:
            m_AnimaMotion = CAnimation::MOTION_PLAYER_DEATH;
            break;
        default:
			assert(false);
            break;
    }
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�A�C�e����ǉ�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CPlayer::AddItem(void)
{
    m_apItemUI[m_nHaveItem] = CItem_ui::Create(D3DXVECTOR3(SCREEN_WIDTH - 100.0f, SCREEN_HEIGHT - 300.0f - m_nHaveItem * 100.0f, 0.0f));
    m_nHaveItem++;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//���͂�����ɕϊ�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
float CPlayer::InputToAngle(CInputKeyboard* const pInputKey)
{
    //�ړ�
    if(pInputKey->GetKeyPress(DIK_W))
    {
        //�ړ������w��
        m_fMoveVector = 270.0f;
    }
    if(pInputKey->GetKeyPress(DIK_S))
    {
        //�ړ������w��
        m_fMoveVector = 90.0f;
    }
    if(pInputKey->GetKeyPress(DIK_A))
    {
        //�ړ������w��
        m_fMoveVector = 0.0f;
        //���������̏���
        if(pInputKey->GetKeyPress(DIK_W))
        {
            m_fMoveVector = 315.0f;
        }
        else if(pInputKey->GetKeyPress(DIK_S))
        {
            m_fMoveVector = 45.0f;
        }
    }
    if(pInputKey->GetKeyPress(DIK_D))
    {
        //�ړ������w��
        m_fMoveVector = 180.0f;
        //���������̏���
        if(pInputKey->GetKeyPress(DIK_W))
        {
            m_fMoveVector = 225.0f;
        }
        else if(pInputKey->GetKeyPress(DIK_S))
        {
            m_fMoveVector = 135.0f;
        }
    }
    return m_fMoveVector;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�ړ����x�ύX
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
float CPlayer::ChangeMoveSpeed(void)
{
    float fMoveSpeed = NULL;
    //���ꂼ��̏�ԂɊ��蓖�Ă�ꂽ�ړ����x����
    switch(m_state)
    {
        case STATE_SPRINT:
            fMoveSpeed = PLAYER_MOVE_SPEED_SPRINT;
            break;
        case STATE_CROUCH_WALK:
            fMoveSpeed = PLAYER_MOVE_SPEED_CROUCH;
            break;
        case STATE_AIM:
            fMoveSpeed = PLAYER_MOVE_SPEED_AIM;
            break;
        case STATE_RELOAD:
            fMoveSpeed = 0.0f;
            break;
        case STATE_RELOAD_WALK:
            fMoveSpeed = PLAYER_MOVE_SPEED_AIM;
            break;
        case STATE_DEATH:
            fMoveSpeed = 0.0f;
            break;
        default:
            fMoveSpeed = PLAYER_MOVE_SPEED;
            break;
    }

	//���킲�Ƃ̈ړ����x�̔{����ݒ�
	float fMoveRate = 0.0f;
	switch (CManager::GetWeaponsMode())
	{
	case CManager::WEAPONS_MODE_AR:
		fMoveRate = AR_MOVE_RATE;
		break;
	case CManager::WEAPONS_MODE_HG:
		fMoveRate = HG_MOVE_RATE;
		break;
	default:
		assert(false);
		break;
	}
    return fMoveSpeed *= fMoveRate;;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�ړ�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CPlayer::Move(CInputKeyboard* const pInputKey)
{
    D3DXVECTOR3 move = ZEROVECTOR3;                       //�ړ���
    D3DXVECTOR3 HittedPolyNormal[COLLISION_RAY_COUNT];    //���C�������������b�V���̖@��
    int nCountHit = 0;                                    //�����������b�V���̐�

    m_fMoveVector = InputToAngle(pInputKey);
    m_fMoveVector += m_rot.y;
    if(m_fMoveVector < 0)
    {
        m_fMoveVector += 360;
    }
    if(m_fMoveVector > 360)
    {
        m_fMoveVector -= 360;
    }

    //�ړ����x�ݒ�
    float fMoveSpeed = ChangeMoveSpeed();

    //������ꂽ�ړ����x�����ƂɈړ�����x�N�g���𐶐�
    move = D3DXVECTOR3(fMoveSpeed * cosf(D3DXToRadian(m_fMoveVector)), 0, fMoveSpeed * sinf(D3DXToRadian(m_fMoveVector)));

    if(Collision(CManager::GetStageModel()->GetModelData(), HittedPolyNormal, &nCountHit))    //�ǂɐG�ꂽ�ꍇ
    {
        for(int nCount = 0; nCount < nCountHit; nCount++)
        {
            float NormalRot            = D3DXToDegree(atan2f(HittedPolyNormal[nCount].z, HittedPolyNormal[nCount].x));
            float CollisionRotRange[2] = {};
            CollisionRotRange[0]       = NormalRot - 90;
            CollisionRotRange[1]       = NormalRot + 90;
            for(int nCountRange = 0; nCountRange < 2; nCountRange++)
            {
                if(CollisionRotRange[nCountRange] < 0)
                {
                    CollisionRotRange[nCountRange] += 360;
                }
                if(CollisionRotRange[nCountRange] > 360)
                {
                    CollisionRotRange[nCountRange] -= 360;
                }
            }
            if(CollisionRotRange[0] > CollisionRotRange[1])
            {
                if(CollisionRotRange[0] > m_fMoveVector && CollisionRotRange[1] < m_fMoveVector)
                {
                    move = CalcWallScratchVector(move, HittedPolyNormal[nCount]);    //�ǂ���x�N�g�����v�Z
                }
            }
            else
            {
                if(CollisionRotRange[0] > m_fMoveVector || CollisionRotRange[1] < m_fMoveVector)
                {
                    move = CalcWallScratchVector(move, HittedPolyNormal[nCount]);    //�ǂ���x�N�g�����v�Z
                }
            }
        }
    }
    //�ʒu�Ɉړ��ʂ𑫂�
    m_pos += move;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�A�C�e���g�p
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CPlayer::UseItem(CSound* const pSound)
{
    pSound->PlaySoundA(CSound::SOUND_LABEL_SE_HEAL);
    m_nHaveItem--;
    m_apItemUI[m_nHaveItem]->Uninit();
    m_apItemUI[m_nHaveItem] = NULL;
    m_nLife                 = START_LIFE;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�����[�h�J�n����
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CPlayer::BeginReload(CSound* const pSound, const bool bMove)
{
    pSound->PlaySoundA(CSound::SOUND_LABEL_SE_MAGAZINEOUT);
    if(bMove)
    {
        m_state = STATE_RELOAD_WALK;
    }
    else
    {
        m_state = STATE_RELOAD;
    }
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�����[�h�I������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CPlayer::EndReload(CSound* const pSound)
{
    if(m_state == STATE_RELOAD || m_state == STATE_RELOAD_WALK)
    {
        //�c�e����0�ȉ��̏ꍇ�A0�ɖ߂�
        if(m_nRemainingAmmo <= 0)
        {
            m_nRemainingAmmo = 0;
        }
        //�����[�h��������BulletUI���ăN���G�C�g
        for(int nCountBullet = m_nRemainingAmmo; nCountBullet < m_nMagazineSize; nCountBullet++)
        {
            m_pBulletUi[nCountBullet] = CBullet_ui::Create(D3DXVECTOR3((SCREEN_WIDTH - (15.0f + (15.0f * nCountBullet))), (SCREEN_HEIGHT - 70.0f), 0.0f));
        }

        m_nRemainingAmmo = m_nMagazineSize;
        m_state          = STATE_STAND;
        pSound->PlaySoundA(CSound::SOUND_LABEL_SE_MAGAZINESET);
    }
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//��ԕύX
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CPlayer::ChangeState(CInputKeyboard* const pInputKey, CInputMouse* const pInputMou, CSound* const pSound, const bool bMove)
{
    //�����[�h���̕����Ɨ����~�܂�̐؂�ւ�
    if(m_state == STATE_RELOAD && bMove)
    {
        m_state = STATE_RELOAD_WALK;
    }
    else if(m_state == STATE_RELOAD_WALK && bMove == false)
    {
        m_state = STATE_RELOAD;
    }

    if(m_state != STATE_RELOAD && m_state != STATE_RELOAD_WALK)
    {
        if(pInputMou->GetKeyTrigger(CInputMouse::MOUSE_BUTTON_RIGHT))    //�E�N���b�N����AIM
        {
            pSound->PlaySoundA(CSound::SOUND_LABEL_SE_AIM);
        }
        if(pInputMou->GetKeyPress(CInputMouse::MOUSE_BUTTON_RIGHT))    //�E�N���b�N����AIM
        {
            m_state = STATE_AIM;
            //�N���X�w�A�������ꍇ�̓N���X�w�A�𐶐�����
            if(m_pCrosshair == NULL)
            {
                m_pCrosshair = CCrosshair::Create(30.0f);
            }
        }
        else if(pInputKey->GetKeyPress(DIK_LSHIFT) && bMove)    // LSHIFT����������Ă��邩�ړ����Ȃ�X�v�����g
        {
            m_state = STATE_SPRINT;
        }
        else if(pInputKey->GetKeyPress(DIK_LCONTROL) && bMove)
        {
            m_state = STATE_CROUCH_WALK;
        }
        else if(pInputKey->GetKeyPress(DIK_LCONTROL) && bMove == false)    // LCONTROL����������Ă��邳��Ă���ꍇ�͂��Ⴊ��
        {
            m_state = STATE_CROUCH;
        }
        else if(bMove)
        {
            m_state = STATE_WALK;
        }
        else    //��L�̂ǂ�ɂ����Ă͂܂�Ȃ��ꍇ�ʏ�
        {
            m_state = STATE_STAND;
        }
    }
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�e������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CPlayer::Shot(const int nBulletDamage, const float fSpread, CSound* const pSound)
{
    pSound->PlaySoundA(CSound::SOUND_LABEL_SE_ASSAULT);
    CObject* pHitObject = GetHitObject();    //�����蔻�肳�ꂽ�I�u�W�F�N�g���擾
    m_Weapons_UI->Gleams();
    //�o���b�gUI�����݂���Ȃ�e������ꂽ�^�C�~���O��Uninit����
    if(m_pBulletUi[m_nRemainingAmmo] != NULL && m_nRemainingAmmo >= 0)
    {
        m_pBulletUi[m_nRemainingAmmo]->Uninit();
    }
    if(pHitObject != NULL)
    {
        if(((CModel*)pHitObject)->GetParentObject() != NULL)
        {
            switch(((CModel*)pHitObject)->GetParentObject()->GetObjType())    //�����������f���̐e�I�u�W�F�N�g�̃^�C�v�ɂ���ď�����ς���
            {
                case OBJTYPE_ENEMY:
                    ((CEnemy*)((CModel*)pHitObject)->GetParentObject())->Hit(nBulletDamage);
                    break;
                case OBJTYPE_STAGE:
                    break;
                default:
                    ((CModel*)pHitObject)->GetParentObject()->Uninit();
                    break;
            }
        }
    }
    m_pCrosshair->AddSpread(fSpread);    //�N���X�w�A�̊g�U�𑝂₷
}
