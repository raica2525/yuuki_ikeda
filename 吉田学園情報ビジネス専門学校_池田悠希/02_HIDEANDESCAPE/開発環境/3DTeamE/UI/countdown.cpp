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
    m_nTimeLimit   = 0;
    m_nElapsedTime = 0;
    m_nSoundCount  = 0;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//デストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CCountDown::~CCountDown()
{
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//生成処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CCountDown* CCountDown::Create(const int nLimitTime, const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
    CCountDown* pCountDown = new CCountDown;

    pCountDown->m_nTimeLimit = nLimitTime * 60;
    pCountDown->m_pos        = pos;
    pCountDown->m_size       = size;

    pCountDown->Init();
    return pCountDown;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//初期化関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
HRESULT CCountDown::Init(void)
{
    for(int nCount = 0; nCount < DIGIT_NUM; nCount++)
    {
        if(nCount < DIGIT_NUM - DIGIT_NUM_INT)
        {
            m_apNumber[nCount] = CNumber::Create(0, D3DXVECTOR3(m_pos.x + m_size.x / 2.0f - m_size.x / 5.0f * nCount - m_size.x / 10.0f, m_pos.y + m_size.y * 0.1f, 0.0f), D3DXVECTOR3(m_size.x / 5.0f * 1.5f, (m_size.y - 25.0f) / 3.0f * 2.0f, 0.0f));
        }
        else
        {
            m_apNumber[nCount] = CNumber::Create(0, D3DXVECTOR3(m_pos.x + m_size.x / 2.0f - m_size.x / 5.0f * nCount - m_size.x / 10.0f, m_pos.y, 0.0f), D3DXVECTOR3(m_size.x / 5.0f * 1.5f, m_size.y - 25.0f, 0.0f));
        }
    }
    m_pObject2d = CObject2D::Create(m_pos, m_size, 1);
    m_pObject2d->BindTexture(m_pTexture);
    m_nSoundCount = 0;
    return S_OK;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//終了関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CCountDown::Uninit(void)
{
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//更新関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CCountDown::Update(void)
{
    float fDisplayTime = 0;    //表示用の時間
    m_nElapsedTime++;          //経過時間を増やす
    //残り時間を減らす
    fDisplayTime = (float)((m_nTimeLimit - m_nElapsedTime) * 1000.0f / 60.0f);
    //残り時間が0以下になったら0に戻す
    if(fDisplayTime < 0)
    {
        fDisplayTime = 0.0f;
    }
    //桁ごとに分けて表示する数字を変更する
    for(int nCount = 0; nCount < DIGIT_NUM; nCount++)
    {
        m_apNumber[nCount]->SetValue(((int)fDisplayTime % (int)powf(10.0f, nCount + 1)) / (int)powf(10.0f, nCount));
    }

    //時間切れの処理
    if(m_nElapsedTime >= m_nTimeLimit)
    {
        if(m_nSoundCount == 0)
        {
            CManager::GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_MAPEXPLOSION);
            m_nSoundCount++;
        }
        //プレイヤーの体力を最大体力分減らす(絶対殺す)
        CManager::GetPlayer()->AddLife(-START_LIFE);
    }
    //数字の更新処理
    for(int nCount = 0; nCount < DIGIT_NUM; nCount++)
    {
        m_apNumber[nCount]->Update();
    }
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//描画関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CCountDown::Draw(void)
{
    for(int nCount = 0; nCount < DIGIT_NUM; nCount++)
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
    if(m_pTexture != NULL)
    {
        m_pTexture->Release();
        m_pTexture = NULL;
    }
}
