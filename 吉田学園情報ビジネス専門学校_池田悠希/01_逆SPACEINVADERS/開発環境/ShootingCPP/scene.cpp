//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
// scene.cpp
// Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "scene.h"
#include "renderer.h"
#include "scene2d.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//静的メンバ変数宣言
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CScene* CScene::m_apScene[PRIORITY_MAX][MAX_SCENE] = {};
int CScene::m_nNumAll                              = 0;

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//コンストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CScene::CScene(int nPriority)
{
    m_objType = OBJTYPE_NONE;
    for(int nCount = 0; nCount < MAX_SCENE; nCount++)
    {
        if(m_apScene[nPriority][nCount] == NULL)
        {
            m_apScene[nPriority][nCount] = this;    //配列にポインタを格納
            m_nPriority                  = nPriority;
            m_nNumScene                  = nCount;
            m_nNumAll++;    //全体のシーン数をインクリメント
            break;
        }
    }
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//デストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CScene::~CScene()
{
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//更新処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CScene::UpdateAll(void)
{
    for(int nCntPriority = PRIORITY_MAX - 1; nCntPriority >= 0; nCntPriority--)
    {
        for(int nCount = 0; nCount < MAX_SCENE; nCount++)
        {
            if(m_apScene[nCntPriority][nCount] != NULL)
            {
                m_apScene[nCntPriority][nCount]->Update();
            }
        }
    }
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//描画処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CScene::DrawAll(void)
{
    for(int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
    {
        for(int nCount = 0; nCount < MAX_SCENE; nCount++)
        {
            if(m_apScene[nCntPriority][nCount] != NULL)
            {
                m_apScene[nCntPriority][nCount]->Draw();
            }
        }
    }
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//全開放処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CScene::ReleaseAll(void)
{
    for(int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
    {
        for(int nCount = 0; nCount < MAX_SCENE; nCount++)
        {
            if(m_apScene[nCntPriority][nCount] != NULL)
            {
                m_apScene[nCntPriority][nCount]->Uninit();
                m_apScene[nCntPriority][nCount] = NULL;
            }
        }
    }
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//開放処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CScene::Release(void)
{
    m_apScene[m_nPriority][m_nNumScene] = NULL;
    delete this;
    m_nNumAll--;    //シーン数をデクリメント
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//オブジェクトタイプ取得
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CScene::OBJTYPE CScene::GetObjType(void)
{
    return m_objType;
}
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//オブジェクトタイプ設定
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CScene::SetObjType(OBJTYPE type)
{
    m_objType = type;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//シーンの先頭ポインタを取得
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CScene** CScene::GetScene(void)
{
    return &m_apScene[0][0];
}
