//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	countdown.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "countdown.h"
#include "gameoveroverlay.h"
#include "number.h"
#include "manager.h"
#include "player.h"
#include "renderer.h"	
#include "sound.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//静的メンバ変数宣言
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

LPDIRECT3DTEXTURE9 CCountDown::m_pTexture = NULL;
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//コンストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

CCountDown::CCountDown() : CObject(2)
{
	ZeroMemory(m_apNumber, sizeof(m_apNumber));
	m_nTimeLimit = 0;
	m_nElapsedTime = 0;
	m_nSoundCount = 0;
}
CCountDown::~CCountDown()
{
}
CCountDown* CCountDown::Create(int nLimitTime, D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    CCountDown* pCountDown = NULL;
    pCountDown             = new CCountDown;

    pCountDown->m_nTimeLimit = nLimitTime*60;
    pCountDown->m_pos        = pos;
    pCountDown->m_size       = size;

	pCountDown->Init();
	return pCountDown;
}
HRESULT CCountDown::Init(void)
{
	for (int nCount = 0; nCount < 5; nCount++)
	{
		if (nCount < 3)
		{
			m_apNumber[nCount] = CNumber::Create(0, D3DXVECTOR3(m_pos.x + m_size.x / 2 - m_size.x / 5 * nCount - m_size.x / 10, m_pos.y+ m_size.y*0.1f, 0), D3DXVECTOR3(m_size.x / 5 * 1.5f, (m_size.y - 25)/3*2, 0));
		}
		else
		{
			m_apNumber[nCount] = CNumber::Create(0, D3DXVECTOR3(m_pos.x + m_size.x / 2 - m_size.x / 5 * nCount - m_size.x / 10, m_pos.y, 0), D3DXVECTOR3(m_size.x / 5 * 1.5f, m_size.y - 25, 0));
		}
	}
	m_pObject2d = CObject2D::Create(m_pos, m_size, 1);
	m_pObject2d->BindTexture(m_pTexture);
	m_nSoundCount = 0;
	return S_OK;
}
void CCountDown::Uninit(void)
{
}
void CCountDown::Update(void)
{
	CSound* pSound = CManager::GetSound();

	float fDisplayTime = 0;
	m_nElapsedTime++;
	fDisplayTime = (float)((m_nTimeLimit - m_nElapsedTime) * 1000 /60);
	if (fDisplayTime < 0)
	{
		fDisplayTime = 0;
	}
	for (int nCount = 0; nCount < 5; nCount++)
	{
		m_apNumber[nCount]->SetValue(((int)fDisplayTime % (int)pow(10, nCount + 1)) / (int)pow(10, nCount));
	}
	if (m_nElapsedTime >= m_nTimeLimit)
	{
		if (m_nSoundCount == 0)
		{
			pSound->PlaySoundA(CSound::SOUND_LABEL_SE_MAPEXPLOSION);
			m_nSoundCount++;
		}
		CManager::GetPlayer()->AddLife(-START_LIFE);
	}
	for (int nCount = 0; nCount < 5; nCount++)
	{
		m_apNumber[nCount]->Update();
	}

}
void CCountDown::Draw(void)
{
	for (int nCount = 0; nCount < 5; nCount++)
	{
		m_apNumber[nCount]->Draw();
	}
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//テクスチャロード
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
HRESULT CCountDown::Load(void)
{
	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "Data/Texture/Num_Haikei.png", &m_pTexture);
	return S_OK;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//テクスチャアンロード
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CCountDown::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}