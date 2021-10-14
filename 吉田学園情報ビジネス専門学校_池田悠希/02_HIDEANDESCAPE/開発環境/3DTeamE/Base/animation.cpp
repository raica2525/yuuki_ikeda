//=============================================================================
//
// �A�j���[�V�������� [animation.cpp]
// Author : ��K���E�g�c
//
//=============================================================================

//*****************************************************************************
// �x������
//*****************************************************************************
#define _CRT_SECURE_NO_WARNINGS
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "animation.h"
#include <stdio.h>
#include <stdlib.h>
//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
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
// �R���X�g���N�^
//=============================================================================
CAnimation::CAnimation(int nPriority)
{
	m_AnimationType = ANIMATION_NONE;		//�A�j���[�V�����^�C�v
	m_nCountAnime = -1;						//�Đ����̃A�j���[�V����
	m_nCountFrame = 0;						//�Đ����̃t���[��
	m_nCountKeySet = 0;						//�Đ����̃L�[�Z�b�g
	memset(&m_modelData, 0, sizeof(m_modelData));
	m_AnimatEnd = false;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CAnimation::~CAnimation()
{
}

//=============================================================================
// ���[�h����
//=============================================================================
HRESULT CAnimation::Load(void)
{
	for (int nCountAnima=0;nCountAnima<ANIMATION_MAX;nCountAnima++)
	{
		//�f�[�^���[�h�֐��̌Ăяo��
		DataLoad((ANIMATION_TYPE)nCountAnima);
	}

	return S_OK;
}

//=============================================================================
// �����֐�
//=============================================================================
CAnimation * CAnimation::Create(ANIMATION_TYPE AnimationType)
{
	CAnimation * pAnimation;
	pAnimation = new CAnimation;
	pAnimation->Init(AnimationType);
	return pAnimation;
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CAnimation::Init(ANIMATION_TYPE AnimationType)
{
	//�^�C�v�ǂݍ���
	m_AnimationType = AnimationType;
	return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CAnimation::Uninit(void)
{
	
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CAnimation::Update(void)
{
	if (m_AnimatEnd == true)
	{
		if (m_nCountFrame == 0)
		{
			//�A�j���[�V�����A�b�v�f�[�g
			for (int nAnime = 0; nAnime < MODEL_LABEL_MAX; nAnime++)
			{
				m_modelData[nAnime].rotMove = (m_animation[m_AnimationType][m_nCountAnime].keySet[m_nCountKeySet].key[nAnime].rot - m_modelData[nAnime].rot) / (float)m_animation[m_AnimationType][m_nCountAnime].keySet[m_nCountKeySet].frame;
				m_modelData[nAnime].posMove = (m_animation[m_AnimationType][m_nCountAnime].keySet[m_nCountKeySet].key[nAnime].pos - m_modelData[nAnime].pos) / (float)m_animation[m_AnimationType][m_nCountAnime].keySet[m_nCountKeySet].frame;
			}
		}
		//�A�j���[�V�����A�b�v�f�[�g
		for (int nAnime = 0; nAnime < MODEL_LABEL_MAX; nAnime++)
		{
			m_modelData[nAnime].rot += m_modelData[nAnime].rotMove;
			m_modelData[nAnime].pos += m_modelData[nAnime].posMove;
		}
	}
	//�t���[���J�E���g
	m_nCountFrame++;

	//���̒l�܂Ńt���[������������
	if (m_animation[m_AnimationType][m_nCountAnime].keySet[m_nCountKeySet].frame == m_nCountFrame)
	{
		//�t���[��������
		m_nCountFrame = 0;
		//�L�[�Z�b�g�X�V
		m_nCountKeySet+=1;

		//�L�[���ő�܂ł�������
		if (m_nCountKeySet == m_animation[m_AnimationType][m_nCountAnime].keyNum)
		{
			//�A�j�����I��
			m_AnimatEnd = false;

			//���[�v���������邩�A���Ȃ���
			if (m_animation[m_AnimationType][m_nCountAnime].isLoop == true)
			{
				//����ꍇ
				m_nCountKeySet = 0;
				m_AnimatEnd = true;
			}
		}
	}

}

//=============================================================================
//�@�f�[�^���[�h�֐�
//=============================================================================
void CAnimation::DataLoad(ANIMATION_TYPE AnimationType)
{

	int nAnimeKeySet = 0;					//�L�[�Z�b�g�ԍ�
	int nModelParts = 0;					//���f���p�[�c���
	int nAnimation = 0;						//�A�j���[�V�����ԍ�
	char cFileString[256];					//�ǂݍ��݃f�[�^
	memset(&cFileString, 0, sizeof(cFileString));
	//�t�@�C���I�[�v��
	m_pFile[AnimationType] = fopen(m_pFileName[AnimationType], "r");

	if (m_pFile[AnimationType] != NULL)
	{
		//���̃f�[�^�����I���܂œǂݍ���
		while (strcmp(cFileString, "END_SCRIPT") != 0)
		{
			//������
			memset(cFileString, 0, sizeof(cFileString));
			//�ǂݍ���
			fscanf(m_pFile[AnimationType],"%s", cFileString);

			//�����̔�r
			if (strcmp(cFileString,"MOTIONSET")==0)
			{
				while (strcmp(cFileString, "END_MOTIONSET") != 0)
				{
					//������
					memset(cFileString, 0, sizeof(cFileString));
					//�ǂݍ���
					fscanf(m_pFile[AnimationType], "%s", cFileString);

					//���[�v�m�F
					if (strcmp(cFileString, "LOOP") == 0)
					{
						int nBool;
						//�ǂݍ���
						fscanf(m_pFile[AnimationType], " = %d ", &nBool);
						//bool�m�F
						if (nBool != 0)
						{
							m_animation[AnimationType][nAnimation].isLoop = true;
						}
						else
						{
							m_animation[AnimationType][nAnimation].isLoop = false;
						}
					}
					//�L�[���m�F
					if (strcmp(cFileString, "NUM_KEY") == 0)
					{
						//�ǂݍ���
						fscanf(m_pFile[AnimationType], " = %d ", &m_animation[AnimationType][nAnimation].keyNum);
					}

					//�A�j���[�V�����L�[�Z�b�g���ǂݍ���
					if (strcmp(cFileString, "KEYSET") == 0)
					{
						//�p�[�c�̏����󂯎��I���܂�
						while (strcmp(cFileString, "END_KEYSET") != 0)
						{
							//������
							memset(cFileString, 0, sizeof(cFileString));
							//�ǂݍ���
							fscanf(m_pFile[AnimationType], "%s", cFileString);

							//�L�[�t���[����
							if (strcmp(cFileString, "FRAME") == 0)
							{
								//�ǂݍ���
								fscanf(m_pFile[AnimationType], " = %d ", &m_animation[AnimationType][nAnimation].keySet[nAnimeKeySet].frame);
							}
							//�A�j���[�V�����L�[���ǂݍ���
							if (strcmp(cFileString, "KEY") == 0)
							{
								while (strcmp(cFileString, "END_KEY") != 0)
								{
									//������
									memset(cFileString, 0, sizeof(cFileString));
									//�ǂݍ���
									fscanf(m_pFile[AnimationType], "%s", cFileString);
									//�p�[�c�̈ʒu���
									if (strcmp(cFileString, "POS") == 0)
									{
										//�ǂݍ���
										fscanf(m_pFile[AnimationType], " = %f %f %f",
											&m_animation[AnimationType][nAnimation].keySet[nAnimeKeySet].key[nModelParts].pos.x,
											&m_animation[AnimationType][nAnimation].keySet[nAnimeKeySet].key[nModelParts].pos.y,
											&m_animation[AnimationType][nAnimation].keySet[nAnimeKeySet].key[nModelParts].pos.z);
									}
									//�p�[�c�̌������
									if (strcmp(cFileString, "ROT") == 0)
									{
										//�ǂݍ���
										fscanf(m_pFile[AnimationType], " = %f %f %f",
											&m_animation[AnimationType][nAnimation].keySet[nAnimeKeySet].key[nModelParts].rot.x,
											&m_animation[AnimationType][nAnimation].keySet[nAnimeKeySet].key[nModelParts].rot.y,
											&m_animation[AnimationType][nAnimation].keySet[nAnimeKeySet].key[nModelParts].rot.z);
									}
								}
								nModelParts++;//�p�[�c�ԍ����Z
							}
						}
						nAnimeKeySet++;//���[�V�����ԍ����Z
						nModelParts = 0;
					}
				}
				nAnimation++;	//�A�j���[�V�����ԍ����Z
				nAnimeKeySet = 0;
				nModelParts = 0;
			}
		}
		fclose(m_pFile[AnimationType]);	//�t�@�C�������
	}
}


//=============================================================================
// �Z�b�g�A�j���[�V�����֐�
//=============================================================================
void CAnimation::SetAnimation(int PlayerAnima)
{
	//�v���C���[�̃����[�h�A�j���[�V��������
	if (PlayerAnima == MOTION_PLAYER_RELOAD
		|| PlayerAnima == MOTION_PLAYER_RELOAD_MOVE)
	{
		if (m_nCountAnime == MOTION_PLAYER_RELOAD
			|| m_nCountAnime == MOTION_PLAYER_RELOAD_MOVE)
		{
			if (m_nCountAnime != PlayerAnima)
			{
				//�Đ��t���[����������
				m_nCountFrame = 0;
				//�Đ��L�[�t���[����������
				m_nCountKeySet = m_nCountKeySet;
				//�Đ��A�j���ύX
				m_nCountAnime = PlayerAnima;
				return;
			}

		}
	}
	//�Đ����̃A�j���X�V
	if (m_nCountAnime != PlayerAnima)
	{
		//�Đ��t���[����������
		m_nCountFrame = 0;
		//�Đ��L�[�t���[����������
		m_nCountKeySet = 0;
		//�A�j�����Đ�����Ă��邩
		m_AnimatEnd = true;
	}
	//�Đ��A�j���ύX
	m_nCountAnime = PlayerAnima;
}

