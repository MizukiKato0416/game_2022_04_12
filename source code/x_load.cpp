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
	D3DXLoadMeshFromX("data/MODEL/player_01/00_player_body_01.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_PLAYER_BODY], NULL, &m_aNumMat[X_TYPE_PLAYER_BODY], &m_apMesh[X_TYPE_PLAYER_BODY]);

	//�v���C���[�̓�
	D3DXLoadMeshFromX("data/MODEL/player_01/01_player_head_01.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_PLAYER_HEAD], NULL, &m_aNumMat[X_TYPE_PLAYER_HEAD], &m_apMesh[X_TYPE_PLAYER_HEAD]);

	//�v���C���[�̉E��r
	D3DXLoadMeshFromX("data/MODEL/player_01/02_player_armR_01.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_PLAYER_ARM_R], NULL, &m_aNumMat[X_TYPE_PLAYER_ARM_R], &m_apMesh[X_TYPE_PLAYER_ARM_R]);

	//�v���C���[�̉E�r
	D3DXLoadMeshFromX("data/MODEL/player_01/03_player_frontarmR_01.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_PLAYER_FRONTARM_R], NULL, &m_aNumMat[X_TYPE_PLAYER_FRONTARM_R], &m_apMesh[X_TYPE_PLAYER_FRONTARM_R]);

	//�v���C���[�̉E��
	D3DXLoadMeshFromX("data/MODEL/player_01/04_player_handR_01.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_PLAYER_HAND_R], NULL, &m_aNumMat[X_TYPE_PLAYER_HAND_R], &m_apMesh[X_TYPE_PLAYER_HAND_R]);

	//�v���C���[�̍���r
	D3DXLoadMeshFromX("data/MODEL/player_01/05_player_armL_01.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_PLAYER_ARM_L], NULL, &m_aNumMat[X_TYPE_PLAYER_ARM_L], &m_apMesh[X_TYPE_PLAYER_ARM_L]);

	//�v���C���[�̍��r
	D3DXLoadMeshFromX("data/MODEL/player_01/06_player_frontarmL_01.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_PLAYER_FRONTARM_L], NULL, &m_aNumMat[X_TYPE_PLAYER_FRONTARM_L], &m_apMesh[X_TYPE_PLAYER_FRONTARM_L]);

	//�v���C���[�̍���
	D3DXLoadMeshFromX("data/MODEL/player_01/07_player_handL_01.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_PLAYER_HAND_L], NULL, &m_aNumMat[X_TYPE_PLAYER_HAND_L], &m_apMesh[X_TYPE_PLAYER_HAND_L]);

	//�v���C���[�̍�
	D3DXLoadMeshFromX("data/MODEL/player_01/08_player_waist_01.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_PLAYER_WAIST], NULL, &m_aNumMat[X_TYPE_PLAYER_WAIST], &m_apMesh[X_TYPE_PLAYER_WAIST]);

	//�v���C���[�̉E��
	D3DXLoadMeshFromX("data/MODEL/player_01/09_player_thighR_01.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_PLAYER_THIGH_R], NULL, &m_aNumMat[X_TYPE_PLAYER_THIGH_R], &m_apMesh[X_TYPE_PLAYER_THIGH_R]);

	//�v���C���[�̉E�r
	D3DXLoadMeshFromX("data/MODEL/player_01/10_player_legR_01.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_PLAYER_LEG_R], NULL, &m_aNumMat[X_TYPE_PLAYER_LEG_R], &m_apMesh[X_TYPE_PLAYER_LEG_R]);

	//�v���C���[�̉E��
	D3DXLoadMeshFromX("data/MODEL/player_01/11_player_footR_01.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_PLAYER_FOOT_R], NULL, &m_aNumMat[X_TYPE_PLAYER_FOOT_R], &m_apMesh[X_TYPE_PLAYER_FOOT_R]);

	//�v���C���[�̍���
	D3DXLoadMeshFromX("data/MODEL/player_01/12_player_thighL_01.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_PLAYER_THIGH_L], NULL, &m_aNumMat[X_TYPE_PLAYER_THIGH_L], &m_apMesh[X_TYPE_PLAYER_THIGH_L]);

	//�v���C���[�̍��r
	D3DXLoadMeshFromX("data/MODEL/player_01/13_player_legL_01.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_PLAYER_LEG_L], NULL, &m_aNumMat[X_TYPE_PLAYER_LEG_L], &m_apMesh[X_TYPE_PLAYER_LEG_L]);

	//�v���C���[�̍���
	D3DXLoadMeshFromX("data/MODEL/player_01/14_player_footL_01.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_PLAYER_FOOT_L], NULL, &m_aNumMat[X_TYPE_PLAYER_FOOT_L], &m_apMesh[X_TYPE_PLAYER_FOOT_L]);

	//�v���C���[�̌�
	D3DXLoadMeshFromX("data/MODEL/player_01/15_player_sword_01.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_PLAYER_SWORD], NULL, &m_aNumMat[X_TYPE_PLAYER_SWORD], &m_apMesh[X_TYPE_PLAYER_SWORD]);

	//��01
	D3DXLoadMeshFromX("data/MODEL/room/wall_01.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_WALL_01], NULL, &m_aNumMat[X_TYPE_WALL_01], &m_apMesh[X_TYPE_WALL_01]);

	//��01
	D3DXLoadMeshFromX("data/MODEL/room/piller_01.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_PILLER_01], NULL, &m_aNumMat[X_TYPE_PILLER_01], &m_apMesh[X_TYPE_PILLER_01]);

	//�I
	D3DXLoadMeshFromX("data/MODEL/enemy/bee.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_BEE], NULL, &m_aNumMat[X_TYPE_BEE], &m_apMesh[X_TYPE_BEE]);

	//���^�G�̑�
	D3DXLoadMeshFromX("data/MODEL/enemy_fat/00_enemy_fat_body.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_ENEMY_FAT_BODY], NULL, &m_aNumMat[X_TYPE_ENEMY_FAT_BODY], &m_apMesh[X_TYPE_ENEMY_FAT_BODY]);

	//���^�G�̓�
	D3DXLoadMeshFromX("data/MODEL/enemy_fat/01_enemy_fat_head.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_ENEMY_FAT_HEAD], NULL, &m_aNumMat[X_TYPE_ENEMY_FAT_HEAD], &m_apMesh[X_TYPE_ENEMY_FAT_HEAD]);

	//���^�G�̉E�r
	D3DXLoadMeshFromX("data/MODEL/enemy_fat/02_enemy_fat_armR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_ENEMY_FAT_ARM_R], NULL, &m_aNumMat[X_TYPE_ENEMY_FAT_ARM_R], &m_apMesh[X_TYPE_ENEMY_FAT_ARM_R]);

	//���^�G�̍��r
	D3DXLoadMeshFromX("data/MODEL/enemy_fat/03_enemy_fat_armL.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_ENEMY_FAT_ARM_L], NULL, &m_aNumMat[X_TYPE_ENEMY_FAT_ARM_L], &m_apMesh[X_TYPE_ENEMY_FAT_ARM_L]);

	//���^�G�̑�
	D3DXLoadMeshFromX("data/MODEL/enemy_fat/04_enemy_fat_leg.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_ENEMY_FAT_LEG], NULL, &m_aNumMat[X_TYPE_ENEMY_FAT_LEG], &m_apMesh[X_TYPE_ENEMY_FAT_LEG]);

	//�{�X�̑�
	D3DXLoadMeshFromX("data/MODEL/enemy_boss/00_enemy_boss_body.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_ENEMY_BOSS_BODY], NULL, &m_aNumMat[X_TYPE_ENEMY_BOSS_BODY], &m_apMesh[X_TYPE_ENEMY_BOSS_BODY]);

	//�{�X�̓�
	D3DXLoadMeshFromX("data/MODEL/enemy_boss/01_enemy_boss_head.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_ENEMY_BOSS_HEAD], NULL, &m_aNumMat[X_TYPE_ENEMY_BOSS_HEAD], &m_apMesh[X_TYPE_ENEMY_BOSS_HEAD]);

	//�{�X�̉E�r
	D3DXLoadMeshFromX("data/MODEL/enemy_boss/02_enemy_boss_armR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_ENEMY_BOSS_ARM_R], NULL, &m_aNumMat[X_TYPE_ENEMY_BOSS_ARM_R], &m_apMesh[X_TYPE_ENEMY_BOSS_ARM_R]);

	//�{�X�̍��r
	D3DXLoadMeshFromX("data/MODEL/enemy_boss/03_enemy_boss_armL.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_ENEMY_BOSS_ARM_L], NULL, &m_aNumMat[X_TYPE_ENEMY_BOSS_ARM_L], &m_apMesh[X_TYPE_ENEMY_BOSS_ARM_L]);

	//�{�X�̑�
	D3DXLoadMeshFromX("data/MODEL/enemy_boss/04_enemy_boss_leg.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_ENEMY_BOSS_LEG], NULL, &m_aNumMat[X_TYPE_ENEMY_BOSS_LEG], &m_apMesh[X_TYPE_ENEMY_BOSS_LEG]);
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
