//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	result.h
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

#ifndef _RESULT_H_
#define _RESULT_H_
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "main.h"
#include "polygon.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���X��`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CResult : public CPolygon
{
public:
    CResult();     //�R���X�g���N�^
    ~CResult();    //�f�X�g���N�^

    HRESULT Init(void);    //����������
    void Uninit(void);     //�I������
    void Draw(void);       //�`�揈��
    static HRESULT Load(void);
    static void Unload(void);

    static CResult* Create();    //�|���S����������
    void DrawRanking(void);
    void UpdateRanking(void);

private:
    static LPDIRECT3DTEXTURE9 m_pTexture;    // �e�N�X�`���ւ̃|�C���^
    LPD3DXFONT m_pFont;
    int m_nTopScore[MAX_RANKING];
    int m_nRank;
};

#endif
