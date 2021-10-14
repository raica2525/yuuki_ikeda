//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	input.h
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

#ifndef _FADE_H_
#define _FADE_H_
#include "main.h"
#include "manager.h"
#include "polygon.h"

// �t�F�[�h�̏��
class CFade : public CPolygon
{
public:
    CFade();
    ~CFade();
    typedef enum
    {
        FADE_NONE = 0,    // �����Ȃ����
        FADE_IN,          // �t�F�[�h�C������
        FADE_OUT,         // �t�F�[�h�A�E�g����
        FADE_MAX
    } FADE;

    // �v���g�^�C�v�錾
    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    void Draw(void);

    static CFade* Create(CManager::GAMEMODE modeNext);
    FADE GetFadePhase(void);
    static bool GetUse(void);

private:
    FADE m_fadePhase;                 // �t�F�[�h���
    CManager::GAMEMODE m_modeNext;    // ���̉�ʁi���[�h�j
    D3DXCOLOR m_colorFade;            // �t�F�[�h�F
    static bool m_bUse;
};
#endif
