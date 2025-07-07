#pragma once

#include "Entity/GEntity.h"



class GEditorWindow : public GEntity
{
public:
	GEditorWindow();
	virtual ~GEditorWindow();

	virtual void Initialize();
	virtual void Update();
	virtual void OnGUI();
	virtual void OnEnable();
	virtual void OnDisable();
	virtual void OnDestroy();

private:
};