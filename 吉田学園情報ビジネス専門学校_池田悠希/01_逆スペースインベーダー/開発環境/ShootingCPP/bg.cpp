//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	bg.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

#include "bg.h"
#include "manager.h"
#include "renderer.h"
#include "scene2d.h"
LPDIRECT3DTEXTURE9 CBg::m_apTexture[NUM_BG_LAYER] = {};
CBg::CBg()
{
	memset(m_apScene2d, NULL, sizeof(m_apScene2d));
	for (int nCount = 0; nCount < NUM_BG_LAYER; nCount++)
	{
		m_TexPos[nCount][0] = D3DXVECTOR2(0, 0);
		m_TexPos[nCount][1] = D3DXVECTOR2(1, 0);
		m_TexPos[nCount][2] = D3DXVECTOR2(0, 1);
		m_TexPos[nCount][3] = D3DXVECTOR2(1, 1);
	}
}

CBg::~CBg()
{

}

HRESULT CBg::Init(void)
{
	for (int nCount = 0; nCount < NUM_BG_LAYER-1; nCount++)
	{
		m_apScene2d[nCount] = CScene2d::Create(0);
		m_apScene2d[nCount]->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0));
		m_apScene2d[nCount]->SetWorldPos(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0));
		m_apScene2d[nCount]->SetObjType(OBJTYPE_BG);
		m_apScene2d[nCount]->SetSize(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT,0));
		m_apScene2d[nCount]->BindTexture(m_apTexture[nCount]);
	}
	m_apScene2d[3] = CScene2d::Create(0);
	m_apScene2d[3]->SetPos(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT / 2, 0));
	m_apScene2d[3]->SetWorldPos(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT / 2, 0));
	m_apScene2d[3]->SetObjType(OBJTYPE_BG);
	m_apScene2d[3]->SetSize(D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT, 0));
	m_apScene2d[3]->BindTexture(m_apTexture[3]);
	return S_OK;
}

void CBg::Uninit(void)
{
	for (int nCount = 0; nCount < NUM_BG_LAYER; nCount++)
	{
		m_apScene2d[nCount] = NULL;
	}
	Release();
}

void CBg::Update(void)
{

 	for (int nCount = 0; nCount < NUM_BG_LAYER-1; nCount++)
	{
		for (int nCountTex = 0; nCountTex < NUM_VERTEX; nCountTex++)
		{
			m_TexPos[nCount][nCountTex] += D3DXVECTOR2(0.0015f*(nCount+1), 0);
		}
		m_apScene2d[nCount]->SetTexPos(m_TexPos[nCount]);
	}
}

void CBg::Draw(void)
{

}

CBg* CBg::Create(void)
{
	CBg* pBg = NULL;
	pBg = new CBg;
	pBg->Init();
	return pBg;
}

HRESULT CBg::Load(void)
{
	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "Resources\\bg100.png", &m_apTexture[0]);
	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "Resources\\bg101.png", &m_apTexture[1]);
	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "Resources\\bg102.png", &m_apTexture[2]);
	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "Resources\\earth.png", &m_apTexture[3]);

	return S_OK;
}

void CBg::Unload(void)
{
	for (int nCount = 0; nCount < NUM_BG_LAYER; nCount++)
	{
		if (m_apTexture[nCount] != NULL) {
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}