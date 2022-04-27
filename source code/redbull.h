//=============================================================================
//
// redbull�N���X���� [redbull.h]
// Author : �H������
//
//=============================================================================
#ifndef _REDBULL_H_
#define _REDBULL_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "happening.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CRedbull : public CHappenig
{
public:
	CRedbull(CObject::PRIORITY Priority = CObject::PRIORITY::HAPPENING);	// �f�t�H���g�R���X�g���N�^
	~CRedbull();	// �f�t�H���g�f�X�g���N�^
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	void Draw(void);	// �`��
	static CRedbull *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot);
private:
	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXVECTOR3 m_rot;	// ��]
};

#endif