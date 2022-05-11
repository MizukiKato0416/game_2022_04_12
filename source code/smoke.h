//===========================================
//���G�t�F�N�g�̏���
//Author:KatoMizuki
//===========================================
#ifndef _SMOKE_H_
#define _SMOKE_H_

#include "object.h"

//�O���錾
class CEffect3D;

//================================================
//�}�N����`
//================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CSmoke : public CObject
{
public:
	CSmoke(CObject::PRIORITY Priority = CObject::PRIORITY::EFFECT3D);		//�R���X�g���N�^
	~CSmoke();																//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CSmoke *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, const D3DXVECTOR3 &rot, const D3DXVECTOR3 &move, const D3DXVECTOR3 &addRot,
		                  const D3DXVECTOR3 &addSize, const float &fSubtractAlpha);
	//�ړ��ʐݒ菈��
	void SetMove(const D3DXVECTOR3 move) { m_move = move; }
	//�ړ��ʎ擾����
	D3DXVECTOR3 GetMove(void) { return m_move; }

private:
	D3DXVECTOR3 m_size;						//�T�C�Y
	D3DXVECTOR3 m_move;						//�ړ���
	D3DXVECTOR3 m_pos;						//�ʒu
	D3DXVECTOR3 m_rot;						//����
	D3DXVECTOR3 m_addRot;					//��]���Z�l
	D3DXVECTOR3 m_addSize;					//�T�C�Y���Z�l
	CEffect3D *m_pEffect3D;					//�G�t�F�N�g�̃|�C���^
	float m_fSubtractAlpha;					//���l���Z�l
};

#endif // !_SMOKE_H_