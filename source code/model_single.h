//===========================================
//���f���P�̂��o������
//Author:��������
//===========================================
#ifndef _MODEL_SINGLE_H_
#define _MODEL_SINGLE_H_
#include "object.h"
#include "x_load.h"

//�O���錾
class CModel;

//================================================
//�}�N����`
//================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CModelSingle : public CObject
{
public:
	//---------------------------
	// �񋓌^
	//---------------------------
	enum class HAPPENING_TYPE
	{
		NONE = 0,	// ����
		TRAMPOLINE,	// �g�����|����
		FAN,	// ��@
		BALANCE_BALL,	// �o�����X�{�[��
		GIRL,	// ���L�q
		MAX,	// ����
	};
	//�����o�֐�
	CModelSingle(CObject::PRIORITY Priority = CObject::PRIORITY::MODEL);				//�R���X�g���N�^
	~CModelSingle();											//�f�X�g���N�^

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CModelSingle *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot, const CXload::X_TYPE &type, CModel *pParent, const bool &Collision);
	static bool SimpleCollision(CObject *&pObject);	//��]��������_���ȓ����蔻��
	static bool Collision(CObject *pObject);		//y������]�����Ă��������蔻��
	static bool CollisionAny(CObject *&pObject);		//�����̏Փ˔���
	void SetPos(const D3DXVECTOR3 &pos) { m_pos = pos; }
	D3DXVECTOR3 GetPos(void) { return m_pos; }

private:
	//�����o�ϐ�
	D3DXVECTOR3 m_pos;					//�ʒu
	D3DXVECTOR3	m_size;					//�T�C�Y
	D3DXVECTOR3 m_rot;					//����
	D3DXVECTOR3 m_move;					//�ړ���
	CModel *m_pModel;					//���f���̃|�C���^
	D3DXMATRIX m_mtxWorld;				//���[���h�}�g���b�N�X
	CModel *m_pParent;					//�e���f���ւ̃|�C���^
	CXload::X_TYPE m_type;				//�o�����f���̎��
	bool m_bCollision;					//�����蔻������邩�ǂ���
};

#endif // !_MODEL_SINGLE_H_