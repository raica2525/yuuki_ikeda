//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	light.cpp
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "light.h"

#include "main.h"
#include "manager.h"
#include "renderer.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�R���X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CLight::CLight()
{
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�f�X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CLight::~CLight()
{
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//����������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CLight::Init(void)
{
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();    //�f�o�C�X�ւ̃|�C���^

    D3DXVECTOR3 vecDir;    //���C�g�̕����x�N�g��
    //���C�g���N���A����
    ZeroMemory(&m_light, sizeof(D3DLIGHT9));
    //���C�g�̎�ނ�ݒ�
    m_light.Type = D3DLIGHT_DIRECTIONAL;
    //���C�g�̊g�U����ݒ�
    m_light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
    m_light.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
    //���C�g�̕�����ݒ�
    vecDir = D3DXVECTOR3(0.2f, -0.8f, -0.4f);
    D3DXVec3Normalize(&vecDir, &vecDir);    //���K������
    m_light.Direction = vecDir;
    //���C�g��ݒ肷��
    pDevice->SetLight(0, &m_light);
    //���C�g��L���ɂ���
    pDevice->LightEnable(0, TRUE);
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�I������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CLight::Uninit(void)
{
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�X�V����
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CLight::Update(void)
{
}
