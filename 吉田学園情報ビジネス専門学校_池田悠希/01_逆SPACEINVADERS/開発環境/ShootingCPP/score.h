//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	score.h
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

#ifndef _SCORE_H_
#define _SCORE_H_
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "main.h"
#include "scene.h"

class CNumber;
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���X��`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CScore : public CScene
{
public:
    CScore();     //�R���X�g���N�^
    ~CScore();    //�f�X�g���N�^

    static CScore* Create();    //�|���S����������

    HRESULT Init();       //����������
    void Uninit(void);    //�I������
    void Update(void);    //�X�V����
    void Draw(void);      //�`�揈��

    void SetScore(int nScore);
    void AddScore(int nScore);
    int GetScore(void);

private:
    CNumber* m_apNumber[DIGIT_SCORE];
    int m_nScore;
};

#endif
