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
	CFloor(int nPriority = PRIORITY_POLYGON_3D);	//�R���X�g���N�^
	~CFloor();										//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CFloor *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot);
	static bool Collision(CObject *pObject);			//�����蔻��

private:
};

#endif // !_FLOOR_H_