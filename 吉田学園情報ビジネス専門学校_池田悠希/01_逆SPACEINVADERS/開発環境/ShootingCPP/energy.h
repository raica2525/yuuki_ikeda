//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	energy.h
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

#ifndef _ENERGY_H_
#define _ENERGY_H_
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "main.h"
#include "scene.h"

class CPolygon;
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���X��`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CEnergy : public CScene
{
public:
    CEnergy();     //�R���X�g���N�^
    ~CEnergy();    //�f�X�g���N�^

    typedef enum
    {
        MODE_NORMAL = 0,
        MODE_OVERHEAT,
        MODE_MAX
    } MODE;
    static CEnergy* Create();    //�|���S����������

    HRESULT Init();       //����������
    void Uninit(void);    //�I������
    void Update(void);    //�X�V����
    void Draw(void);      //�`�揈��
    int GetEnergy(void);
    void ReduceEnergy(int nValue);
    static HRESULT Load(void);
    static void Unload(void);

private:
    CPolygon* m_apPolygon[NUM_GAUGE_LAYER];
    int m_nEnergy;
    MODE m_mode;
    static LPDIRECT3DTEXTURE9 m_pTexture;
};

#endif
