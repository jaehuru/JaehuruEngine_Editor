#pragma once

#include "Windows/GEditorWindow.h"


class GEditor;

class GInspectorWindow : public GEditorWindow
{
public:
	GInspectorWindow();
	~GInspectorWindow();

	void	Initialize()	override;
	void	Update()		override;
	void	OnGUI()			override;
	void	Run()			override;
	void	OnEnable()		override;
	void	OnDisable()		override;
	void	OnDestroy()		override;

private:
	vector<GEditor*> mEditors;
};

