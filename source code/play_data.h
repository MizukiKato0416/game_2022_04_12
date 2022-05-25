//===========================================
//�v���C�f�[�^�Ǘ�����
//Author:��������
//===========================================
#ifndef _PLAY_DATA_H_
#define _PLAY_DATA_H_
#include "main.h"

//�O���錾
class CGauge;
class CScore;

//================================================
//�}�N����`
//================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CPlayData
{
public:
	CPlayData();			//�R���X�g���N�^
	~CPlayData();			//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);
	void Uninit(void);

	void SetScore(const int &nScore) { m_nScore = nScore; }		//�X�R�A�̐ݒ�
	int GetScore(void) { return m_nScore; }						//�X�R�A�̎擾
	void SetScorePoint(CScore *&pScore) { m_pScore = pScore; }	//�X�R�A�̃|�C���^�ݒ菈��
	CScore *GetScorePoint(void) { return m_pScore; }			//�X�R�A�̃|�C���^�擾����
	void SetTime(const int &nTime) { m_nTime = nTime; }			//���Ԃ̐ݒ�
	int GetTime(void) { return m_nTime; }						//���Ԃ̎擾
	vector<bool> GetFlag(void) { return m_trophy_flag; }		// �Z�b�^�[
	void SetFlag(vector<bool> frag) { m_trophy_flag = frag; }	// �Z�b�^�[
	string GetPasword(void) { return m_pasword; }		// �Q�b�_�[
	void SetPasword(string pas) { m_pasword = pas; }	// �Z�b�^�[
	int GetPlayNum(void) { return m_play_num; }			// �Q�b�_�[
	void AddPlayNum(int num) { if (m_play_num >= INT_MAX) m_play_num = INT_MAX; m_play_num += num; }	// ���Z

private:
	//�����o�ϐ�
	int m_nScore;				//�X�R�A
	CScore *m_pScore;			//�X�R�A�̃|�C���^
	int m_nTime;				//����
	vector<bool> m_trophy_flag;	// �g���t�B�[�̃t���O
	string m_pasword;	// �p�X���[�h
	int m_play_num;		// �v���C��
};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_PLAY_DATA_H_