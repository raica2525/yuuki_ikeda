//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	bullet.cpp
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "bullet.h"
#include "manager.h"
#include "renderer.h"
#include "explosion.h"
#include "sound.h"
#include "player.h"
#include "score.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�ÓI�����o�ϐ��錾
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
LPDIRECT3DTEXTURE9 CBullet::m_pTexture = NULL;

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�R���X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CBullet::CBullet() : CScene2d(1)
{
	//�ϐ�������
    m_bHit = false;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�f�X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CBullet::~CBullet()
{
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//����������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
HRESULT CBullet::Init(void)
{
	//������
    CScene2d::Init();
	//�e�N�X�`������
    BindTexture(m_pTexture);

    return S_OK;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�I������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CBullet::Uninit(void)
{
    CScene2d::Uninit();
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�X�V����
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CBullet::Update(void)
{
	//���[���h���W�擾
    D3DXVECTOR3 worldPos = GetWorldPos();
	//�X�N���[����̍��W�擾
    D3DXVECTOR3 screenPos = GetPos();;
    CScene** pScene = GetScene();
	bool bElase = false;
	//�e���ړ�
    SetWorldPos(worldPos + m_move);
    CScene2d::Update();

	//�X�R�A�|�C���^�擾
    CScore* pScore = NULL;
    for(int nCount = 0; nCount < MAX_SCENE * PRIORITY_MAX; nCount++)
    {
        if((*(pScene + nCount)) != NULL)
        {
            if((*(pScene + nCount))->GetObjType() == OBJTYPE_SCORE)
            {
                pScore = (CScore*)(*(pScene + nCount));
            }
        }
    }

	//�����蔻��
    for(int nCount = 0; nCount < MAX_SCENE * PRIORITY_MAX; nCount++)
    {
        if((*(pScene + nCount)) != NULL)
        {
            if((*(pScene + nCount))->GetObjType() == OBJTYPE_PLAYER)	//�v���C���[�Ƃ̓����蔻��
            {
                D3DXVECTOR3 PlayerPos = ((CPlayer*)(*(pScene + nCount)))->GetPos();
				
                if(screenPos.x + (BULLET_SIZE_X / 2) > PlayerPos.x - (PLAYER_SIZE_X / 2) && screenPos.x - (BULLET_SIZE_X / 2) < PlayerPos.x + (PLAYER_SIZE_X / 2) 
					&& screenPos.y + (BULLET_SIZE_Y / 2) > PlayerPos.y - (PLAYER_SIZE_Y / 2) && screenPos.y - (BULLET_SIZE_Y / 2) < PlayerPos.y + (PLAYER_SIZE_Y / 2))
                {
					//���������Ƃ��̏���
                    ((CPlayer*)(*(pScene + nCount)))->HitBullet();
                    m_bHit = true;
                }
            }
            else if((*(pScene + nCount))->GetObjType() == OBJTYPE_MAP_TILE || (*(pScene + nCount))->GetObjType() == OBJTYPE_MAP_TILE_BRAKABLE)	//�}�b�v�^�C���Ƃ̓����蔻��
            {
                D3DXVECTOR3 TilePos = ((CScene2d*)(*(pScene + nCount)))->GetPos();

                if(screenPos.x + (BULLET_SIZE_X / 2) > TilePos.x - (MAP_TILE_SIZE / 2) && screenPos.x - (BULLET_SIZE_X / 2) < TilePos.x + (MAP_TILE_SIZE / 2) 
					&& screenPos.y + (BULLET_SIZE_Y / 2) > TilePos.y - (MAP_TILE_SIZE / 2) && screenPos.y - (BULLET_SIZE_Y / 2) < TilePos.y + (MAP_TILE_SIZE / 2))
                {
					//���������Ƃ��̏���
                    m_bHit = true;
                    if((*(pScene + nCount))->GetObjType() == OBJTYPE_MAP_TILE)
                    {
						//���������^�C���̐F�����łȂ���Δ�������
                        if(((CScene2d*)(*(pScene + nCount)))->GetCol() != D3DCOLOR_RGBA(255,255,255,255))
                        {
                            pScore->AddScore(-10);
                            ((CScene2d*)(*(pScene + nCount)))->SetCol(D3DCOLOR_RGBA(255, 255, 255, 255));
                        }
                    }
                }
            }
        }
    }
	if (screenPos.x<0 || screenPos.x>SCREEN_WIDTH || screenPos.y < 0 || screenPos.y > SCREEN_HEIGHT)
	{
		bElase = true;
	}
	//�e�����������ꍇ
    if(m_bHit)
    {
		//��������
		CExplosion::Create(screenPos, D3DCOLOR_RGBA(255, 255, 255, 255));
		bElase = true;
    }
	if (bElase)
	{
		Uninit();
	}
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�`�揈��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CBullet::Draw(void)
{
    CScene2d::Draw();
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���G�C�g�֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
    CBullet* pBullet = new CBullet;
	//���[���h���W�̐ݒ�
    pBullet->SetWorldPos(pos);
	//���ˉ��Đ�
    CManager::GetSound()->Play(CSound::SE_SHOT);
	//�ړ��ʐݒ�
    pBullet->m_move = move;
	//�傫��������
    pBullet->SetSize(D3DXVECTOR3(BULLET_SIZE_X, BULLET_SIZE_Y, 0));
	//�I�u�W�F�N�g�^�C�v�ݒ�
    pBullet->SetObjType(OBJTYPE_BULLET);
	//�������֐����s
    pBullet->Init();
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�t�@�C���ǂݍ��݊֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
HRESULT CBullet::Load(void)
{
	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "Resources\\Explosion.png", &m_pTexture);
	return S_OK;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�ǂݍ��݃f�[�^�j������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CBullet::Unload(void)
{
	//�e�N�X�`���j��
    if(m_pTexture != NULL)
    {
        m_pTexture->Release();
        m_pTexture = NULL;
    }
}
