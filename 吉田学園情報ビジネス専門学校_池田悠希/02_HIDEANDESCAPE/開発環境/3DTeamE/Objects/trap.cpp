//=============================================================================
//
// �g���b�v���� [trap.cpp]
// Author : �g�c�I�l
//
//=============================================================================


//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "trap.h"
#include "explosion.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "sound.h"

//*****************************************************************************
//�@�ÓI�����o�ϐ��̏�����
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTrap::CTrap()
{
	m_Startpos = ZEROVECTOR3;
	m_Endpos = ZEROVECTOR3;
	m_pTexture = NULL;
	SetObjType(OBJTYPE_NONE);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTrap::~CTrap()
{
}

CTrap * CTrap::Create(D3DXVECTOR3 Startpos, D3DXVECTOR3 Endpos)
{
	CTrap* pTrap = NULL;
	pTrap = new CTrap;
	pTrap->m_Startpos = Startpos;
	pTrap->m_Endpos = Endpos;
	pTrap->SetPos((Startpos + Endpos) / 2);
	pTrap->SetRot(D3DXVECTOR3(90.0f, D3DXToDegree(atan2f((Startpos.x - Endpos.x), (Startpos.z - Endpos.z))), 0.0f));
	pTrap->SetSize(D3DXVECTOR3(1.0f, sqrtf(((Startpos.x - Endpos.x)*(Startpos.x - Endpos.x)) + ((Startpos.z - Endpos.z)*(Startpos.z - Endpos.z))), 1.0f));
	for (int nMesh = 0; nMesh < MESH_Y_BLOCK + 1; nMesh++)
	{
		pTrap->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f - (nMesh*0.1f)), nMesh);
	}
	pTrap->Init();
	return pTrap;
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CTrap::Init(void)
{
	CMeshCylinder::Init();
	return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CTrap::Uninit(void)
{
	CMeshCylinder::Uninit();
	Release();
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CTrap::Update(void)
{
	CObject* pTop[PRIORITY_MAX] = {};
	CObject* pNext = NULL;
	CSound* pSound = CManager::GetSound();              //�T�E���h�̎擾
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		//���X�g�g�b�v�擾
		pTop[nCount] = *(CObject::GetTop() + nCount);
	}

	//����
	float fDistanve;
	//NULL�`�F�b�N
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		//NULL�`�F�b�N
		if (pTop[nCount] != NULL)
		{
			pNext = pTop[nCount];
			while (pNext != NULL)
			{
				//�I�u�W�F�N�g�^�C�v�`�F�b�N
				if (pNext->GetObjType() == OBJTYPE_MODEL)
				{
					//NULL�`�F�b�N
					if (((CModel *)pNext)->GetParentObject() != NULL)
					{
						if (((CModel*)pNext)->GetParentObject()->GetObjType() == OBJTYPE_PLAYER)
						{
							if (Search(((CModel*)pNext)->GetModelData(), fDistanve) == TRUE)
							{
								if (GetSize().y>fDistanve)
								{
									//���j
									CExplosion::Create(D3DXVECTOR3(CManager::GetPlayer()->GetPos().x, CManager::GetPlayer()->GetPos().y + 30, CManager::GetPlayer()->GetPos().z), ZEROVECTOR3, D3DXVECTOR3(100, 100, 100));

									//�v���C���[�_���[�W
									CManager::GetPlayer()->AddLife(-45);

									//�I������
									Uninit();
								}
							}
						}
					}
				}
				//���̑Ώۂ�ǂݍ���
				pNext = pNext->GetNext();
			}
		}
	}
	CMeshCylinder::Update();

}

//=============================================================================
// �`��֐�
//=============================================================================
void CTrap::Draw(void)
{
	CMeshCylinder::Draw();
}

//=============================================================================
// ���m�֐�
//=============================================================================
BOOL CTrap::Search(CModel::MODELDATA modeldata, float &fDistanve)
{
	BOOL bSearch = FALSE;					//�������Ă��邩
	D3DXMATRIX mtxWorld;
	D3DXMATRIX InversedWorldMatrix;	//�t��p�}�g���b�N�X
	D3DXVECTOR3 TransformedPos, NormalizedVec, TranceformedVec;

	//�P�ʃx�N�g���ɕϊ�
	D3DXVec3Normalize(&NormalizedVec, &(m_Endpos - m_Startpos));
	//�t�s�񐶐�
	D3DXMatrixInverse(&InversedWorldMatrix, NULL, &modeldata.mtxWorld);
	//�t�s��ŕϊ�
	D3DXVec3TransformCoord(&TransformedPos, &m_Startpos, &InversedWorldMatrix);
	D3DXVec3TransformNormal(&TranceformedVec, &NormalizedVec, &InversedWorldMatrix);
	//�����蔻����m�F
	D3DXIntersect(modeldata.pMesh, &TransformedPos, &TranceformedVec, &bSearch, NULL, NULL, NULL, &fDistanve, NULL, NULL);
	return bSearch;

}


