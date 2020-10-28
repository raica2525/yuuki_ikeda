//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	player.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

#include "bullet.h"
#include "manager.h"
#include "renderer.h"
#include "explosion.h"
#include "sound.h"
#include "player.h"
#include "score.h"
LPDIRECT3DTEXTURE9 CBullet::m_pTexture = NULL;
CBullet::CBullet() :CScene2d(1)
{
	m_bHit = false;
}

CBullet::~CBullet()
{

}

HRESULT CBullet::Init(void)
{
	CScene2d::Init();
	BindTexture(m_pTexture);

	return S_OK;
}

void CBullet::Uninit(void)
{
	CScene2d::Uninit();
}

void CBullet::Update(void)
{
	D3DXVECTOR3 worldPos;
	D3DXVECTOR3 screenPos;
	CScene** pScene = NULL;

	worldPos = GetWorldPos();
	pScene = GetScene();
	//位置取得
	worldPos = GetWorldPos();
	screenPos = GetPos();
	SetWorldPos(worldPos + m_move);
	CScene2d::Update();
	CScore *pScore = NULL;
	for (int nCount = 0; nCount < MAX_SCENE*PRIORITY_MAX; nCount++)
	{
		if ((*(pScene + nCount)) != NULL)
		{
			if ((*(pScene + nCount))->GetObjType() == OBJTYPE_SCORE)
			{
				pScore = (CScore*)(*(pScene + nCount));
			}
		}
	}

	for (int nCount = 0; nCount < MAX_SCENE*PRIORITY_MAX; nCount++)
	{
		if ((*(pScene + nCount)) != NULL)
		{
			if ((*(pScene + nCount))->GetObjType() == OBJTYPE_PLAYER)
			{
				D3DXVECTOR3 PlayerPos = ((CPlayer*)(*(pScene + nCount)))->GetPos();

				if (screenPos.x + (BULLET_SIZE_X / 2) > PlayerPos.x - (PLAYER_SIZE_X / 2) 
				 && screenPos.x - (BULLET_SIZE_X / 2) < PlayerPos.x + (PLAYER_SIZE_X / 2)
				 && screenPos.y + (BULLET_SIZE_Y / 2) > PlayerPos.y - (PLAYER_SIZE_Y / 2)
				 && screenPos.y - (BULLET_SIZE_Y / 2) < PlayerPos.y + (PLAYER_SIZE_Y / 2))
				{
					((CPlayer*)(*(pScene + nCount)))->HitBullet();
					m_bHit = true;
				}
			}
			else if ((*(pScene + nCount))->GetObjType() == OBJTYPE_MAP_TILE|| (*(pScene + nCount))->GetObjType() == OBJTYPE_MAP_TILE_BRAKABLE)
			{
				D3DXVECTOR3 TilePos = ((CScene2d*)(*(pScene + nCount)))->GetPos();

				if (screenPos.x + (BULLET_SIZE_X / 2) > TilePos.x - (MAP_TILE_SIZE / 2)
					&& screenPos.x - (BULLET_SIZE_X / 2) < TilePos.x + (MAP_TILE_SIZE / 2)
					&& screenPos.y + (BULLET_SIZE_Y / 2) > TilePos.y - (MAP_TILE_SIZE / 2)
					&& screenPos.y - (BULLET_SIZE_Y / 2) < TilePos.y + (MAP_TILE_SIZE / 2))
				{
					m_bHit = true;
					if ((*(pScene + nCount))->GetObjType() == OBJTYPE_MAP_TILE)
					{
						if (((CScene2d*)(*(pScene + nCount)))->GetCol() != 0xffffffff)
						{
							pScore->AddScore(-10);
							((CScene2d*)(*(pScene + nCount)))->SetCol(0xffffffff);
						}
					}
				}
			}
		}
	}
	if (screenPos.x > SCREEN_WIDTH || screenPos.x<0 || screenPos.y>SCREEN_HEIGHT || screenPos.y < 0 || m_bHit)
	{
		if(!(screenPos.x<0))
		CExplosion::Create(screenPos,D3DCOLOR_RGBA(255,255,255,255));

		Uninit();
	}
	
}

void CBullet::Draw(void)
{
	CScene2d::Draw();
}

void CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
 	CBullet* pBullet = NULL;
	pBullet = new CBullet;
	pBullet->SetWorldPos(pos);
	CScene** pScene;
	pScene = GetScene();
	CManager::GetSound()->Play(CSound::SE_SHOT);
	pBullet->m_move = move;
	pBullet->SetSize(D3DXVECTOR3(BULLET_SIZE_X, BULLET_SIZE_Y,0));
	pBullet->SetObjType(OBJTYPE_BULLET);
	pBullet->Init();
}

HRESULT CBullet::Load(void)
{
 	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "Resources\\Explosion.png", &m_pTexture);

	return S_OK;
}
 
void CBullet::Unload(void)
{
	if (m_pTexture != NULL) {
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}