//=============================================================================
//
// ���ѕ������� [trophy.h]
// Author : �H������
//
//=============================================================================
#ifndef _HISTORY_LETTER_H_
#define _HISTORY_LETTER_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "object.h"
#include "input_keyboard.h"
#include "trophy.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CObject2D;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CHistory : public CObject
{
public:
	CHistory(PRIORITY priorty = PRIORITY::HISTORY_LETTER);	// �f�t�H���g�R���X�g���N�^
	~CHistory();	// �f�t�H���g�f�X�g���N�^
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	void Draw(void);	// �`��
	static CHistory *Create(CTrophy::TROPHY type);

private:
	CObject2D *m_history;// ����
	CTrophy::TROPHY m_type;	// ���т̎��
	static bool m_in_object;	// �łĂ��Ă���т����邩
	int m_cout_stop;		// �~�܂�b��
	bool m_stop;		// �~�܂��Ă邩
	bool m_in_or_out;	// �łĂ��Ă邩�����Ă邩
	bool m_history_in;	// �������łĂ��Ă邩

};

#endif // !_HISTORY_LETTER_H_