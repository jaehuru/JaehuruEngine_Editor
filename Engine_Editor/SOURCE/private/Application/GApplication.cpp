//Editor
#include "Application/GApplication.h"
#include "Editor/GEditor.h"
#include "Editor/GEditorWindow.h"
//Core
#include "HighLevelInterface/IApplication.h"
#include "Renderer/RRenderer.h"
#include "Actor/AActor.h"
#include "Component/Transform/JTransform.h"





extern IApplication application;

bool GApplication::Initialize()
{
	imGguiInitialize();

	return true;
}

void GApplication::Update()
{
}

void GApplication::OnGUI()
{
	imGuiRender();
}

void GApplication::Run()
{
	Update();
	OnGUI();
}

void GApplication::Release()
{
	// Cleanup
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

bool GApplication::imGguiInitialize()
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	// Setup Platform/Renderer backends
	ImGui_ImplWin32_Init(application.GetHwnd());

	RGraphicDevice_DX11*& graphicdevice = GetDevice();
	ID3D11Device* device = graphicdevice->GetID3D11Device().Get();
	ID3D11DeviceContext* device_context = graphicdevice->GetID3D11DeviceContext().Get();

	ImGui_ImplDX11_Init(device, device_context);

	return false;
}

void GApplication::imGuiRender()
{
	// Our state
	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	// Start the Dear ImGui frame
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	//imGuizmo
	ImGuiIO& io = ImGui::GetIO();

	ImGuizmo::SetOrthographic(false/*!isPerspective*/);
	ImGuizmo::SetDrawlist(ImGui::GetCurrentWindow()->DrawList);

	ImGuizmo::BeginFrame();

	UINT width = application.GetWidth();
	UINT height = application.GetHeight();
	float windowWidth = (float)ImGui::GetWindowWidth();
	float windowHeight = (float)ImGui::GetWindowHeight();

	RECT rect = { 0, 0, 0, 0 };
	::GetClientRect(application.GetHwnd(), &rect);

	// Transform start
	//ImGuizmo::SetRect(0, 0, width, height);
	ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, windowHeight);

	FMatrix viewMatirx;
	FMatrix projectionMatirx;

	if (renderer::mainCamera)
	{
		viewMatirx = renderer::mainCamera->GetViewMatrix();
		projectionMatirx = renderer::mainCamera->GetProjectionMatrix();
	}

	FMatrix modelMatrix;
	if (renderer::selectedActor)
	{
		modelMatrix = renderer::selectedActor->GetComponent<JTransform>()->GetWorldMatrix();
	}

	ImGuizmo::Manipulate(*viewMatirx.m, *projectionMatirx.m,
		ImGuizmo::OPERATION::TRANSLATE, ImGuizmo::LOCAL, *modelMatrix.m);

	// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);

	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
	{
		static float f = 0.0f;
		static int counter = 0;

		ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

		ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
		ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
		ImGui::Checkbox("Another Window", &show_another_window);

		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

		if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
			counter++;
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
		ImGui::End();
	}

	// 3. Show another simple window.
	if (show_another_window)
	{
		ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		ImGui::Text("Hello from another window!");
		if (ImGui::Button("Close Me"))
			show_another_window = false;
		ImGui::End();
	}

	// Rendering
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());


	// Update and Render additional Platform Windows
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
	}
}