#pragma once

#include "Entity/GEntity.h"



class GEditor : public GEntity
{
public:
	enum class EState
	{
		Paused,
		Active,
		Disabled,
		Destroyed
	};

	GEditor();
	virtual ~GEditor();

	virtual void Initialize();
	virtual void Update();
	virtual void OnGUI();
	virtual void OnEnable();
	virtual void OnDisable();
	virtual void OnDestroy();

private:
	EState mState;
};