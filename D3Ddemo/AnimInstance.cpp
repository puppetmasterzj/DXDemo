#include "stdafx.h"
#include "AnimInstance.h"


CAnimInstance::CAnimInstance(void)
{
}


CAnimInstance::~CAnimInstance(void)
{
	//delete m_pAnimController;
}

bool CAnimInstance::Init(IRenderRes* resource)
{
	IRenderActor::Init(resource);
	return m_pAnimController = ((CD3DXAnimation*)resource)->CloneAnimCtrl();
}



bool CAnimInstance::PlayAnimation(LPCTSTR name, bool isLoop)
{
	LPD3DXANIMATIONSET pAnimationSet = NULL;
	m_pAnimController->GetAnimationSetByName(name, &pAnimationSet);
	m_pAnimController->SetTrackAnimationSet(0, pAnimationSet);
	return true;
}

void CAnimInstance::Update(float delayTime)
{
	m_pAnimController->AdvanceTime(delayTime, NULL); 
}

void CAnimInstance::SetSpeed(float speed)
{
	m_fSpeed = speed;
}

int CAnimInstance::GetAnimationNum() const
{
	return m_pAnimController->GetMaxNumAnimationSets();
}

LPD3DXANIMATIONSET CAnimInstance::GetAnimationSet(int index) const
{
	if (index >= 0 && index < GetAnimationNum())
	{
		LPD3DXANIMATIONSET pAnimSet = NULL;
		m_pAnimController->GetAnimationSet(index, &pAnimSet);
		return pAnimSet;
	}
	return NULL;
}

