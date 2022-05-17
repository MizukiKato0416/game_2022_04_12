//===========================================
//�|�[�Y����
//Authore:��������
//===========================================
#ifndef _PAUSE_H_
#define _PAUSE_H_
#include "object.h"
#include "main.h"

//�O���錾
class CObject2D;
class CManager;

//================================================
//�}�N����`
//================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CPause : public CObject
{
public:
	CPause(CObject::PRIORITY Priority = CObject::PRIORITY::PAUSE);			//�R���X�g���N�^
	~CPause();										//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static bool GetPause(void);
	static bool SetPause(const bool &bPause);
	static CPause *Create(void);

private:
	//��ʑJ�ڂ̑I�����{�^��
	typedef enum
	{
		SELECT_START = 0,		//�ĊJ�{�^��
		SELECT_EXIT,			//���j���[�ɖ߂�{�^��
		SELECT_MAX
	}SELECT;

	CObject2D *m_apObject2D[SELECT_MAX];	//UI
	CObject2D *m_pObject2D[2];				//�|�[�Y�̃t���[��
	CObject2D *m_pPauseButton;				// �|�[�Y�{�^��
	static bool m_bPause;					//�|�[�Y��ʂ��ǂ���
};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_PAUSE_H_