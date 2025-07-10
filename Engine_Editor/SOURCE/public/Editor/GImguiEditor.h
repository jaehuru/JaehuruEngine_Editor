#pragma once
//Editor
#include "Windows/GEditorWindow.h"

class GImguiEditor : public GEditorWindow
{
public:
	GImguiEditor();
	~GImguiEditor();

	void Initialize() override;
	void Update() override;
	void OnGUI() override;
	void Run() override;
	void OnEnable() override;
	void OnDisable() override;
	void OnDestroy() override;
	void OnEvent(IEvent& e) override;

	void Begin();
	void End();
	void Release();
	void SetDarkThemeColors();

	void BlockEvent(bool block) { mBlockEvent = block; }

private:
	bool mBlockEvent;
};

