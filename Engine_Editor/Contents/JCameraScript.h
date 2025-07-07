#pragma once

#include "Component/Script/JScript.h"


class JCameraScript : public JScript
{
public:
	JCameraScript();
	~JCameraScript();

	void	Initialize()	override;
	void	Update()		override;
	void	LateUpdate()	override;
	void	Render()		override;

private:

};

