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

//================================================
//�}�N����`
//================================================
#define GAME01_MAX_ROAD		(2)		//���̍ő吔

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
	//�����o�ϐ�
	CPlayer *m_pPlayer;					//�v���C���[�̃|�C���^
	CFloor *m_pFloor;					//���̃|�C���^
	CRoad *m_apRoad[GAME01_MAX_ROAD];	//���̃|�C���^
};

#endif // !_GAME01_H_