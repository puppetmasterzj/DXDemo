/*!
 * \file AllocateHierarchy.h
 *
 * \author puppet_master
 * \date ���� 2015
 *
 * \΢��SDK�Դ��Ĺ��ڹ����������࣬���ڹ��������Ĵ����Լ����Ƹ���
 * \ע������ֱ��ʹ�ø��࣬���ǽ�������η�װ����ʹ�á�
 */

#ifndef __ALLOCATEHIERARCHY_H_
#define __ALLOCATEHIERARCHY_H_

//--------------------------------------------------------------------------------------
// Name: struct D3DXFRAME_DERIVED
// Desc: 
//--------------------------------------------------------------------------------------
struct D3DXFRAME_DERIVED : public D3DXFRAME
{
	D3DXMATRIXA16 CombinedTransformationMatrix;
};


//--------------------------------------------------------------------------------------
// Name: struct D3DXMESHCONTAINER_DERIVED
// Desc: Structure derived from D3DXMESHCONTAINER so we can add some app-specific
//       info that will be stored with each mesh
//--------------------------------------------------------------------------------------
struct D3DXMESHCONTAINER_DERIVED : public D3DXMESHCONTAINER
{
	//������Ϣ
	LPDIRECT3DTEXTURE9* ppTextures;       //��������  

	//������Ϣ             
	LPD3DXMESH pOrigMesh;					//ԭʼ����
	LPD3DXATTRIBUTERANGE pAttributeTable;	//���Ա�
	DWORD NumAttributeGroups;				//������������������������
	DWORD NumInfl;							//ÿ����������ܼ�������Ӱ��
	LPD3DXBUFFER pBoneCombinationBuf;		//������ϻ���
	D3DXMATRIX** ppBoneMatrixPtrs;			//������ϱ任����
	D3DXMATRIX* pBoneOffsetMatrices;		//������ʼ�任����
	DWORD NumPaletteEntries;				//������������
	bool UseSoftwareVP;						//�Ƿ�ʹ��������㴦��
	DWORD iAttributeSW;						// used to denote the split between SW and HW if necessary for non-indexed skinning
};

//--------------------------------------------------------------------------------------
// Name: class CAllocateHierarchy
// Desc: Custom version of ID3DXAllocateHierarchy with custom methods to create
//       frames and meshcontainers.
//������.X�ļ��м��������Լ���������
//--------------------------------------------------------------------------------------
class CAllocateHierarchy : public ID3DXAllocateHierarchy
{
private:
	HRESULT AllocateName( LPCSTR Name, LPSTR* pNewName );
	HRESULT GenerateSkinnedMesh( IDirect3DDevice9* pd3dDevice, D3DXMESHCONTAINER_DERIVED* pMeshContainer );
public:
	STDMETHOD( CreateFrame )( THIS_ LPCSTR Name, LPD3DXFRAME *ppNewFrame );
	STDMETHOD( CreateMeshContainer )( THIS_
		LPCSTR Name,
		CONST D3DXMESHDATA *pMeshData,
		CONST D3DXMATERIAL *pMaterials,
		CONST D3DXEFFECTINSTANCE *pEffectInstances,
		DWORD NumMaterials,
		CONST DWORD *pAdjacency,
		LPD3DXSKININFO pSkinInfo,
		LPD3DXMESHCONTAINER *ppNewMeshContainer );
	STDMETHOD( DestroyFrame )( THIS_ LPD3DXFRAME pFrameToFree );
	STDMETHOD( DestroyMeshContainer )( THIS_ LPD3DXMESHCONTAINER pMeshContainerBase );

	CAllocateHierarchy()
	{
	}
};

#endif


