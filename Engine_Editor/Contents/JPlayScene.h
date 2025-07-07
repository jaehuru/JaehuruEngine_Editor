#pragma once
#include "Scene/JScene.h"

class APlayer;

class JPlayScene : public JScene
{
public:
	JPlayScene();
	~JPlayScene();

	void	Initialize()	override;
	void	Update()		override;
	void	LateUpdate()	override;
	void	Render()		override;

	void	OnEnter()		override;
	void	OnExit()		override;

private:
};

