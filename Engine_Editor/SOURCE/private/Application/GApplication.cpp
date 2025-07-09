//Editor
#include "Application/GApplication.h"
#include "Editor/GEditor.h"
#include "Windows/GEditorWindow.h"
#include "Windows/GInspectorWindow.h"
//Core
#include "HighLevelInterface/IApplication.h"
#include "Renderer/RRenderer.h"
#include "Actor/AActor.h"
#include "Component/Transform/JTransform.h"
#include "Graphics/RRenderTarget.h"
#include "Resource/RTexture.h"



extern IApplication application;

map<wstring, GEditorWindow*> GApplication::mEditorWindows;
ImGuiWindowFlags GApplication::mFlag = ImGuiWindowFlags_None;
ImGuiDockNodeFlags GApplication::mDockspaceFlags = ImGuiDockNodeFlags_None;
GApplication::EState GApplication::mState = GApplication::EState::Active;
bool GApplication::mFullScreen = true;
FVector2 GApplication::mViewportBounds[2] = {};
FVector2 GApplication::mViewportSize;
bool GApplication::mViewportFocused = false;
bool GApplication::mViewportHovered = false;
RRenderTarget* GApplication::mFrameBuffer = nullptr;

bool GApplication::Initialize()
{
	imGguiInitialize();
	mFrameBuffer = renderer::FrameBuffer;
	GInspectorWindow* inspector = new GInspectorWindow();
	mEditorWindows.insert(make_pair(L"InspectorWindow", inspector));

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

void GApplication::OpenProject()
{

}

void GApplication::NewScene()
{

}

void GApplication::SaveScene()
{

}

void GApplication::SaveSceneAs()
{

}

void GApplication::OpenScene(const filesystem::path& path)
{

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

	/*io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
	io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;*/


	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

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

	// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
	// because it would be confusing to have two docking targets within each others.
	mFlag = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	if (mFullScreen)
	{
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->Pos);
		ImGui::SetNextWindowSize(viewport->Size);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		mFlag |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		mFlag |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	}

	// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
	// and handle the pass-thru hole, so we ask Begin() to not render a background.
	if (mDockspaceFlags & ImGuiDockNodeFlags_PassthruCentralNode)
		mFlag |= ImGuiWindowFlags_NoBackground;

	// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
	// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
	// all active windows docked into it will lose their parent and become undocked.
	// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
	// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	bool Active = static_cast<bool>(mState);
	ImGui::Begin("GApplication", &Active, mFlag);
	ImGui::PopStyleVar();

	if (mFullScreen)
		ImGui::PopStyleVar(2);

	// DockSpace
	ImGuiIO& io = ImGui::GetIO();
	ImGuiStyle& style = ImGui::GetStyle();
	float minWinSizeX = style.WindowMinSize.x;
	style.WindowMinSize.x = 370.0f;
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), mDockspaceFlags);
	}

	style.WindowMinSize.x = minWinSizeX;

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Open Project...", "Ctrl+O"))
				OpenProject();

			ImGui::Separator();

			if (ImGui::MenuItem("New Scene", "Ctrl+N"))
				NewScene();

			if (ImGui::MenuItem("Save Scene", "Ctrl+S"))
				SaveScene();

			if (ImGui::MenuItem("Save Scene As...", "Ctrl+Shift+S"))
				SaveSceneAs();

			ImGui::Separator();

			if (ImGui::MenuItem("Exit"))
				application.Close();

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Script"))
		{
			if (ImGui::MenuItem("Reload assembly", "Ctrl+R"))
			{
				//ScriptEngine::ReloadAssembly(); ���� C#��ũ��Ʈ �߰������ ����� �߰��� ����
			}

			ImGui::EndMenu();
		}


		ImGui::EndMenuBar();
	}

	for (auto iter : mEditorWindows)
		iter.second->Run();

	// viewport
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
	ImGui::Begin("Scene");

	auto viewportMinRegion = ImGui::GetWindowContentRegionMin(); // 씬뷰의 최소 좌표
	auto viewportMaxRegion = ImGui::GetWindowContentRegionMax(); // 씬뷰의 최대 좌표
	auto viewportOffset = ImGui::GetWindowPos(); // 씬뷰의 위치

	const int letTop = 0;
	mViewportBounds[letTop] = { viewportMinRegion.x + viewportOffset.x, viewportMinRegion.y + viewportOffset.y };

	const int rightBottom = 1;
	mViewportBounds[rightBottom] = { viewportMaxRegion.x + viewportOffset.x, viewportMaxRegion.y + viewportOffset.y };

	// check if the mouse,keyboard is on the Sceneview
	mViewportFocused = ImGui::IsWindowFocused();
	mViewportHovered = ImGui::IsWindowHovered();

	// to do : mouse, keyboard event
	// 

	ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
	mViewportSize = { viewportPanelSize.x, viewportPanelSize.y };
	RTexture* texture = mFrameBuffer->GetAttachmentTexture(0);
	ImGui::Image((ImTextureID)texture->GetSRV().Get(), ImVec2{ mViewportSize.x, mViewportSize.y }
	, ImVec2{ 0, 0 }, ImVec2{ 1, 1 });

	// Open Scene by drag and drop
	if (ImGui::BeginDragDropTarget())
	{
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("PROJECT_ITEM"))
		{
			const wchar_t* path = (const wchar_t*)payload->Data;
			OpenScene(path);
		}
		ImGui::EndDragDropTarget();
	}

	// To do : guizmo

	ImGui::End();
	ImGui::PopStyleVar();

	ImGui::End();

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