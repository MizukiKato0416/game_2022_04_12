//================================================
//���b�V���t�B�[���h����
//Author:��������
//================================================
#include "renderer.h"
#include "meshfield.h"
#include "object3D.h"
#include "manager.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CMeshField::CMeshField(CObject::PRIORITY Priority):CObject(Priority)
{
	m_pTexture = nullptr;
	m_pVtxBuff = nullptr;
	m_pIdxBuff = nullptr;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_indexPos.clear();
	m_indexSavePos.clear();
	m_bufferPos.clear();
	m_indexRot.clear();
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLine = 0;
	m_nVertical = 0;
	m_indexMtxWorld.clear();
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================

//================================================
//�f�X�g���N�^
//================================================
CMeshField::~CMeshField()
{

}

//================================================
//����������
//================================================
HRESULT CMeshField::Init(void)
{
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//�ʒu�E�T�C�Y�ݒ菈��
	CObject::SetPos(m_pos);
	CObject::SetSize(m_size);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * ((m_nVertical + 1) * (m_nLine + 1)),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		nullptr);


	VERTEX_3D *pVtx;
	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	int nNum = 0;
	for (int nVertical = 0; nVertical < m_nVertical + 1; nVertical++)
	{
		for (int nLine = 0; nLine < m_nLine + 1; nLine++, nNum++)
		{
			//�v�f��ǉ�
			m_bufferPos.push_back(D3DXVECTOR3(-m_size.x / 2.0f + (m_size.x / m_nLine) * nLine,
			                                  0.0f,
			                                  m_size.z / 2.0f - (m_size.z / m_nVertical) * nVertical));

			//���_���W
			pVtx[nNum].pos = m_bufferPos[nNum];
			//�J���[
			pVtx[nNum].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			//�e�N�X�`��
			pVtx[nNum].tex = D3DXVECTOR2(0.0f + (1.0f * nLine), 0.0f + (1.0f * nVertical));
		}
	}

	//�@���x�N�g�������߂�
	D3DXVECTOR3 vec[2];		//�O�όv�Z�p�x�N�g��
	D3DXVECTOR3 vecNor;		//�@���x�N�g��

	//�O�όv�Z�̂��߂̃x�N�g�������߂�
	vec[0] = D3DXVECTOR3(pVtx[1].pos.x - pVtx[0].pos.x, pVtx[1].pos.y - pVtx[0].pos.y, pVtx[1].pos.z - pVtx[0].pos.z);
	vec[1] = D3DXVECTOR3(pVtx[m_nLine + 1].pos.x - pVtx[0].pos.x, pVtx[m_nLine + 1].pos.y - pVtx[0].pos.y, pVtx[m_nLine + 1].pos.z - pVtx[0].pos.z);

	//�O�όv�Z
	D3DXVec3Cross(&vecNor, &vec[0], &vec[1]);

	//�x�N�g���𐳋K������(�x�N�g���̑傫����1�ɂ���)
	D3DXVec3Normalize(&vecNor, &vecNor);

	//�@��
	nNum = 0;
	for (int nVertical = 0; nVertical < m_nVertical + 1; nVertical++)
	{
		for (int nLine = 0; nLine < m_nLine + 1; nLine++, nNum++)
		{
			pVtx[nNum].nor = D3DXVECTOR3(vecNor.x, vecNor.y, vecNor.z);
		}
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * ((m_nVertical - 1) * (m_nLine + 3) + (m_nLine + 1) * (m_nVertical + 1)),
								D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pIdxBuff, nullptr);

	WORD *pIdx;		//�C���f�b�N�X���ւ̃|�C���^
	//�C���f�b�N�X�o�b�t�@�����b�N���ԍ��f�[�^�ւ̃|�C���^���擾
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCnt1 = 0; nCnt1 < m_nVertical; nCnt1++)
	{
		for (int nCnt2 = 0; nCnt2 < m_nLine + 1; nCnt2++)
		{
			//�ԍ��f�[�^�̐ݒ�
			pIdx[(nCnt2 * 2) + 0 + (m_nLine + 2) * 2 * nCnt1] = static_cast<WORD>((m_nLine + 1) + nCnt2 + (m_nLine + 1) * nCnt1);
			pIdx[(nCnt2 * 2) + 1 + (m_nLine + 2) * 2 * nCnt1] = static_cast<WORD>(0 + nCnt2 + (m_nLine + 1) * nCnt1);
			//�v�f��ǉ�
			m_indexPos.push_back(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			m_indexPos.push_back(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			m_indexSavePos.push_back(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			m_indexSavePos.push_back(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			D3DXMATRIX temp;
			m_indexMtxWorld.push_back(temp);
			m_indexMtxWorld.push_back(temp);
			m_indexRot.push_back(m_rot);
			m_indexRot.push_back(m_rot);
		}
	}

	for (int nCnt3 = 0; nCnt3 < m_nVertical - 1; nCnt3++)
	{
		pIdx[((m_nLine + 1) * 2 + 0) * (nCnt3 + 1) + (2 * nCnt3)] = static_cast<WORD>(m_nLine + (m_nLine + 1) * nCnt3);
		pIdx[((m_nLine + 1) * 2 + 1) * (nCnt3 + 1) + (1 * nCnt3)] = static_cast<WORD>(m_nLine * 2 + 2 + (m_nLine + 1) * nCnt3);
		//�v�f��ǉ�
		m_indexPos.push_back(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		m_indexPos.push_back(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		m_indexSavePos.push_back(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		m_indexSavePos.push_back(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		D3DXMATRIX temp;
		m_indexMtxWorld.push_back(temp);
		m_indexMtxWorld.push_back(temp);
		m_indexRot.push_back(m_rot);
		m_indexRot.push_back(m_rot);
	}

	//�C���f�b�N�X�o�b�t�@���A�����b�N����
	m_pIdxBuff->Unlock();

	//���_���W��ۑ�
	for (int nIndexCnt1 = 0; nIndexCnt1 < m_nVertical; nIndexCnt1++)
	{
		for (int nIndexCnt2 = 0; nIndexCnt2 < m_nLine + 1; nIndexCnt2++)
		{
			//�ʒu��ݒ�
			m_indexSavePos[(nIndexCnt2 * 2) + 0 + (m_nLine + 2) * 2 * nIndexCnt1] = m_bufferPos[(m_nLine + 1) + nIndexCnt2 + (m_nLine + 1) * nIndexCnt1];
			m_indexSavePos[(nIndexCnt2 * 2) + 1 + (m_nLine + 2) * 2 * nIndexCnt1] = m_bufferPos[0 + nIndexCnt2 + (m_nLine + 1) * nIndexCnt1];
		}
	}

	for (int nIndexCnt3 = 0; nIndexCnt3 < m_nVertical - 1; nIndexCnt3++)
	{
		//�ʒu��ݒ�
		m_indexSavePos[((m_nLine + 1) * 2 + 0) * (nIndexCnt3 + 1) + (2 * nIndexCnt3)] = m_bufferPos[m_nLine + (m_nLine + 1) * nIndexCnt3];
		m_indexSavePos[((m_nLine + 1) * 2 + 1) * (nIndexCnt3 + 1) + (1 * nIndexCnt3)] = m_bufferPos[(m_nLine * 2 + 2 + (m_nLine + 1) * nIndexCnt3)];
	}


	//�I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(CObject::OBJTYPE::FLOOR);

	//�ŏ������`�悷��
	Draw();
	//���_�̎擾�A�ݒ�
	GetIndexPos();

	return S_OK;
}

//================================================
//�I������
//================================================
void CMeshField::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	//�C���f�b�N�X�o�b�t�@�̔j��
	if (m_pIdxBuff != nullptr)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = nullptr;
	}

	//�I�u�W�F�N�g�̔j��
	Release();
}

//================================================
//�X�V����
//================================================
void CMeshField::Update(void)
{
	
}

//================================================
//�`�揈��
//================================================
void CMeshField::Draw(void)
{
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DXMatrixIdentity(&m_mtxWorld);		//���[���h�}�g���b�N�X�̏�����

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);

	pDevice->SetFVF(FVF_VERTEX_3D);					//���_�t�H�[�}�b�g�̐ݒ�

	pDevice->SetTexture(0, m_pTexture);				//�e�N�X�`���̐ݒ�

	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
									0,
									0,
									((m_nLine + 1) * (m_nVertical + 1)),				//���_�̐�
									0,													//�J�n���钸�_�̃C���f�b�N�X
									2 * m_nLine * m_nVertical + (m_nVertical * 4) - 4);	//�`�悷��v���~�e�B�u��
}

//================================================
//��������
//================================================
CMeshField* CMeshField::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, const D3DXVECTOR3 &rot, const int &nLine, const int &nVertical)
{
	//�C���X�^���X�̐���
	CMeshField *pMeshField = nullptr;
	if (pMeshField == nullptr)
	{
		pMeshField = new CMeshField;
		if (pMeshField != nullptr)
		{
			//�ϐ�������
			pMeshField->m_rot = rot;
			pMeshField->m_nLine = nLine;
			pMeshField->m_nVertical = nVertical;
			pMeshField->m_pos = pos;
			pMeshField->m_size = size;
			//����������
			pMeshField->Init();
		}
	}
	return pMeshField;
}

//================================================
//�e�N�X�`�����蓖�ď���
//================================================
void CMeshField::BindTexture(const LPDIRECT3DTEXTURE9 &pTexture)
{
	m_pTexture = pTexture;
}

//================================================
//�����蔻��
//================================================
bool CMeshField::Collision(CObject *&pSubjectObject, const float &fRadius)
{
	//���n���Ă��邩�ǂ���
	bool bLand = false;

	//�I�u�W�F�N�g��������|�C���^
	vector<CObject*> object;

	//�擪�̃|�C���^����
	object = CObject::GetObject(static_cast<int>(CObject::PRIORITY::MESH_FIELD));
	int nProprty_Size = object.size();

	for (int nCnt = 0; nCnt < nProprty_Size; nCnt++)
	{
		if (object[nProprty_Size]->GetObjType() == CObject::OBJTYPE::FLOOR)
		{
			//�|�C���^��CMeshField�ɃL���X�g
			CMeshField *pMeshField = nullptr;
			pMeshField = (CMeshField*)object[nProprty_Size];

			for (int nCnt1 = 0; nCnt1 < 2 * pMeshField->m_nLine * pMeshField->m_nVertical + (pMeshField->m_nVertical * 4) - 4; nCnt1++)
			{
				//�Ώۂ̌��݈ʒu�擾
				D3DXVECTOR3 pos = pSubjectObject->GetPos();
				D3DXVECTOR3 diff = pos - pMeshField->m_indexPos[nCnt1];
				if (D3DXVec3LengthSq(&diff) > fRadius*fRadius)
				{
					continue;
				}

				

				////���g����Ώۂ̃I�u�W�F�N�g�܂ł̋��������߂�
				//float fSubjectRadius = sqrtf((pos.x - pMeshField->m_indexPos[nCnt1].x) * (pos.x - pMeshField->m_indexPos[nCnt1].x) +
				//                             (pos.z - pMeshField->m_indexPos[nCnt1].z) * (pos.z - pMeshField->m_indexPos[nCnt1].z));

				////�w�肳�ꂽ�͈͓��ɂ���|���S�����������蔻����s��
				//if (fSubjectRadius > fRadius)
				//{
				//	continue;
				//}

				//�e���_����e���_�̃x�N�g�����Z�o
				D3DXVECTOR3 vecVtx[VERTEX_3D_NUM - 1];
				
				//����
				if (nCnt1 % 2 == 0)
				{
					vecVtx[0] = pMeshField->m_indexPos[nCnt1 + 1] - pMeshField->m_indexPos[nCnt1];
					vecVtx[1] = pMeshField->m_indexPos[nCnt1 + 2] - pMeshField->m_indexPos[nCnt1 + 1];
					vecVtx[2] = pMeshField->m_indexPos[nCnt1] - pMeshField->m_indexPos[nCnt1 + 2];
				}
				else
				{//�
					vecVtx[0] = pMeshField->m_indexPos[nCnt1] - pMeshField->m_indexPos[nCnt1 + 2];
					vecVtx[1] = pMeshField->m_indexPos[nCnt1 + 1] - pMeshField->m_indexPos[nCnt1];
					vecVtx[2] = pMeshField->m_indexPos[nCnt1 + 2] - pMeshField->m_indexPos[nCnt1 + 1];
				}

				//�@���ۑ��p
				D3DXVECTOR3 vecNor;

				D3DXVECTOR3 vecVtxInv = -vecVtx[2];

				//�|���S���̖@�������߂�
				D3DXVec3Cross(&vecNor, &vecVtx[0], &vecVtxInv);

				//nCnt����̎�
				if (nCnt1 % 2 == 1)
				{
					vecNor *= -1.0f;
				}

				//�x�N�g���𐳋K������(�x�N�g���̑傫����1�ɂ���)
				D3DXVec3Normalize(&vecNor, &vecNor);

				//�e���_����Ώۂ̌��݈ʒu�܂ł̃x�N�g�����Z�o
				D3DXVECTOR3 vecObj[VERTEX_3D_NUM - 1];
				vecObj[0] = pos - pMeshField->m_indexPos[nCnt1];
				vecObj[1] = pos - pMeshField->m_indexPos[nCnt1 + 1];
				vecObj[2] = pos - pMeshField->m_indexPos[nCnt1 + 2];

				//�Ώۂ�1�t���[���O�̈ʒu�擾
				D3DXVECTOR3 posOld = pSubjectObject->GetPosOld();

				//�e���_����Ώۂ�1�t���[���O�̈ʒu�܂ł̃x�N�g�����Z�o
				D3DXVECTOR3 vecObjOld[VERTEX_3D_NUM - 1];
				vecObjOld[0] = posOld - pMeshField->m_indexPos[nCnt1];
				vecObjOld[1] = posOld - pMeshField->m_indexPos[nCnt1 + 1];
				vecObjOld[2] = posOld - pMeshField->m_indexPos[nCnt1 + 2];

				//�e���_����Ώۂ̌��݈ʒu�܂ł̃x�N�g���Ɗe���_����e���_�̃x�N�g���̊O��(2D)�����߂�
				float fvecCross[VERTEX_3D_NUM - 1];
				//�e���_����Ώۂ�1�t���[���O�̈ʒu�܂ł̃x�N�g���Ɗe���_����e���_�̃x�N�g���̊O��(2D)�����߂�
				float fvecCrossOld[VERTEX_3D_NUM - 1];

				for (int nCntVec = 0; nCntVec < VERTEX_3D_NUM - 1; nCntVec++)
				{
					//�O�ς̌v�Z
					fvecCross[nCntVec] = (vecVtx[nCntVec].x * vecObj[nCntVec].z) - (vecObj[nCntVec].x * vecVtx[nCntVec].z);
					fvecCrossOld[nCntVec] = (vecVtx[nCntVec].x * vecObjOld[nCntVec].z) - (vecObjOld[nCntVec].x * vecVtx[nCntVec].z);

					//nCnt����̎�
					if (nCnt1 % 2 == 1)
					{
						fvecCross[nCntVec] *= -1.0f;
						fvecCrossOld[nCntVec] *= -1.0f;
					}
				}
				
				//�|���S���͈͓̔��ɂ��邩�ǂ���
				if ((fvecCross[0] <= 0.0f && fvecCross[1] <= 0.0f && fvecCross[2] <= 0.0f) ||
					(fvecCrossOld[0] <= 0.0f && fvecCrossOld[1] <= 0.0f && fvecCrossOld[2] <= 0.0f))
				{
					//�|���S���̈ʒu����Ώۂ̌��݂̈ʒu�̃x�N�g�����Z�o
					D3DXVECTOR3 vecPos;
					vecPos = pos - pMeshField->m_indexPos[nCnt1];

					//�Z�o�����x�N�g���Ɩ@���̃x�N�g���̓��ς����߂�
					float fVecDot;
					fVecDot = D3DXVec3Dot(&vecNor, &vecPos);

					//�|���S���̒��_����Ώۂ�1�t���[���O�̈ʒu�̃x�N�g�����Z�o
					D3DXVECTOR3 vecPosOld;
					vecPosOld = posOld - pMeshField->m_indexPos[nCnt1];

					//�Z�o�����x�N�g���Ɩ@���̃x�N�g���̓��ς����߂�
					float fVecDotOld;
					fVecDotOld = D3DXVec3Dot(&vecNor, &vecPosOld);

					//���ς̌v�Z���ʂ��}�C�i�X�̎�
					if (fVecDot < 0.0f && fVecDotOld >= -FLT_EPSILON * 10000)
					{
						//�����o���ʒu�����߂�
						D3DXVECTOR3 objectPos = pos;

						objectPos.y = pMeshField->m_indexPos[nCnt1].y - 1.0f / vecNor.y *
							          (vecNor.x * (objectPos.x - pMeshField->m_indexPos[nCnt1].x) +
								       vecNor.z * (objectPos.z - pMeshField->m_indexPos[nCnt1].z));

						pSubjectObject->SetPos(objectPos);
						bLand = true;
					}
				}
			}
		}
	}
	return bLand;
}

//================================================
//���_���W�ݒ菈��
//================================================
void CMeshField::SetVtxPos(const int &nNumVtx, const D3DXVECTOR3 &pos)
{
	VERTEX_3D *pVtx;
	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	m_bufferPos[nNumVtx] = pos;
	//���_���W
	pVtx[nNumVtx].pos = m_bufferPos[nNumVtx];

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	//WORD *pIdx;		//�C���f�b�N�X���ւ̃|�C���^
	////�C���f�b�N�X�o�b�t�@�����b�N���ԍ��f�[�^�ւ̃|�C���^���擾
	//m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	//for (int nCnt1 = 0; nCnt1 < m_nVertical; nCnt1++)
	//{
	//	for (int nCnt2 = 0; nCnt2 < m_nLine + 1; nCnt2++)
	//	{
	//		//�ԍ��f�[�^�̐ݒ�
	//		pIdx[(nCnt2 * 2) + 0 + (m_nLine + 2) * 2 * nCnt1] = static_cast<WORD>((m_nLine + 1) + nCnt2 + (m_nLine + 1) * nCnt1);
	//		pIdx[(nCnt2 * 2) + 1 + (m_nLine + 2) * 2 * nCnt1] = static_cast<WORD>(0 + nCnt2 + (m_nLine + 1) * nCnt1);
	//	}
	//}

	//for (int nCnt3 = 0; nCnt3 < m_nVertical - 1; nCnt3++)
	//{
	//	pIdx[((m_nLine + 1) * 2 + 0) * (nCnt3 + 1) + (2 * nCnt3)] = static_cast<WORD>(m_nLine + (m_nLine + 1) * nCnt3);
	//	pIdx[((m_nLine + 1) * 2 + 1) * (nCnt3 + 1) + (1 * nCnt3)] = static_cast<WORD>(m_nLine * 2 + 2 + (m_nLine + 1) * nCnt3);
	//}

	////�C���f�b�N�X�o�b�t�@���A�����b�N����
	//m_pIdxBuff->Unlock();

	//���_���W��ۑ�
	for (int nIndexCnt1 = 0; nIndexCnt1 < m_nVertical; nIndexCnt1++)
	{
		for (int nIndexCnt2 = 0; nIndexCnt2 < m_nLine + 1; nIndexCnt2++)
		{
			//�ʒu��ݒ�
			m_indexSavePos[(nIndexCnt2 * 2) + 0 + (m_nLine + 2) * 2 * nIndexCnt1] = m_bufferPos[(m_nLine + 1) + nIndexCnt2 + (m_nLine + 1) * nIndexCnt1];
			m_indexSavePos[(nIndexCnt2 * 2) + 1 + (m_nLine + 2) * 2 * nIndexCnt1] = m_bufferPos[0 + nIndexCnt2 + (m_nLine + 1) * nIndexCnt1];
		}
	}

	for (int nIndexCnt3 = 0; nIndexCnt3 < m_nVertical - 1; nIndexCnt3++)
	{
		//�ʒu��ݒ�
		m_indexSavePos[((m_nLine + 1) * 2 + 0) * (nIndexCnt3 + 1) + (2 * nIndexCnt3)] = m_bufferPos[m_nLine + (m_nLine + 1) * nIndexCnt3];
		m_indexSavePos[((m_nLine + 1) * 2 + 1) * (nIndexCnt3 + 1) + (1 * nIndexCnt3)] = m_bufferPos[(m_nLine * 2 + 2 + (m_nLine + 1) * nIndexCnt3)];
	}
}

//================================================
//�C���f�b�N�X�o�b�t�@�[�̒��_�ʒu�擾����
//================================================
void CMeshField::GetIndexPos(void)
{
	D3DXMATRIX mtxRot, mtxTrans;			//�v�Z�p�}�g���b�N�X

	//�e�̃��[���h�}�g���b�N�X
	D3DXMATRIX mtxParent;

	for (int nCntVtx = 0; nCntVtx < (int)m_indexMtxWorld.size(); nCntVtx++)
	{
		D3DXMatrixIdentity(&m_indexMtxWorld[nCntVtx]);		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&mtxParent);						//���[���h�}�g���b�N�X�̏�����

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&m_indexMtxWorld[nCntVtx], &m_indexMtxWorld[nCntVtx], &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, m_indexSavePos[nCntVtx].x, m_indexSavePos[nCntVtx].y, m_indexSavePos[nCntVtx].z);
		D3DXMatrixMultiply(&m_indexMtxWorld[nCntVtx], &m_indexMtxWorld[nCntVtx], &mtxTrans);

		//�e�̃}�g���b�N�X
		mtxParent = m_mtxWorld;

		//�Z�o�����e�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃��[���h�}�g���b�N�X���|�����킹��
		D3DXMatrixMultiply(&m_indexMtxWorld[nCntVtx], &m_indexMtxWorld[nCntVtx], &mtxParent);
	}

	//���_�̐ݒ�
	for (int nCntVtxPos = 0; nCntVtxPos < (int)m_indexMtxWorld.size(); nCntVtxPos++)
	{
		m_indexPos[nCntVtxPos] = D3DXVECTOR3(m_indexMtxWorld[nCntVtxPos]._41, m_indexMtxWorld[nCntVtxPos]._42, m_indexMtxWorld[nCntVtxPos]._43);
	}
}
