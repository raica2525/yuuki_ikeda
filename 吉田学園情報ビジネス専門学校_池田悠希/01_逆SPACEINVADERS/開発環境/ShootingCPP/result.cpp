//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	result.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

#include "result.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "scene.h"
#include "score.h"
#include <stdio.h>
LPDIRECT3DTEXTURE9 CResult::m_pTexture = NULL;
CResult::CResult()
{
    ZeroMemory(&m_nTopScore, sizeof(m_nTopScore));
    m_nRank = MAX_RANKING;
}

CResult::~CResult()
{
}

HRESULT CResult::Init(void)
{
    CPolygon::Init();
    BindTexture(m_pTexture);
    D3DXCreateFont(CManager::GetRenderer()->GetDevice(),
                   100,
                   0,
                   0,
                   0,
                   FALSE,
                   SHIFTJIS_CHARSET,
                   OUT_DEFAULT_PRECIS,
                   DEFAULT_QUALITY,
                   DEFAULT_PITCH,
                   "Terminal",
                   &m_pFont);
    return S_OK;
}

void CResult::Uninit(void)
{
    if(m_pFont != NULL)
    {
        m_pFont->Release();
        m_pFont = NULL;
    }
    CPolygon::Uninit();
}

void CResult::Update(void)
{
    CPolygon::Update();
}

void CResult::Draw(void)
{
    CPolygon::Draw();
    DrawRanking();
}

CResult* CResult::Create(void)
{
    CResult* pResult = new CResult;
    pResult->Init();
    pResult->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
    pResult->SetSize(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
    pResult->SetRot(0);
    pResult->SetCol(D3DXCOLOR(1, 1, 1, 1));
    return pResult;
}

HRESULT CResult::Load(void)
{
    D3DXCreateTextureFromFile(
      CManager::GetRenderer()->GetDevice(), "Resources\\result.png", &m_pTexture);

    return S_OK;
}

void CResult::Unload(void)
{
    if(m_pTexture != NULL)
    {
        m_pTexture->Release();
        m_pTexture = NULL;
    }
}

void CResult::UpdateRanking(void)
{
    m_nRank      = MAX_RANKING;
    int Score   = 0;
    FILE* pFile = NULL;
    pFile       = fopen("Resources\\ranking.txt", "r");
    for(int nCount = 0; nCount < MAX_RANKING; nCount++)
    {
		if (fscanf(pFile, "%d", &m_nTopScore[nCount]) == EOF)
		{
			break;
		}
    }
    fclose(pFile);
    CScene** pScene = CScene::GetScene();
    for(int nCount = 0; nCount < MAX_SCENE * PRIORITY_MAX; nCount++)
    {
        if((*(pScene + nCount)) != NULL)
        {
            if((*(pScene + nCount))->GetObjType() == CScene::OBJTYPE_SCORE)
            {
                Score = ((CScore*)(*(pScene + nCount)))->GetScore();
            }
        }
    }
    if(m_nTopScore[MAX_RANKING - 1] <= Score)
    {
        m_nTopScore[MAX_RANKING - 1] = Score;
        m_nRank--;
        for(; m_nTopScore[m_nRank - 1] <= m_nTopScore[m_nRank]; m_nRank--)
        {
            if(m_nRank <= 0)
            {
                break;
            }
            int Buff                = m_nTopScore[m_nRank - 1];
            m_nTopScore[m_nRank - 1] = m_nTopScore[m_nRank];
            m_nTopScore[m_nRank]     = Buff;
        }
    }
    pFile = fopen("Resources\\ranking.txt", "w");
    for(int nCount = 0; nCount < MAX_RANKING; nCount++)
    {
        fprintf(pFile, "%d\n", m_nTopScore[nCount]);
    }
    fclose(pFile);
}
void CResult::DrawRanking(void)
{
    RECT rect      = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    char str[1024] = {};
    char cNum[256];

    for(int nCount = 0; nCount < MAX_RANKING / 2; nCount++)
    {
        sprintf(cNum,
                "%d位:%d      %d位:%d\n",
                nCount + 1,
                m_nTopScore[nCount],
                nCount + MAX_RANKING / 2 + 1,
                m_nTopScore[nCount + MAX_RANKING / 2]);
        strcat(str, cNum);
    }
    if(m_nRank < MAX_RANKING)
    {
        sprintf(cNum, "あなたは%d位", m_nRank + 1);
        strcat(str, cNum);
    }
    else
    {
        sprintf(cNum, "あなたはランク外");
        strcat(str, cNum);
    }
    //テキスト描画
    m_pFont->DrawText(
      NULL, str, -1, &rect, DT_CENTER | DT_VCENTER, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}
