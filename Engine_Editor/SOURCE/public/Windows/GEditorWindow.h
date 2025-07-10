#pragma once

#include "Entity/GEntity.h"



class GEditorWindow : public GEntity
{
public:
	enum class EState
	{
		Disable,
		Active,
		Destroy,
	};

	GEditorWindow();
	virtual ~GEditorWindow();

	virtual void	Initialize();
	virtual void	Update();
	virtual void	OnGUI();
	virtual void	Run();
	virtual void	OnEnable();
	virtual void	OnDisable();
	virtual void	OnDestroy();
	virtual void	OnEvent(IEvent& e);

	ImGuiWindowFlags	GetFlag() const { return mFlag; }
	EState				GetState() const { return mState; }
	ImVec2				GetSize() const { return mSize; }

	void	SetState(EState State) { mState = State; }
	void	SetSize(ImVec2 size) { mSize = size; }

private:
	ImGuiWindowFlags	mFlag;
	EState				mState;
	ImVec2				mSize;
};