//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	renderer.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#ifndef _RENDERER_H_
#define _RENDERER_H_

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "main.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CRenderer
{
public:
    CRenderer();
    ~CRenderer();

    HRESULT Init(HWND hWnd, bool bWindow);    //初期化処理
    void Uninit(void);                        //終了処理
    void Update(void);                        //更新処理
    void Draw(void);                          //描画処理
    //ゲッター関数
    LPDIRECT3DDEVICE9 GetDevice(void);

private:
    LPDIRECT3D9 m_pD3D;                // Direct3Dオブジェクト
    LPDIRECT3DDEVICE9 m_pD3DDevice;    // Deviceオブジェクト(描画に必要)
};

#endif
