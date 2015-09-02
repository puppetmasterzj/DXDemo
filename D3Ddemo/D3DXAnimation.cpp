#include "stdafx.h"
#include "D3DXAnimation.h"


CD3DXAnimation::CD3DXAnimation(IDirect3DDevice9* device)
	:m_pDevice(device),
	 m_pAllocateHier(NULL),
	 m_pAnimController(NULL),
	 m_pFrameRoot(NULL),
	 m_pBoneMatrix(NULL)
{
}


CD3DXAnimation::~CD3DXAnimation(void)
{
	D3DXFrameDestroy(m_pFrameRoot, m_pAllocateHier);
	SAFE_RELEASE(m_pAnimController);
	SAFE_DELETE(m_pAllocateHier);
}

//--------------------------------------------------------------------------------------
// Name: SetupBoneMatrixPointers()
// Desc: ���úø�����ܵ���ϱ任����
//--------------------------------------------------------------------------------------
HRESULT CD3DXAnimation::SetupBoneMatrixPointers( LPD3DXFRAME pFrameBase, LPD3DXFRAME pFrameRoot )
{
	if( pFrameBase->pMeshContainer != NULL )
	{
		D3DXFRAME_DERIVED* pFrame = NULL;
		D3DXMESHCONTAINER_DERIVED* pMeshContainer = (D3DXMESHCONTAINER_DERIVED*)pFrameBase->pMeshContainer;

		// if there is a skinmesh, then setup the bone matrices
		if (pMeshContainer->pSkinInfo != NULL)
		{
			UINT cBones = pMeshContainer->pSkinInfo->GetNumBones();
			pMeshContainer->ppBoneMatrixPtrs = new D3DXMATRIX*[cBones];
			for (UINT iBone = 0; iBone < cBones; iBone++)
			{
				pFrame = (D3DXFRAME_DERIVED*)D3DXFrameFind(pFrameRoot, pMeshContainer->pSkinInfo->GetBoneName(iBone));
				if (pFrame == NULL) return E_FAIL;

				pMeshContainer->ppBoneMatrixPtrs[iBone] = &pFrame->CombinedTransformationMatrix;
			}
		}
	}

	if (pFrameBase->pFrameSibling != NULL)
	{
		if (FAILED(SetupBoneMatrixPointers(pFrameBase->pFrameSibling, pFrameRoot)))
			return E_FAIL;
	}

	if (pFrameBase->pFrameFirstChild != NULL)
	{
		if (FAILED(SetupBoneMatrixPointers(pFrameBase->pFrameFirstChild, pFrameRoot)))
			return E_FAIL;
	}

	return S_OK;
}

//--------------------------------------------------------------------------------------
// Name: DrawFrame()
// Desc: ���ƹ���
//--------------------------------------------------------------------------------------
void CD3DXAnimation::DrawFrame( IDirect3DDevice9* pd3dDevice, LPD3DXFRAME pFrame )
{
	if (pFrame == NULL) return;
	LPD3DXMESHCONTAINER pMeshContainer;
	pMeshContainer = pFrame->pMeshContainer;                    // ȡ����������
	while( pMeshContainer != NULL )                      
	{
		DrawMeshContainer(pd3dDevice, pMeshContainer, pFrame);  // ���Ʒǿ���Ƥ����
		pMeshContainer = pMeshContainer->pNextMeshContainer;    // ����������������
	}

	DrawFrame(pd3dDevice, pFrame->pFrameSibling);               // �����ֵܿ��
	DrawFrame(pd3dDevice, pFrame->pFrameFirstChild);            // �����ӿ��
}

