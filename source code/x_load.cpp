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
//������
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

	//�v���C���[�K�[���̑�
	D3DXLoadMeshFromX("data/MODEL/player_01/girl_body.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_PLAYER_GIRL_BODY], NULL, &m_aNumMat[X_TYPE_PLAYER_GIRL_BODY], &m_apMesh[X_TYPE_PLAYER_GIRL_BODY]);

	//�v���C���[�K�[���̉E�r
	D3DXLoadMeshFromX("data/MODEL/player_01/girl_armR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_PLAYER_GIRL_ARM_R], NULL, &m_aNumMat[X_TYPE_PLAYER_GIRL_ARM_R], &m_apMesh[X_TYPE_PLAYER_GIRL_ARM_R]);

	//�v���C���[�K�[���̍��r
	D3DXLoadMeshFromX("data/MODEL/player_01/girl_armL.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_PLAYER_GIRL_ARM_L], NULL, &m_aNumMat[X_TYPE_PLAYER_GIRL_ARM_L], &m_apMesh[X_TYPE_PLAYER_GIRL_ARM_L]);

	//�v���C���[�K�[���̉E��
	D3DXLoadMeshFromX("data/MODEL/player_01/girl_legsR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_PLAYER_GIRL_LEG_R], NULL, &m_aNumMat[X_TYPE_PLAYER_GIRL_LEG_R], &m_apMesh[X_TYPE_PLAYER_GIRL_LEG_R]);

	//�v���C���[�K�[���̍���
	D3DXLoadMeshFromX("data/MODEL/player_01/girl_legsL.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_PLAYER_GIRL_LEG_L], NULL, &m_aNumMat[X_TYPE_PLAYER_GIRL_LEG_L], &m_apMesh[X_TYPE_PLAYER_GIRL_LEG_L]);

	//��
	D3DXLoadMeshFromX("data/MODEL/stage/thorn.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_THORN], NULL, &m_aNumMat[X_TYPE_THORN], &m_apMesh[X_TYPE_THORN]);

	//�_
	D3DXLoadMeshFromX("data/MODEL/stage/cloud.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_CLOUD], NULL, &m_aNumMat[X_TYPE_CLOUD], &m_apMesh[X_TYPE_CLOUD]);

	//���_
	D3DXLoadMeshFromX("data/MODEL/stage/cloud_gray.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_CLOUD_GRAY], NULL, &m_aNumMat[X_TYPE_CLOUD_GRAY], &m_apMesh[X_TYPE_CLOUD_GRAY]);

	//�n��
	D3DXLoadMeshFromX("data/MODEL/stage/road.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_GROUND], NULL, &m_aNumMat[X_TYPE_GROUND], &m_apMesh[X_TYPE_GROUND]);

	//�g�����|����
	D3DXLoadMeshFromX("data/MODEL/stage/trampoline.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_TRAMPLINE], NULL, &m_aNumMat[X_TYPE_TRAMPLINE], &m_apMesh[X_TYPE_TRAMPLINE]);

	//��@
	D3DXLoadMeshFromX("data/MODEL/stage/fan.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_FAN], NULL, &m_aNumMat[X_TYPE_FAN], &m_apMesh[X_TYPE_FAN]);

	//��s�@
	D3DXLoadMeshFromX("data/MODEL/stage/airplane.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_AIRPLANE], NULL, &m_aNumMat[X_TYPE_AIRPLANE], &m_apMesh[X_TYPE_AIRPLANE]);

	//�Z䊐�
	D3DXLoadMeshFromX("data/MODEL/stage/starring.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_STARRING], NULL, &m_aNumMat[X_TYPE_STARRING], &m_apMesh[X_TYPE_STARRING]);

	//���b�h�u��
	D3DXLoadMeshFromX("data/MODEL/stage/redbull.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_REDBULL], NULL, &m_aNumMat[X_TYPE_REDBULL], &m_apMesh[X_TYPE_REDBULL]);

	//�X�^�[�g�n�_
	D3DXLoadMeshFromX("data/MODEL/stage/start.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_START], NULL, &m_aNumMat[X_TYPE_START], &m_apMesh[X_TYPE_START]);

	//���P�b�g
	D3DXLoadMeshFromX("data/MODEL/stage/rocket.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_ROCKET], NULL, &m_aNumMat[X_TYPE_ROCKET], &m_apMesh[X_TYPE_ROCKET]);

	//�o�i�i
	D3DXLoadMeshFromX("data/MODEL/stage/banana.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_BANANA], NULL, &m_aNumMat[X_TYPE_BANANA], &m_apMesh[X_TYPE_BANANA]);
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
