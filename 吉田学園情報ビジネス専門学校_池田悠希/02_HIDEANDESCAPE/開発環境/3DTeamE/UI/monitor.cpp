//=============================================================================
//
// 偵察機処理 [uav.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "monitor.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "countdown.h"

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CMonitor::m_pTexture = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CMonitor::CMonitor() :CObject2D(3)
{
	D3DXVECTOR3	m_pos = ZEROVECTOR3;
	D3DXVECTOR3	m_size = ZEROVECTOR3;
	D3DCOLOR	m_col = D3DCOLOR_RGBA(255, 255, 255, 255);
	m_nCounterAnim = 0;				//アニメカウンタ
	m_nPatternAnim = 0;				//アニメパターン
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_texpos[nCount] = D3DXVECTOR2(0.0f, 0.0f);
	}
}

//=============================================================================
// デストラクタ
//=============================================================================
CMonitor::~CMonitor()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CMonitor::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		"Data/Texture/monitor.png",								// ファイルの名前
		&m_pTexture);								// 読み込むメモリー
	return S_OK;
}

//=============================================================================
// テクスチャ破棄関数
//=============================================================================
void CMonitor::Unload(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// 生成関数
//=============================================================================
CMonitor * CMonitor::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CMonitor* pMonitor = NULL;
	pMonitor = new CMonitor;
	pMonitor->m_pos = pos;
	pMonitor->m_size = size;
	pMonitor->Init();

	return pMonitor;
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CMonitor::Init(void)
{
	SetPos(m_pos);
	SetSize(m_size);
	BindTexture(m_pTexture);	//テクスチャの割り当て
	//サウンドの取得
	CSound * pSound = CManager::GetSound();
	pSound->StopSound();
	pSound->PlaySound(CSound::SOUND_LABEL_SE_KEYBOARD);
	CObject2D::Init();
	return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CMonitor::Uninit(void)
{
	CObject2D::Uninit();
}

//=============================================================================
// 更新関数
//=============================================================================
void CMonitor::Update(void)
{
	//サウンドの取得
	CSound * pSound = CManager::GetSound();
	//カウントインクリメント
	m_nCounterAnim++;

	//カウントが4以上になった場合
	if (m_nCounterAnim > 20)
	{
		//カウントを0にする
		m_nCounterAnim = 0;

		//パターンのインクリメント
		m_nPatternAnim++;
		//パターンが13になった場合
		if (m_nPatternAnim > 9)
		{
			pSound->StopSound();
			pSound->PlaySound(CSound::SOUND_LABEL_SE_MAPEXPLOSION);
			pSound->PlaySound(CSound::SOUND_LABEL_SE_ALARM);
			pSound->PlaySound(CSound::SOUND_LABEL_BGM_LASTMAP);
			CCountDown::Create(60, D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 - 200, 0.0f), D3DXVECTOR3(200.0f, 100.0f, 100.0f));
			//終了
			Uninit();
			return;
		}
	}

	m_texpos[0] = D3DXVECTOR2(m_nPatternAnim * 0.1f, 0.0f);
	m_texpos[1] = D3DXVECTOR2(m_nPatternAnim * 0.1f + 0.1f, 0.0f);
	m_texpos[2] = D3DXVECTOR2(m_nPatternAnim * 0.1f, 1.0f);
	m_texpos[3] = D3DXVECTOR2(m_nPatternAnim * 0.1f + 0.1f, 1.0f);

	SetTexPos(m_texpos);
}

//=============================================================================
// 描画関数
//=============================================================================
void CMonitor::Draw(void)
{
	CObject2D::Draw();
}

