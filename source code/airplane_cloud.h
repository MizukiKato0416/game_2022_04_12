//===========================================
//��s�@�_�̏���
//Author:KatoMizuki
//===========================================
#ifndef _AIRPLANE_CLOUD_H_
#define _AIRPLANE_CLOUD_H_

#include "object.h"

//�O���錾
class CEffect3D;

//================================================
//�}�N����`
//================================================
#define AIRPLANE_CLOUD_SIZE_RAND	(float (rand() % 40 + 20))		//�G�t�F�N�g���o���T�C�Y�̃����_���l

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CAirplaneCloud : public CObject
{
public:
	CAirplaneCloud(CObject::PRIORITY Priority = CObject::PRIORITY::EFFECT3D);		//�R���X�g���N�^
	~CAirplaneCloud();																//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CAirplaneCloud *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 move, const int nNumEffect);

	void SetMove(const D3DXVECTOR3 move) { m_move = move; }	//�ړ��ʐݒ菈��

private:
	D3DXVECTOR3 m_move;						//�ړ���
	D3DXVECTOR3 m_size;						//�T�C�Y
	D3DXVECTOR3 m_pos;						//�ʒu
	std::vector<CEffect3D*> m_pEffect3D;	//�G�t�F�N�g�̃|�C���^
	int m_nNumEffect;						//�G�t�F�N�g�̐�
};

#endif // !_AIRPLANE_CLOUD_H_