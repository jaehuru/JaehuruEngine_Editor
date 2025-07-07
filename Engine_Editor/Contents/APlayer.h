#pragma once

#include "Actor/AActor.h"

class APlayer : public AActor
{
public:
	void Initialize()	override;
	void Update()		override;
	void LateUpdate()	override;
	void Render()		override;

private:
};

