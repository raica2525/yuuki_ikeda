//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	item.cpp
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "item.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "score.h"
#include "bullet.h"
#include "player.h"
#include "life.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�ÓI�����o�ϐ��錾
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
LPDIRECT3DTEXTURE9 CItem::m_apTexture[TYPE_MAX] = {};

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�R���X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CItem::CItem() : CScene2d(2)
{
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�f�X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CItem::~CItem()
{
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//����������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
HRESULT CItem::Init(void)
{
    CScene2d::Init();
	//�e�N�X�`������
    BindTexture(m_apTexture[m_type]);

    return S_OK;
}
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�I������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CItem::Uninit(void)
{
    CScene2d::Uninit();
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�X�V����
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CItem::Update(void)
{
	//�V�[���擾
    CScene** pScene       = GetScene();
	//�擾���ꂽ��
    bool bGet             = false;
	//��ʏ�̍��W���擾
    D3DXVECTOR3 screenPos = GetPos();

	//�v���C���[�̃|�C���^��T��
    for(int nCount = 0; nCount < MAX_SCENE * PRIORITY_MAX; nCount++)
    {
        if((*(pScene + nCount)) != NULL)
        {
            if((*(pScene + nCount))->GetObjType() == OBJTYPE_PLAYER)
            {
				//�v���C���[�̍��W�擾
                D3DXVECTOR3 PlayerPos = ((CPlayer*)(*(pScene + nCount)))->GetPos();
				//�v���C���[�Əd�Ȃ��Ă����
                if(screenPos.x + (ITEM_SIZE / 2) > PlayerPos.x - (PLAYER_SIZE_X / 2) && screenPos.x - (ITEM_SIZE / 2) < PlayerPos.x + (PLAYER_SIZE_X / 2) 
					&& screenPos.y + (ITEM_SIZE / 2) > PlayerPos.y - (PLAYER_SIZE_Y / 2)&& screenPos.y - (ITEM_SIZE / 2) < PlayerPos.y + (PLAYER_SIZE_Y / 2))
                {
					//�v���C���[�̃��C�t�𑝂₷
                    ((CPlayer*)(*(pScene + nCount)))->GetLife()->AddLife(30);
                    bGet = true;
                }
            }
        }
    }
    CScene2d::Update();
	//�擾����Ă���Ώ���
    if(bGet)
    {
        Uninit();
    }
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�`�揈��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CItem::Draw(void)
{
    CScene2d::Draw();
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���G�C�g�֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CItem::Create(D3DXVECTOR3 pos, TYPE type)
{
	//�������m��
    CItem* pItem = new CItem; 
	//�e����ݒ�
    pItem->SetWorldPos(pos);
    pItem->SetSize(D3DXVECTOR3(ITEM_SIZE, ITEM_SIZE, 0));
    pItem->SetObjType(OBJTYPE_ITEM);
    pItem->m_type = type;
	//�����֐�
    pItem->Init();
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�t�@�C���ǂݍ��ݏ���
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
HRESULT CItem::Load(void)
{
    D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "Resources\\item01.png", &m_apTexture[TYPE_LIFE]);
    return S_OK;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�ǂݍ��݃f�[�^�j������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CItem::Unload(void)
{
	//�e�N�X�`���j��
    for(int nCount = 0; nCount < TYPE_MAX; nCount++)
    {
        if(m_apTexture[nCount] != NULL)
        {
            m_apTexture[nCount]->Release();
            m_apTexture[nCount] = NULL;
        }
    }
}
