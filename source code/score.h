//===========================================
//�X�R�A����
//Authore:��������
//===========================================
#ifndef _SCORE_H_
#define _SCORE_H_
#include "object.h"
#include "number.h"

//�O���錾
class CObject2D;

//================================================
//�}�N����`
//================================================
#define MAX_SCORE_POLYGON		(8)				//�|���S���̍ő吔
#define MAX_SCORE				(99999999)		//�X�R�A�̍ő�l
#define SCORE_POLYGON_WIDTH		(30.0f)			//�|���S���̕�
#define SCORE_POLYGON_HEIGHT	(60.0f)			//�|���S���̍���

//========================================================
//�\���̂̒�`
//========================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CScore : public CObject
{
public:
	CScore(CObject::PRIORITY Priority = CObject::PRIORITY::SCORE);	//�R���X�g���N�^
	~CScore();								//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetScore(const int &nScore);
	void AddScore(const int &nValue);
	int GetScore(void);
	CObject2D *GetConma(void) { return m_pConma; }
	CObject2D *GetMeter(void) { return m_pUnit; }
	CNumber *GetNumber(const int &nNumber);

	static CScore *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size);

private:
	CNumber *m_apNumber[MAX_SCORE_POLYGON];			//number�̃C���X�^���X
	int m_nScore;									//�X�R�A
	D3DXVECTOR3 m_pos;								//�ʒu
	D3DXVECTOR3 m_size;								//�T�C�Y
	CObject2D *m_pUnit;								//�P�ʂ̃|�C���^
	CObject2D *m_pConma;							//�X�R�A�̃|�C���^
};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_SCORE_H_