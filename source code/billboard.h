//===========================================
//3D�|���S��(�r���{�[�h)����
//Author:��������
//===========================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_
#include "object3D.h"

//================================================
//�}�N����`
//================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CBillboard : public CObject
{
public:
	//�r���{�[�h�̏����̎��
	enum class BILLBOARD_MODE
	{
		NONE = 0,
		NORMAL,			//���ʂ̃r���{�[�h
		BESIDE_ONLY,	//���ɂ��������Ȃ��r���{�[�h
		MAX
	};

	CBillboard(int nPriority = PRIORITY_POLYGON_3D);	//�R���X�g���N�^
	~CBillboard();										//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CBillboard *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	D3DXVECTOR3 GetPos(void);								//�ʒu�擾����
	void SetPos(D3DXVECTOR3 pos, D3DXVECTOR3 size);			//�ʒu�ݒ菈��
	void SetTex(int nPattern, int nMaxPattern);				//�e�N�X�`���A�j���[�V�����ݒ菈��
	void SetTex(float fMoveTexU, float fMoveTexV);			//�e�N�X�`���ړ��ݒ菈��
	void SetCol(D3DCOLORVALUE col);							//�J���[�o�����[�ݒ菈��
	void SetCol(D3DXCOLOR col);								//�J���[�ݒ菈��
	D3DXCOLOR GetCol(void);									//�J���[�擾����
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);			//�e�N�X�`���ݒ菈��
	void SetMode(BILLBOARD_MODE mode) { m_mode = mode; }	//���[�h�ݒ菈��
	BILLBOARD_MODE GetMode(void) { return m_mode; }			//���[�h�擾����
	void SetCulling(bool bCulling);							//�J�����O�ݒ菈��
	void SetAlphaBlend(bool bAlphaBlend);					//���Z�����ݒ菈��
	void SetAlphaTest(bool bAlphaTest);						//���A�e�X�g�ݒ菈��
	void SetLighting(bool bLighting);						//���C�e�B���O�ݒ菈��

private:

protected:
	D3DXVECTOR3 m_pos;							//�|���S���̈ʒu
	D3DXVECTOR3 m_vtxPos[VERTEX_3D_NUM];		//���_�̈ʒu
	D3DXVECTOR3	m_size;							//�T�C�Y
	D3DXVECTOR3 m_rot;							//����
	D3DXVECTOR3 m_vtxRot[VERTEX_3D_NUM];		//���_�̌���
	LPDIRECT3DTEXTURE9 m_pTexture;				//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//���_�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;						//���[���h�}�g���b�N�X
	D3DXMATRIX m_vtxMtxWorld[VERTEX_3D_NUM];	//���_�̃��[���h�}�g���b�N�X
	BILLBOARD_MODE m_mode;						//�r���{�[�h�̏����̎��
	bool m_bCulling;							//�J�����O���s�����s��Ȃ���
	bool m_bAlphaBlend;							//���Z�������邩�ǂ���
	bool m_bAlphaTest;							//���e�X�g���邩�ǂ���
	bool m_bLighting;							//���C�e�B���O�L�����ǂ���
};

#endif // !_BILLBOARD_H_