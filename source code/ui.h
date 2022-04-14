//===========================================
//UI����
//Authore:��������
//===========================================
#ifndef _UI_H_
#define _UI_H_
#include "object2D.h"

//�O���錾
class CControl;

//================================================
//�}�N����`
//================================================
#define UI_CROSS_SIZE		(40.0f)		//�o�cUI�̃T�C�Y

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CUi : public CObject2D
{
public:
	//UI�̎��
	enum class TYPE
	{
		NONE = 0,
		PRESS_START,	//PRESSSTART
		MAX
	};

	CUi(CObject::PRIORITY Priority = CObject::PRIORITY::UI);	//�R���X�g���N�^
	~CUi();								//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CUi *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, const int &nPriolty, const TYPE &type);
	TYPE GetUIType(void) { return m_type; }		//��ގ擾����

private:
	TYPE m_type;						// UI�̎��
	LPDIRECT3DTEXTURE9 m_pTexture;		//�e�N�X�`���ւ̃|�C���^
	CControl *m_pControl;
	D3DXVECTOR3 m_pos;					//�ʒu
	D3DXVECTOR3 m_size;					//�T�C�Y
};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_UI_H_