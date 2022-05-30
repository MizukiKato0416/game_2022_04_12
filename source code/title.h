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
#include "input_keyboard.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CObject2D;
class CLetter;

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
	string GetPasWord(void) { return m_pasword; }	// �Q�b�_�[

private:
	void SeletMode(void);	// �I������
	void Tutorial(void);	// �`���[�g���A������
	void ColUpdate(void);	// �J���[�̍X�V����
	void ResultTimer(void);	// ���U���g�ւ̑J��
	void PasWord(void);	// �p�X���[�h���͏���
	CObject2D *m_click;	// CLICK���S
	CObject2D *m_pas_word;// �p�X���[�h���͗�
	vector<CObject2D*> m_button;// �{�^��
	vector<CObject2D*> m_tutorial;// �`���[�g���A��
	vector<CLetter*> m_pas_font;// �p�X���[�h
	vector<wstring> m_key_name;	// �p�X���[�h1��������
	vector<string> m_letter_single;	// �p�X���[�h
	string m_pasword;	// �p�X���[�h
	int m_count_letter;	// �e�L�X�g�J�E���g
	int m_result_timer;	// ���U���g�ւ̃^�C�}�[
	int m_letter_limitl;	// ��������
	bool m_fade_flag;	// �t�F�[�h�t���O
	bool m_tutorial_flag;	// �`���[�g���A����
	bool m_pas_drop;	// �p�X���[�h�ł�����
};

#endif // !_TITLE_H_