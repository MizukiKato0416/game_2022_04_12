//=============================================================================
//
// �X�^�[�����O�N���X���� [starring.h]
// Author : �H������
//
//=============================================================================
#ifndef _STARRING_H_
#define _STARRING_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "texture.h"
#include "object.h"
#include "happening.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CStarring : public CHappenig
{
public:
	CStarring(CObject::PRIORITY Priority = CObject::PRIORITY::HAPPENING);	// �f�t�H���g�R���X�g���N�^
	~CStarring();	// �f�t�H���g�f�X�g���N�^
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	void Draw(void);	// �`��
	static CStarring *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot);
private:
	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXVECTOR3 m_rot;	// ��]
};

#endif