//=============================================================================
//
// �I�u�W�F�N�g���� [object.h]
// Author : �H������
//
//=============================================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "texture.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CObject
{
public:
	//---------------------------
	// �񋓌^
	//---------------------------
	enum class PRIORITY
	{
		NONE = 0,	//�Ȃ�
		MAX
	};

	enum class OBJTYPE
	{
		NONE = 0,	//�Ȃ�
		MAX
	};
	CObject(LAYER_TYPE Layer = LAYER_TYPE::LAYER_00);	// �f�t�H���g�R���X�g���N�^
	virtual ~CObject();	// �f�t�H���g�f�X�g���N�^
	virtual HRESULT Init(void) = 0;	// ������
	virtual void Uninit(void) = 0;	// �I��
	virtual void Update(void) = 0;	// �X�V
	virtual void Draw(void) = 0;	// �`��
	static void ReleaseAll(void);	// �S�j��
	static void UpdateAll(void);	// �S�X�V
	static void DrawAll(void);		// �S�`��
	D3DXVECTOR3 GetPos(void) { return m_pos; }			// �Q�b�_�[
	D3DXVECTOR3 GetSize(void) { return m_size; }		// �Q�b�_�[
	bool GetDeath(void) { return m_deth; }			// �Q�b�_�[
	D3DXVECTOR3 GetPosOld(void) { return m_pos_old; }	// �Q�b�_�[
	OBJTYPE GetObjType(void) { return m_obj_type; }		// �Q�b�_�[
	static CObject GetObject(int priority) { return m_object[priority]; }	// �Q�b�_�[
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }		// �Z�b�^�[
	void SetSize(D3DXVECTOR3 size) { m_size = size; }	// �Z�b�^�[
	void SetObjType(OBJTYPE obj_type) { m_obj_type = obj_type; }	// �Z�b�^�[
	void SetPosOld(D3DXVECTOR3 pos_old) { m_pos_old = pos_old; }	// �Z�b�^�[
	void SetPriority(int priority) { m_priority = priority; }		// �Z�b�^�[
private:
	static vector<CObject*> m_object[(int)LAYER_TYPE::MAX_LAYER];	// �I�u�W�F�N�g
	D3DXVECTOR3	m_pos;		// �ʒu
	D3DXVECTOR3 m_pos_old;	// 1�t���[���O�̈ʒu
	D3DXVECTOR3 m_size;		// �T�C�Y
	OBJTYPE m_obj_type;		// �I�u�W�F�N�g�̎��
	int m_priority;	// �`�揇
	bool m_deth;	// ���S�t���O
protected:
	void Release(void) { m_deth = true; }		// ���S�t���O���Ă�
};

#endif