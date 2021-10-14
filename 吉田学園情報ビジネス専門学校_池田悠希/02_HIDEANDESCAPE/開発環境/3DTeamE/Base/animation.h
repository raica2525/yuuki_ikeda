//=============================================================================
//
// アニメーション [animation.h]
// Author : 二階堂・吉田
//
//=============================================================================
#ifndef _ANIMATION_H_
#define _ANIMATION_H_
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include <stdio.h>
#include <stdlib.h>
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MOTION_KEYSET_MAX		5	//キーセット最大数
#define MODEL_LABEL_MAX			17	//モデルパーツの最大数
#define MAX_ANIME				10	//アニメションの最大数
//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CAnimation
{
public:
	typedef enum
	{
		ANIMATION_NONE = -1,
		ANIMATION_PLAYER_AR,
		ANIMATION_PLAYER_HG,
		ANIMATION_LIGHT_ENEMY,
		ANIMATION_HEAVY_ENEMY,
		ANIMATION_MAX
	}ANIMATION_TYPE;

	typedef enum
	{
		MOTION_PLAYER_NONE = -1,
		MOTION_PLAYER_NEUTRAL,
		MOTION_PLAYER_MOVE,
		MOTION_PLAYER_CROUCHING,
		MOTION_PLAYER_SPRINT,
		MOTION_PLAYER_AIM,
		MOTION_PLAYER_CROUCHING_MOVE,
		MOTION_PLAYER_RELOAD,
		MOTION_PLAYER_RELOAD_MOVE,
		MOTION_PLAYER_DEATH,
		MOTION_PLAYER_MAX
	}MOTION_PLAYER;

	typedef enum
	{
		MOTION_LIGHT_ENEMY_NONE = -1,
		MOTION_LIGHT_ENEMY_NEUTRAL,
		MOTION_LIGHT_ENEMY_MOVE,
		MOTION_LIGHT_ENEMY_ATTACK,
		MOTION_LIGHT_ENEMY_DEATH,
		MOTION_LIGHT_ENEMY_MAX
	}MOTION_LIGHT_ENEMY;

	typedef enum
	{
		MOTION_HEAVY_ENEMY_NONE = -1,
		MOTION_HEAVY_ENEMY_NEUTRAL,
		MOTION_HEAVY_ENEMY_MOVE,
		MOTION_HEAVY_ENEMY_ATTACK,
		MOTION_HEAVY_ENEMY_DEATH,
		MOTION_HEAVY_ENEMY_MAX
	}MOTION_HEAVY_ENEMY;


	CAnimation(int nPriority = 0);
	~CAnimation();
	static HRESULT Load(void);
	static CAnimation * Create(ANIMATION_TYPE AnimationType);
	HRESULT Init(ANIMATION_TYPE AnimationType);
	void Uninit(void);
	void Update(void);
	static void DataLoad(ANIMATION_TYPE AnimationType);
	void SetAnimation(int PlayerAnima);
	bool GetAnimeEnd(void) { return m_AnimatEnd; }
	int GetAnimation(void) { return m_nCountAnime; };
	D3DXVECTOR3 GetAnimePos(int nParts) { return m_modelData[nParts].pos; }
	D3DXVECTOR3 GetAnimeRot(int nParts) { return m_modelData[nParts].rot; }
	void SetAnimePos(int nParts,D3DXVECTOR3 pos) { m_modelData[nParts].pos = pos; }
	void SetAnimeRot(int nParts,D3DXVECTOR3 rot) { m_modelData[nParts].rot = rot; }
private:

	/*アニメーションキー情報*/
	typedef struct
	{
		D3DXVECTOR3		pos;						//位置
		D3DXVECTOR3		rot;						//回転
		D3DXMATRIX		mtxWorldAnime;				//行列計算
	}AnimationKey;
	/*アニメーションキーセット情報*/
	typedef struct
	{
		int				frame;						//キーフレーム数
		AnimationKey	key[MODEL_LABEL_MAX];		//キーセットに含むキー情報
	}AnimationKeySet;
	/*アニメーション情報*/
	typedef struct
	{
		bool			isLoop;						//モーションループ設定
		int				keyNum;						//キー数
		AnimationKeySet keySet[MOTION_KEYSET_MAX];	//アニメーションに含むキーセット情報
	}Animation;
	typedef struct
	{
		D3DXVECTOR3		pos;						//位置
		D3DXVECTOR3		rot;						//回転
		D3DXVECTOR3		posMove;					//位置
		D3DXVECTOR3		rotMove;					//回転
		D3DXMATRIX		mtxWorldAnime;				//行列計算
	}ModelData;

	ModelData	m_modelData[MODEL_LABEL_MAX];		//アニメーションさせるパーツの情報
	static Animation	m_animation[ANIMATION_MAX][MAX_ANIME];				//アニメーション情報
	
	static FILE * m_pFile[ANIMATION_MAX];
	static char * m_pFileName[ANIMATION_MAX];
	int				m_nCountAnime;					//再生中のアニメーション
	int				m_nCountFrame;					//再生中のフレーム
	int				m_nCountKeySet;					//再生中のキーセット
	ANIMATION_TYPE	m_AnimationType;				//アニメーションタイプ
	bool			m_AnimatEnd;					//アニメが終了しているか
};
#endif