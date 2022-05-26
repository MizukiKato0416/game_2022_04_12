//===========================================
//�G���f�B���O�V�[������
//Authore:��������
//===========================================
#ifndef _ENDING_SCENE_H_
#define _ENDING_SCENE_H_
#include "object.h"

//�O���錾
class CObject2D;
class CNextDialogUI;
class CDialog;

//================================================
//�}�N����`
//================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CEndingScene : public CObject
{
public:
	CEndingScene();				//�R���X�g���N�^
	~CEndingScene();				//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	CObject2D *m_pObject2D;				//object2D�̃|�C���^
	CNextDialogUI *m_pNextDialogUI;		//���̃Z���t�ɍs��UI�̃|�C���^
	CDialog *m_pDialog;					//��b�̃|�C���^
	int m_nConter;						//�t���[���J�E���^�[
};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_ENDING_SCENE_H_