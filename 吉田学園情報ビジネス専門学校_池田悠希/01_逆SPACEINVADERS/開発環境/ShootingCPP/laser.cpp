//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	laser.cpp
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "laser.h"
#include "laserlayer.h"
#include "manager.h"
#include "renderer.h"
#include "explosion.h"
#include "enemy.h"
#include "score.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�}�N����`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#define WHITE D3DCOLOR_RGBA(255, 255, 255, 255)
#define RED D3DCOLOR_RGBA(255, 0, 0, 255)
#define FRAME_BLOCK_BRAKE (51)
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�R���X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CLaser::CLaser() : CScene(1)
{
    m_nDamage    = 0;
    m_fRot       = 0;
    m_nWidth     = 0;
    m_bHit       = false;
    m_bPenetrate = false;
    memset(m_vtxPos, 0, sizeof(m_vtxPos));
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�f�X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CLaser::~CLaser()
{
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//����������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
HRESULT CLaser::Init(void)
{
    return S_OK;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�I������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CLaser::Uninit(void)
{
    m_pPolygon->Uninit();
	delete m_pPolygon;
	m_pPolygon = NULL;

    m_pLaserLayer->Uninit();
	delete m_pLaserLayer;
	m_pPolygon = NULL;

    CScene::Release();
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�X�V����
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CLaser::Update(void)
{
    CEnemy* pClosestEnemy         = NULL;          //���[�U�[�������������ň�ԋ߂��G
    CEnemy* apHitEnemy[MAX_SCENE] = {};            //���[�U�[�����������G�̃��X�g
    int nHitEnemyCount            = 0;             //���[�U�[�����������G�̐�
    CScene2d* pClosestTile        = NULL;          //���[�U�[�������������ň�ԋ߂��}�b�v�^�C��
    CScene** pScene               = GetScene();    //�V�[���|�C���^���擾
    CScore* pScore                = NULL;          //�X�R�A�̃|�C���^

    //�z����[���N���A
    ZeroMemory(apHitEnemy, sizeof(apHitEnemy));
    //�X�R�A�̃I�u�W�F�N�g�T��
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
    //���[�U�[��������I�u�W�F�N�g��T��
    GetHittedObject(pScene, apHitEnemy, &nHitEnemyCount, &pClosestEnemy, &pClosestTile);
    //�G�ƃ}�b�v�^�C�������ɓ�����ꍇ
    if(pClosestEnemy != NULL && pClosestTile != NULL)
    {
        //���[�U�[���ђʑ����������Ă���ꍇ
        if(m_bPenetrate)
        {
            for(int nCount = 0; nCount < nHitEnemyCount; nCount++)
            {
                D3DXVECTOR3 EnemyPos = apHitEnemy[nCount]->GetPos();
                //��ԋ߂��^�C�������߂��G�����[�U�[�ɓ�����
                if(D3DXVec3Length(&(EnemyPos - m_pos)) < D3DXVec3Length(&(pClosestTile->GetPos() - m_pos)))
                {
                    apHitEnemy[nCount]->HitLaser(m_nDamage);
                }
                HitTile(pClosestTile, pScore);
            }
        }
        else
        {
            D3DXVECTOR3 EnemyPos = pClosestEnemy->GetPos();
            //��ԋ߂��G����ԋ߂��^�C�������߂������ꍇ
            if(D3DXVec3Length(&(EnemyPos - m_pos)) < D3DXVec3Length(&(pClosestTile->GetPos() - m_pos)))
            {
                pClosestEnemy->HitLaser(m_nDamage);
                SetLaserSize(D3DXVECTOR3(D3DXVec3Length(&(EnemyPos - m_pos)), (float)m_nWidth, 0.0f));
            }
            else
            {
                HitTile(pClosestTile, pScore);
            }
        }
    }
    else if(pClosestEnemy != NULL)
    {    //�G�ɂ���������ꍇ
         //���[�U�[���ђʑ����������Ă���ꍇ
        if(m_bPenetrate)
        {
            for(int nCount = 0; nCount < nHitEnemyCount; nCount++)
            {
                D3DXVECTOR3 EnemyPos = apHitEnemy[nCount]->GetPos();
                apHitEnemy[nCount]->HitLaser(m_nDamage);
            }
        }
        else
        {
            D3DXVECTOR3 EnemyPos = pClosestEnemy->GetPos();
            pClosestEnemy->HitLaser(m_nDamage);
            SetLaserSize(D3DXVECTOR3(D3DXVec3Length(&(EnemyPos - m_pos)), (float)m_nWidth, 0.0f));
        }
    }
    else if(pClosestTile != NULL)
    {    //�}�b�v�^�C���ɂ���������ꍇ
        HitTile(pClosestTile, pScore);
    }
    m_pPolygon->SetPos(m_pos);
    m_pLaserLayer->SetPos(m_pos);

    m_pPolygon->Update();
    m_pLaserLayer->Update();
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�`�揈��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CLaser::Draw(void)
{
    m_pPolygon->Draw();
    m_pLaserLayer->Draw();
    Uninit();
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���G�C�g�֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CLaser::Create(D3DXVECTOR3 pos, D3DCOLOR col, int nWidth, float fRot, int nDamage, bool bPenetrate)
{
	float fDefaultLaserLength = D3DXVec3Length(&D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
	//�������m��
    CLaser* pLaser       = new CLaser();
	//�e�ϐ�������
    pLaser->m_pos        = pos;
    pLaser->m_col        = col;
    pLaser->m_nWidth     = nWidth;
    pLaser->m_fRot       = fRot;
    pLaser->m_nDamage    = nDamage;
    pLaser->m_bPenetrate = bPenetrate;
	//�I�u�W�F�N�g�^�C�v�ݒ�
    pLaser->SetObjType(OBJTYPE_LASER);
	//�g�p����|���S���̃������m��
    pLaser->m_pPolygon    = CPolygon::Create(D3DXVECTOR3((float)(pLaser->m_pos.x + fDefaultLaserLength/2), pLaser->m_pos.y, 0.0f), D3DXVECTOR3(fDefaultLaserLength, (float)pLaser->m_nWidth, 0), pLaser->m_fRot, OBJTYPE_LASER);
    pLaser->m_pLaserLayer = CLaserLayer::Create(D3DXVECTOR3((float)(pLaser->m_pos.x + fDefaultLaserLength/2), pLaser->m_pos.y, 0.0f), pLaser->m_col, pLaser->m_nWidth, (int)fDefaultLaserLength, pLaser->m_fRot);
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�����蔻�菈��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
bool CLaser::CheckCollision(D3DXVECTOR3* pObjVtx)
{
    for(int nCount = 0; nCount < NUM_VERTEX; nCount++)
    {
        m_vtxPos[nCount] = m_pPolygon->GetVtxPos(nCount);
    }

    D3DXVECTOR3 nullvec;
    D3DXVECTOR3 vec1 = m_vtxPos[1] - m_vtxPos[0];
    D3DXVECTOR3 vec2 = m_vtxPos[3] - m_vtxPos[1];
    D3DXVECTOR3 vec3 = m_vtxPos[2] - m_vtxPos[3];
    D3DXVECTOR3 vec4 = m_vtxPos[0] - m_vtxPos[2];

    for(int nCountVtx = 0; nCountVtx < NUM_VERTEX; nCountVtx++)
    {
        if((*D3DXVec3Cross(&nullvec, &vec1, &(pObjVtx[nCountVtx] - m_vtxPos[0]))).z > 0 && (*D3DXVec3Cross(&nullvec, &vec3, &(pObjVtx[nCountVtx] - m_vtxPos[3]))).z < 0)
        {
            if(nCountVtx == 3)
            {
                return false;
            }
        }
        else
        {
            break;
        }
    }

    for(int nCountVtx = 0; nCountVtx < NUM_VERTEX; nCountVtx++)
    {
        if((*D3DXVec3Cross(&nullvec, &vec2, &(pObjVtx[nCountVtx] - m_vtxPos[1]))).z < 0 && (*D3DXVec3Cross(&nullvec, &vec4, &(pObjVtx[nCountVtx] - m_vtxPos[2]))).z > 0)
        {
            if(nCountVtx == 3)
            {
                return false;
            }
        }
        else
        {
            break;
        }
    }

    for(int nCountVtx = 0; nCountVtx < NUM_VERTEX; nCountVtx++)
    {
        if((*D3DXVec3Cross(&nullvec, &vec3, &(pObjVtx[nCountVtx] - m_vtxPos[3]))).z > 0 && (*D3DXVec3Cross(&nullvec, &vec1, &(pObjVtx[nCountVtx] - m_vtxPos[0]))).z < 0)
        {
            if(nCountVtx == 3)
            {
                return false;
            }
        }
        else
        {
            break;
        }
    }

    for(int nCountVtx = 0; nCountVtx < NUM_VERTEX; nCountVtx++)
    {
        if((*D3DXVec3Cross(&nullvec, &vec4, &(pObjVtx[nCountVtx] - m_vtxPos[2]))).z < 0 && (*D3DXVec3Cross(&nullvec, &vec2, &(pObjVtx[nCountVtx] - m_vtxPos[1]))).z > 0)
        {
            if(nCountVtx == 3)
            {
                return false;
            }
        }
        else
        {
            break;
        }
    }

    return true;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//���[�U�[�����������I�u�W�F�N�g���擾
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CLaser::GetHittedObject(CScene** pScene, CEnemy** apHitEnemy, int* pHitEnemyCount, CEnemy** pClosestEnemy, CScene2d** pClosestTile)
{
    int nHitEnemyCount = 0;
    //���[�U�[�����������I�u�W�F�N�g���擾
    for(int nCount = 0; nCount < MAX_SCENE * PRIORITY_MAX; nCount++)
    {
        if((*(pScene + nCount)) != NULL)
        {
			//�G�̓����蔻��
            if((*(pScene + nCount))->GetObjType() == OBJTYPE_ENEMY)
            {
                D3DXVECTOR3 EnemyPos = ((CEnemy*)(*(pScene + nCount)))->GetPos();
                D3DXVECTOR3 EnemyVtx[4];
                EnemyVtx[0] = EnemyPos + D3DXVECTOR3((float)-ENEMY_SIZE / 2, (float)-ENEMY_SIZE / 2, 0.0f);
                EnemyVtx[1] = EnemyPos + D3DXVECTOR3((float)ENEMY_SIZE / 2, (float)-ENEMY_SIZE / 2, 0.0f);
                EnemyVtx[2] = EnemyPos + D3DXVECTOR3((float)-ENEMY_SIZE / 2, (float)ENEMY_SIZE / 2, 0.0f);
                EnemyVtx[3] = EnemyPos + D3DXVECTOR3((float)ENEMY_SIZE / 2, (float)ENEMY_SIZE / 2, 0.0f);
                if(EnemyPos.x - ENEMY_SIZE / 2 < SCREEN_WIDTH && EnemyPos.x + ENEMY_SIZE / 2 > 0)
                {
                    if(CheckCollision(EnemyVtx))
                    {
						//���[�U�[���ђʂ��邩�ǂ���
                        if(m_bPenetrate)
                        {
                            apHitEnemy[nHitEnemyCount] = (CEnemy*)pScene[nCount];
                            *pClosestEnemy             = (CEnemy*)pScene[nCount];
                            nHitEnemyCount++;
                        }
                        else
                        {
							//�ђʂ��Ȃ��Ȃ��ԋ߂��G��T��
                            if(*pClosestEnemy == NULL)
                            {
                                *pClosestEnemy = (CEnemy*)pScene[nCount];
                            }
                            else
                            {
                                D3DXVECTOR3 ClosestEnemyPos = (*pClosestEnemy)->GetPos();
                                if(D3DXVec3Length(&(EnemyPos - m_pos)) < D3DXVec3Length(&(ClosestEnemyPos - m_pos)))
                                {
                                    *pClosestEnemy = (CEnemy*)pScene[nCount];
                                }
                            }
                        }
                    }
                }
            }
            else if((*(pScene + nCount))->GetObjType() == OBJTYPE_MAP_TILE || (*(pScene + nCount))->GetObjType() == OBJTYPE_MAP_TILE_BRAKABLE)
            {
				//�^�C���̓����蔻��
                D3DXVECTOR3 TilePos = ((CScene2d*)(*(pScene + nCount)))->GetPos();
                D3DXVECTOR3 TileVtx[4];
                TileVtx[0] = TilePos + D3DXVECTOR3((float)-MAP_TILE_SIZE / 2, (float)-MAP_TILE_SIZE / 2, 0.0f);
                TileVtx[1] = TilePos + D3DXVECTOR3((float)MAP_TILE_SIZE / 2, (float)-MAP_TILE_SIZE / 2, 0.0f);
                TileVtx[2] = TilePos + D3DXVECTOR3((float)-MAP_TILE_SIZE / 2, (float)MAP_TILE_SIZE / 2, 0.0f);
                TileVtx[3] = TilePos + D3DXVECTOR3((float)MAP_TILE_SIZE / 2, (float)MAP_TILE_SIZE / 2, 0.0f);
                if(TilePos.x - MAP_TILE_SIZE / 2 < SCREEN_WIDTH && TilePos.x + MAP_TILE_SIZE / 2 > 0)
                {
					//�����������ň�ԋ߂��^�C����T��
                    if(CheckCollision(TileVtx))
                    {
                        if(*pClosestTile == NULL)
                        {
                            *pClosestTile = (CScene2d*)pScene[nCount];
                        }
                        else
                        {
                            D3DXVECTOR3 ClosestTilePos = (*pClosestTile)->GetPos();
                            if(D3DXVec3Length(&(TilePos - m_pos)) < D3DXVec3Length(&(ClosestTilePos - m_pos)))
                            {
                                *pClosestTile = (CScene2d*)pScene[nCount];
                            }
                        }
                    }
                }
            }
        }
    }
    *pHitEnemyCount = nHitEnemyCount;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�^�C���ɂ��������Ƃ��̏���
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CLaser::HitTile(CScene2d* pTile, CScore* pScore)
{
	if (pTile != NULL)
	{
		//��ԋ߂��^�C�����j��\�Ȃ�
		if (pTile->GetObjType() == OBJTYPE_MAP_TILE_BRAKABLE)
		{
			//��ԋ߂��^�C���̐F�̐ԈȊO�̐��������炷
			pTile->SetCol(pTile->GetCol() - D3DCOLOR_RGBA(0, 255 / FRAME_BLOCK_BRAKE, 255 / FRAME_BLOCK_BRAKE, 0));
			if (pTile->GetCol() <= RED)
			{
				pTile->Uninit();
			}
		}
		else
		{
			if (pTile->GetCol() != m_col)
			{
				if (pTile->GetCol() == WHITE)
				{
					pScore->AddScore(10);
				}
				pTile->SetCol(m_col);
			}
		}
		SetLaserSize(D3DXVECTOR3(D3DXVec3Length(&(pTile->GetPos() - m_pos)), (float)m_nWidth, 0.0f));
	}
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//���[�U�[�̃T�C�Y�ݒ�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CLaser::SetLaserSize(D3DXVECTOR3 size)
{
    m_pPolygon->SetSize(size);
    m_pLaserLayer->SetSize(size);
}
