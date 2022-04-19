//=============================================================================
//X�t�@�C���ǂݍ��ݏ���
//Author:��������
//=============================================================================
#include "x_load.h"
#include "renderer.h"
#include "manager.h"

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CXload::CXload()
{

}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CXload::~CXload()
{

}

//=============================================================================
//�e�N�X�`���̐���
//=============================================================================
void CXload::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X���擾����

	//X�t�@�C���ǂݍ���

	//�v���C���[�̑�
	D3DXLoadMeshFromX("data/MODEL/player_01/body.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_PLAYER_BODY], NULL, &m_aNumMat[X_TYPE_PLAYER_BODY], &m_apMesh[X_TYPE_PLAYER_BODY]);

	//�v���C���[�̉E�r
	D3DXLoadMeshFromX("data/MODEL/player_01/armR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_PLAYER_ARM_R], NULL, &m_aNumMat[X_TYPE_PLAYER_ARM_R], &m_apMesh[X_TYPE_PLAYER_ARM_R]);

	//�v���C���[�̍��r
	D3DXLoadMeshFromX("data/MODEL/player_01/armL.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_PLAYER_ARM_L], NULL, &m_aNumMat[X_TYPE_PLAYER_ARM_L], &m_apMesh[X_TYPE_PLAYER_ARM_L]);

	//�v���C���[�̉E��
	D3DXLoadMeshFromX("data/MODEL/player_01/legsR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_PLAYER_LEG_R], NULL, &m_aNumMat[X_TYPE_PLAYER_LEG_R], &m_apMesh[X_TYPE_PLAYER_LEG_R]);

	//�v���C���[�̍���
	D3DXLoadMeshFromX("data/MODEL/player_01/legsL.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_PLAYER_LEG_L], NULL, &m_aNumMat[X_TYPE_PLAYER_LEG_L], &m_apMesh[X_TYPE_PLAYER_LEG_L]);

	//�v���C���[�̍���
	D3DXLoadMeshFromX("data/MODEL/a.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_A], NULL, &m_aNumMat[X_TYPE_A], &m_apMesh[X_TYPE_A]);

	//�_
	D3DXLoadMeshFromX("data/MODEL/cloud.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_CLOUD], NULL, &m_aNumMat[X_TYPE_CLOUD], &m_apMesh[X_TYPE_CLOUD]);
}	

//=============================================================================
//�I��
//=============================================================================
void CXload::Uninit(void)
{
	for (int nCntXload = 0; nCntXload < X_TYPE_MAX; nCntXload++)
	{
		//���b�V���̔j��
		if (m_apMesh[nCntXload] != NULL)
		{
			m_apMesh[nCntXload]->Release();
			m_apMesh[nCntXload] = NULL;
		}

		//�}�e���A���̔j��
		if (m_apBuffMat[nCntXload] != NULL)
		{
			m_apBuffMat[nCntXload]->Release();
			m_apBuffMat[nCntXload] = NULL;
		}
	}
}

//=============================================================================
//���b�V���̊��蓖��
//=============================================================================
LPD3DXMESH CXload::GetMesh(const X_TYPE &type)
{
	return m_apMesh[type];
}

//=============================================================================
//�}�e���A�����蓖��
//=============================================================================
LPD3DXBUFFER CXload::GetBuffMat(const X_TYPE &type)
{
	return m_apBuffMat[type];
}

//=============================================================================
//�}�e���A�������蓖��
//=============================================================================
DWORD CXload::GetNumMat(const X_TYPE &type)
{
	return m_aNumMat[type];
}
