//===========================================
//���G�t�F�N�g�̏���
//Author:KatoMizuki
//===========================================
#ifndef _WIND_H_
#define _WIND_H_

#include "object.h"
#include "effect3D.h"

//�O���錾

//================================================
//�}�N����`
//================================================
#define WIND_MAX_PATTERN	(8)		//���̃A�j���[�V�����̐�

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CWind : public CEffect3D
{
public:
	CWind(CObject::PRIORITY Priority = CObject::PRIORITY::EFFECT3D);		//�R���X�g���N�^
	~CWind();																//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CWind *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, const int &nInitTexAnimNum);

private:
	int m_nInitTexAnimNum;					//�����e�N�X�`���A�j���[�V�����̔ԍ�
	int m_nTexAnimCounter;					//�A�j���[�V�����J�E���^�[
};

#endif // !_WIND_H_