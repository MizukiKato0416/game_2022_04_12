//=============================================================================
//
// �n�v�j���O�e�N���X���� [happening.h]
// Author : �H������
//
//=============================================================================
#ifndef _HAPPENING_H_
#define _HAPPENING_H_

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CModelSingle;

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "texture.h"
#include "object.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CHappenig : public CObject
{
public:
	CHappenig(CObject::PRIORITY Priority = CObject::PRIORITY::HAPPENING);	// �f�t�H���g�R���X�g���N�^
	~CHappenig();	// �f�t�H���g�f�X�g���N�^
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	void Draw(void);	// �`��
	void SetPos(const D3DXVECTOR3 &pos) { m_pos = pos; }	// �Z�b�^�[
	void SetRot(const D3DXVECTOR3 &rot) { m_rot = rot; }	// �Z�b�^�[
	void SetModel(CModelSingle *model) { m_model = model; }	// �Z�b�^�[
private:
	CModelSingle *m_model;	// ���f��
	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXVECTOR3 m_rot;	// ����
};

#endif