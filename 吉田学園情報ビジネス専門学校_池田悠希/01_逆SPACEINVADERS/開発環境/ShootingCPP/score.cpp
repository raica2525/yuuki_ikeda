//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	score.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "score.h"
#include "manager.h"
#include "renderer.h"
#include "number.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//コンストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CScore::CScore() : CScene(4)
{
    memset(m_apNumber, 0, sizeof(m_apNumber));
    m_nScore = 0;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//デストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CScore::~CScore()
{
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//初期化関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
HRESULT CScore::Init(void)
{
    for(int nCount = DIGIT_SCORE - 1; nCount >= 0; nCount--)
    {
		m_apNumber[nCount] = CNumber::Create(0, D3DXVECTOR3(SCREEN_WIDTH - (((float)nCount + 0.5f) * SCORE_SIZE_X), SCORE_SIZE_Y / 2, 0), D3DXVECTOR3(SCORE_SIZE_X, SCORE_SIZE_Y, 0), D3DCOLOR_RGBA(0, 50, 255, 255));
    }
    return S_OK;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//終了処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CScore::Uninit(void)
{
    for(int nCount = 0; nCount < DIGIT_SCORE; nCount++)
    {
		m_apNumber[nCount]->Uninit();
		delete m_apNumber[nCount];
        m_apNumber[nCount] = NULL;
    }
    Release();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//更新処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CScore::Update(void)
{
    for(int nCount = 0; nCount < DIGIT_SCORE; nCount++)
    {
        m_apNumber[nCount]->Update();
    }
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//描画処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CScore::Draw(void)
{
    for(int nCount = 0; nCount < DIGIT_SCORE; nCount++)
    {
        m_apNumber[nCount]->Draw();
    }
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クリエイト関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CScore* CScore::Create(void)
{
    CScore* pScore = new CScore;
    pScore->SetObjType(OBJTYPE_SCORE);
    pScore->Init();

    return pScore;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//スコア設定
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CScore::SetScore(int nScore)
{
    m_nScore = nScore;
    for(int nCount = 0; nCount < DIGIT_SCORE; nCount++)
    {
        m_apNumber[nCount]->SetValue((m_nScore % (int)pow(10, nCount + 1)) / (int)pow(10, nCount));
    }
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//スコア追加
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CScore::AddScore(int nScore)
{
    m_nScore += nScore;
    for(int nCount = 0; nCount < DIGIT_SCORE; nCount++)
    {
        m_apNumber[nCount]->SetValue((m_nScore % (int)pow(10, nCount + 1)) / (int)pow(10, nCount));
    }
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//スコア取得
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
int CScore::GetScore(void)
{
    return m_nScore;
}