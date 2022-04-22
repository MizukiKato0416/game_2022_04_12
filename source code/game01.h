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
	CGame01(CObject::PRIORITY Priority = CObject::PRIORITY::NONE);		//�R���X�g���N�^
	~CGame01();									//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	void Camera(void);					//�J�����̏���
	void Road(void);					//���̏���
	void Gauge(void);					//�Q�[�W����
	void Shot(void);					//���ˏ���

	//�����o�ϐ�
	CPlayer *m_pPlayer;					//�v���C���[�̃|�C���^
	CFloor *m_pFloor;					//���̃|�C���^
	CRoad *m_apRoad[GAME01_MAX_ROAD];	//���̃|�C���^
	D3DXVECTOR3 m_mouseTriggerPos;		//�}�E�X���N���b�N�����u�Ԃ̈ʒu
	CGauge *m_pGauge;					//���˃Q�[�W
	int m_nGaugeCounter;				//�Q�[�W�����^���̎��Ԃ�ݒ肷�邽�߂̃J�E���^�[
	CBg *m_pBg[GAME01_MAX_BG];			//�w�i�̃|�C���^
};

#endif // !_GAME01_H_