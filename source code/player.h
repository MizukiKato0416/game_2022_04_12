//===========================================
//�v���C���[����
//Author:��������
//===========================================
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "object.h"

//�O���錾
class CModel;
class CMotionPlayer;

//================================================
//�}�N����`
//================================================
#define MAX_PLAYER_MODEL					(16)		//���f���̐�

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CPlayer : public CObject
{
public:

	//�����o�֐�
	CPlayer(CObject::PRIORITY Priority = CObject::PRIORITY::PLAYER);				//�R���X�g���N�^
	~CPlayer();												//�f�X�g���N�^

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	void SetModelPos(int nCntModel, D3DXVECTOR3 pos);								//���f���̈ʒu�ݒ菈��
	D3DXVECTOR3 GetModelPos(int nCntModel);											//���f���̈ʒu�擾����
	D3DXVECTOR3 GetRot(void) { return m_rot; }										//�v���C���[�̌����擾����
	void SetModelRot(int nCntModel, D3DXVECTOR3 rot);								//���f���̌����ݒ菈��
	D3DXVECTOR3 GetModelRot(int nCntModel);											//���f���̌����擾����
	void SetMove(D3DXVECTOR3 move) { m_move = move; }								//�ړ��ʐݒ菈��
	static void CPlayer::Collision(CObject *pSubjectObject, float fObjRadius);		//�����蔻�菈��
	bool CPlayer::CollisionOnly(CObject *pSubjectObject, float fObjRadius);			//�Փ˔���݂̂̏���

private:
	//�����o�֐�
	void Move(void);								//�ړ�����
	void Rotate(void);								//��]����
	void Jump(void);								//�W�����v����

	//�����o�ϐ�
	D3DXVECTOR3 m_pos;								//�ʒu
	D3DXVECTOR3 m_posOld;							//1�t���[���O�̈ʒu
	D3DXVECTOR3 m_move;								//�|���S���̈ړ���
	D3DXVECTOR3	m_size;								//�T�C�Y
	D3DXVECTOR3 m_rot;								//����
	CModel *m_apModel[MAX_PLAYER_MODEL];			//���f���̃|�C���^
	D3DXMATRIX m_mtxWorld;							//���[���h�}�g���b�N�X
	CModel *m_pParent;								//�e���f���ւ̃|�C���^
	CMotionPlayer *m_pMotionPlayer;					//���[�V�����v���C���[�̃|�C���^
	float m_fObjectiveRot;							//�ړI�̌���
	float m_fNumRot;								//������ς����
	bool m_bRotate;									//��]���Ă��邩�ǂ���
	bool m_bJump;									//�W�����v���Ă邩�ǂ���
	
};

#endif // !_PLAYER_H_