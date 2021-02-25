//=============================================================================
//
// 音 [sound.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include <xaudio2.h>
//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CSound
{
public:
	//*****************************************************************************
	// サウンドファイル
	//*****************************************************************************
	typedef enum
	{
		SOUND_LABEL_BGM_TITLE = 0,		// 弾発射音
		SOUND_LABEL_BGM_MAP,
		SOUND_LABEL_BGM_LASTMAP,
		SOUND_LABEL_BGM_WEAPONSELECT,
		SOUND_LABEL_BGM_RESULT,
		SOUND_LABEL_BGM_CONTINUE,
		SOUND_LABEL_SE_TITLESTART,
		SOUND_LABEL_SE_BUTTONSELECT,
		SOUND_LABEL_SE_BUTTONPUSH,
		SOUND_LABEL_SE_ALARM,
		SOUND_LABEL_SE_MAPEXPLOSION,
		SOUND_LABEL_SE_KEYBOARD,
		SOUND_LABEL_SE_AIM,
		SOUND_LABEL_SE_ASSAULT,
		SOUND_LABEL_SE_MAGAZINESET,
		SOUND_LABEL_SE_MAGAZINEOUT,
		SOUND_LABEL_SE_SCREAM,
		SOUND_LABEL_SE_PLAYERDOWN,
		SOUND_LABEL_SE_TRAP,
		SOUND_LABEL_SE_EXCLAMATIONMARK,
		SOUND_LABEL_SE_QUESTION,
		SOUND_LABEL_SE_ENEMYATTACK,
		SOUND_LABEL_SE_HG,
		SOUND_LABEL_SE_HEAL,
		SOUND_LABEL_SE_AIR,
		SOUND_LABEL_MAX
	} SOUND_LABEL;

	CSound();
	~CSound();
	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);

private:
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
	//*****************************************************************************
	// パラメータ構造体定義
	//*****************************************************************************
	typedef struct
	{
		char *pFilename;	// ファイル名
		int nCntLoop;		// ループカウント
	} PARAM;
	IXAudio2 *m_pXAudio2;								// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice *m_pMasteringVoice;			// マスターボイス
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// ソースボイス
	BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// オーディオデータ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// オーディオデータサイズ
	static PARAM m_aParam[SOUND_LABEL_MAX];
};
#endif