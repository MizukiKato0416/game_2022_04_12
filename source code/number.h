//===========================================
//�i���o�[����
//Authore:��������
//===========================================
#ifndef _NUMBER_H_
#define _NUMBER_H_

//================================================
//�}�N����`
//================================================
#define FVF_VERTEX_2D_NUMBER (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)	//���_�t�H�[�}�b�g
#define VERTEX_NUM_NUMBER (4)												//���_��

//========================================================
//�\���̂̒�`
//========================================================
typedef struct
{
	D3DXVECTOR3 pos;		//���_���W
	float rhw;				//1.0f�ŌŒ�
	D3DCOLOR col;			//���_�J���[
	D3DXVECTOR2 tex;		//�e�N�X�`�����W
} VERTEX_2D_NUMBER;

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CNumber
{
public:
	CNumber();			//�R���X�g���N�^
	~CNumber();							//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetNumber(int nNumber);
	void SetCol(D3DCOLORVALUE col);

	static CNumber *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size);
	void BindTexture(const LPDIRECT3DTEXTURE9 &pTexture);				//�e�N�X�`�����蓖��

private:
	LPDIRECT3DTEXTURE9 m_pTexture;			//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;						//�|���S���̈ʒu
	D3DXVECTOR3	m_size;						// �T�C�Y
};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_NUMBER_H_