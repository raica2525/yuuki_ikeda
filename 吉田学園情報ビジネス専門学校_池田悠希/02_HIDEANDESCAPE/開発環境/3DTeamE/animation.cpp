//=============================================================================
//
// アニメーション処理 [animation.cpp]
// Author : 二階堂・吉田
//
//=============================================================================

//*****************************************************************************
// 警告制御
//*****************************************************************************
#define _CRT_SECURE_NO_WARNINGS
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "animation.h"
#include <stdio.h>
#include <stdlib.h>
//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
FILE * CAnimation::m_pFile[ANIMATION_MAX] = {};
CAnimation::Animation CAnimation::m_animation[ANIMATION_MAX][MAX_ANIME] = {};
char *CAnimation::m_pFileName[ANIMATION_MAX]=
{
	"Data/AnimationData/PlayerAnimation_AK.txt",
	"Data/AnimationData/PlayerAnimation_HG.txt",
	"Data/AnimationData/EnemyLightAnimation.txt",
	"Data/AnimationData/EnemyHeavyAnimation.txt",

};
//=============================================================================
// コンストラクタ
//=============================================================================
CAnimation::CAnimation(int nPriority)
{
	m_AnimationType = ANIMATION_NONE;		//アニメーションタイプ
	m_nCountAnime = -1;						//再生中のアニメーション
	m_nCountFrame = 0;						//再生中のフレーム
	m_nCountKeySet = 0;						//再生中のキーセット
	memset(&m_modelData, 0, sizeof(m_modelData));
	m_AnimatEnd = false;
}

//=============================================================================
//デストラクタ
//=============================================================================
CAnimation::~CAnimation()
{
}

//=============================================================================
// ロード処理
//=============================================================================
HRESULT CAnimation::Load(void)
{
	for (int nCountAnima=0;nCountAnima<ANIMATION_MAX;nCountAnima++)
	{
		//データロード関数の呼び出し
		DataLoad((ANIMATION_TYPE)nCountAnima);
	}

	return S_OK;
}

