//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	renderer.h
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "main.h"

class CRenderer
{
public:
    CRenderer();
    ~CRenderer();

    HRESULT Init(HWND hWnd, bool bWindow);
    void Uninit(void);
    void Update(void);
    void Draw(void);
    LPDIRECT3DDEVICE9 GetDevice(void)
    {
        return m_pD3DDevice;
    }

private:
#ifdef _DEBUG
    void DrawFPS(void);
#endif
    // void DrawRemain(void);

    LPDIRECT3D9 m_pD3D;                // Direct3D�I�u�W�F�N�g
    LPDIRECT3DDEVICE9 m_pD3DDevice;    // Device�I�u�W�F�N�g(�`��ɕK�v)
#ifdef _DEBUG
    LPD3DXFONT m_pFont;    // �t�H���g�ւ̃|�C���^
#endif
};

#endif
