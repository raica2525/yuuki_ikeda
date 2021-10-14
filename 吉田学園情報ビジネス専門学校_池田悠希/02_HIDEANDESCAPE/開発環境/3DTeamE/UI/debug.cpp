//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	debug.cpp
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#define _CRT_SECURE_NO_WARNINGS
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "debug.h"

#include <stdio.h>

#include "manager.h"
#include "renderer.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�ÓI�����o�ϐ��錾
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
LPD3DXFONT CDebug::m_pFont = NULL;
char CDebug::m_str[512]    = {};

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�R���X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CDebug::CDebug()
{
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�f�X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CDebug::~CDebug()
{
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//����������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
HRESULT CDebug::Init()
{
    //�t�H���g����
    D3DXCreateFont(CManager::GetRenderer()->GetDevice(), 50, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Arial Black", &m_pFont);
    return S_OK;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�\���ݒ菈��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CDebug::Print(char* const fmt, ...)
{
    va_list list;
    va_start(list, fmt);
    for(char* pointer = fmt; *pointer != '\0'; pointer++)
    {
        char str[256] = {};
        ZeroMemory(str, sizeof(str));
        switch(*pointer)
        {
            case '%':
                pointer++;    //�|�C���^������炷(1�����i�߂�)
                switch(*pointer)
                {
                    case 'd':
                        wsprintf(str, "%d", va_arg(list, int));
                        break;
                    case 'f':
                        wsprintf(str, "%f", va_arg(list, double));
                        break;
                    case 'c':
                        wsprintf(str, "%c", va_arg(list, char));
                        break;
                    case 's':
                        wsprintf(str, "%s", va_arg(list, const char*));
                        break;
                    case '%':
                        wsprintf(str, "%%");
                        break;
                    default:
                        break;
                }
                break;
            default:
                memcpy(str, pointer, 1);
                break;
        }
        strcat(m_str, str);
    }
    va_end(list);
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�`�揈��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CDebug::Draw(void)
{
    RECT rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    // �e�L�X�g�`��
    m_pFont->DrawText(NULL, m_str, -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
    ZeroMemory(m_str, sizeof(m_str));
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�I������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CDebug::Uninit(void)
{
    //�t�H���g�̊J��
    if(m_pFont != NULL)
    {
        m_pFont->Release();
        m_pFont = NULL;
    }
}