//--------------------------------------------------------------------------------------
// Name: DrawMeshContainer()
// Desc: ������Ƥ�����е���Ƥ����
//--------------------------------------------------------------------------------------
void CD3DXAnimation::DrawMeshContainer( IDirect3DDevice9* pd3dDevice, LPD3DXMESHCONTAINER pMeshContainerBase, LPD3DXFRAME pFrameBase )
{
	D3DXMESHCONTAINER_DERIVED* pMeshContainer = ( D3DXMESHCONTAINER_DERIVED* )pMeshContainerBase;
	D3DXFRAME_DERIVED* pFrame = ( D3DXFRAME_DERIVED* )pFrameBase;
	UINT iMaterial;
	UINT NumBlend;
	UINT iAttrib;
	DWORD AttribIdPrev;
	LPD3DXBONECOMBINATION pBoneComb;

	UINT iMatrixIndex;
	D3DXMATRIXA16 matTemp;
	D3DCAPS9 d3dCaps;
	pd3dDevice->GetDeviceCaps( &d3dCaps );

	// first check for skinning
	if( pMeshContainer->pSkinInfo != NULL )
	{
		AttribIdPrev = UNUSED32;
		pBoneComb = reinterpret_cast<LPD3DXBONECOMBINATION>( pMeshContainer->pBoneCombinationBuf->GetBufferPointer() );

		// Draw using default vtx processing of the device (typically HW)
		for( iAttrib = 0; iAttrib < pMeshContainer->NumAttributeGroups; iAttrib++ )
		{
			NumBlend = 0;
			for( DWORD i = 0; i < pMeshContainer->NumInfl; ++i )
			{
				if( pBoneComb[iAttrib].BoneId[i] != UINT_MAX )
				{
					NumBlend = i;
				}
			}

			if( d3dCaps.MaxVertexBlendMatrices >= NumBlend + 1 )
			{
				// first calculate the world matrices for the current set of blend weights and get the accurate count of the number of blends
				for( DWORD i = 0; i < pMeshContainer->NumInfl; ++i )
				{
					iMatrixIndex = pBoneComb[iAttrib].BoneId[i];
					if( iMatrixIndex != UINT_MAX )
					{
						D3DXMatrixMultiply( &matTemp, &pMeshContainer->pBoneOffsetMatrices[iMatrixIndex],
							pMeshContainer->ppBoneMatrixPtrs[iMatrixIndex] );
						pd3dDevice->SetTransform( D3DTS_WORLDMATRIX( i ), &matTemp );
					}
				}

				pd3dDevice->SetRenderState( D3DRS_VERTEXBLEND, NumBlend );

				// lookup the material used for this subset of faces
				if( ( AttribIdPrev != pBoneComb[iAttrib].AttribId ) || ( AttribIdPrev == UNUSED32 ) )
				{
					pd3dDevice->SetMaterial( &pMeshContainer->pMaterials[pBoneComb[iAttrib].AttribId].MatD3D );
					pd3dDevice->SetTexture( 0, pMeshContainer->ppTextures[pBoneComb[iAttrib].AttribId] );
					AttribIdPrev = pBoneComb[iAttrib].AttribId;
				}

				// draw the subset now that the correct material and matrices are loaded
				pMeshContainer->MeshData.pMesh->DrawSubset( iAttrib );
			}
		}
		pd3dDevice->SetRenderState( D3DRS_VERTEXBLEND, 0 );
	}
	else  // standard mesh, just draw it after setting material properties
	{
		pd3dDevice->SetTransform( D3DTS_WORLD, &pFrame->CombinedTransformationMatrix );

		for( iMaterial = 0; iMaterial < pMeshContainer->NumMaterials; iMaterial++ )
		{
			pd3dDevice->SetMaterial( &pMeshContainer->pMaterials[iMaterial].MatD3D );
			pd3dDevice->SetTexture( 0, pMeshContainer->ppTextures[iMaterial] );
			pMeshContainer->MeshData.pMesh->DrawSubset( iMaterial );
		}
	}
}

//--------------------------------------------------------------------------------------
// Name: UpdateFrameMatrics()
// Desc: ���¿���еı任����
//--------------------------------------------------------------------------------------
void CD3DXAnimation::UpdateFrameMatrices( LPD3DXFRAME pFrameBase, LPD3DXMATRIX pParentMatrix )
{
	if (pFrameBase == NULL || pParentMatrix == NULL) return;
	D3DXFRAME_DERIVED* pFrame = ( D3DXFRAME_DERIVED* )pFrameBase;

	// ����ǰ����������ڸ�������ƫ�ƾ������ۻ�����
	D3DXMatrixMultiply(&pFrame->CombinedTransformationMatrix, &pFrame->TransformationMatrix, pParentMatrix);

	UpdateFrameMatrices(pFrame->pFrameSibling, pParentMatrix);                              // �����ֵܹ���
	UpdateFrameMatrices(pFrame->pFrameFirstChild, &pFrame->CombinedTransformationMatrix);   // �����ӹ���
}

//---------------------------------------------------------
//Name:������¶���ⲿ���õĺ���
//Desc:���ڶ����Ĵ��������£�����
//---------------------------------------------------------

bool CD3DXAnimation::Init(LPCTSTR filename)
{
	m_pAllocateHier = new CAllocateHierarchy();
	D3DXLoadMeshHierarchyFromX(filename, D3DXMESH_MANAGED, m_pDevice, m_pAllocateHier, NULL, &m_pFrameRoot, &m_pAnimController);
	SetupBoneMatrixPointers(m_pFrameRoot, m_pFrameRoot);

	return true;
}

void CD3DXAnimation::SetAnimationByName(LPCTSTR name)
{
	LPD3DXANIMATIONSET pAnimationSet = NULL;
	m_pAnimController->GetAnimationSetByName(name, &pAnimationSet);
	m_pAnimController->SetTrackAnimationSet((UINT)1.0, pAnimationSet);
}

void CD3DXAnimation::SetMatrix(LPD3DXMATRIX mtrix)
{
	UpdateFrameMatrices(m_pFrameRoot, mtrix);
}

void CD3DXAnimation::UpdateAnimation(double timeDelay)
{
	m_pAnimController->AdvanceTime(timeDelay, NULL);
}

void CD3DXAnimation::Render()
{
	DrawFrame(m_pDevice, m_pFrameRoot);
}

