//=============================================================================
//
// �g���t�B�[���[������ [trophy.h]
// Author : �H������
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "object.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CObject2D;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CTitle : public CObject
{
public:
	CTitle(PRIORITY priorty = PRIORITY::NONE);	// �f�t�H���g�R���X�g���N�^
	~CTitle();	// �f�t�H���g�f�X�g���N�^
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	void Draw(void);	// �`��

private:
	void SeletMode(void);
	void Tutorial(void);
	void ColUpdate(void);
	void ResultTimer(void);
	void PasWord(void);
	CObject2D *m_click;	// CLICK���S
	vector<CObject2D*> m_button;// �{�^��
	vector<CObject2D*> m_tutorial;// �`���[�g���A��
	vector<CObject2D*> m_pas_word;// �p�X���[�h���͗�
	int m_result_timer;	// ���U���g�ւ̃^�C�}�[
	bool m_fade_flag;	// �t�F�[�h�t���O
	bool m_tutorial_flag;	// �`���[�g���A����
};

#endif // !_TITLE_H_