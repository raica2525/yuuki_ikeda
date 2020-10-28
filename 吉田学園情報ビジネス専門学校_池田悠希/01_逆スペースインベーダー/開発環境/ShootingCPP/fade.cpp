#include"fade.h"
#include "renderer.h"
bool CFade::bUse = false;
CFade::CFade()
{
	m_fadePhase = FADE_NONE;			// フェード状態
	m_modeNext = CManager::GAMEMODE_TITLE;	// 次の画面（モード）
	m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);		// フェード色
}
CFade::~CFade()
{

}
HRESULT CFade::Init(void)
{
	CPolygon::Init();
	return S_OK;
}

void CFade::Uninit(void)
{
	bUse = false;
	CPolygon::Uninit();
	CManager::KillFade();
}

void CFade::Update(void)
{

		if (m_fadePhase == FADE_IN)// フェードイン処理
		{
			m_colorFade.a -= FADE_RATE;// α値を減算して後ろの画面を浮き上がらせる
			if (m_colorFade.a <= 0.0f)
			{
				// フェード処理終了
				m_colorFade.a = 0.0f;
				m_fadePhase = FADE_NONE;
			}
		}
		else if (m_fadePhase == FADE_OUT)// フェードアウト処理
		{
			m_colorFade.a += FADE_RATE;// α値を加算して後ろの画面を消していく

			if (m_colorFade.a >= 1.0f)
			{
				// フェードイン処理に切り替え
				m_colorFade.a = 1.0f;
				m_fadePhase = FADE_IN;

				// モードを設定
				CManager::SetGamemode(m_modeNext);
			}
		}
		CPolygon::SetCol(m_colorFade);
		CPolygon::Update();
		if (m_fadePhase == FADE_NONE)
		{
			Uninit();
		}
}

void CFade::Draw(void)
{
	CPolygon::Draw();
}

CFade* CFade::Create(CManager::GAMEMODE modeNext)
{
	CFade* pFade = NULL;
	if (!bUse)
	{
		pFade = new CFade;
		pFade->m_fadePhase = FADE_OUT;
		pFade->m_modeNext = modeNext;
		pFade->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
		pFade->SetSize(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
		pFade->SetRot(0);
		pFade->m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	// 黒い画面（透明）
		bUse = true;
		pFade->Init();
		
	}
	return pFade;
}

CFade::FADE CFade::GetFadePhase(void)
{
	return m_fadePhase;
}

bool CFade::GetUse(void)
{
	return bUse;
}