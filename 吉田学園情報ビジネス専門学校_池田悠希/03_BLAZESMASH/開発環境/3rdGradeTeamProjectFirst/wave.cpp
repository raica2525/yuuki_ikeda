//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	wave.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "wave.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "library.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//マクロ定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#define TEX_DIV_RATE (1.2f)
#define SIZE_SCALE_RATE (1.1f)

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//コンストラクタ
//Author:池田悠希
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CWave::CWave() :CScene(OBJTYPE_WAVE)
{
    m_pos = DEFAULT_VECTOR;
    m_size = DEFAULT_VECTOR;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//デストラクタ
//Author:池田悠希
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CWave::~CWave()
{

}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//初期化処理
//Author:池田悠希
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
HRESULT CWave::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    // メンバ変数に結びつける
    m_pos = pos;
    m_size = size;
    m_pTexture = CManager::GetTexture()->GetInfo(7)->pTexture;    // 波のドーナッツ

    VERTEX_2D*pVtx = NULL;
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

    // 頂点バッファの生成
    for (int nCount = 0; nCount < POLYTYPE_MAX ; nCount++)
    {
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_apVtxBuff[nCount], NULL);
    }

    //円形のステンシル生成用ポリゴン
    m_apVtxBuff[POLYTYPE_STENCIL]->Lock(0, 0, (void**)&pVtx, 0);

    // 頂点情報を設定
    pVtx[0].pos = m_pos + D3DXVECTOR3(-m_size.x / 2.0f, -m_size.y / 2.0f, 0.0f);
    pVtx[1].pos = m_pos + D3DXVECTOR3(m_size.x / 2.0f, -m_size.y / 2.0f, 0.0f);
    pVtx[2].pos = m_pos + D3DXVECTOR3(-m_size.x / 2.0f, m_size.y / 2.0f, 0.0f);
    pVtx[3].pos = m_pos + D3DXVECTOR3(m_size.x / 2.0f, m_size.y / 2.0f, 0.0f);

    //テクスチャ座標の設定
    pVtx[0].tex[0] = D3DXVECTOR2(0.0f, 0.0f);
    pVtx[1].tex[0] = D3DXVECTOR2(1.0f, 0.0f);
    pVtx[2].tex[0] = D3DXVECTOR2(0.0f, 1.0f);
    pVtx[3].tex[0] = D3DXVECTOR2(1.0f, 1.0f);

    //rhwの設定
    pVtx[0].rhw = 1.0f;
    pVtx[1].rhw = 1.0f;
    pVtx[2].rhw = 1.0f;
    pVtx[3].rhw = 1.0f;

    //頂点カラーの設定(0～255)
    pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
    pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
    pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
    pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
    m_apVtxBuff[0]->Unlock();

    pVtx = NULL;

    //テクスチャ
    m_apVtxBuff[POLYTYPE_REAL]->Lock(0, 0, (void**)&pVtx, 0);

    // 頂点情報を設定
    pVtx[0].pos = m_pos + D3DXVECTOR3(-m_size.x / 2.0f, -m_size.y / 2.0f, 0.0f);
    pVtx[1].pos = m_pos + D3DXVECTOR3(m_size.x / 2.0f, -m_size.y / 2.0f, 0.0f);
    pVtx[2].pos = m_pos + D3DXVECTOR3(-m_size.x / 2.0f, m_size.y / 2.0f, 0.0f);
    pVtx[3].pos = m_pos + D3DXVECTOR3(m_size.x / 2.0f, m_size.y / 2.0f, 0.0f);

    //テクスチャ座標の設定
    for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
    {
        pVtx[nCount].tex[0] = D3DXVECTOR2(pVtx[nCount].pos.x / (float)SCREEN_WIDTH, pVtx[nCount].pos.y / (float)SCREEN_HEIGHT);
    }

    //rhwの設定
    pVtx[0].rhw = 1.0f;
    pVtx[1].rhw = 1.0f;
    pVtx[2].rhw = 1.0f;
    pVtx[3].rhw = 1.0f;

    //頂点カラーの設定
    pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
    pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
    pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
    pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

    m_apVtxBuff[POLYTYPE_REAL]->Unlock();

    return S_OK;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//終了処理
