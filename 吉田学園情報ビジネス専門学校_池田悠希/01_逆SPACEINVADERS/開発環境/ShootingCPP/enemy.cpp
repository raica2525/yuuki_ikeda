//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	enemy.cpp
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "enemy.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "score.h"
#include "bullet.h"
#include "player.h"
#include "item.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�ÓI�����o�ϐ��錾
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
LPDIRECT3DTEXTURE9 CEnemy::m_apTexture[TYPE_MAX] = {};

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�R���X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CEnemy::CEnemy() : CScene2d(2)
{
    m_nLife      = ENEMY_LIFE;
    m_state      = STATE_NORMAL;
    m_nShotCount = 60;
    m_nBulletRot = 0;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�f�X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CEnemy::~CEnemy()
{
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//����������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
HRESULT CEnemy::Init(void)
{
    CScene2d::Init();

    if(m_type == TYPE_CANON_DOWN)	//������̃e�N�X�`��������
    {
        BindTexture(m_apTexture[TYPE_CANON_UP]);
    }
    else	//���̑��̏ꍇ�͂��ꂼ��̃e�N�X�`��������
    {
        BindTexture(m_apTexture[m_type]);
    }
    return S_OK;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�I������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CEnemy::Uninit(void)
{
    CScene2d::Uninit();
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�X�V����
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CEnemy::Update(void)
{
    D3DXVECTOR3 move      = D3DXVECTOR3(0, 0, 0);
    D3DXVECTOR3 screenPos = GetPos();
    if(screenPos.x < SCREEN_WIDTH && m_type != TYPE_CANON_DOWN && m_type != TYPE_CANON_UP)//�C��ȊO�̓G�����ɓ�����
    {
        move.x -= 1;
    }
	//���W�ݒ�
    SetWorldPos(GetWorldPos() + move);
    CScene** pScene = GetScene();
	//�_���[�W���󂯂Ă���G�͐F��ς���
    if(m_state == STATE_DAMAGE)
    {
        SetCol(D3DCOLOR_RGBA(255, 0, 0, 255));
    }
    else if(m_state == STATE_NORMAL)
    {
        SetCol(D3DCOLOR_RGBA(255, 255, 255, 255));
    }
	//�G�̎�ʂɂ���ď�����ς���
    switch(m_type)
    {
		//�C��
        case TYPE_CANON_UP:
        case TYPE_CANON_DOWN:
            for(int nCount = 0; nCount < MAX_SCENE * PRIORITY_MAX; nCount++)
            {
                if((*(pScene + nCount)) != NULL)
                {
                    if((*(pScene + nCount))->GetObjType() == OBJTYPE_PLAYER)
                    {
						//�v���C���[���W�擾
                        D3DXVECTOR3 PlayerPos = ((CPlayer*)(*(pScene + nCount)))->GetPos();

                        D3DXVECTOR2 texPos[4];
						//�v���C���[�̕����Ɍ�����
                        if(m_type == TYPE_CANON_UP)
                        {
                            if(GetPos().x < PlayerPos.x)
                            {
                                texPos[0] = D3DXVECTOR2(1, 0);
                                texPos[1] = D3DXVECTOR2(0, 0);
                                texPos[2] = D3DXVECTOR2(1, 1);
                                texPos[3] = D3DXVECTOR2(0, 1);
                            }
                            else
                            {
                                texPos[0] = D3DXVECTOR2(0, 0);
                                texPos[1] = D3DXVECTOR2(1, 0);
                                texPos[2] = D3DXVECTOR2(0, 1);
                                texPos[3] = D3DXVECTOR2(1, 1);
                            }
                        }
                        else
                        {
                            if(GetPos().x < PlayerPos.x)
                            {
                                texPos[0] = D3DXVECTOR2(1, 1);
                                texPos[1] = D3DXVECTOR2(0, 1);
                                texPos[2] = D3DXVECTOR2(1, 0);
                                texPos[3] = D3DXVECTOR2(0, 0);
                            }
                            else
                            {
                                texPos[0] = D3DXVECTOR2(0, 1);
                                texPos[1] = D3DXVECTOR2(1, 1);
                                texPos[2] = D3DXVECTOR2(0, 0);
                                texPos[3] = D3DXVECTOR2(1, 0);
                            }
                        }
                        SetTexPos(texPos);
						
						//��ʓ��Ȃ�v���C���[�Ɍ������Ēe���΂�
                        if(GetPos().x > 0 && GetPos().x < SCREEN_WIDTH)
                        {
                            if(m_nShotCount-- <= 0)
                            {

                                D3DXVECTOR3 BulletMove;
                                for(int nCount = 0; nCount < MAX_SCENE * PRIORITY_MAX; nCount++)
                                {
                                    if((*(pScene + nCount)) != NULL)
                                    {
                                        if((*(pScene + nCount))->GetObjType() == OBJTYPE_PLAYER)
                                        {
                                            D3DXVec3Normalize(&BulletMove, &((((CPlayer*)(*(pScene + nCount)))->GetPos()) - GetPos()));
                                            BulletMove *= BULLET_SPEED;
                                            break;
                                        }
                                    }
                                }
                                CBullet::Create(GetPos(), BulletMove);
                                m_nShotCount = SHOT_CYCLE;
                            }
                        }
                    }
                }
            }
            break;

			//�ʏ�̓G
        case TYPE_NORMAL:

			//��莞�Ԃ��ƂɃv���C���[�Ɍ������Ēe�𔭎˂���
            if(m_nShotCount-- <= 0)
            {
                for(int nCount = 0; nCount < MAX_SCENE * PRIORITY_MAX; nCount++)
                {
                    if((*(pScene + nCount)) != NULL)
                    {
                        if((*(pScene + nCount))->GetObjType() == OBJTYPE_PLAYER)
                        {
                            D3DXVECTOR3 PlayerPos = ((CPlayer*)(*(pScene + nCount)))->GetPos();
                            if(GetPos().x > PlayerPos.x && GetPos().x < SCREEN_WIDTH)
                            {
                                D3DXVECTOR3 BulletMove;
                                for(int nCount = 0; nCount < MAX_SCENE * PRIORITY_MAX; nCount++)
                                {
                                    if((*(pScene + nCount)) != NULL)
                                    {
                                        if((*(pScene + nCount))->GetObjType() == OBJTYPE_PLAYER)
                                        {
                                            D3DXVec3Normalize(&BulletMove, &((((CPlayer*)(*(pScene + nCount)))->GetPos()) - GetPos()));
                                            BulletMove *= BULLET_SPEED;
                                            break;
                                        }
                                    }
                                }
                                CBullet::Create(GetPos(), BulletMove);
                                m_nShotCount = SHOT_CYCLE;
                            }
                        }
                    }
                }
            }
            break;

			//�X�v�����N���[���G
        case TYPE_SPRINKLER:
			//��ʓ��Ȃ��莞�Ԃ��Ƃɒe���΂�܂�
            if(m_nShotCount-- < 0)
            {
                if(GetPos().x > 0 && GetPos().x < SCREEN_WIDTH)
                {
                    m_nBulletRot += 13;
                    D3DXVECTOR3 BulletVec = D3DXVECTOR3(cosf(D3DXToRadian(m_nBulletRot)), sinf(D3DXToRadian(m_nBulletRot)), 0);
                    CBullet::Create(GetPos(), BulletVec * BULLET_SPEED);
                    BulletVec = D3DXVECTOR3(cosf(D3DXToRadian(m_nBulletRot - 180)), sinf(D3DXToRadian(m_nBulletRot - 180)), 0);
                    CBullet::Create(GetPos(), BulletVec * BULLET_SPEED);
                    m_nShotCount = 3;
                }
            }
    }
    m_state = STATE_NORMAL;
    CScene2d::Update();

	//��ʂ̍��[��荶�ɂ���Ώ���
    if(GetPos().x + ENEMY_SIZE / 2 < 0)
    {
        Uninit();
    }
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�`�揈��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CEnemy::Draw(void)
{
    CScene2d::Draw();
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���G�C�g�֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CEnemy::Create(D3DXVECTOR3 pos, TYPE type)
{
    CEnemy* pEnemy = new CEnemy;
    pEnemy->SetWorldPos(pos);
    pEnemy->SetSize(D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0));
    pEnemy->SetObjType(OBJTYPE_ENEMY);
    pEnemy->m_type = type;
    pEnemy->Init();
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�t�@�C���ǂݍ��݊֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
HRESULT CEnemy::Load(void)
{
    D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "Resources\\enemy01.png", &m_apTexture[TYPE_NORMAL]);
    D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "Resources\\enemy02.png", &m_apTexture[TYPE_SPRINKLER]);
    D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "Resources\\enemy03.png", &m_apTexture[TYPE_CANON_UP]);
    return S_OK;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�ǂݍ��݃f�[�^�j������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CEnemy::Unload(void)
{
	//�e�N�X�`���j��
    for(int nCount = 0; nCount < TYPE_MAX; nCount++)
    {
        if(m_apTexture[nCount] != NULL)
        {
            m_apTexture[nCount]->Release();
            m_apTexture[nCount] = NULL;
        }
    }
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�e�ۂ������������̏���
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CEnemy::HitLaser(int nDamage)
{
    m_state = STATE_DAMAGE;
    m_nLife -= nDamage;
    if(m_nLife <= 0)
    {
		//�X�v�����N���[�̓G��|�������͉񕜃A�C�e�����o��
        if(m_type == TYPE_SPRINKLER)
        {
            CItem::Create(GetPos(), CItem::TYPE_LIFE);
        }

		//���S���̉����o��
        CManager::GetSound()->Play(CSound::SE_EXPLOSION);
        CScene** pScene = GetScene();

		//�|�����G�̎�ނɂ���ăX�R�A�����Z
        for(int nCount = 0; nCount < MAX_SCENE * PRIORITY_MAX; nCount++)
        {
            if((*(pScene + nCount)) != NULL)
            {
                if((*(pScene + nCount))->GetObjType() == OBJTYPE_SCORE)
                {
                    switch(m_type)
                    {
                        case TYPE_NORMAL:
                            ((CScore*)(*(pScene + nCount)))->AddScore(100);
                            break;
                        case TYPE_SPRINKLER:
                            ((CScore*)(*(pScene + nCount)))->AddScore(500);
                            break;
                        case TYPE_CANON_DOWN:
                        case TYPE_CANON_UP:
                            ((CScore*)(*(pScene + nCount)))->AddScore(150);
                    }
                }
            }
        }
        Uninit();
    }
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//��Ԏ擾����
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CEnemy::STATE CEnemy::GetState(void)
{
    return m_state;
}
