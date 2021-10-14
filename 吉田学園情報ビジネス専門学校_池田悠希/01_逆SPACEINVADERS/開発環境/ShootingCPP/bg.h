//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	bg.h
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

#ifndef _BG_H_
#define _BG_H_
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "main.h"
#include "scene.h"

class CScene2d;
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���X��`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CBg : public CScene
{
public:
    CBg();     //�R���X�g���N�^
    ~CBg();    //�f�X�g���N�^

    static HRESULT Load(void);
    static void Unload(void);
    static CBg* Create();    //�|���S����������

    HRESULT Init();       //����������
    void Uninit(void);    //�I������
    void Update(void);    //�X�V����
    void Draw(void);      //�`�揈��

private:
    CScene2d* m_apScene2d[NUM_BG_LAYER];
    static LPDIRECT3DTEXTURE9 m_apTexture[NUM_BG_LAYER];    // �e�N�X�`���ւ̃|�C���^
    D3DXVECTOR2 m_TexPos[NUM_BG_LAYER][NUM_VERTEX];
};

#endif
