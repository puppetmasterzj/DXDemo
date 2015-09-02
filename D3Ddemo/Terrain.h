/************************************************************************/
/*��װ��ά���ε���                                                                     */
/************************************************************************/
#ifndef __TERRAIN_H_
#define __TERRAIN_H_
#include <vector>
#include <string>
#pragma once
struct TERRAINVERTEX
{
	float _x, _y, _z;
	float _u, _v;
	TERRAINVERTEX(float x, float y, float z, float u, float v) : _x(x), _y(y),_z(z),_u(u),_v(v){}
	static const DWORD FVF = D3DFVF_XYZ | D3DFVF_TEX1;
};

class CTerrain
{
private:
	LPDIRECT3DDEVICE9	m_pDevice;				//�豸ָ��
	LPDIRECT3DTEXTURE9  m_pTexture;				//��������
	LPDIRECT3DINDEXBUFFER9 m_pIndexBuffer;		//��������
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;	//���㻺��

	std::vector<float> m_vHeightInfo;			//��Ÿ߶���Ϣ
			
	int m_nCellsPerRow;							//ÿ�еĵ�Ԫ��				
	int m_nCellsPerCol;							//ÿ�еĵ�Ԫ��
	int m_nVertsPerRow;							//ÿ�еĶ�����
	int m_nVertesPerCol;						//ÿ�еĶ�����
	int m_nNumVertices;							//�ܹ�������
	float m_fTerrainWidth;						//���εĿ��
	float m_fTerrainDepth;						//���ε����
	float m_fCellSpacing;						//��Ԫ��ļ��
	float m_fHeightScale;						//�߶�����ϵ��

public:
	CTerrain(IDirect3DDevice9 *pDv);
	virtual ~CTerrain(void);

	//���ļ��м��ظ߶�ͼ�Լ�����
	bool LoadTerrainFromFile(std::string RawFilename, std::string TextureFilename);
	//���γ�ʼ������(��������������࣬�߶ȱ���)
	bool InitTerrain(int nRows, int nCols, float fSpace, float fScale);
	//���Ƶ��κ���
	bool RenderTerrain(D3DXMATRIX* pMatWorld, bool bDrawFrame = false);
};
#endif

