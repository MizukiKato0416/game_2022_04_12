//===========================================
//�^�C������
//Author:��������
//===========================================
#ifndef _TIME_H_
#define _TIME_H_
#include "object.h"
#include "number.h"

//================================================
//�}�N����`
//================================================
#define MAX_TIME_POLYGON		(3)				//�|���S���̍ő吔
#define TIME_POLIGON_POSY		(30.0f)			//�^�C���̃|���S����posY
#define TIME_POLYGON_WIDTH		(50.0f)			//�|���S���̕�
#define TIME_POLYGON_HEIGHT		(80.0f)			//�|���S���̍���
#define START_TIME				(0)				//�ŏ��̃^�C��

//================================================
//�O���錾
//================================================

//========================================================
//�\���̂̒�`
//========================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CTime : public CObject
{
public:
	CTime(CObject::PRIORITY Priority = CObject::PRIORITY::UI);		//�R���X�g���N�^
	~CTime();								//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void AddTime(const int &nValue);
	void SetTime(const int &nTime);
	int GetTime(void);
	CNumber *GetNumber(const int nNumber);

	static CTime *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, const int &nStartTime);

private:
	CNumber *m_apNumber[MAX_TIME_POLYGON];	//number�̃C���X�^���X
	int m_nTime;							//�^�C��
	int m_nCounter;							//���Ԃ�ς��邽�߂̃J�E���^�[
	D3DXVECTOR3 m_pos;						//�ʒu
	D3DXVECTOR3 m_size;						//�T�C�Y
};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_SCORE_H_#pragma once
