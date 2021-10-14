//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	renderer.h
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#ifndef _RENDERER_H_
#define _RENDERER_H_

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "main.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���X��`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CRenderer
{
public:
    CRenderer();
    ~CRenderer();

    HRESULT Init(HWND hWnd, bool bWindow);    //����������
    void Uninit(void);                        //�I������
    void Update(void);                        //�X�V����
    void Draw(void);                          //�`�揈��
    //�Q�b�^�[�֐�
    LPDIRECT3DDEVICE9 GetDevice(void);

private:
    LPDIRECT3D9 m_pD3D;                // Direct3D�I�u�W�F�N�g
    LPDIRECT3DDEVICE9 m_pD3DDevice;    // Device�I�u�W�F�N�g(�`��ɕK�v)
};

#endif
