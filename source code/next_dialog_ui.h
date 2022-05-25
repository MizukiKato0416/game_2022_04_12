//===========================================
//���̃Z���t�ɍs��UI����
//Authore:��������
//===========================================
#ifndef _NEXT_DILOG_UI_H_
#define _NEXT_DILOG_UI_H_
#include "object2D.h"

//�O���錾

//================================================
//�}�N����`
//================================================
#define NEXT_DILOG_UI_SIZE		(36.0f)		//NEXT_DILOG_UI�̃T�C�Y
#define NEXT_DILOG_UI_POS_X		(1180.0f)	//NEXT_DILOG_UI�̈ʒuX
#define NEXT_DILOG_UI_POS_Y		(680.0f)	//NEXT_DILOG_UI�̈ʒuY

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CNextDialogUI : public CObject2D
{
public:
	//NEXT_DILOG_UI�̎��
	enum class TYPE
	{
		NONE = 0,
		PRESS_START,	//PRESSSTART
		MAX
	};

	CNextDialogUI(CObject::PRIORITY Priority = CObject::PRIORITY::NEXT_DIALOG_UI);	//�R���X�g���N�^
	~CNextDialogUI();								//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CNextDialogUI *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size);

private:
	float m_fRotation;			//��]�l
	int m_nCounter;				//�����Ă���\��������܂ł̃J�E���^�[
};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_NEXT_DILOG_UI_H_