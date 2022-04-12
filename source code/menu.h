//===========================================
//���j���[����
//Authore:��������
//===========================================
#ifndef _MENU_H_
#define _MENU_H_
#include "object.h"
#include "main.h"

//�O���錾
class CObject2D;

//================================================
//�}�N����`
//================================================
#define MENU_UI_START_SIZE_X			(304.0f)	//START��UI�̃T�C�YX
#define MENU_UI_START_SIZE_Y			(84.0f)		//START��UI�̃T�C�YY
#define MENU_UI_EXIT_SIZE_X				(304.0f)	//EXIT��UI�̃T�C�YX
#define MENU_UI_EXIT_SIZE_Y				(84.0f)		//EXIT��UI�̃T�C�YY
#define MENU_UI_NOT_SELECT_COLOR_ALPHA	(0.4f)		//�I������Ă��Ȃ��Ƃ���UI�̃��l

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CMenu : public CObject
{
public:
	CMenu();				//�R���X�g���N�^
	~CMenu();				//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	//�I����
	typedef enum
	{
		SELECT_MENU_TYPE_NONE = 0,
		SELECT_MENU_TYPE_TUTORIAL,		//Tutorial
		SELECT_MENU_TYPE_GAME_START,	//GameStart
		SELECT_MENU_TYPE_EXIT,			//Exit
		SELECT_MENU_TYPE_MAX			//�I�����ő�l
	} SELECT_MENU_TYPE;

	int m_nSelect;										//�I����
	CObject2D *m_apObject2D[SELECT_MENU_TYPE_MAX];		//UI
};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_MENU_H_