//===========================================
//���P�b�g�V�[������
//Authore:��������
//===========================================
#ifndef _ROCKET_SCENE_H_
#define _ROCKET_SCENE_H_
#include "object.h"

//�O���錾
class CPlayer;
class CModelSingle;
class CBg;
class CScore;

//================================================
//�}�N����`
//================================================
#define ROCKET_SCENE_BG_NUM		(4)			//�w�i�̐�

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CRocketScene : public CObject
{
public:
	CRocketScene();				//�R���X�g���N�^
	~CRocketScene();				//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	void Score(void);			//�X�R�A����
	void Camera(void);			//�J��������

	CPlayer *m_pPlayer;						//�v���C���[�̃|�C���^
	CModelSingle *m_pRocket;				//���P�b�g�̃|�C���^
	CBg *m_apBg[ROCKET_SCENE_BG_NUM];		//�w�i�̃|�C���^
	CScore *m_pScore;						//�X�R�A�̃|�C���^
	bool m_bResult;							//���U���g�ɍs�����ǂ���
	int m_nCounter;							//���U���g�ɍs���J�E���^�[
};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_ROCKET_SCENE_H_