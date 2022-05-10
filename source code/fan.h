//=============================================================================
//
// �t�@���N���X���� [fan.h]
// Author : �H������
//
//=============================================================================
#ifndef _FAN_H_
#define _FAN_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "happening.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CFan : public CHappenig
{
public:
	CFan(CObject::PRIORITY Priority = CObject::PRIORITY::HAPPENING);	// �f�t�H���g�R���X�g���N�^
	~CFan();	// �f�t�H���g�f�X�g���N�^
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	void Draw(void);	// �`��
	static CFan *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot);
private:
	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXVECTOR3 m_rot;	// ��]
	int m_nCntSlow;		//�X���[�ɂȂ鎞�ԃJ�E���g�p
	bool m_bHitPlayer;	//�v���C���[�ɓ����������ǂ���
};

#endif