//===========================================
//�Q�[������
//Author:��������
//===========================================
#ifndef _GAME01_H_
#define _GAME01_H_
#include "object.h"
#include "main.h"

//�O���錾
class CPlayer;
class CFloor;
class CRoad;
class CGauge;
class CBg;
class CObject2D;
class CRocket;
class CModelSingle;
class CLetter;
class CNextDialogUI;
class CDialog;
class CPause;

//================================================
//�}�N����`
//================================================
#define GAME01_MAX_ROAD		(2)		//���̍ő吔
#define GAME01_MAX_BG		(3)		//�w�i�̍ő吔

//========================================================
//�\���̂̒�`
//========================================================

//================================================
//�N���X�̒�`
//================================================
class CGame01 : public CObject
{
public:
	CGame01(CObject::PRIORITY Priority = CObject::PRIORITY::GAME);		//�R���X�g���N�^
	~CGame01();									//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
	//�I���ݒ菈��
	void SetFinish(bool bFinish) { m_bFinish = bFinish; }
	//�I���擾����
	bool GetFinish(void) { return m_bFinish; }
	//�|�[�Y�ݒ菈��
	void SetPause(bool bPause) { m_bPause = bPause; }
	//�|�[�Y�擾����
	bool GetPause(void) { return m_bPause; }
	//�Z���t���o���Ă��邩�ǂ����ݒ菈��
	void SetDialog(bool bDialog) { m_bDialog = bDialog; }
	//�Z���t���o���Ă��邩�ǂ����擾����
	bool GetDialog(void) { return m_bDialog; }

private:
	void Camera(void);											//�J�����̏���
	void Road(void);											//���̏���
	void Gauge(void);											//�Q�[�W����
	void UninitGauge(void);										//�Q�[�W����������
	void UninitArrow(void);										//������������
	void Shot(void);											//���ˏ���
	void ShotUi(void);											//����UI����
	void Rocket(void);											//���P�b�g�̏���
	void Finish(void);											//�S�[������
	void FlyingDistanceFlag(void);								//�g���t�B�[�̔򋗗��̃t���O����
	void Mask(void);											//�}�X�N����
	void Click(void);											//�N���b�N����
		
	//�����o�ϐ�
	CPlayer *m_pPlayer;					//�v���C���[�̃|�C���^
	CFloor *m_pFloor;					//���̃|�C���^
	CModelSingle *m_pStart;				//�X�^�[�g���̃|�C���^
	CRoad *m_apRoad[GAME01_MAX_ROAD];	//���̃|�C���^
	D3DXVECTOR3 m_mouseTriggerPos;		//�}�E�X���N���b�N�����u�Ԃ̈ʒu
	CGauge *m_pGauge;					//���˃Q�[�W
	CObject2D *m_pGaugeFrame;			//�Q�[�W�̃t���[��
	int m_nGaugeCounter;				//�Q�[�W�����^���̎��Ԃ�ݒ肷�邽�߂̃J�E���^�[
	CBg *m_pBg[GAME01_MAX_BG];			//�w�i�̃|�C���^
	CRocket *m_pRocket;					//���P�b�g�̃|�C���^
	int m_nShotUiCounter;				//���˂����ۂ�UI�p�J�E���^�[
	CObject2D *m_pShotUi;				//���˂����ۂ�UI
	D3DXVECTOR3 m_shotMoveVec;			//���˂���Ƃ��̈ړ��ʃx�N�g��
	bool m_bReleaseMouse;				//�}�E�X�𗣂������ǂ���
	CObject2D *m_pArrow;				//���UI�̃|�C���^
	bool m_bFinish;						//�I���t���O
	int m_nFinishCounter;				//�I�����̃J�E���^�[
	bool m_bPause;						//�|�[�Y�̃t���O
	CObject2D *m_pDengerMask;			//�}�X�N
	bool m_bAddCol;						//�J���[���Z�̐؂�ւ�
	int m_nClick;						//�N���b�N������
	bool m_bDialog;						//�Z���t���o���Ă��邩�ǂ���	
	CPause *m_pPause;					//�̃|�C���^
};	

#endif // !_GAME01_H_