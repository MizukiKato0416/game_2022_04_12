//=============================================================================
//
// �o�i�i�N���X���� [banana.h]
// Author : ��������
//
//=============================================================================
#ifndef _BANANA_H_
#define _BANANA_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "happening.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CBanana : public CHappenig
{
public:
	CBanana(CObject::PRIORITY Priority = CObject::PRIORITY::HAPPENING);	// �f�t�H���g�R���X�g���N�^
	~CBanana();	// �f�t�H���g�f�X�g���N�^
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	void Draw(void);	// �`��
	static CBanana *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot);
private:
	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXVECTOR3 m_rot;	// ��]
	int m_nCntSlow;		//�X���[�ɂȂ鎞�ԃJ�E���g�p
	bool m_bHitPlayer;	//�v���C���[�ɓ����������ǂ���
};

#endif
