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
#include "inputkeyboard.h"
#include "inputmouse.h"
#include "manager.h"
#include "bullet.h"
#include "renderer.h"
#include "sound.h"
#include "laser.h"
#include "life.h"
#include "energy.h"
#include "stdio.h"
#include "number.h"
#include "cursol.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�ÓI�����o�ϐ��錾
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture   = NULL;
LPDIRECT3DTEXTURE9 CPlayer::m_pTextureUI = NULL;

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�R���X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CPlayer::CPlayer() : CScene2d(2)
{
    m_pLife       = NULL;
    m_LaserType   = CLaser::LASERTYPE_STRONG_STRAIGHT;
    m_nStateCount = 0;
    m_nCountFrame = 0;
    m_pPolygon    = NULL;
    m_CountNumber = NULL;
    m_pCursol     = NULL;
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
    CScene2d::Init();
    BindTexture(m_pTexture);

    return S_OK;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�I������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CPlayer::Uninit(void)
{
    if(m_pPolygon != NULL)
    {
        m_pPolygon->Uninit();
		delete m_pPolygon;
		m_pPolygon = NULL;
    }

	if (m_CountNumber != NULL)
	{
		m_CountNumber->Uninit();
		delete m_CountNumber;
		m_CountNumber = NULL;
	}

	//���񂾂��Ƃ�Manager�ɋ�����
    CManager::SetAlive(false);

    CScene2d::Uninit();
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�X�V����
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CPlayer::Update(void)
{
	//�ړ�
	D3DXVECTOR3 WorldPos = Move();

	//�^�C���Ƃ̓����蔻��
	CollisionTile(&WorldPos);

	//��ʊO����
	bool bGameOver = OutOfScreen();

    //�ʒu�ݒ�
    SetWorldPos(WorldPos);
	
	//���[�U�[����
	ShotLaser();

	//���[�U�[�^�C�v�ݒ�
	ChangeLaserType();

	//posOld�ݒ�
    m_posOld = WorldPos;

    CScene2d::Update();

	//���Ԑ����̐����X�V
    if(m_CountNumber != NULL)
    {
        m_CountNumber->Update();
    }

	//�Q�[���I�[�o�[�ɂȂ�����E��
    if(bGameOver)
    {
        Uninit();
    }
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�`�揈��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CPlayer::Draw(void)
{
    CScene2d::Draw();

	//��ʊO�ɏo���Ƃ���UI������
    if(m_pPolygon != NULL)
    {
        m_pPolygon->Draw();
    }
    if(m_CountNumber != NULL)
    {
        m_CountNumber->Draw();
    }
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���G�C�g�֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CPlayer::Create(D3DXVECTOR3 pos)
{
    CPlayer* pPlayer = new CPlayer();     
    pPlayer->SetPos(pos);
    pPlayer->SetWorldPos(pos);
    pPlayer->Init();
    pPlayer->SetSize(D3DXVECTOR3(PLAYER_SIZE_X, PLAYER_SIZE_Y, 0.0f));
    pPlayer->SetObjType(OBJTYPE_PLAYER);
    pPlayer->m_pLife   = CLife::Create();
    pPlayer->m_pEnergy = CEnergy::Create();
    CManager::SetAlive(true);
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�t�@�C���ǂݍ��݊֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
HRESULT CPlayer::Load(void)
{
    D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "Resources\\backtocombat.png", &m_pTextureUI);
    D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "Resources\\player.png", &m_pTexture);
    return S_OK;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�e�N�X�`���j���֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CPlayer::Unload(void)
{
    if(m_pTexture != NULL)
    {
        m_pTexture->Release();
        m_pTexture = NULL;
    }
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//��e����
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CPlayer::HitBullet(void)
{
    m_pLife->AddLife(-10);
    if(m_pLife->GetLife() <= 0)
    {
        //�Q�[���I�[�o�[
        CManager::GameOver();
        Uninit();
    }
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�Q�b�^�[�֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CLife* CPlayer::GetLife(void)
{
    return m_pLife;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�Z�b�^�[�֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CPlayer::SetOverHeat(bool bOverHeat)
{
    m_bOverHeat = bOverHeat;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�^�C������݂��v���C���[�̕������擾
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
int CPlayer::CheckSide(D3DXVECTOR3* pObjVtx)
{
    D3DXVECTOR3 worldPos = GetWorldPos();	//���[���h���W�̎擾
	D3DXVECTOR3 nullvec;	//�����p���p�ϐ�

	//�^�C���̃|���S���̑Ίp���̍��E����𗘗p���ĕ������擾
    if((*D3DXVec3Cross(&nullvec, &(pObjVtx[3] - pObjVtx[0]), &(worldPos - pObjVtx[0]))).z < 0)
    {
        if((*D3DXVec3Cross(&nullvec, &(pObjVtx[1] - pObjVtx[2]), &(worldPos - pObjVtx[2]))).z < 0)
        {
            return 1;
        }
        else
        {
            return 2;
        }
    }
    else
    {
        if((*D3DXVec3Cross(&nullvec, &(pObjVtx[1] - pObjVtx[2]), &(worldPos - pObjVtx[2]))).z < 0)
        {
            return 3;
        }
        else
        {
            return 4;
        }
    }
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//���͂��p�x�ɕϊ�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
int CPlayer::InputToAngle(void)
{
	CInputKeyboard* pInputKey = CManager::GetInputKey();
	int vec = 0;
	//�L�[�{�[�h���͂��p�x�ɕϊ�����
	if (pInputKey->GetKeyPress(DIK_W))
	{
		vec = -90;
	}
	if (pInputKey->GetKeyPress(DIK_S))
	{
		vec = 90;
	}
	if (pInputKey->GetKeyPress(DIK_A))
	{
		vec = 180;

		if (pInputKey->GetKeyPress(DIK_W))
		{
			vec = -135;
		}
		else if (pInputKey->GetKeyPress(DIK_S))
		{
			vec = 135;
		}
	}
	if (pInputKey->GetKeyPress(DIK_D))
	{
		vec = 0;
		if (((CInputKeyboard*)pInputKey)->GetKeyPress(DIK_W))
		{
			vec = -45;
		}
		else if (pInputKey->GetKeyPress(DIK_S))
		{
			vec = 45;
		}
	}
	return vec;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�ړ�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
D3DXVECTOR3 CPlayer::Move(void)
{
	D3DXVECTOR3 move;
	CInputKeyboard* pInputKey = CManager::GetInputKey();
	D3DXVECTOR3 WorldPos = GetWorldPos();
	//�L�[���͏���
	m_nMoveVector = InputToAngle();

	if (pInputKey->GetKeyPress(DIK_LSHIFT) && !m_bOverHeat)	//�X�v�����g�ړ�
	{
		move = D3DXVECTOR3(PLAYER_MOVE_RATE_SPRINT * cosf(D3DXToRadian(m_nMoveVector)), PLAYER_MOVE_RATE_SPRINT * sinf(D3DXToRadian(m_nMoveVector)), 0);
		m_pEnergy->ReduceEnergy(1);
	}
	else	//�ʏ�ړ�
	{
		move = D3DXVECTOR3(PLAYER_MOVE_RATE * cosf(D3DXToRadian(m_nMoveVector)), PLAYER_MOVE_RATE * sinf(D3DXToRadian(m_nMoveVector)), 0);
	}

	//�t�L�[�������������Ƃ��̏���
	if (pInputKey->GetKeyPress(DIK_D) && ((CInputKeyboard*)pInputKey)->GetKeyPress(DIK_A))
	{
		move.x = 0;
	}
	if (pInputKey->GetKeyPress(DIK_W) && ((CInputKeyboard*)pInputKey)->GetKeyPress(DIK_S))
	{
		move.y = 0;
	}

	//�L�[�������Ă���Ƃ������ړ�
	if (pInputKey->GetKeyPress(DIK_W) || pInputKey->GetKeyPress(DIK_A) || pInputKey->GetKeyPress(DIK_S) || pInputKey->GetKeyPress(DIK_D))
	{
		return WorldPos + move;
	}
	else
	{
		return WorldPos;
	}
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//��ʊO�ɏo���Ƃ��̏���
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
bool CPlayer::OutOfScreen(void)
{
	//��ʊO����
	D3DXVECTOR3 ScreenPos = GetPos();
	if (ScreenPos.x < 0 || ScreenPos.x > SCREEN_WIDTH || ScreenPos.y < 0 || ScreenPos.y > SCREEN_HEIGHT)
	{
		if (m_pPolygon == NULL)
		{
			m_pPolygon = CPolygon::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_WIDTH, 0), 0, OBJTYPE_UI);
			m_pPolygon->BindTexture(m_pTextureUI);
		}
		if (m_CountNumber == NULL)
		{
			m_CountNumber = CNumber::Create(LOST_FLAME / 60, D3DXVECTOR3(SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 3) * 2, 0), D3DXVECTOR3(200, 400, 0), D3DCOLOR_RGBA(255, 0, 0, 255));
		}

		m_nCountFrame++;
		if (m_CountNumber != NULL)
		{
			m_CountNumber->SetValue((int)((LOST_FLAME - m_nCountFrame) / 60));
		}
		if (m_nCountFrame > LOST_FLAME)
		{
			if (m_pPolygon != NULL)
			{
				m_pPolygon->Uninit();
				delete m_pPolygon;
				m_pPolygon = NULL;
			}
			if (m_CountNumber != NULL)
			{
				m_CountNumber->Uninit();
				delete m_CountNumber;
				m_CountNumber = NULL;
			}
			CManager::GameOver();
			return true;
		}
	}
	else
	{
		m_nCountFrame = 0;
		if (m_pPolygon != NULL)
		{
			m_pPolygon->Uninit();
			delete m_pPolygon;
			m_pPolygon = NULL;
		}
		if (m_CountNumber != NULL)
		{
			m_CountNumber->Uninit();
			delete m_CountNumber;
			m_CountNumber = NULL;
		}
	}
	return false;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�^�C���Ƃ̓����蔻��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CPlayer::CollisionTile(D3DXVECTOR3* pWorldPos)
{
	//�^�C���Ƃ̓����蔻��
	CScene** pScene = CScene::GetScene();
	//�^�C����T��
	for (int nCount = 0; nCount < MAX_SCENE * PRIORITY_MAX; nCount++)
	{
		if ((*(pScene + nCount)) != NULL)
		{
			
			if ((*(pScene + nCount))->GetObjType() == OBJTYPE_MAP_TILE || (*(pScene + nCount))->GetObjType() == OBJTYPE_MAP_TILE_BRAKABLE)
			{
				//�^�C���̍��W���擾
				D3DXVECTOR3 TilePos = ((CScene2d*)(*(pScene + nCount)))->GetWorldPos();
				//�^�C���Ƃ̓����蔻��
				if (pWorldPos->x + (PLAYER_SIZE_X / 2) > TilePos.x - (MAP_TILE_SIZE / 2) && pWorldPos->x - (PLAYER_SIZE_X / 2) < TilePos.x + (MAP_TILE_SIZE / 2)
					&& pWorldPos->y + (PLAYER_SIZE_Y / 2) > TilePos.y - (MAP_TILE_SIZE / 2) && pWorldPos->y - (PLAYER_SIZE_Y / 2) < TilePos.y + (MAP_TILE_SIZE / 2))
				{
					//�^�C���̒��_���W���擾
					D3DXVECTOR3 TileVtxPos[4];
					TileVtxPos[0] = D3DXVECTOR3(TilePos.x - (MAP_TILE_SIZE / 2), TilePos.y - (MAP_TILE_SIZE / 2), 0);
					TileVtxPos[1] = D3DXVECTOR3(TilePos.x + (MAP_TILE_SIZE / 2), TilePos.y - (MAP_TILE_SIZE / 2), 0);
					TileVtxPos[2] = D3DXVECTOR3(TilePos.x - (MAP_TILE_SIZE / 2), TilePos.y + (MAP_TILE_SIZE / 2), 0);
					TileVtxPos[3] = D3DXVECTOR3(TilePos.x + (MAP_TILE_SIZE / 2), TilePos.y + (MAP_TILE_SIZE / 2), 0);

					//�^�C���̒��_���W����v���C���[�ƃ^�C���̈ʒu�֌W���擾
					int Side = CheckSide(TileVtxPos);	
					
					//�v���C���[�ƃ^�C���̈ʒu�֌W�ɂ���ăv���C���[�̍��W��␳
					if (Side == 1 || Side == 4)
					{
						pWorldPos->y = m_posOld.y;
					}
					if (Side == 2 || Side == 3)
					{
						pWorldPos->x = m_posOld.x;
					}
				}
			}
		}
	}
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//���[�U�[����
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CPlayer::ShotLaser(void)
{
	CInputMouse* pInputMouse = CManager::GetInputMouse();
	//���[�U�[����
	if (!m_bOverHeat && pInputMouse->GetKeyPress(0))
	{
		D3DXVECTOR3 ScreenPos = GetPos();
		//���݂̃��[�U�[�^�C�v�ɂ���Ĕ��˂��郌�[�U�[��ύX
		switch (m_LaserType)
		{
		case CLaser::LASERTYPE_STRONG_STRAIGHT:
			CLaser::Create(ScreenPos, D3DCOLOR_RGBA(255, 0, 0, 255), LASER_WIDTH, 0, 5, true);
			m_pEnergy->ReduceEnergy(3);
			break;
		case CLaser::LASERTYPE_WEEK_DIAGONAL:
			POINT point;
			GetCursorPos(&point);
			ScreenToClient(FindWindow(CLASS_NAME, NULL), &point);
			CLaser::Create(ScreenPos, D3DCOLOR_RGBA(0, 0, 255, 255), LASER_WIDTH / 2, atan2f(point.y - ScreenPos.y, point.x - ScreenPos.x), 5, false);
			m_pEnergy->ReduceEnergy(2);
			break;
		default:
			break;
		}
	}
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//���[�U�[�̎�ސݒ�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CPlayer::ChangeLaserType(void)
{
	CInputMouse* pInputMouse = CManager::GetInputMouse();
	//�E�N���b�N���ꂽ���Ƀ��[�U�[�̎�ނ�ύX
	if (pInputMouse->GetKeyTrigger(1))
	{
		m_LaserType = (CLaser::LASERTYPE)(m_LaserType + 1);

		//���[�U�[�̎�ނ��ő�l�ɂȂ����Ƃ��ɖ߂�
		if (m_LaserType == CLaser::LASERTYPE_MAX)
		{
			m_LaserType = CLaser::LASERTYPE_STRONG_STRAIGHT;
		}
		//���[�U�[�̎�ނɂ���ăJ�[�\���̕\����\����ύX
		if (m_LaserType == CLaser::LASERTYPE_WEEK_DIAGONAL)
		{
			if (m_pCursol == NULL)
			{
				m_pCursol = CCursol::Create();
			}
		}
		else
		{
			if (m_pCursol != NULL)
			{
				m_pCursol->Uninit();
				m_pCursol = NULL;
			}
		}
	}
}