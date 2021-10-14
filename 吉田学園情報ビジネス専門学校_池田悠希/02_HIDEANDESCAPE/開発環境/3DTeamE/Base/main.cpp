//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	main.cpp
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "main.h"

#include "manager.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�}�N����`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#define WINDOW_NAME "HIDE and ESCAPE"    // �E�C���h�E�̃L���v�V������

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�v���g�^�C�v�錾
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�O���[�o���ϐ�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
LPDIRECT3D9 g_pD3D             = NULL;    // Direct3D�I�u�W�F�N�g
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;    // Device�I�u�W�F�N�g(�`��ɕK�v)

#ifdef _DEBUG
LPD3DXFONT g_pFont = NULL;    // �t�H���g�ւ̃|�C���^
int g_nCountFPS;              // FPS�J�E���^
#endif

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//���C���֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    CManager* pManager = NULL;    //�}�l�[�W���̃|�C���^
    WNDCLASSEX wcex =
      {
        sizeof(WNDCLASSEX),
        CS_CLASSDC,
        WndProc,
        0,
        0,
        hInstance,
        NULL,
        LoadCursor(NULL, IDC_ARROW),
        (HBRUSH)(COLOR_WINDOW + 1),
        NULL,
        CLASS_NAME,
        NULL};
    RECT rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    HWND hWnd;
    MSG msg;
    DWORD dwCurrentTime;
    DWORD dwFrameCount;
    DWORD dwExecLastTime;
    DWORD dwFPSLastTime;

    // �E�B���h�E�N���X�̓o�^
    RegisterClassEx(&wcex);

    // �w�肵���N���C�A���g�̈���m�ۂ��邽�߂ɕK�v�ȃE�B���h�E���W���v�Z
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

    // �E�B���h�E�̍쐬
    hWnd = CreateWindow(CLASS_NAME,
                        WINDOW_NAME,
                        WS_VISIBLE | WS_POPUP,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        (rect.right - rect.left),
                        (rect.bottom - rect.top),
                        NULL,
                        NULL,
                        hInstance,
                        NULL);
    //����������
    pManager = new CManager;
    pManager->Init(hWnd, true, hInstance);

    // ����\��ݒ�
    timeBeginPeriod(1);

    // �t���[���J�E���g������
    dwCurrentTime =
      dwFrameCount = 0;
    dwExecLastTime =
      dwFPSLastTime = timeGetTime();

    // �E�C���h�E�̕\��
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    // ���b�Z�[�W���[�v
    while(1)
    {
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if(msg.message == WM_QUIT)
            {    // PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
                break;
            }
            else
            {
                // ���b�Z�[�W�̖|��ƃf�B�X�p�b�`
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            dwCurrentTime = timeGetTime();    // ���݂̎��Ԃ��擾
            if((dwCurrentTime - dwFPSLastTime) >= 500)
            {    // 0.5�b���ƂɎ��s
#ifdef _DEBUG
                // FPS���Z�o
                g_nCountFPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);
#endif
                dwFPSLastTime = dwCurrentTime;    // ���݂̎��Ԃ�ۑ�
                dwFrameCount  = 0;
            }

            if((dwCurrentTime - dwExecLastTime) >= (1000 / 60) && GetActiveWindow() == hWnd)
            {                                      // 1/60�b�o��
                dwExecLastTime = dwCurrentTime;    // ���݂̎��Ԃ�ۑ�

                // �X�V����
                pManager->Update();

                // �`�揈��
                pManager->Draw();

                dwFrameCount++;
            }
        }
    }

    // �I������
    if(pManager != NULL)
        pManager->Uninit();
    delete pManager;
    pManager = NULL;

    // �E�B���h�E�N���X�̓o�^������
    UnregisterClass(CLASS_NAME, wcex.hInstance);

    // ����\��߂�
    timeEndPeriod(1);

    return (int)msg.wParam;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�E�B���h�E�v���V�[�W��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_CREATE:
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            break;
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//FPS�擾
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#ifdef _DEBUG
int GetFPS(void)
{
    return g_nCountFPS;
}
#endif
