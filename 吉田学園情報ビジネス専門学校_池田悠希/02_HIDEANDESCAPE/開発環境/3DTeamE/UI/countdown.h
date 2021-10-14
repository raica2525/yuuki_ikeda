//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	countdown.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#ifndef _COUNTDOWN_H_
#define _COUNTDOWN_H_
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "object2d.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//マクロ定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#define TIME_SIZE_X (200.0f)
#define TIME_SIZE_Y (100.0f)
#define DIGIT_NUM (5)
#define DIGIT_NUM_INT (2)
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//前方宣言
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CNumber;

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

class CCountDown : public CObject
{
public:
    CCountDown();
    ~CCountDown();

    HRESULT Init(void);    //初期化処理
    void Uninit(void);     //終了処理
    void Update(void);     //更新処理
    void Draw(void);       //描画処理

    static CCountDown* Create(int nLimitTime, D3DXVECTOR3 pos, D3DXVECTOR3 size);    //生成処理

    static HRESULT Load(void);    //テクスチャ読込
    static void Unload(void);     //テクスチャ破棄

private:
    static LPDIRECT3DTEXTURE9 m_pTexture;    // テクスチャへのポインタ
    int m_nTimeLimit;                        //時間制限
    int m_nElapsedTime;                      //経過時間
    int m_nSoundCount;                       //再生されている音声の数
    D3DXVECTOR3 m_pos;                       //座標
    D3DXVECTOR3 m_size;                      //サイズ
    D3DCOLOR m_col;                          //色
    CNumber* m_apNumber[DIGIT_NUM];          //数字のポインタ
    CObject2D* m_pObject2d;                  //背景のポインタ
};
#endif
