//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	item.cpp
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "item.h"

#include "inputkeyboard.h"
#include "inputmouse.h"
#include "main.h"
#include "manager.h"
#include "player.h"
#include "renderer.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�}�N����`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#define ITEM_MODEL_SIZE (0.05f)
#define ITEM_OBTAIN_RANGE (20.0f)
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�ÓI�����o�ϐ��錾
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CModel::MODELDATA CItem::m_modelData = {};

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�R���X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CItem::CItem()
{
    m_fFrameCounter = 0.0f;
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
    CModel::Init();
    //���f���̊���
    BindModel(m_modelData);
    return S_OK;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�I������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CItem::Uninit(void)
{
    //���f���̔j��
    CModel::Uninit();
    Release();
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�X�V����
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CItem::Update(void)
{
    CPlayer* pPlayer      = CManager::GetPlayer();
    D3DXVECTOR3 playerPos = pPlayer->GetPos();
    D3DXVECTOR3 pos       = GetPos();
    //���������ɂӂ�ӂ킳���鏈��
    m_fFrameCounter += 0.05f;
    SetRot(GetRot() + D3DXVECTOR3(0.0f, D3DXToRadian(1.0f), 0.0f));
    SetPos(pos + D3DXVECTOR3(0.0f, sinf(m_fFrameCounter) / 5.0f, 0.0f));
    CModel::Update();

    // y���W�𖳎�����
    playerPos.y = pos.y = 0.0f;
    //��苗���܂ŋ߂Â�����A�C�e������肷�鏈��
    if(D3DXVec3Length(&(playerPos - pos)) < ITEM_OBTAIN_RANGE)
    {
        //���肵���Ƃ��̏���
        pPlayer->AddItem();
        Uninit();
    }
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�`�揈��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CItem::Draw(void)
{
    CModel::Draw();
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���G�C�g�֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CItem* CItem::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
    // �������̊m��
    CItem* pItem = new CItem;
    //�e����̐ݒ�
    pItem->SetPos(pos);
    pItem->SetRot(rot);
    pItem->SetSize(D3DXVECTOR3(ITEM_MODEL_SIZE, ITEM_MODEL_SIZE, ITEM_MODEL_SIZE));
    // ����������
    pItem->Init();

    return pItem;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//���f���ǂݍ���
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CItem::Load(void)
{
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
    D3DXLoadMeshFromX("Data\\Model\\Kaihuku.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_modelData.pBuffMat, NULL, &m_modelData.nNumMat, &m_modelData.pMesh);
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//���f���j��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CItem::Unload(void)
{
    //���b�V���̔j��
    if(m_modelData.pMesh != NULL)
    {
        m_modelData.pMesh->Release();
    }
    //�}�e���A���̔j��
    if(m_modelData.pBuffMat != NULL)
    {
        m_modelData.pBuffMat->Release();
    }
	ZeroMemory(&m_modelData, sizeof(m_modelData));
}
