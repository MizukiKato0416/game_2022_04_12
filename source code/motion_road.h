//===========================================
//���[�V�����ǂݍ��ݏ���
//Author:��������
//===========================================
#ifndef _MOTION_ROAD_H_
#define _MOTION_ROAD_H_
#include "main.h"

//================================================
//�}�N����`
//================================================
#define MOTION_MAX_KEY_INFO	(128)	//�L�[�̏��̍ő�l

//================================================
//�\���̂̒�`
//================================================
//�L�[�̍\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 rot;	//����
} KEY;

//�L�[���̍\����
typedef struct
{
	int nFrame;						//�Đ��t���[��
	std::vector<KEY> aKey;			//�e���f���̃L�[�v�f(�p�[�c�̍ő吔)
} KEY_INFO;

//���[�V�������̍\����
typedef struct
{
	bool bLoop;										//���[�v���邩�ǂ���
	int nNumKey;									//�L�[�̑���
	KEY_INFO aKeyInfo[MOTION_MAX_KEY_INFO];			//�L�[�̏��
} MOTION_INFO;

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CMotionRoad
{
public:
	//���[�V�����������Ă���I�u�W�F�N�g�̎��
	typedef enum
	{
		MOTION_HAVE_TYPE_PLAYER = 0,				//�v���C���[
		MOTION_HAVE_TYPE_ENEMY_BEE,					//�I�^�̓G
		MOTION_HAVE_TYPE_ENEMY_FAT,					//���^�̓G
		MOTION_HAVE_TYPE_ENEMY_BOSS,				//�{�X�̓G
		MOTION_HAVE_TYPE_MAX
	} MOTION_HAVE_TYPE;

	//�v���C���[�̃��[�V�����̎��
	typedef enum
	{
		MOTION_PLAYER_TYPE_NEUTRAL = 0,		//�j���[�g����
		MOTION_PLAYER_TYPE_MOVE,			//�ړ�
		MOTION_PLAYER_TYPE_SLASH_01,		//�a��1
		MOTION_PLAYER_TYPE_SLASH_02,		//�a��2
		MOTION_PLAYER_TYPE_SLASH_03,		//�a��3
		MOTION_PLAYER_TYPE_SLASH_04,		//�a��4
		MOTION_PLAYER_TYPE_DAMAGE,			//��_���[�W
		MOTION_PLAYER_TYPE_SPECIAL,			//�K�E�Z1
		MOTION_PLAYER_TYPE_MAGIC_01,		//���@�U��1
		MOTION_PLAYER_TYPE_GUARD,			//�K�[�h
		MOTION_PLAYER_TYPE_MAX
	} MOTION_PLAYER_TYPE;

	CMotionRoad();			//�R���X�g���N�^
	~CMotionRoad();			//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	static CMotionRoad *Create(void);								//��������
	//���[�V�������擾����
	MOTION_INFO GetMotionInfo(const MOTION_HAVE_TYPE &motionHaveType, const int &nMotionType);
	//���[�V�������->�L�[���->�Đ��t���[���擾����
	int GetMotionKeyInfoFrame(const MOTION_HAVE_TYPE &motionHaveType, const int &nMotionType, const int &nCntKey);
	//���[�V�������->�L�[���->�ʒu�擾����
	D3DXVECTOR3 GetMotionKeyInfoPos(const MOTION_HAVE_TYPE &motionHaveType, const int &nMotionType, const int &nCntKey, const int &nCntModel);
	//���[�V�������->�L�[���->��]�擾����
	D3DXVECTOR3 GetMotionKeyInfoRot(const MOTION_HAVE_TYPE &motionHaveType, const int &nMotionType, const int &nCntKey, const int &nCntModel);
	//���[�V�������->�L�[���->�ʒu�Ɖ�]�ݒ菈��
	void SetMotionKeyInfoPosRot(const MOTION_HAVE_TYPE &motionHaveType, const int &nMotionType, const int &nCntKey, const int &nCntModel, const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot);

private:
	std::vector<MOTION_INFO> m_aInfo[MOTION_HAVE_TYPE_MAX];			//���[�V�������
};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_MOTION_ROAD_H_