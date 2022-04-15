//=============================================================================
//
// rsoad���� [road.h]
// Author : �H������
//
//=============================================================================
#ifndef _ROAD_H_
#define _ROAD_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "object.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CFloor;
class CModelSingle;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CRoad : public CObject
{
public:
	CRoad(CObject::PRIORITY priorty = PRIORITY::ROAD);	// �f�t�H���g�R���X�g���N�^
	~CRoad();	// �f�t�H���g�f�X�g���N�^
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	void Draw(void);	// �`��
	static CRoad *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, const CModelSingle::HAPPENING_TYPE &type, const float &move_speed);	// ��������
	void SetSpeed(const float &move_speed) { m_move_speed = move_speed; }	// �Z�b�^�[
	float GetSpeed(void) { return m_move_speed; }	// �Q�b�_�[
private:
	CModelSingle::HAPPENING_TYPE m_happening_type;	// ���
	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXVECTOR3 m_size;	// �T�C�Y
	CFloor *m_floor;	// ��
	CModelSingle *m_happening_model;	// �n�v�j���O�p���f��
	float m_move_speed;	// �ړ���
};

#endif