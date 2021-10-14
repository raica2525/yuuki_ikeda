//=============================================================================
//
// �� [sound.h]
// Author : ��K������
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include <xaudio2.h>
//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CSound
{
public:
	//*****************************************************************************
	// �T�E���h�t�@�C��
	//*****************************************************************************
	typedef enum
	{
		SOUND_LABEL_BGM_TITLE = 0,		// �e���ˉ�
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
	// �p�����[�^�\���̒�`
	//*****************************************************************************
	typedef struct
	{
		char *pFilename;	// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g
	} PARAM;
	IXAudio2 *m_pXAudio2;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice;			// �}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// �\�[�X�{�C�X
	BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^�T�C�Y
	static PARAM m_aParam[SOUND_LABEL_MAX];
};
#endif