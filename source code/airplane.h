//===========================================
//��s�@�̏���
//Author:KatoMizuki
//===========================================
#ifndef _AIRPLANE_H_
#define _AIRPLANE_H_

#include "happening.h"

//�O���錾
class CEffect3D;

//================================================
//�}�N����`
//================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CAirplane : public CHappenig
{
public:
	CAirplane(CObject::PRIORITY Priority = CObject::PRIORITY::HAPPENING);		//�R���X�g���N�^
	~CAirplane();																//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CAirplane *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot);



private:
	D3DXVECTOR3 m_pos;						//�ʒu
	D3DXVECTOR3 m_rot;						//����
};

#endif // !_AIRPLANE_H_