#include "DXUT.h"
#include "SingleAnimation.h"

void SingleAnimation::Initialize()
{
}

void SingleAnimation::Update()
{
	if (renderer->CurrentAnime->IsEndOnThisFrame == true)
	{
		Destroy(Base);
	}
}

void SingleAnimation::Release()
{
}
