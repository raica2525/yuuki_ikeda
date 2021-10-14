//=============================================================================
//
// �G���� [enemy.cpp]
// Author : ��K������ �g�c�I�l
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "enemy.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "exclamationmark.h"
#include "explosion.h"
#include "hiteffect.h"
#include "input.h"
#include "inputkeyboard.h"
#include "manager.h"
#include "player.h"
#include "question.h"
#include "sound.h"
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEnemy::CEnemy()
{
    m_pos  = ZEROVECTOR3;        //�ʒu
    m_move = ZEROVECTOR3;        //�ړ�
    m_rot  = ZEROVECTOR3;        //����
    m_size = ZEROVECTOR3;        //�T�C�Y
    memset(m_TourPos, NULL, sizeof(m_TourPos));    //����ʒu
    m_nLife = 0;                                   //�̗�
    SetObjType(OBJTYPE_ENEMY);                     //�I�u�W�F�N�g�^�C�v�ݒ�
    m_TourCount    = 0;                            //���񂵂Ă���ʒu
    m_TourMax      = 0;                            //����ʒu�̍ő�l
    m_pQuestion    = NULL;
    m_pExclamation = NULL;
	m_nAttack_SE   = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEnemy::~CEnemy()
{
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CEnemy::Init(void)
{
    //���[���h���W�擾�p
    m_pModel = CModel::Create(NULL, this, {}, m_pos, m_rot, m_size);
    //�G�l�~�[�̈ʒu�Z�b�g
    m_pModel->SetPos(m_pos);
    //�G�l�~�[�̌����Z�b�g
    m_pModel->SetRot(m_rot);
    //�I�u�W�F�N�g�^�C�v�ݒ�
    m_pModel->SetObjType(OBJTYPE_NONE);
    //�����蔻��
    SetCollisionBullet(true);
    return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CEnemy::Uninit(void)
{
    m_pModel->Uninit();
    Release();
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CEnemy::Update(void)
{
    m_pModel->SetPos(m_pos);
    m_pModel->SetRot(m_rot);
}

//=============================================================================
// �`��֐�
//=============================================================================
void CEnemy::Draw(void)
{
}

//=============================================================================
// �ʒu�ݒ�֐�
//=============================================================================
void CEnemy::SetPos(D3DXVECTOR3(pos))
{
    m_pos = pos;
}

//=============================================================================
// �����ݒ�֐�
//=============================================================================
void CEnemy::SetRot(D3DXVECTOR3(rot))
{
    m_rot = rot;
}

//=============================================================================
// �T�C�Y�ݒ�֐�
//=============================================================================
void CEnemy::SetSize(D3DXVECTOR3(size))
{
    m_size = size;
}

//=============================================================================
// ����ʒu�ݒ�֐�
//=============================================================================
void CEnemy::SetTour(int nTour, D3DXVECTOR3(pos))
{
    m_TourPos[nTour] = pos;
    m_TourMax=nTour+1;
}

//=============================================================================
// ���[�h�`�F���W�֐�
//=============================================================================
void CEnemy::SetMode(ENEMY_MODE mode)
{
	m_Mode = mode;
}

//=============================================================================
//�@���C�t�ݒ�֐�
//=============================================================================
void CEnemy::SetLife(int nLife)
{
    m_nLife = nLife;
}

//=============================================================================
//�@�N�G�X�`�����ݒ�֐�
//=============================================================================
void CEnemy::SetQuestion(CQuestion * pQuestion)
{
    CSound* pSound = CManager::GetSound();    //�T�E���h�̎擾
    pSound->PlaySoundA(CSound::SOUND_LABEL_SE_QUESTION);
    m_pQuestion = pQuestion;
}

//=============================================================================
//�@�I�ݒ�֐�
//=============================================================================
void CEnemy::SetExclamation(CExclamationMark * pExclamation)
{
    CSound* pSound = CManager::GetSound();    //�T�E���h�̎擾
    pSound->PlaySoundA(CSound::SOUND_LABEL_SE_EXCLAMATIONMARK);
    m_pExclamation = pExclamation;
}

//=============================================================================
// �X�e�[�^�X�ݒ�֐�
//=============================================================================
void CEnemy::SetState(ENEMY_STATE state)
{
    m_State = state;
}

//=============================================================================
// ���C�t���Z�֐�
//=============================================================================
void CEnemy::SubLife(int nSublife)
{
	m_nLife -= nSublife;
	CHitEffect::HitEffectCreate(D3DXVECTOR3(m_pos.x,m_pos.y + 20,m_pos.z), D3DXVECTOR3(2.0f, 2.0f, 2.0f ), D3DCOLOR_RGBA(255,255,0,255));
    //���C�t�O�̂Ƃ�
    if(m_nLife <= 0)
    {
        //NULL�`�F�b�N
        if(m_pQuestion != NULL)
        {
            m_pQuestion->Uninit();
            m_pQuestion = NULL;
        }

        if(m_pExclamation != NULL)
        {
            m_pExclamation->Uninit();
            m_pExclamation = NULL;
        }
        //�I������
        m_State = STATE_DEATH;
    }
}

//=============================================================================
// HIT�֐�
//=============================================================================
void CEnemy::Hit(int nDamage)
{
	m_State = STATE_DAMAGE;
	SubLife(nDamage);

}

//=============================================================================
// �U���֐�
//=============================================================================
void CEnemy::Attack(int nDamage)
{
    CSound* pSound = CManager::GetSound();    //�T�E���h�̎擾
	m_nAttack_SE += 1;
	if (m_nAttack_SE>=5)
	{
		pSound->PlaySoundA(CSound::SOUND_LABEL_SE_ENEMYATTACK);
		m_nAttack_SE = 0;
	}

    //�����_���֐��̏�����
    srand((unsigned)time(NULL));

	int nAttackHit = (rand() % +4);

    //10��ɂP��
    if(nAttackHit == 0)
    {
        //�q�b�g
        CManager::GetPlayer()->AddLife(nDamage);
    }
}

//=============================================================================
// ����֐�
//=============================================================================
bool CEnemy::Tour(void)
{
    //�ڕW�̈ʒu
    float fAngle;
	bool bTour=false;
	if (m_TourMax-1 != 0)
	{
		bTour = true;
		 //�ڕW�̈ʒu�ɂ����Ƃ�
		 if(m_pos.x + 5 > m_TourPos[m_TourCount].x
		    && m_pos.x - 5 < m_TourPos[m_TourCount].x
		    && m_pos.y + 5 > m_TourPos[m_TourCount].y
		    && m_pos.y - 5 < m_TourPos[m_TourCount].y
		    && m_pos.z + 5 > m_TourPos[m_TourCount].z
		    && m_pos.z - 5 < m_TourPos[m_TourCount].z)
		 {
		     //���̏���ʒu��ݒ�
		     m_TourCount += 1;
		     //�ݒ肳��Ă��鏄��ʒu�����I������
		     if(m_TourCount == m_TourMax)
		     {
		         //�ŏ��̏���ʒu�ɖ߂�
		         m_TourCount = 0;
		     }
		 }
		//�ڕW�̈ʒu�����擾
		fAngle = atan2f((-m_pos.x + m_TourPos[m_TourCount].x), (-m_pos.z + m_TourPos[m_TourCount].z));

		//�ڕW�܂ł̈ړ�
		m_move.x = sinf(fAngle) * 1.0f;
		m_move.z = cosf(fAngle) * 1.0f;

		/*����*/
		m_move.x += (0.0f - m_move.x) * 0.5f;
		m_move.y += (0.0f - m_move.y) * 0.5f;
		m_move.z += (0.0f - m_move.z) * 0.5f;

		//�ʒu�X�V
		m_pos += m_move;

		//�ړ������Ɍ���
		Direction(m_TourPos[m_TourCount]);

	}
	return bTour;
}

//=============================================================================
// �����֐�
//=============================================================================
void CEnemy::Direction(D3DXVECTOR3(pos))
{
    //�ڕW�̊p�x���擾
    float fRotDist = D3DXToDegree(atan2f((m_pos.x - pos.x), (m_pos.z - pos.z)));

    //��������
    if(fRotDist >= D3DXToDegree(m_rot.y) + (180))
    {    //-180�x����180�x�ɂȂ鏈��
        m_rot.y  = D3DXToRadian(180);
        fRotDist = (180);
    }
    else if(fRotDist <= D3DXToDegree(m_rot.y) + (-180))
    {    //180�x����-180�x�ɂȂ鏈��
        m_rot.y  = D3DXToRadian(-180);
        fRotDist = (-180);
    }

    //�����X�V
    m_rot += D3DXToRadian((D3DXVECTOR3(0.0f, fRotDist, 0.0f) - D3DXToDegree(m_rot)) * 0.09f);
}

//=============================================================================
// ���G�֐�
//=============================================================================
bool CEnemy::Search(const float fRangeDistance, const float fViewingAngle)
{
    CObject* pTop[PRIORITY_MAX] = {};
    CObject* pNext              = NULL;
    for(int nCount = 0; nCount < PRIORITY_MAX; nCount++)
    {
        //���X�g�g�b�v�擾
        pTop[nCount] = *(CObject::GetTop() + nCount);
    }

    //�v���C���[�܂ł̋���
    float fDistancePlayer  = 0;
    float fClosestDistance = 999999999.9f;
    float fDistance        = 0;
    bool bSearch           = false;
    float fPlayerRotOld    = 0.0f;
    //NULL�`�F�b�N
    for(int nCount = 0; nCount < PRIORITY_MAX; nCount++)
    {
        //NULL�`�F�b�N
        if(pTop[nCount] != NULL)
        {
            pNext = pTop[nCount];
            while(pNext != NULL)
            {
                //�I�u�W�F�N�g�^�C�v�`�F�b�N
                if(pNext->GetObjType() == OBJTYPE_MODEL)
                {
                    //NULL�`�F�b�N
                    if(((CModel*)pNext)->GetParentObject() != NULL)
                    {
                        if(((CModel*)pNext)->GetParentObject()->GetObjType() == OBJTYPE_PLAYER)
                        {
                            //���G�m�F�֐�
							if (CheckSearch(((CModel*)pNext)->GetModelData(), &fDistancePlayer))
							{
								//�����m�F
								if (fRangeDistance > fDistancePlayer)
								{
									//�����m�F
									if (fRangeDistance > fDistancePlayer)
									{
										//�v���C���[�̕���
										float fPlayerRot = D3DXToDegree(atan2f((m_pos.x - ((CPlayer*)((CModel*)pNext)->GetParentObject())->GetPos().x), (m_pos.z - ((CPlayer*)((CModel*)pNext)->GetParentObject())->GetPos().z)));
										//����̉E�ƍ��̍ő吔

										float fSearch_R = D3DXToDegree(m_rot.y) + (fViewingAngle / 2);
										float fSearch_L = D3DXToDegree(m_rot.y) - (fViewingAngle / 2);

										if (fSearch_R > 180)
										{
											fSearch_R -= 360;
										}
										if (fSearch_L < -180)
										{
											fSearch_L += 360;
										}
										if (fSearch_R > fSearch_L)
										{
											if (fSearch_R > fPlayerRot
												&& fSearch_L < fPlayerRot)
											{
												//�����������̏���
												bSearch = true;
											}
										}
										else
										{
											if (fSearch_R > fPlayerRot
												|| fSearch_L < fPlayerRot)
											{
												//�����������̏���
												bSearch = true;
											}
										}

									}
								}
							}
                        }
                        else if(((CModel*)pNext)->GetParentObject()->GetObjType() != OBJTYPE_ENEMY)
                        {
                            if(CheckSearch(((CModel*)pNext)->GetModelData(), &fDistance) == TRUE)
                            {
                                if(fClosestDistance == 0 || fClosestDistance > fDistance)
                                {
                                    fClosestDistance = fDistance;
                                }
                            }
                        }
                    }
                }
                //���̑Ώۂ�ǂݍ���
                pNext = pNext->GetNext();
            }
        }
    }
    if(fDistancePlayer > fClosestDistance)
    {
        bSearch = false;
    }
    //������Ȃ������Ƃ�
    return bSearch;
}

//=============================================================================
// �����֐�
//=============================================================================
bool CEnemy::Found(void)
{
	CObject* pTop[PRIORITY_MAX] = {};
	CObject* pNext = NULL;
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		//���X�g�g�b�v�擾
		pTop[nCount] = *(CObject::GetTop() + nCount);
	}
	float fDistancePlayer = 0;
	float fClosestDistance = 999999999.9f;
	float fDistance = 0;
	bool bFound = false;
	
	//NULL�`�F�b�N
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		//NULL�`�F�b�N
		if (pTop[nCount] != NULL)
		{
			pNext = pTop[nCount];
			while (pNext != NULL)
			{
				//�I�u�W�F�N�g�^�C�v�`�F�b�N
				if (pNext->GetObjType() == OBJTYPE_MODEL)
				{
					//NULL�`�F�b�N
					if (((CModel *)pNext)->GetParentObject() != NULL)
					{
						if (((CModel*)pNext)->GetParentObject()->GetObjType() == OBJTYPE_PLAYER)
						{
							if (CheckSearch(((CModel*)pNext)->GetModelData(), &fDistancePlayer))
							{
								bFound = true;
							}
						}
						else if (((CModel*)pNext)->GetParentObject()->GetObjType() != OBJTYPE_ENEMY)
						{
							if (CheckSearch(((CModel*)pNext)->GetModelData(), &fDistance))
							{
								if (fClosestDistance == 0 || fClosestDistance>fDistance)
								{
									fClosestDistance = fDistance;
								}
							}
						}

					}
				}

				//���̑Ώۂ�ǂݍ���
				pNext = pNext->GetNext();
			}
		}
	}
	if (fDistancePlayer > fClosestDistance)
	{
		bFound = false;
	}

	return bFound;
}

//=============================================================================
// ���G�m�F�֐�
//=============================================================================
BOOL CEnemy::CheckSearch(CModel::MODELDATA modeldata, float* fDistance)
{
	BOOL bSearch = false;					//�������Ă��邩
	D3DXMATRIX InversedWorldMatrix;	//�t��p�}�g���b�N�X
	D3DXVECTOR3 TransformedPos, NormalizedVec , TranceformedVec;
	//�P�ʃx�N�g���ɕϊ�
	D3DXVec3Normalize(&NormalizedVec, &((CManager::GetPlayer()->GetCenter()) - (m_pos + D3DXVECTOR3(0.0f, 33.0f, 0.0f))));
	//�t�s�񐶐�
	D3DXMatrixInverse(&InversedWorldMatrix, NULL, &modeldata.mtxWorld);
	//�t�s��ŕϊ�
	D3DXVec3TransformCoord(&TransformedPos, &(m_pos + D3DXVECTOR3(0.0f, 33.0f, 0.0f)), &InversedWorldMatrix);
	D3DXVec3TransformNormal(&TranceformedVec, &NormalizedVec, &InversedWorldMatrix);
	//�����蔻����m�F
	D3DXIntersect(modeldata.pMesh, &TransformedPos, &TranceformedVec, &bSearch, NULL, NULL, NULL, fDistance, NULL, NULL);

	return bSearch;
}

