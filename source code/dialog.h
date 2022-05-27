//===========================================
//��b�̏���
//Author:KatoMizuki
//===========================================
#ifndef _DIALOG_H_
#define _DIALOG_H_

#include "object.h"
#include "object2D.h"
#include "manager.h"
#include "texture.h"

//�O���錾
class CLetter;
class CNextDialogUI;

//================================================
//�}�N����`
//================================================
//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CDialog : public CObject
{
public:
	//�|�[�Y�̎��
	enum class POSE
	{
		NORMAL = 0,	    //�m������
		DOMINATE,	    //���Ɏ�𓖂Ă�
		HNDS_UP,	    //�����������
		MAX
	};
	//��̎��
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
	//�t���[���̎��
	enum class FRAME
	{
		NORMAL = 0,		//����
		MAX
	};
	//��b�����o���V�[���̎��
	enum class SCENE_TYPE
	{
		NONE = 0,
		CLICK_SCENE,		//�N���b�N�A�ł̃V�[��
		ENDROLL_SCENE,		//�G���h���[���̃V�[��
		MAX
	};
	//�h��鉉�o�̎��
	enum class SHAKE_TYPE
	{
		NONE = 0,			//�Ȃ�
		UP_TO_DOWN,			//�ォ�牺
		DOWN_TO_UP,			//�������
		RIGHT_AND_LEFT,		//���E����
		//RANDOM,				//�����_��
		MAX
	};

	//================================================
	//�\���̂̒�`
	//================================================
	//��b�̍\��
	typedef struct
	{
		int nPersonPose;					//�L�����|�[�Y
		int nPersonFace;					//�L������
		int nFrame;							//�t���[��
		string sBgTexturePas;				//�w�i�̃e�N�X�`���̃p�X
		CDialog::SHAKE_TYPE shakeType;		//�h��̎��
		int nNumShake;						//�h��̉�
		D3DXVECTOR3 shakeSpeed;				//�h��̑���
		D3DXVECTOR3 shakeMinusSpeed;		//�h��̑������}�C�i�X�����
		float fShakeWidth;					//�h��̕�
	} DIALOG_BODY;


	CDialog(CObject::PRIORITY Priority = CObject::PRIORITY::DIALOG);	//�R���X�g���N�^
	~CDialog();															//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CDialog *Create(const SCENE_TYPE &sceneType);
	bool Dialog(const int &nCntDialog);		//�Z���t����
	void UninitDialog(void);				//�Z���t�j������
	void SetDialog(const int &nNumDialog);	//�Z���t�ݒ菈��
	//�S�����\�����ꂽ���ǂ����ݒ菈��
	void SetDialogFinish(bool bDialogFinish) { m_bDialogFinish = bDialogFinish; }
	//�S�����\�����ꂽ���ǂ����擾����
	bool GetDialogFinish(void) { return m_bDialogFinish; }

private:
	void LoadTxt(void);					//�e�L�X�g�t�@�C�����[�h����
	void Shake(void);					//�h�ꏈ��

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
	SCENE_TYPE m_sceneType;				//��b���o���V�[���̎��
	bool m_bRead;						//�ǂݍ��ݎn�߂邩�ǂ���
	CManager::MODE m_nextScene;			//�V�[���̑J�ڐ�
	bool m_bUninit;						//�������ǂ���
	CObject2D *m_pBg;					//�w�i
	bool m_bShake;						//�h��邩�ǂ���
	D3DXVECTOR3 m_createPosePos;		//�������̃|�[�Y�̈ʒu
	D3DXVECTOR3 m_createFacePos;		//�������̊�̈ʒu
	D3DXVECTOR3 m_move;					//�ړ���
	int m_nCounterShake;				//������
	bool m_bShakeReturn;				//�h��̐܂�Ԃ�
};

#endif // !_DIALOG_H_