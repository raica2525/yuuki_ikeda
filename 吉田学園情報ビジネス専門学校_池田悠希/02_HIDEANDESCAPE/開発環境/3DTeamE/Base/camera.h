//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	camera.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CCamera
{
public:
    CCamera();
    ~CCamera();

    HRESULT Init(void);      //初期化処理
    void Uninit(void);       //終了処理
    void Update(void);       //更新処理
    void SetCamera(void);    //カメラ設定

    D3DXVECTOR3 GetRot(void);     //回転取得
    D3DXVECTOR3 GetPosR(void);    //注視点取得

    void SetRot(D3DXVECTOR3 rot);    //回転設定

private:
    D3DXVECTOR3 m_posV;                 //カメラの座標
    D3DXVECTOR3 m_posR;                 //注視点の座標
    D3DXVECTOR3 m_vecU;                 //カメラの上方向
    D3DXMATRIX m_mtxProjection;         //プロジェクションマトリックス
    D3DXMATRIX m_mtxView;               //ビューマトリックス
    float m_fDistance;                  //視点-注意点の距離
    float m_fDistanceFromPlayer;        //プレイヤーからの距離
    float m_fDistanceFromPlayerDest;    //プレイヤーからの距離の目標値
    D3DXVECTOR3 m_rot;                  //回転角
};

#endif