//Author:池田悠希
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CWave::Uninit(void)
{
    // 頂点バッファの破棄
    for (int nCount = 0; nCount < POLYTYPE_MAX; nCount++)
    {
        if (m_apVtxBuff[nCount] != NULL)
        {
            m_apVtxBuff[nCount]->Release();
            m_apVtxBuff[nCount] = NULL;
        }
    }
    Release();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//更新処理
//Author:池田悠希
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CWave::Update(void)
{
    VERTEX_2D*pVtx = NULL;

	//ポリゴンを拡大する
    m_size.x *= SIZE_SCALE_RATE;
    m_size.y *= SIZE_SCALE_RATE;

    for (int nCount = 0; nCount < POLYTYPE_MAX; nCount++)
    {
        pVtx = NULL;
        m_apVtxBuff[nCount]->Lock(0, 0, (void**)&pVtx, 0);
        if (nCount == POLYTYPE_REAL)
        {
			//一旦ポリゴンを少し小さくする
            m_size.x /= TEX_DIV_RATE;
            m_size.y /= TEX_DIV_RATE;

            pVtx[0].pos = m_pos + D3DXVECTOR3(-m_size.x / 2.0f,-m_size.y / 2.0f, 0.0f);
            pVtx[1].pos = m_pos + D3DXVECTOR3(m_size.x / 2.0f, -m_size.y / 2.0f, 0.0f);
            pVtx[2].pos = m_pos + D3DXVECTOR3(-m_size.x / 2.0f, m_size.y / 2.0f, 0.0f);
            pVtx[3].pos = m_pos + D3DXVECTOR3(m_size.x / 2.0f, m_size.y / 2.0f, 0.0f);

			//小さくした状態でテクスチャを割り当てることでテクスチャを少しずらす
            for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
            {
                pVtx[nCount].tex[0] = D3DXVECTOR2(pVtx[nCount].pos.x / SCREEN_WIDTH, pVtx[nCount].pos.y / SCREEN_HEIGHT);
            }

			//大きさを元に戻す
			m_size.x *= TEX_DIV_RATE;
			m_size.y *= TEX_DIV_RATE;
        }

		//頂点座標の更新
        pVtx[0].pos = m_pos + D3DXVECTOR3(-m_size.x / 2.0f,-m_size.y / 2.0f, 0.0f);
        pVtx[1].pos = m_pos + D3DXVECTOR3(m_size.x / 2.0f, -m_size.y / 2.0f, 0.0f);
        pVtx[2].pos = m_pos + D3DXVECTOR3(-m_size.x / 2.0f, m_size.y / 2.0f, 0.0f);
        pVtx[3].pos = m_pos + D3DXVECTOR3(m_size.x / 2.0f, m_size.y / 2.0f, 0.0f);

        m_apVtxBuff[nCount]->Unlock();
    }

    // 一定サイズに達したら破棄
    if (m_size.x > SCREEN_WIDTH * 2)
    {
        Uninit();
    }
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//描画処理
//Author:池田悠希
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CWave::Draw(void)
{
	//ステンシルに描画
    CreateStencil();
	
	//生成したステンシルを使って描画

    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//Zテストの設定
    pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
    pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
    pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);

    pDevice->SetRenderState(D3DRS_STENCILREF, 0x01);
    pDevice->SetRenderState(D3DRS_STENCILMASK, 0xff);

    pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);

    pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
    pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
    pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);

    // 頂点バッファをデータストリームに設定
    pDevice->SetStreamSource(0, m_apVtxBuff[POLYTYPE_REAL], 0, sizeof(VERTEX_2D));

    // 頂点フォーマットの設定
    pDevice->SetFVF(FVF_VERTEX_2D);

    // テクスチャの設定（スクリーン全体のテクスチャ）
    pDevice->SetTexture(0, CManager::GetRenderer()->GetScreenTexture());

    // ポリゴンの描画
    pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
    pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
    pDevice->SetTexture(0, NULL);
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クリエイト関数
//Author:池田悠希
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CWave* CWave::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    CWave* pWave = new CWave;
    pWave->Init(ConvertScreenPos(pos), size);
    return pWave;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//ステンシル生成
//Author:池田悠希
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CWave::CreateStencil(void)
{
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

    // アルファテストの有効化
    pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
    pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);

    // 不透明にする値の設定
    pDevice->SetRenderState(D3DRS_ALPHAREF, 128);

	//Zテストが成功しないように設定
    pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
    pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_NEVER);

	//ステンシルの設定
    pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);
    pDevice->SetRenderState(D3DRS_STENCILREF, 0x01);
    pDevice->SetRenderState(D3DRS_STENCILMASK, 0xff);
    pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);

    pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
    pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_REPLACE);
    pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);

    // 頂点バッファをデータストリームに設定
    pDevice->SetStreamSource(0, m_apVtxBuff[POLYTYPE_STENCIL], 0, sizeof(VERTEX_2D));

    // 頂点フォーマットの設定
    pDevice->SetFVF(FVF_VERTEX_2D);

    // テクスチャの設定（くりぬくテクスチャ）
    pDevice->SetTexture(0, m_pTexture);

    // ポリゴンの描画
    pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

    pDevice->SetTexture(0, NULL);
    pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}
