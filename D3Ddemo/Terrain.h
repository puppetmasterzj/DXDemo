/************************************************************************/
/*封装三维地形的类                                                                     */
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
	LPDIRECT3DDEVICE9	m_pDevice;				//设备指针
	LPDIRECT3DTEXTURE9  m_pTexture;				//纹理坐标
	LPDIRECT3DINDEXBUFFER9 m_pIndexBuffer;		//索引缓存
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;	//顶点缓存

	std::vector<float> m_vHeightInfo;			//存放高度信息
			
	int m_nCellsPerRow;							//每行的单元数				
	int m_nCellsPerCol;							//每列的单元数
	int m_nVertsPerRow;							//每行的顶点数
	int m_nVertesPerCol;						//每列的顶点数
	int m_nNumVertices;							//总共顶点数
	float m_fTerrainWidth;						//地形的宽度
	float m_fTerrainDepth;						//地形的深度
	float m_fCellSpacing;						//单元格的间距
	float m_fHeightScale;						//高度缩放系数

public:
	CTerrain(IDirect3DDevice9 *pDv);
	virtual ~CTerrain(void);

	//从文件中加载高度图以及纹理
	bool LoadTerrainFromFile(std::string RawFilename, std::string TextureFilename);
	//地形初始化函数(行数，列数，间距，高度比例)
	bool InitTerrain(int nRows, int nCols, float fSpace, float fScale);
	//绘制地形函数
	bool RenderTerrain(D3DXMATRIX* pMatWorld, bool bDrawFrame = false);
};
#endif

