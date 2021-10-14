//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	countdown.h
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#ifndef _COUNTDOWN_H_
#define _COUNTDOWN_H_
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "object2d.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�}�N����`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#define TIME_SIZE_X (200.0f)
#define TIME_SIZE_Y (100.0f)
#define DIGIT_NUM (5)
#define DIGIT_NUM_INT (2)
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�O���錾
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CNumber;

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���X��`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

class CCountDown : public CObject
{
public:
    CCountDown();
    ~CCountDown();

    HRESULT Init(void);    //����������
    void Uninit(void);     //�I������
    void Update(void);     //�X�V����
    void Draw(void);       //�`�揈��

    static CCountDown* Create(int nLimitTime, D3DXVECTOR3 pos, D3DXVECTOR3 size);    //��������

    static HRESULT Load(void);    //�e�N�X�`���Ǎ�
    static void Unload(void);     //�e�N�X�`���j��

private:
    static LPDIRECT3DTEXTURE9 m_pTexture;    // �e�N�X�`���ւ̃|�C���^
    int m_nTimeLimit;                        //���Ԑ���
    int m_nElapsedTime;                      //�o�ߎ���
    int m_nSoundCount;                       //�Đ�����Ă��鉹���̐�
    D3DXVECTOR3 m_pos;                       //���W
    D3DXVECTOR3 m_size;                      //�T�C�Y
    D3DCOLOR m_col;                          //�F
    CNumber* m_apNumber[DIGIT_NUM];          //�����̃|�C���^
    CObject2D* m_pObject2d;                  //�w�i�̃|�C���^
};
#endif
