#pragma once

class GApplication
{
public:
	static bool Initialize();
	static void Update();
	static void OnGUI();
	static void Run();
	static void Release();

private:
	static bool imGguiInitialize();
	static void imGuiRender();
};