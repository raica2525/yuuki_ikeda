//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	enemy.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

#include "enemy.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "score.h"
#include "bullet.h"
#include "player.h"
#include "item.h"
LPDIRECT3DTEXTURE9 CEnemy::m_apTexture[TYPE_MAX] = {};
CEnemy::CEnemy() :CScene2d(2)
{
	m_nLife = ENEMY_LIFE;
	m_state = STATE_NORMAL;
	m_nShotCount = 60;
	m_nBulletRot = 0;
}

CEnemy::~CEnemy()
{

}

HRESULT CEnemy::Init(void)
{
	CScene2d::Init();
	
	if (m_type == TYPE_CANON_DOWN)
	{
		BindTexture(m_apTexture[m_type-1]);
	}
	else
	{
		BindTexture(m_apTexture[m_type]);
	}
	return S_OK;
}

void CEnemy::Uninit(void)
{
	CScene2d::Uninit();
}

void CEnemy::Update(void)
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move = D3DXVECTOR3(0,0,0);
	D3DXVECTOR3 screenPos = GetPos();
	if (screenPos.x < SCREEN_WIDTH&& m_type != TYPE_CANON_DOWN&& m_type != TYPE_CANON_UP)
	{
		move.x -= 1;
	}
	SetWorldPos(GetWorldPos()+ move);
	CScene** pScene = GetScene();
	if (m_state == STATE_DAMAGE)
	{
		SetCol(D3DCOLOR_RGBA(255, 0, 0, 255));
	}
	else if (m_state == STATE_NORMAL)
	{
		SetCol(D3DCOLOR_RGBA(255, 255, 255, 255));
	}
	switch (m_type)
	{
	case TYPE_CANON_UP:
	case TYPE_CANON_DOWN:
		for (int nCount = 0; nCount < MAX_SCENE*PRIORITY_MAX; nCount++)
		{
			if ((*(pScene + nCount)) != NULL)
			{
				if ((*(pScene + nCount))->GetObjType() == OBJTYPE_PLAYER)
				{
					D3DXVECTOR3 PlayerPos = ((CPlayer*)(*(pScene + nCount)))->GetPos();

					D3DXVECTOR2 texPos[4];
					if (m_type == TYPE_CANON_UP)
					{
						if (GetPos().x < PlayerPos.x)
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
						if (GetPos().x < PlayerPos.x)
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
					if (GetPos().x > 0 && GetPos().x<SCREEN_WIDTH)
					{
						if (m_nShotCount-- <= 0)
						{
			
							D3DXVECTOR3 BulletMove;
							for (int nCount = 0; nCount < MAX_SCENE*PRIORITY_MAX; nCount++)
							{
								if ((*(pScene + nCount)) != NULL)
								{
									if ((*(pScene + nCount))->GetObjType() == OBJTYPE_PLAYER)
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
	case TYPE_NORMAL:
		if (m_nShotCount-- <= 0)
		{
			for (int nCount = 0; nCount < MAX_SCENE*PRIORITY_MAX; nCount++)
			{
				if ((*(pScene + nCount)) != NULL)
				{
					if ((*(pScene + nCount))->GetObjType() == OBJTYPE_PLAYER)
					{
						D3DXVECTOR3 PlayerPos = ((CPlayer*)(*(pScene + nCount)))->GetPos();
						if (GetPos().x > PlayerPos.x&&GetPos().x<SCREEN_WIDTH)
						{
							D3DXVECTOR3 BulletMove;
							for (int nCount = 0; nCount < MAX_SCENE*PRIORITY_MAX; nCount++)
							{
								if ((*(pScene + nCount)) != NULL)
								{
									if ((*(pScene + nCount))->GetObjType() == OBJTYPE_PLAYER)
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
	case TYPE_SPRINKLER:
		if (m_nShotCount-- < 0)
		{
			if (GetPos().x > 0 && GetPos().x < SCREEN_WIDTH)
			{
				m_nBulletRot += 13;
				D3DXVECTOR3 BulletVec = D3DXVECTOR3(cosf(D3DXToRadian(m_nBulletRot)), sinf(D3DXToRadian(m_nBulletRot)), 0);
				CBullet::Create(GetPos(), BulletVec*BULLET_SPEED);
				BulletVec = D3DXVECTOR3(cosf(D3DXToRadian(m_nBulletRot-180)), sinf(D3DXToRadian(m_nBulletRot - 180)), 0);
				CBullet::Create(GetPos(), BulletVec*BULLET_SPEED);
				m_nShotCount = 3;
			}
		}
		
	
	}
	m_state = STATE_NORMAL;
	CScene2d::Update();
	if (GetPos().x+ENEMY_SIZE/2 < 0)
	{
		Uninit();
	}
}

void CEnemy::Draw(void)
{
	CScene2d::Draw();
}

void CEnemy::Create(D3DXVECTOR3 pos, TYPE type)
{
	CEnemy* pEnemy = NULL;
	pEnemy = new CEnemy;
	pEnemy->SetWorldPos(pos);
	pEnemy->SetSize(D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE,0));
	pEnemy->SetObjType(OBJTYPE_ENEMY);
	pEnemy->m_type = type;
	pEnemy->Init();

}

HRESULT CEnemy::Load(void)
{
	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "Resources\\enemy01.png", &m_apTexture[TYPE_NORMAL]);
	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "Resources\\enemy02.png", &m_apTexture[TYPE_SPRINKLER]);
	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "Resources\\enemy03.png", &m_apTexture[TYPE_CANON_UP]);
	return S_OK;
}

void CEnemy::Unload(void)
{
	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	{
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
	
}

void CEnemy::HitBullet(int nDamage)
{
	m_state = STATE_DAMAGE;
	m_nLife -= nDamage;
	if (m_nLife <= 0)
	{
		if (m_type == TYPE_SPRINKLER)
		{
			CItem::Create(GetPos(), CItem::TYPE_LIFE);
		}
		CManager::GetSound()->Play(CSound::SE_EXPLOSION);
		CScene **pScene = GetScene();
		for (int nCount = 0; nCount < MAX_SCENE*PRIORITY_MAX; nCount++)
		{
			if ((*(pScene + nCount)) != NULL)
			{
				if ((*(pScene + nCount))->GetObjType() == OBJTYPE_SCORE)
				{
					switch (m_type)
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

CEnemy::STATE CEnemy::GetState(void)
{
	return m_state;
}