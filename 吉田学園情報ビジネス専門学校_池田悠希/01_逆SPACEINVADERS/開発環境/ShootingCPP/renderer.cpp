//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	renderer.cpp
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"
#include "number.h"
#include "manager.h"
#include "title.h"
#include "result.h"
#include "fade.h"
#include "tutorial.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�R���X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CRenderer::CRenderer()
{
    m_pD3D       = NULL;
    m_pD3DDevice = NULL;
#ifdef _DEBUG
    m_pFont = NULL;
#endif
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�f�X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CRenderer::~CRenderer()
{
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//����������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
HRESULT CRenderer::Init(HWND hWnd, bool bWindow)
{
    D3DPRESENT_PARAMETERS d3dpp;
    D3DDISPLAYMODE d3ddm;

    // Direct3D�I�u�W�F�N�g�̍쐬
    m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
    if(m_pD3D == NULL)
    {
        return E_FAIL;
    }

    // ���݂̃f�B�X�v���C���[�h���擾
    if(FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
    {
        return E_FAIL;
    }

    // �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
    ZeroMemory(&d3dpp, sizeof(d3dpp));                                 // ���[�N���[���N���A
    d3dpp.BackBufferCount            = 1;                              // �o�b�N�o�b�t�@�̐�
    d3dpp.BackBufferWidth            = (int)SCREEN_WIDTH;              // �Q�[����ʃT�C�Y(��)
    d3dpp.BackBufferHeight           = (int)SCREEN_HEIGHT;             // �Q�[����ʃT�C�Y(����)
    d3dpp.BackBufferFormat           = d3ddm.Format;                   // �J���[���[�h�̎w��
    d3dpp.SwapEffect                 = D3DSWAPEFFECT_DISCARD;          // �f���M���ɓ������ăt���b�v����
    d3dpp.EnableAutoDepthStencil     = TRUE;                           // �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
    d3dpp.AutoDepthStencilFormat     = D3DFMT_D16;                     // �f�v�X�o�b�t�@�Ƃ���16bit���g��
    d3dpp.Windowed                   = bWindow;                        // �E�B���h�E���[�h
    d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;        // ���t���b�V�����[�g
    d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_DEFAULT;    // �C���^�[�o��

    // �f�o�C�X�̐���
    // �f�B�X�v���C�A�_�v�^��\�����߂̃f�o�C�X���쐬
    // �`��ƒ��_�������n�[�h�E�F�A�ōs�Ȃ�
    if(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice)))
    {
        // ��L�̐ݒ肪���s������
        // �`����n�[�h�E�F�A�ōs���A���_������CPU�ōs�Ȃ�
        if(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice)))
        {
            // ��L�̐ݒ肪���s������
            // �`��ƒ��_������CPU�ōs�Ȃ�
            if(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice)))
            {
                // �������s
                return E_FAIL;
            }
        }
    }

    // �����_�[�X�e�[�g�̐ݒ�
    m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);     //���ʂ��J�����O
    m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);    //�����x���g����
    m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);    //���f�X�e�B

    // �T���v���[�X�e�[�g�̐ݒ�
    m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_MIRROR);
    m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_MIRROR);
    m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);    //�h�b�g�G�̂Ƃ���D3DTEXF_POINT
    m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

    // �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
    m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
    m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
    m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
    srand((unsigned int)time(0));

#ifdef _DEBUG
    // �f�o�b�O���\���p�t�H���g�̐���
    D3DXCreateFont(m_pD3DDevice, 100, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pFont);
#endif

    return S_OK;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�I������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CRenderer::Uninit(void)
{

#ifdef _DEBUG
    // �f�o�b�O���\���p�t�H���g�̔j��
    if(m_pFont != NULL)
    {
        m_pFont->Release();
        m_pFont = NULL;
    }
#endif

    // �f�o�C�X�̔j��
    if(m_pD3DDevice != NULL)
    {
        m_pD3DDevice->Release();
        m_pD3DDevice = NULL;
    }

    // Direct3D�I�u�W�F�N�g�̔j��
    if(m_pD3D != NULL)
    {
        m_pD3D->Release();
        m_pD3D = NULL;
    }
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�X�V����
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CRenderer::Update(void)
{
    CTitle* pTitle       = CManager::GetTitle();
	CResult* pResult = CManager::GetResult();
	CTutorial* pTutorial = CManager::GetTutorial();

	//���݂̃Q�[�����[�h�ɉ����čX�V���������s
    switch(CManager::GetGamemode())
    {
        case CManager::GAMEMODE_TITLE:
            pTitle->Update();
            break;
        case CManager::GAMEMODE_TUTORIAL:
            pTutorial->Update();
            break;
        case CManager::GAMEMODE_MAIN:
            CScene::UpdateAll();
            break;
        case CManager::GAMEMODE_RESULT:
            pResult->Update();
            break;
    }
	//�t�F�[�h�����݂���Ȃ�i�t�F�[�h���Ȃ�j�X�V
    CFade* pFade = CManager::GetFade();
    if(pFade != NULL)
    {
        pFade->Update();
    }
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�`�揈��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CRenderer::Draw(void)
{
    // �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
    m_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);
    CTitle* pTitle       = CManager::GetTitle();
	CResult* pResult = CManager::GetResult();
	CTutorial* pTutorial = CManager::GetTutorial();

    // Direct3D�ɂ��`��̊J�n
    if(SUCCEEDED(m_pD3DDevice->BeginScene()))
    {
		//�Q�[�����[�h�ɂ���ĕ`�揈�������s
        switch(CManager::GetGamemode())
        {
            case CManager::GAMEMODE_TITLE:
                pTitle->Draw();
                break;
            case CManager::GAMEMODE_TUTORIAL:
                pTutorial->Draw();
                break;
            case CManager::GAMEMODE_MAIN:
                CScene::DrawAll();
                break;
            case CManager::GAMEMODE_RESULT:
                pResult->Draw();
                break;
        }

		//�t�F�[�h�����݂���Ȃ�t�F�[�h��`��
        CFade* pFade = CManager::GetFade();
        if(pFade != NULL)
        {
            pFade->Draw();
        }

#ifdef _DEBUG
        // FPS�\��
        DrawFPS();
#endif
        // Direct3D�ɂ��`��̏I��
        m_pD3DDevice->EndScene();
    }

    // �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
    m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

#ifdef _DEBUG
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//FPS�\��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CRenderer::DrawFPS(void)
{
    RECT rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    char str[256];

    wsprintf(str, "FPS:%d\n", GetFPS());

    // �e�L�X�g�`��
    m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}
#endif
