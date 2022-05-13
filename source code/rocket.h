//===========================================
//���P�b�g�̏���
//Author:KatoMizuki
//===========================================
#ifndef _ROCKET_H_
#define _ROCKET_H_

#include "happening.h"

//�O���錾
class CEffect3D;
class CSmoke;

//================================================
//�}�N����`
//================================================
#define ROCKET_INIT_ROT_Y		(-D3DX_PI / 4.0f)		//�������̌���
#define ROCKET_SMOKE_NUM		(3)						//��s�@�_���o����

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CRocket : public CHappenig
{
public:
	CRocket(CObject::PRIORITY Priority = CObject::PRIORITY::HAPPENING);		//�R���X�g���N�^
	~CRocket();																//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CRocket *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot);

	bool GetHitPlayer(void) { return m_bHitPlayer; }							//�v���C���[�ɓ����������ǂ����擾����
	void SetHitPlayer(const bool bHitPlayer) { m_bHitPlayer = bHitPlayer; }		//�v���C���[�ɓ����������ǂ����擾����

private:
	D3DXVECTOR3 m_pos;						//�ʒu
	D3DXVECTOR3 m_rot;						//����
	bool m_bHitPlayer;						//�v���C���[�Ɠ����������ǂ���
	vector<CSmoke*> m_pSmoke;				//�_�̃|�C���^
};

#endif // !_ROCKET_H_