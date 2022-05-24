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
		X_TYPE_PLAYER_ARM_R,					//�v���C���[�̉E�r
		X_TYPE_PLAYER_ARM_L,					//�v���C���[�̍��r
		X_TYPE_PLAYER_LEG_R,					//�v���C���[�̉E��
		X_TYPE_PLAYER_LEG_L,					//�v���C���[�̍���
		X_TYPE_PLAYER_GIRL_BODY,				//�v���C���[�K�[���̑�
		X_TYPE_PLAYER_GIRL_ARM_R,				//�v���C���[�K�[���̉E�r
		X_TYPE_PLAYER_GIRL_ARM_L,				//�v���C���[�K�[���̍��r
		X_TYPE_PLAYER_GIRL_LEG_R,				//�v���C���[�K�[���̉E��
		X_TYPE_PLAYER_GIRL_LEG_L,				//�v���C���[�K�[���̍���
		X_TYPE_THORN,							//��
		X_TYPE_CLOUD,							//�_
		X_TYPE_CLOUD_GRAY,						//���_
		X_TYPE_GROUND,							//�n��
		X_TYPE_TRAMPLINE,						//�g�����|����
		X_TYPE_FAN,								//��@
		X_TYPE_AIRPLANE,						//��s�@
		X_TYPE_STARRING,						//�Z䊐�
		X_TYPE_REDBULL,							//���b�h�u��
		X_TYPE_START,							//�X�^�[�g�n�_
		X_TYPE_ROCKET,							//���P�b�g
		X_TYPE_BANANA,							//�o�i�i
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