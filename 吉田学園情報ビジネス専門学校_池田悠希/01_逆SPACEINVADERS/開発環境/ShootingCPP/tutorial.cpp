//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	title.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

#include "tutorial.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
LPDIRECT3DTEXTURE9 CTutorial::m_pTexture = NULL;
CTutorial::CTutorial()
{
}

CTutorial::~CTutorial()
{
}

HRESULT CTutorial::Init(void)
{
    CPolygon::Init();
    BindTexture(m_pTexture);

    return S_OK;
}

void CTutorial::Uninit(void)
{
    CPolygon::Uninit();
}

void CTutorial::Update(void)
{
    CPolygon::Update();
}

void CTutorial::Draw(void)
{
    CPolygon::Draw();
}

CTutorial* CTutorial::Create(void)
{
    CTutorial* pTutorial = new CTutorial;
    pTutorial->Init();
    pTutorial->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
    pTutorial->SetSize(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
    pTutorial->SetRot(0);
    pTutorial->SetCol(D3DXCOLOR(1, 1, 1, 1));
    return pTutorial;
}

HRESULT CTutorial::Load(void)
{
    D3DXCreateTextureFromFile(
      CManager::GetRenderer()->GetDevice(), "Resources\\tutorial.png", &m_pTexture);

    return S_OK;
}

void CTutorial::Unload(void)
{
    if(m_pTexture != NULL)
    {
        m_pTexture->Release();
        m_pTexture = NULL;
    }
}
