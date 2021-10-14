//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
// scene.cpp
// Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "scene.h"
#include "renderer.h"
#include "scene2d.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�ÓI�����o�ϐ��錾
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CScene* CScene::m_apScene[PRIORITY_MAX][MAX_SCENE] = {};
int CScene::m_nNumAll                              = 0;

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�R���X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CScene::CScene(int nPriority)
{
    m_objType = OBJTYPE_NONE;
    for(int nCount = 0; nCount < MAX_SCENE; nCount++)
    {
        if(m_apScene[nPriority][nCount] == NULL)
        {
            m_apScene[nPriority][nCount] = this;    //�z��Ƀ|�C���^���i�[
            m_nPriority                  = nPriority;
            m_nNumScene                  = nCount;
            m_nNumAll++;    //�S�̂̃V�[�������C���N�������g
            break;
        }
    }
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�f�X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CScene::~CScene()
{
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�X�V����
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CScene::UpdateAll(void)
{
    for(int nCntPriority = PRIORITY_MAX - 1; nCntPriority >= 0; nCntPriority--)
    {
        for(int nCount = 0; nCount < MAX_SCENE; nCount++)
        {
            if(m_apScene[nCntPriority][nCount] != NULL)
            {
                m_apScene[nCntPriority][nCount]->Update();
            }
        }
    }
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�`�揈��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CScene::DrawAll(void)
{
    for(int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
    {
        for(int nCount = 0; nCount < MAX_SCENE; nCount++)
        {
            if(m_apScene[nCntPriority][nCount] != NULL)
            {
                m_apScene[nCntPriority][nCount]->Draw();
            }
        }
    }
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�S�J������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CScene::ReleaseAll(void)
{
    for(int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
    {
        for(int nCount = 0; nCount < MAX_SCENE; nCount++)
        {
            if(m_apScene[nCntPriority][nCount] != NULL)
            {
                m_apScene[nCntPriority][nCount]->Uninit();
                m_apScene[nCntPriority][nCount] = NULL;
            }
        }
    }
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�J������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CScene::Release(void)
{
    m_apScene[m_nPriority][m_nNumScene] = NULL;
    delete this;
    m_nNumAll--;    //�V�[�������f�N�������g
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�I�u�W�F�N�g�^�C�v�擾
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CScene::OBJTYPE CScene::GetObjType(void)
{
    return m_objType;
}
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�I�u�W�F�N�g�^�C�v�ݒ�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CScene::SetObjType(OBJTYPE type)
{
    m_objType = type;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�V�[���̐擪�|�C���^���擾
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CScene** CScene::GetScene(void)
{
    return &m_apScene[0][0];
}
