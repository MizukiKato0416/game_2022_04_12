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

//================================================
//�}�N����`
//================================================

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
	CPlayer *m_pPlayer;			//�v���C���[�̃|�C���^
	CModelSingle *m_pRocket;	//���P�b�g�̃|�C���^
};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_ROCKET_SCENE_H_