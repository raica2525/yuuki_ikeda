//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	score.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

#ifndef _SCORE_H_
#define _SCORE_H_
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "main.h"
#include "scene.h"

class CNumber;
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CScore : public CScene
{
public:
    CScore();     //コンストラクタ
    ~CScore();    //デストラクタ

    static CScore* Create();    //ポリゴン生成処理

    HRESULT Init();       //初期化処理
    void Uninit(void);    //終了処理
    void Update(void);    //更新処理
    void Draw(void);      //描画処理

    void SetScore(int nScore);
    void AddScore(int nScore);
    int GetScore(void);

private:
    CNumber* m_apNumber[DIGIT_SCORE];
    int m_nScore;
};

#endif
