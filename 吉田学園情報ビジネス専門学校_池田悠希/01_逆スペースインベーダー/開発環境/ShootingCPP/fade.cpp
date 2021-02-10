//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	fade.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "fade.h"
#include "renderer.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//静的メンバ変数宣言
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
bool CFade::m_bUse = false;

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//コンストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CFade::CFade()
{
    m_fadePhase = FADE_NONE;                            // フェード状態
    m_modeNext  = CManager::GAMEMODE_TITLE;             // 次の画面（モード）
    m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);    // フェード色
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//デストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CFade::~CFade()
{
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//初期化処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
HRESULT CFade::Init(void)
{
    CPolygon::Init();
    return S_OK;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//終了処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CFade::Uninit(void)
{
    m_bUse = false;
    CPolygon::Uninit();
    CManager::KillFade();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//更新処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CFade::Update(void)
{

    if(m_fadePhase == FADE_IN)    // フェードイン処理
    {
        m_colorFade.a -= FADE_RATE;    // α値を減算して後ろの画面を浮き上がらせる
        if(m_colorFade.a <= 0.0f)
        {
            // フェード処理終了
            m_colorFade.a = 0.0f;
            m_fadePhase   = FADE_NONE;
        }
    }
    else if(m_fadePhase == FADE_OUT)    // フェードアウト処理
    {
        m_colorFade.a += FADE_RATE;    // α値を加算して後ろの画面を消していく

        if(m_colorFade.a >= 1.0f)
        {
            // フェードイン処理に切り替え
            m_colorFade.a = 1.0f;
            m_fadePhase   = FADE_IN;

            // モードを設定
            CManager::SetGamemode(m_modeNext);
        }
    }
    //ポリゴンの色情報を更新
    CPolygon::SetCol(m_colorFade);
    CPolygon::Update();
    //フェードが終了したら消す
    if(m_fadePhase == FADE_NONE)
    {
        Uninit();
    }
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//描画処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CFade::Draw(void)
{
    CPolygon::Draw();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クリエイト関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CFade* CFade::Create(CManager::GAMEMODE modeNext)
{
    CFade* pFade = NULL;
	//フェード中でなければ
    if(!m_bUse)
    {
		//メモリ確保
        pFade              = new CFade;
		//各種情報設定
        pFade->m_fadePhase = FADE_OUT;
        pFade->m_modeNext  = modeNext;
        pFade->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
        pFade->SetSize(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
        pFade->SetRot(0);
        pFade->m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);    // 黒い画面（透明）
        m_bUse             = true;
		//初期化関数
        pFade->Init();
    }
    return pFade;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//フェードの段階取得処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CFade::FADE CFade::GetFadePhase(void)
{
    return m_fadePhase;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//フェード中取得処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
bool CFade::GetUse(void)
{
    return m_bUse;
}
