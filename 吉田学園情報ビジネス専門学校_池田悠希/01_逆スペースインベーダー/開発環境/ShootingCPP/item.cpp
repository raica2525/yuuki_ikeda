//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	item.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

#include "item.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "score.h"
#include "bullet.h"
#include "player.h"
#include "life.h"
LPDIRECT3DTEXTURE9 CItem::m_apTexture[TYPE_MAX] = {};
CItem::CItem() :CScene2d(2)
{
}

CItem::~CItem()
{

}

HRESULT CItem::Init(void)
{
	CScene2d::Init();
	BindTexture(m_apTexture[m_type]);

	return S_OK;
}

void CItem::Uninit(void)
{
	CScene2d::Uninit();
}

void CItem::Update(void)
{
	CScene** pScene = NULL;
	pScene = GetScene();
	bool bGet = false;
	D3DXVECTOR3 screenPos = GetPos();
	for (int nCount = 0; nCount < MAX_SCENE*PRIORITY_MAX; nCount++)
	{
		if ((*(pScene + nCount)) != NULL)
		{
			if ((*(pScene + nCount))->GetObjType() == OBJTYPE_PLAYER)
			{
				D3DXVECTOR3 PlayerPos = ((CPlayer*)(*(pScene + nCount)))->GetPos();

				if (screenPos.x + (ITEM_SIZE / 2) > PlayerPos.x - (PLAYER_SIZE_X / 2)
					&& screenPos.x - (ITEM_SIZE / 2) < PlayerPos.x + (PLAYER_SIZE_X / 2)
					&& screenPos.y + (ITEM_SIZE / 2) > PlayerPos.y - (PLAYER_SIZE_Y / 2)
					&& screenPos.y - (ITEM_SIZE / 2) < PlayerPos.y + (PLAYER_SIZE_Y / 2))
				{
					((CPlayer*)(*(pScene + nCount)))->GetLife()->AddLife(30);
					bGet = true;
				}
			}
		}
	}
	CScene2d::Update();
	if (bGet)
	{
		Uninit();	
	}
}

void CItem::Draw(void)
{
	CScene2d::Draw();
}

void CItem::Create(D3DXVECTOR3 pos, TYPE type)
{
	CItem* pItem = NULL;
	pItem = new CItem;
	pItem->SetWorldPos(pos);
	pItem->SetSize(D3DXVECTOR3(ITEM_SIZE, ITEM_SIZE, 0));
	pItem->SetObjType(OBJTYPE_ITEM);
	pItem->m_type = type;
	pItem->Init();

}

HRESULT CItem::Load(void)
{
	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "Resources\\item01.png", &m_apTexture[TYPE_LIFE]);
	return S_OK;
}

void CItem::Unload(void)
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


