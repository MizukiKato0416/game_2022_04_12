//===========================================
//�L���L���G�t�F�N�g�̏���
//Author:KatoMizuki
//===========================================
#ifndef _SPARKLE_H_
#define _SPARKLE_H_

#include "object.h"

//�O���錾
class CEffect3D;

//================================================
//�}�N����`
//================================================
#define SPARKLE_SIZE_RAND	(float (rand() % 40 + 20))		//�G�t�F�N�g���o���T�C�Y�̃����_���l

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CSparkle : public CObject
{
public:
	CSparkle(CObject::PRIORITY Priority = CObject::PRIORITY::EFFECT3D);		//�R���X�g���N�^
	~CSparkle();																//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CSparkle *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, int nNumEffect);

	void SetMove(D3DXVECTOR3 move) { m_move = move; }	//�ړ��ʐݒ菈��

private:
	D3DXVECTOR3 m_move;						//�ړ���
	D3DXVECTOR3 m_size;						//�T�C�Y
	D3DXVECTOR3 m_pos;						//�ʒu
	std::vector<CEffect3D*> m_pEffect3D;	//�G�t�F�N�g�̃|�C���^
	int m_nNumEffect;						//�G�t�F�N�g�̐�
};

#endif // !_SPARKLE_H_