//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
// object.cpp
// Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "object.h"

#include "debug.h"
#include "object2d.h"
#include "renderer.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�ÓI�����o�ϐ��錾
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CObject* CObject::m_pTop[PRIORITY_MAX] = {};
CObject* CObject::m_pCur[PRIORITY_MAX] = {};

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�R���X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CObject::CObject(const int nPriority)
{
    //����������
    m_bDestroy       = false;
    bCollisionBullet = false;
    //���X�g�\���ɒǉ�
    m_nPriority = nPriority;
    if(m_pTop[nPriority] != NULL)
    {
        m_pCur[nPriority]->m_pNext = this;
    }
    else
    {
        m_pTop[nPriority] = this;
    }
    this->m_pPrev     = m_pCur[nPriority];
    this->m_pNext     = NULL;
    m_pCur[nPriority] = this;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�f�X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CObject::~CObject()
{
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�X�V����
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CObject::UpdateAll(void)
{
    CObject* pNext     = NULL;
    CObject* pNextBuff = NULL;
    int ObjectCount    = 0;
    //���X�g�Ɋ܂܂��I�u�W�F�N�g���X�V
    for(int nCount = 0; nCount < PRIORITY_MAX; nCount++)
    {
        if(m_pTop[nCount] == NULL)
        {
			continue;
        }

		pNext = m_pTop[nCount];
		while (pNext != NULL && !pNext->m_bDestroy)
		{
			pNextBuff = pNext->m_pNext;
			pNext->Update();
			pNext = pNextBuff;
			ObjectCount++;
		}
    }

    //���S�t���O�����Ă����E��
    for(int nCount = 0; nCount < PRIORITY_MAX; nCount++)
    {
		if (m_pTop[nCount] == NULL)
		{
			continue;
		}

        pNext = m_pTop[nCount];
        while(pNext != NULL)
        {
            pNextBuff = pNext->m_pNext;
            if(pNext->m_bDestroy == true)
            {
                pNext->Death();
            }
            pNext = pNextBuff;
        }
        
    }
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�`�揈��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CObject::DrawAll(void)
{
    CObject* pNext = NULL;
    for(int nCount = 0; nCount < PRIORITY_MAX; nCount++)
    {
		if (m_pTop[nCount] == NULL)
		{
			continue;
		}

        pNext = m_pTop[nCount];
        while(pNext != NULL)
        {
            pNext->Draw();
            pNext = pNext->m_pNext;
        }
        
    }
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�S�J������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CObject::ReleaseAll(void)
{
    CObject* pNext     = NULL;
    CObject* pNextBuff = NULL;
    for(int nCount = 0; nCount < PRIORITY_MAX; nCount++)
    {
		if (m_pTop[nCount] == NULL)
		{
			continue;
		}

        pNext = m_pTop[nCount];
        while(pNext != NULL)
        {
            pNextBuff = pNext->m_pNext;
            pNext->Uninit();
            delete pNext;
            pNext = pNextBuff;
        
		}

        m_pTop[nCount] = NULL;
        m_pCur[nCount] = NULL;
    }
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�J������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CObject::Release(void)
{
    //���S�t���O�𗧂Ă�
    m_bDestroy = true;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//���X�g����������Ď��g�������鏈��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CObject::Death(void)
{
    //������Ƃ��̏���
    if(this == m_pTop[m_nPriority])
    {
        m_pTop[m_nPriority] = m_pNext;
    }
    if(this == m_pCur[m_nPriority])
    {
        m_pCur[m_nPriority] = m_pPrev;
    }
    if(m_pNext != NULL)
    {
        m_pNext->m_pPrev = m_pPrev;
    }
    if(m_pPrev != NULL)
    {
        m_pPrev->m_pNext = m_pNext;
    }
    delete this;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�Z�b�^�[�֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CObject::SetObjType(const OBJTYPE type)
{
    m_objType = type;
}

void CObject::SetCollisionBullet(const bool bHit)
{
    bCollisionBullet = bHit;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�Q�b�^�[�֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CObject** CObject::GetTop(void)
{
    return m_pTop;
}

CObject* CObject::GetNext(void)
{
    return m_pNext;
}

CObject* CObject::GetPrev(void)
{
    return m_pPrev;
}

CObject::OBJTYPE CObject::GetObjType(void)
{
    return m_objType;
}

bool CObject::GetCollisionBullet(void)
{
    return bCollisionBullet;
}
