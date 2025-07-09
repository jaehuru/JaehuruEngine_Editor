#include "Windows/GInspectorWindow.h"
#include "Editor/GEditor.h"




GInspectorWindow::GInspectorWindow()
{
	SetName("Inspector");
	SetSize(ImVec2(300, 600));
}

GInspectorWindow::~GInspectorWindow()
{
}

void GInspectorWindow::Initialize()
{
}

void GInspectorWindow::Update()
{
	for (GEditor* editor : mEditors)
	{
		editor->Update();
	}
}

void GInspectorWindow::OnGUI()
{

	for (GEditor* editor : mEditors)
	{
		editor->OnGUI();
	}
}

void GInspectorWindow::Run()
{
	bool Active = (bool)GetState();
	ImGui::Begin(GetName().c_str(), &Active, GetFlag());

	Update();
	OnGUI();

	ImGui::End();
}

void GInspectorWindow::OnEnable()
{
}

void GInspectorWindow::OnDisable()
{
}

void GInspectorWindow::OnDestroy()
{
}