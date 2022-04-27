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
class CSparkle;

//================================================
//�}�N����`
//================================================
#define MAX_PLAYER_MODEL					(5)			//���f���̐�
#define PLAYER_SHOT_MOVE					(40.0f)		//�v���C���[���O�ɐi�ރX�s�[�h

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
	static CPlayer *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot);

	void SetModelPos(const int &nCntModel, const D3DXVECTOR3 &pos);							//���f���̈ʒu�ݒ菈��
	D3DXVECTOR3 GetModelPos(const int &nCntModel);											//���f���̈ʒu�擾����
	D3DXVECTOR3 GetRot(void) { return m_rot; }												//�v���C���[�̌����擾����
	void SetRot(D3DXVECTOR3 &rot) { m_rot = rot; }											//�v���C���[�̌����ݒ菈��
	void SetModelRot(const int &nCntModel, const D3DXVECTOR3 &rot);							//���f���̌����ݒ菈��
	D3DXVECTOR3 GetModelRot(const int &nCntModel);											//���f���̌����擾����
	void SetMove(const D3DXVECTOR3 &move) { m_move = move; }								//�ړ��ʐݒ菈��
	D3DXVECTOR3 GetMove(void) { return m_move; }											//�ړ��ʎ擾����
	static void CPlayer::Collision(CObject *&pSubjectObject, const float &fObjRadius);		//�����蔻�菈��
	bool CPlayer::CollisionOnly(CObject *&pSubjectObject, const float &fObjRadius);			//�Փ˔���݂̂̏���
	bool GetShot(void) { return m_bShot; }													//���ˎ擾����
	void SetShot(bool bShot) { m_bShot = bShot; }											//���ːݒ菈��
	float GetMoveForward(void) { return m_fMoveForward; }									//�O�ɐi�ޗ͎擾����
	void SetMoveForward(const float &fMoveForward);											//�O�ɐi�ޗ͐ݒ菈��
	float GetJump(void) { return m_fJump; }													//�W�����v�͎擾����
	void SetJump(const float &fJump);														//�W�����v�͐ݒ菈��
	float GetBoundMove(void) { return m_fBoundMove; }										//�o�E���h����u�Ԃ̈ړ��ʎ擾����
	void SetBoundMove(const float &fBoundMove) { m_fBoundMove = fBoundMove; }				//�o�E���h����u�Ԃ̈ړ��ʐݒ菈��
	D3DXMATRIX *GetMtx(void) { return &m_mtxWorld; }										//���[���h�}�g���b�N�X�擾����
	void SetObjParent(bool bObjeParent) { m_bObjParent = bObjeParent; }						//�I�u�W�F�N�g�Ƃ̐e�q�֌W�ݒ菈��
	bool GetObjParent(void) { return m_bObjParent; }										//�I�u�W�F�N�g�Ƃ̐e�q�֌W�擾����
	D3DXMATRIX *GetMtxParent(void) { return m_mtxWorldParent; }								//���[���h�}�g���b�N�X�擾����
	void SetMtxParent(D3DXMATRIX *mtx) { m_mtxWorldParent = mtx; }							//���[���h�}�g���b�N�X�ݒ菈��

private:
	//�����o�֐�
	void Move(void);								//�ړ�����
	void Rotate(void);								//��]����

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
	bool m_bShot;									//���˂������ǂ���
	float m_fJump;									//�W�����v��
	float m_fMoveForward;							//�O�ɐi�ޗ�
	float m_fBoundMove;								//�o�E���h����u�Ԃ̈ړ���
	CSparkle *m_pSparkle;							//�O���G�t�F�N�g
	D3DXMATRIX *m_mtxWorldParent;					//�e�̃��[���h�}�g���b�N�X
	bool m_bObjParent;								//���f���ȊO�Ƃ̐e�q�֌W�����邩�ǂ���
};

#endif // !_PLAYER_H_