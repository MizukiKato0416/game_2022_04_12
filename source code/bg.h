//=============================================================================
//
// �w�i���� [bg.h]
// Author : �H������
//
//=============================================================================
#ifndef _BG_H_
#define _BG_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "texture.h"
#include "object3D.h"
#include "object.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CBg : public CObject3D
{
public:
	CBg(CObject::PRIORITY Priority = CObject::PRIORITY::POLYGON_3D);	// �f�t�H���g�R���X�g���N�^
	~CBg();	// �f�t�H���g�f�X�g���N�^
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	void Draw(void);	// �`��
	static CBg *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, const D3DXVECTOR3 &rot, D3DXVECTOR2 uv_move_speed);
	void SetUvMove(const D3DXVECTOR2 speed) { m_uv_move_speed = speed; }
private:
	D3DXVECTOR2 m_uv_move_speed;
	D3DXVECTOR2 m_uv_pos;
};

#endif
