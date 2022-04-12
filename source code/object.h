//===========================================
//�V�[������
//Author:��������
//===========================================
#ifndef _OBJECT_H_
#define _OBJECT_H_
#include "main.h"

//================================================
//�}�N����`
//================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CObject
{
public:
	typedef enum
	{
		PRIORITY_NONE = 0,			//�Ȃ�
		PRIORITY_PLAYER,			//�v���C���[
		PRIORITY_MODEL,				//���f��
		PRIORITY_ENEMY,				//�G
		PRIORITY_LOCK_ON,			//���b�N�I��
		PRIORITY_ENEMY_BULLET,		//�G�̒e
		PRIORITY_POLYGON_3D,		//3D�|���S��
		PRIORITY_SHADOW,			//�e
		PRIORITY_MESH_FIELD,		//���b�V���t�B�[���h
		PRIORITY_CHECK_CIRCLE,		//�`�F�b�N�|�C���g
		PRIORITY_WARP_CIRCLE,		//���[�v�|�C���g
		PRIORITY_MAGIC,				//���@
		PRIORITY_TRAJECTORY,		//���b�V���O��
		PRIORITY_EXPLOSION,			//����
		PRIORITY_SPARK,				//�΂̕�
		PRIORITY_EFFECT3D,			//�p�[�e�B�N��
		PRIORITY_FIRE_BALL,			//���̒e
		PRIORITY_EXCLAMATION_MARK,	//�r�b�N���}�[�N
		PRIORITY_UI,				//UI
		PRIORITY_RANKING,			//�����L���O
		PRIORITY_MAP,				//�}�b�v
		PRIORITY_MASK,				//�}�X�N
		PRIORITY_PAUSE,				//�|�[�Y
		PRIORITY_FADE,				//�t�F�[�h
		PRIORITY_MAX
	} PRIORITY;

	enum class OBJTYPE
	{
		NONE = 0,			//�Ȃ�
		EFFECT_3D,			//3D�G�t�F�N�g
		TRAJECTORY,			//���b�V���O��
		FLOOR,				//��
		MAGIC_CIRCLE,		//���@�w
		MAGIC_THUNDER,		//�����@
		MAGIC_FIRE,			//�����@
		WARP_CIRCLE,		//���[�v���@�w
		CHECK_CIRCLE,		//�`�F�b�N�|�C���g���@�w
		PLAYER,				//�v���C���[
		MODEL,				//���f��
		ENEMY,				//�G
		ENEMY_BEE,			//�G(�I)
		ENEMY_FAT,			//�G(��)
		ENEMY_BOSS,			//�G(�{�X)
		BULLET_ENEMY,		//�G�̒e
		FIRE_BALL,			//���̒e
		EXPLOSION,			//����
		SPARK,				//�΂̕�
		GUARD,				//�K�[�h�G�t�F�N�g
		GAUGE,				//�Q�[�W
		UI,					//UI
		MAP,				//�}�b�v
		POLYGON_3D,			//3D�|���S��
		EXCLAMATION_MARK,	//�r�b�N���}�[�N
		SHADOW,				//�e
		MAX
	};

	CObject(int nPriority = PRIORITY_NONE);			//�R���X�g���N�^
	virtual ~CObject();								//�f�X�g���N�^

	//�����o�֐�
	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	static void ReleaseAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);

	void SetObjType(OBJTYPE objType);			//�I�u�W�F�N�g�^�C�v�ݒ菈��
	OBJTYPE GetObjType(void);					//�I�u�W�F�N�g�^�C�v�擾����
	CObject *GetObjNext(CObject *pObject);		//�����̃I�u�W�F�N�g�̎��̃I�u�W�F�N�g���擾����
	static CObject *GetTopObj(int nPriority);	//�����̃v���C�I���e�B�̐擪�I�u�W�F�N�g�擾����
	D3DXVECTOR3 GetPos(void);					//�ʒu�擾����
	void SetPos(D3DXVECTOR3 pos);				//�ʒu�ݒ菈��
	void SetPosOld(D3DXVECTOR3 posOld);			//1�t���[���O�̈ʒu�ݒ菈��
	D3DXVECTOR3 GetPosOld(void);				//1�t���[���O�̈ʒu�擾����
	D3DXVECTOR3 GetSize(void);					//�T�C�Y�擾����
	void SetSize(D3DXVECTOR3 size);				//�T�C�Y�ݒ菈��
	void SetPriority(int nPriority);			//�v���C�I���e�B�ݒ菈��

protected:
	void Release(void);

private:
	static CObject *m_pTop[PRIORITY_MAX];	//�擪�I�u�W�F�N�g�̃|�C���^
	static CObject *m_pCur[PRIORITY_MAX];	//����(��Ԍ��)�I�u�W�F�N�g�̃|�C���^
	CObject *m_pPrev;						//�O�̃I�u�W�F�N�g�ւ̃|�C���^
	CObject *m_pNext;						//���̃I�u�W�F�N�g�ւ̃|�C���^
	int m_nPriority;						//�D�揇�ʂ̔ԍ�
	OBJTYPE m_objType;						//�I�u�W�F�N�g�̎��
	D3DXVECTOR3 m_pos;						//�|���S���̈ʒu
	D3DXVECTOR3 m_posOld;					//1�t���[���O�̃|���S���̈ʒu
	D3DXVECTOR3 m_size;						//�|���S���̃T�C�Y
	bool m_bDeath;							//���S�t���O
};

#endif // !_OBJECT_H_