//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	life.h
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

#ifndef _LIFE_H_
#define _LIFE_H_
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "main.h"
#include "scene.h"

class CPolygon;
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���X��`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CLife : public CScene
{
public:
    CLife();     //�R���X�g���N�^
    ~CLife();    //�f�X�g���N�^

    static CLife* Create();    //�|���S����������

    HRESULT Init();       //����������
    void Uninit(void);    //�I������
    void Update(void);    //�X�V����
    void Draw(void);      //�`�揈��

    void AddLife(int nLife);
    int GetLife(void);
    static HRESULT Load(void);
    static void Unload(void);

private:
    CPolygon* m_apPolygon[NUM_GAUGE_LAYER];
    int m_nLife;
    static LPDIRECT3DTEXTURE9 m_pTexture;
};

#endif
