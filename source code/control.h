//=============================================================================
// �R���g���[������
// Author:��������
//=============================================================================
#ifndef _CONTROL_H_
#define _CONTROL_H_
#include "main.h"

//�O���錾
class CObject;

//================================================
//�}�N����`
//================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CControl
{
public:
	CControl();									// �R���X�g���N�^
	virtual ~CControl();						// �f�X�g���N�^
	virtual HRESULT Init(const CObject *pObject) = 0;	// ����������
	virtual void Uninit(void) = 0;				// �I������
	virtual void Update(const CObject *pObject) = 0;	// �X�V����
	D3DXVECTOR3 GetMove(void);					// �ړ��ʂ̎擾����

protected:
	D3DXVECTOR3 m_move;							// �ړ���
};

#endif	//_CONTROL_H_