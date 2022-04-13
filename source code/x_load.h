//=============================================================================
//x�t�@�C�����[�h����
//Author:��������
//=============================================================================
#ifndef _X_LOAD_H_
#define _X_LOAD_H_

//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "main.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CXload
{
public:
	//�^�C�v
	typedef enum
	{
		X_TYPE_PLAYER_BODY = 0,					//�v���C���[�̑�
		X_TYPE_PLAYER_HEAD,						//�v���C���[�̓�
		X_TYPE_PLAYER_ARM_R,					//�v���C���[�̉E��r
		X_TYPE_PLAYER_FRONTARM_R,				//�v���C���[�̉E�r
		X_TYPE_PLAYER_HAND_R,					//�v���C���[�̉E��
		X_TYPE_PLAYER_ARM_L,					//�v���C���[�̍���r
		X_TYPE_PLAYER_FRONTARM_L,				//�v���C���[�̍��r
		X_TYPE_PLAYER_HAND_L,					//�v���C���[�̍���
		X_TYPE_PLAYER_WAIST,					//�v���C���[�̍�
		X_TYPE_PLAYER_THIGH_R,					//�v���C���[�̉E��
		X_TYPE_PLAYER_LEG_R,					//�v���C���[�̉E�r
		X_TYPE_PLAYER_FOOT_R,					//�v���C���[�̉E��
		X_TYPE_PLAYER_THIGH_L,					//�v���C���[�̍���
		X_TYPE_PLAYER_LEG_L,					//�v���C���[�̍��r
		X_TYPE_PLAYER_FOOT_L,					//�v���C���[�̍���
		X_TYPE_PLAYER_SWORD,					//�v���C���[�̌�
		X_TYPE_WALL_01,							//��01
		X_TYPE_PILLER_01,						//��01
		X_TYPE_BEE,								//�I
		X_TYPE_ENEMY_FAT_BODY,					//���^�G�̑�
		X_TYPE_ENEMY_FAT_HEAD,					//���^�G�̓�
		X_TYPE_ENEMY_FAT_ARM_R,					//���^�G�̉E�r
		X_TYPE_ENEMY_FAT_ARM_L,					//���^�G�̍��r
		X_TYPE_ENEMY_FAT_LEG,					//���^�G�̑�
		X_TYPE_ENEMY_BOSS_BODY,					//�{�X�̑�
		X_TYPE_ENEMY_BOSS_HEAD,					//�{�X�̓�
		X_TYPE_ENEMY_BOSS_ARM_R,				//�{�X�̉E�r
		X_TYPE_ENEMY_BOSS_ARM_L,				//�{�X�̍��r
		X_TYPE_ENEMY_BOSS_LEG,					//�{�X�̑�
		X_TYPE_MAX								//�ő吔
	} X_TYPE;

	CXload();									//�R���X�g���N�^
	~CXload();									//�f�X�g���N�^

	void Init(void);									// �e�N�X�`���̐���
	LPD3DXMESH GetMesh(const X_TYPE &type);					// ���b�V���̊��蓖��
	LPD3DXBUFFER GetBuffMat(const X_TYPE &type);				// �}�e���A���̊��蓖��
	DWORD GetNumMat(const X_TYPE &type);						// �}�e���A�����̊��蓖��
	X_TYPE GetType(const int &nType) { return (X_TYPE)nType; }	// �^�C�v�擾����
	void Uninit(void);									// �I��
private:
	LPD3DXMESH m_apMesh[X_TYPE_MAX];			//���b�V��(���_���)�ւ̃|�C���^
	LPD3DXBUFFER m_apBuffMat[X_TYPE_MAX];		//�}�e���A��(�ގ����)�ւ̃|�C���^
	DWORD m_aNumMat[X_TYPE_MAX];				//�}�e���A����
};

#endif