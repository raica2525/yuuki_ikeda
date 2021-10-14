//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	crosshair.h
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#ifndef _CROSSHAIR_H_
#define _CROSSHAIR_H_

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "main.h"
#include "object.h"
#include "object2d.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�}�N����`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#define CROSSHAIR_PARTS_COUNT (4)
#define MIN_SPREAD_WALK (80)
#define MIN_SPREAD_STOP (30)
#define ADD_SPREAD_HG (35.0f)
#define ADD_SPREAD_AR (25.0f)

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���X��`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CCrosshair : public CObject
{
public:
    CCrosshair();
    ~CCrosshair();

    HRESULT Init(void);    //����������
    void Uninit(void);     //�I������
    void Update(void);     //�X�V����
    void Draw(void);       //�`�揈��

    static CCrosshair* Create(float fMinSpread);    //��������

    static void Load(void);      //�e�N�X�`���ǂݍ��ݏ���
    static void Unload(void);    //�e�N�X�`���j��

    void AddSpread(float fValue);           //�g�U�ǉ�
    void SetMinSpread(float fMinSpread);    //�g�U�ŏ��l�ݒ�
    float GetSpread(void);                  //�g�U�擾

private:
    static LPDIRECT3DTEXTURE9 m_pTexture;              // �e�N�X�`���ւ̃|�C���^
    CObject2D* m_apObject2d[CROSSHAIR_PARTS_COUNT];    //�N���X�w�A�̃p�[�c�ւ̃|�C���^
    float m_fSpread;                                   //�g�U
    float m_fMinSpread;                                //�g�U�ŏ��l
};

#endif
