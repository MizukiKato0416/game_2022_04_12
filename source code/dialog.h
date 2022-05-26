//===========================================
//��b�̏���
//Author:KatoMizuki
//===========================================
#ifndef _DIALOG_H_
#define _DIALOG_H_

#include "object.h"
#include "object2D.h"

//�O���錾
class CLetter;
class CNextDialogUI;

//================================================
//�}�N����`
//================================================

//================================================
//�\���̂̒�`
//================================================
//��b�̍\��
typedef struct
{
	int nPersonPose;		//�L�����|�[�Y
	int nPersonFace;		//�L������
	int nFrame;				//�t���[��

} DIALOG_BODY;

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CDialog : public CObject
{
public:
	enum class POSE
	{
		NORMAL = 0,	    //�m������
		DOMINATE,	    //���Ɏ�𓖂Ă�
		HNDS_UP,	    //�����������
		MAX
	};
	enum class FACE
	{
		SMILE = 0,		//�Ί�
		SURPRISE,		//����
		EMBARRASSED,	//�Ƃ�
		STUNNED,		//��R
		ANGER,			//�{��
		CRY,			//����
		MELTS,			//�Ƃ낯��
		MAX
	};
	enum class FRAME
	{
		NORMAL = 0,		//����
		MAX
	};

	CDialog(CObject::PRIORITY Priority = CObject::PRIORITY::DIALOG);	//�R���X�g���N�^
	~CDialog();															//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CDialog *Create(void);
	bool Dialog(const int &nCntDialog);		//�Z���t����
	void UninitDialog(void);				//�Z���t�j������
	void SetDialog(const int &nNumDialog);	//�Z���t�ݒ菈��
	//�S�����\�����ꂽ���ǂ����ݒ菈��
	void SetDialogFinish(bool bDialogFinish) { m_bDialogFinish = bDialogFinish; }
	//�S�����\�����ꂽ���ǂ����擾����
	bool GetDialogFinish(void) { return m_bDialogFinish; }

private:
	vector<DIALOG_BODY> m_dialogBody;	//��b�̍\��
	vector<CLetter*> m_pLetter;			//���^�[�̃|�C���^
	vector<wstring> m_dialog;			//�Z���t
	int m_nDialogDelay;					//�Z���t�̃f�B���C
	int m_nDialogCntX;					//�Z���t�̍s�̃J�E���^�[
	int m_nDialogCntY;					//�Z���t�̗�̃J�E���^�[
	int m_nLetterCreateCounter;			//1�������o���܂ł̎���
	CObject2D* m_pPersonPose;			//�|�[�Y�̃|�C���^
	CObject2D* m_pPersonFace;			//��̃|�C���^
	CObject2D* m_pFrame;				//�t���[���̃|�C���^
	POSE m_poseType;					//�|�[�Y�̎��
	FACE m_faceType;					//��̎��
	FRAME m_frameType;					//�t���[���̎��
	bool m_bCreateFinish;				//�g�g�݂����I�������ǂ���
	int m_nDialogNum;					//���Ԗڂ̃Z���t�𐶐����Ă��邩
	CNextDialogUI *m_pNextDialogUI;		//���̃Z���t�ɍs��UI�̃|�C���^
	int m_nCountFrame;					//�t���[���̃J�E���^
	bool m_bDialogFinish;				//�S�����\�����ꂽ���ǂ���
	int m_nMaxDialog;					//����
};
#endif // !_DIALOG_H_