//=============================================================================
// 生成関数
//=============================================================================
CAnimation * CAnimation::Create(ANIMATION_TYPE AnimationType)
{
	CAnimation * pAnimation;
	pAnimation = new CAnimation;
	pAnimation->Init(AnimationType);
	return pAnimation;
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CAnimation::Init(ANIMATION_TYPE AnimationType)
{
	//タイプ読み込み
	m_AnimationType = AnimationType;
	return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CAnimation::Uninit(void)
{
	
}

//=============================================================================
// 更新関数
//=============================================================================
void CAnimation::Update(void)
{
	if (m_AnimatEnd == true)
	{
		if (m_nCountFrame == 0)
		{
			//アニメーションアップデート
			for (int nAnime = 0; nAnime < MODEL_LABEL_MAX; nAnime++)
			{
				m_modelData[nAnime].rotMove = (m_animation[m_AnimationType][m_nCountAnime].keySet[m_nCountKeySet].key[nAnime].rot - m_modelData[nAnime].rot) / (float)m_animation[m_AnimationType][m_nCountAnime].keySet[m_nCountKeySet].frame;
				m_modelData[nAnime].posMove = (m_animation[m_AnimationType][m_nCountAnime].keySet[m_nCountKeySet].key[nAnime].pos - m_modelData[nAnime].pos) / (float)m_animation[m_AnimationType][m_nCountAnime].keySet[m_nCountKeySet].frame;
			}
		}
		//アニメーションアップデート
		for (int nAnime = 0; nAnime < MODEL_LABEL_MAX; nAnime++)
		{
			m_modelData[nAnime].rot += m_modelData[nAnime].rotMove;
			m_modelData[nAnime].pos += m_modelData[nAnime].posMove;
		}
	}
	//フレームカウント
	m_nCountFrame++;

	//一定の値までフレームがいったら
	if (m_animation[m_AnimationType][m_nCountAnime].keySet[m_nCountKeySet].frame == m_nCountFrame)
	{
		//フレーム初期化
		m_nCountFrame = 0;
		//キーセット更新
		m_nCountKeySet+=1;

		//キーが最大までいったら
		if (m_nCountKeySet == m_animation[m_AnimationType][m_nCountAnime].keyNum)
		{
			//アニメが終了
			m_AnimatEnd = false;

			//ループ処理をするか、しないか
			if (m_animation[m_AnimationType][m_nCountAnime].isLoop == true)
			{
				//する場合
				m_nCountKeySet = 0;
				m_AnimatEnd = true;
			}
		}
	}

}

//=============================================================================
//　データロード関数
//=============================================================================
void CAnimation::DataLoad(ANIMATION_TYPE AnimationType)
{

	int nAnimeKeySet = 0;					//キーセット番号
	int nModelParts = 0;					//モデルパーツ情報
	int nAnimation = 0;						//アニメーション番号
	char cFileString[256];					//読み込みデータ
	memset(&cFileString, 0, sizeof(cFileString));
	//ファイルオープン
	m_pFile[AnimationType] = fopen(m_pFileName[AnimationType], "r");

	if (m_pFile[AnimationType] != NULL)
	{
		//そのデータがを終わるまで読み込み
		while (strcmp(cFileString, "END_SCRIPT") != 0)
		{
			//初期化
			memset(cFileString, 0, sizeof(cFileString));
			//読み込み
			fscanf(m_pFile[AnimationType],"%s", cFileString);

			//文字の比較
			if (strcmp(cFileString,"MOTIONSET")==0)
			{
				while (strcmp(cFileString, "END_MOTIONSET") != 0)
				{
					//初期化
					memset(cFileString, 0, sizeof(cFileString));
					//読み込み
					fscanf(m_pFile[AnimationType], "%s", cFileString);

					//ループ確認
					if (strcmp(cFileString, "LOOP") == 0)
					{
						int nBool;
						//読み込み
						fscanf(m_pFile[AnimationType], " = %d ", &nBool);
						//bool確認
						if (nBool != 0)
						{
							m_animation[AnimationType][nAnimation].isLoop = true;
						}
						else
						{
							m_animation[AnimationType][nAnimation].isLoop = false;
						}
					}
					//キー数確認
					if (strcmp(cFileString, "NUM_KEY") == 0)
					{
						//読み込み
						fscanf(m_pFile[AnimationType], " = %d ", &m_animation[AnimationType][nAnimation].keyNum);
					}

					//アニメーションキーセット情報読み込み
					if (strcmp(cFileString, "KEYSET") == 0)
					{
						//パーツの情報を受け取り終わるまで
						while (strcmp(cFileString, "END_KEYSET") != 0)
						{
							//初期化
							memset(cFileString, 0, sizeof(cFileString));
							//読み込み
							fscanf(m_pFile[AnimationType], "%s", cFileString);

							//キーフレーム数
							if (strcmp(cFileString, "FRAME") == 0)
							{
								//読み込み
								fscanf(m_pFile[AnimationType], " = %d ", &m_animation[AnimationType][nAnimation].keySet[nAnimeKeySet].frame);
							}
							//アニメーションキー情報読み込み
							if (strcmp(cFileString, "KEY") == 0)
							{
								while (strcmp(cFileString, "END_KEY") != 0)
								{
									//初期化
									memset(cFileString, 0, sizeof(cFileString));
									//読み込み
									fscanf(m_pFile[AnimationType], "%s", cFileString);
									//パーツの位置情報
									if (strcmp(cFileString, "POS") == 0)
									{
										//読み込み
										fscanf(m_pFile[AnimationType], " = %f %f %f",
											&m_animation[AnimationType][nAnimation].keySet[nAnimeKeySet].key[nModelParts].pos.x,
											&m_animation[AnimationType][nAnimation].keySet[nAnimeKeySet].key[nModelParts].pos.y,
											&m_animation[AnimationType][nAnimation].keySet[nAnimeKeySet].key[nModelParts].pos.z);
									}
									//パーツの向き情報
									if (strcmp(cFileString, "ROT") == 0)
									{
										//読み込み
										fscanf(m_pFile[AnimationType], " = %f %f %f",
											&m_animation[AnimationType][nAnimation].keySet[nAnimeKeySet].key[nModelParts].rot.x,
											&m_animation[AnimationType][nAnimation].keySet[nAnimeKeySet].key[nModelParts].rot.y,
											&m_animation[AnimationType][nAnimation].keySet[nAnimeKeySet].key[nModelParts].rot.z);
									}
								}
								nModelParts++;//パーツ番号加算
							}
						}
						nAnimeKeySet++;//モーション番号加算
						nModelParts = 0;
					}
				}
				nAnimation++;	//アニメーション番号加算
				nAnimeKeySet = 0;
				nModelParts = 0;
			}
		}
		fclose(m_pFile[AnimationType]);	//ファイルを閉じる
	}
}


//=============================================================================
// セットアニメーション関数
//=============================================================================
void CAnimation::SetAnimation(int PlayerAnima)
{
	//プレイヤーのリロードアニメーション処理
	if (PlayerAnima == MOTION_PLAYER_RELOAD
		|| PlayerAnima == MOTION_PLAYER_RELOAD_MOVE)
	{
		if (m_nCountAnime == MOTION_PLAYER_RELOAD
			|| m_nCountAnime == MOTION_PLAYER_RELOAD_MOVE)
		{
			if (m_nCountAnime != PlayerAnima)
			{
				//再生フレームを初期化
				m_nCountFrame = 0;
				//再生キーフレームを初期化
				m_nCountKeySet = m_nCountKeySet;
				//再生アニメ変更
				m_nCountAnime = PlayerAnima;
				return;
			}

		}
	}
	//再生中のアニメ更新
	if (m_nCountAnime != PlayerAnima)
	{
		//再生フレームを初期化
		m_nCountFrame = 0;
		//再生キーフレームを初期化
		m_nCountKeySet = 0;
		//アニメが再生されているか
		m_AnimatEnd = true;
	}
	//再生アニメ変更
	m_nCountAnime = PlayerAnima;
}

