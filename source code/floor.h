//===========================================
//3D�|���S���̏�����
//Author:��������
//===========================================
#ifndef _FLOOR_H_
#define _FLOOR_H_
#include "object3D.h"

//================================================
//�}�N����`
//================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CFloor : public CObject3D
{
public:
	CFloor(CObject::PRIORITY Priority = CObject::PRIORITY::POLYGON_3D);	//�R���X�g���N�^
	~CFloor();										//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CFloor *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, const D3DXVECTOR3 &rot);
	static bool Collision(CObject *pObject);			//�����蔻��

private:
};

#endif // !_FLOOR_H_