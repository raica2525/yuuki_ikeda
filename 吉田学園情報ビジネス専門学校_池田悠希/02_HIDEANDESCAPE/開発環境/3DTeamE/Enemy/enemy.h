//=============================================================================
//
// �G [enemy.h]
// Author : ��K������
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "model.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TOUR_MAX 8	//���񂷂�ő�ʒu
//*****************************************************************************
// �O���錾
//*****************************************************************************
class CQuestion;
class CExclamationMark;
//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CEnemy :public CObject
{
public:

	//��ԃ^�C�v
	typedef enum
	{
		ENEMY_NONE = -1,
		ENEMY_TOUR,		//�ʏ�E����
		ENEMY_WARY,			//�x��
		ENEMY_FOUND,		//�v���C���[����
		ENEMY_MAX
	} ENEMY_MODE;

	typedef enum
	{
		STATE_NONE = -1,
		STATE_NORMAL,		//�ʏ�
		STATE_DAMAGE,		//�_���[�W��H�炤
		STATE_DEATH,		//�j�󂳂��
		STATE_MAX
	} ENEMY_STATE;

	CEnemy();
	virtual ~CEnemy();
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	void SetPos(D3DXVECTOR3(pos));
	void SetRot(D3DXVECTOR3(rot));
	void SetSize(D3DXVECTOR3(size));
	void SetTour(int nTour, D3DXVECTOR3(pos));
	void SetMode(ENEMY_MODE mode);
	void SetLife(int nLife);
	void SetState(ENEMY_STATE state);

	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }

	void Hit(int nDamage);
	void Attack(int nDamage);
	
	bool Tour(void);
	
	void Direction(D3DXVECTOR3(pos));	
	bool Search(const float fRangeDistance, const float fViesswingAngle);
	bool Found(void);
	BOOL CheckSearch(CModel::MODELDATA modeldata,float *fDistance);
	CModel *GetWorld(void) { return m_pModel; }
	ENEMY_MODE GetMode(void){ return m_Mode; }
	ENEMY_STATE GetState(void) { return m_State; }
	void SetQuestion(CQuestion * pQuestion);
	CQuestion *GetQuestion(void) { return m_pQuestion; }
	void SetExclamation(CExclamationMark * pExclamation);
	CExclamationMark *GetExclamation(void) { return m_pExclamation; }
private:
	void SubLife(int nSublife);	//�̗̓Z�b�g
	CModel* m_pModel;			//���f���|�C���^
	D3DXVECTOR3 m_pos;			//�ʒu
	D3DXVECTOR3 m_move;			//�ړ���
	D3DXVECTOR3 m_rot;			//����
	D3DXVECTOR3 m_size;			//�T�C�Y
	int m_nLife;				//�̗�
	ENEMY_MODE m_Mode;			//�G�l�~�[���[�h
	ENEMY_STATE m_State;		//�X�e�[�^���

	D3DXVECTOR3	m_TourPos[TOUR_MAX];			//����ʒu
	int m_TourMax;								//���񂷂�ʒu�̍ő吔
	int m_TourCount;							//���݂̏���ʒu
	CQuestion * m_pQuestion;
	CExclamationMark * m_pExclamation;
	int m_nAttack_SE;
};
#endif