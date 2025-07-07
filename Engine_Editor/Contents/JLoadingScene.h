#pragma once

#include "Scene/JScene.h"


class JLoadingScene : public JScene
{
public:
	JLoadingScene();
	~JLoadingScene();

	void	Initialize()	override;
	void	Update()		override;
	void	LateUpdate()	override;
	void	Render()		override;

	void	OnEnter()		override;
	void	OnExit()		override;

private:
	void	resourcesLoad(mutex& m);

private:
	bool		mbLoadCompleted;
	thread*		mResourcesLoadThread;
	mutex		mMutualExclusion;
};