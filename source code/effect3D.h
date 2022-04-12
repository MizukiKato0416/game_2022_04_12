//===========================================
//�p�[�e�B�N������
//Author:��������
//===========================================
#ifndef _EFFECT3D_H_
#define _EFFECT3D_H_
#include "billboard.h"

//�O���錾
class CControl;

//================================================
//�}�N����`
//================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CEffect3D : public CBillboard
{
public:
	//�G�t�F�N�g�̎��
	enum class EFFECT3D_TYPE
	{
		NONE = 0,
		CHECK,			//�`�F�b�N�|�C���g
		HIT,			//�q�b�g�G�t�F�N�g
		THUNDER,		//��
		FLASH,			//�M��
		FIRE,			//��
		EXPLOSION,		//����
		MAX
	};

	CEffect3D(int nPriority = PRIORITY_EFFECT3D);		//�R���X�g���N�^
	~CEffect3D();										//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CEffect3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, EFFECT3D_TYPE type);

private:
	EFFECT3D_TYPE m_type;		//�G�t�F�N�g�̎��
	CControl *m_pControl;		//�R���g���[���N���X�̃|�C���^
};

#endif // !_EFFECT3D_H_