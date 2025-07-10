//Editor
#include "Application/GApplication.h"
#include "Editor/GEditor.h"
#include "Windows/GEditorWindow.h"
#include "Windows/GInspectorWindow.h"
#include "Editor/GImguiEditor.h"
//Core
#include "HighLevelInterface/JApplication.h"
#include "Renderer/RRenderer.h"
#include "Actor/AActor.h"
#include "Component/Transform/JTransform.h"
#include "Graphics/RRenderTarget.h"
#include "Resource/RTexture.h"
#include "Helpers/Input.h"
#include "Component/Camera/JCamera.h"
#include "Event/JMouseEvent.h"



extern JApplication application;

RRenderTarget* GApplication::mFrameBuffer = nullptr;
GImguiEditor* GApplication::mImguiEditor = nullptr;
map<wstring, GEditorWindow*> GApplication::mEditorWindows;
ImGuiWindowFlags GApplication::mFlag = ImGuiWindowFlags_None;
ImGuiDockNodeFlags GApplication::mDockspaceFlags = ImGuiDockNodeFlags_None;
GApplication::EState GApplication::mState = GApplication::EState::Active;
bool GApplication::mFullScreen = true;
FVector2 GApplication::mViewportBounds[2] = {};
FVector2 GApplication::mViewportSize;
bool GApplication::mViewportFocused = false;
bool GApplication::mViewportHovered = false;
int GApplication::mGuizmoType = -1;
EventCallbackFn GApplication::mEventCallback = nullptr;

bool GApplication::Initialize()
{
	mImguiEditor = new GImguiEditor();
	mFrameBuffer = renderer::FrameBuffer;

	mImguiEditor->Initialize();
	GInspectorWindow* inspector = new GInspectorWindow();
	mEditorWindows.insert(make_pair(L"InspectorWindow", inspector));
	mEventCallback = &GApplication::OnEvent;

	return true;
}

void GApplication::Update()
{
}

void GApplication::OnGUI()
{
	mImguiEditor->Begin();
	OnImGuiRender();
	mImguiEditor->End();
}

void GApplication::Run()
{
	Update();
	OnGUI();
}

void GApplication::Release()
{
	for (auto iter : mEditorWindows)
	{
		delete iter.second;
		iter.second = nullptr;
	}

	// Cleanup
	delete mImguiEditor;
	mImguiEditor = nullptr;
}

void GApplication::OnEvent(IEvent& e)
{
	if (!e.Handled)
	{
		mImguiEditor->OnEvent(e);
	}
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

void GApplication::OnImGuiRender()
{
	// Load Fonts
	// - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
	// - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
	// - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
	// - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
	// - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
	// - Read 'docs/FONTS.md' for more instructions and details.
	// - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
	//io.Fonts->AddFontDefault();
	//io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
	//ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
	//IM_ASSERT(font != NULL);

	// Our state
	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

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
	ImGui::Begin("EditorApplication", &Active, mFlag);
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
				//ScriptEngine::ReloadAssembly();
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

	auto viewportMinRegion = ImGui::GetWindowContentRegionMin(); 
	auto viewportMaxRegion = ImGui::GetWindowContentRegionMax(); 
	auto viewportOffset = ImGui::GetWindowPos(); 

	const int letTop = 0;
	const int rightBottom = 1;
	mViewportBounds[letTop] = { viewportMinRegion.x + viewportOffset.x, viewportMinRegion.y + viewportOffset.y };
	mViewportBounds[rightBottom] = { viewportMaxRegion.x + viewportOffset.x, viewportMaxRegion.y + viewportOffset.y };

	// check if the mouse,keyboard is on the Sceneview
	mViewportFocused = ImGui::IsWindowFocused();
	mViewportHovered = ImGui::IsWindowHovered();

	// to do : mouse, keyboard event
	mImguiEditor->BlockEvent(!mViewportHovered);

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
	AActor* selectedActor = renderer::selectedActor;
	mGuizmoType = ImGuizmo::OPERATION::TRANSLATE;
	if (selectedActor && mGuizmoType != -1)
	{
		ImGuizmo::SetOrthographic(false);
		ImGuizmo::SetDrawlist();
		ImGuizmo::SetRect(mViewportBounds[0].x, mViewportBounds[0].y
			, mViewportBounds[1].x - mViewportBounds[0].x, mViewportBounds[1].y - mViewportBounds[0].y);

		// To do : guizmo...
		// game view camera setting

		// Scene Camera
		const FMatrix& viewMatrix = renderer::mainCamera->GetViewMatrix();
		const FMatrix& projectionMatrix = renderer::mainCamera->GetProjectionMatrix();

		// Object Transform
		JTransform* transform = selectedActor->GetComponent<JTransform>();
		FMatrix worldMatrix = transform->GetWorldMatrix();

		// snapping
		bool snap = Input::GetKey(EKeyCode::Leftcontrol);
		float snapValue = 0.5f;

		// snap to 45 degrees for rotation
		if (mGuizmoType == ImGuizmo::OPERATION::ROTATE)
			snapValue = 45.0f;

		float snapValues[3] = { snapValue, snapValue, snapValue };

		ImGuizmo::Manipulate(*viewMatrix.m, *projectionMatrix.m, static_cast<ImGuizmo::OPERATION>(mGuizmoType)
			, ImGuizmo::LOCAL, *worldMatrix.m, nullptr, snap ? snapValues : nullptr);

		if (ImGuizmo::IsUsing())
		{
			// Decompose matrix to translation, rotation and scale
			float translation[3];
			float rotation[3];
			float scale[3];
			ImGuizmo::DecomposeMatrixToComponents(*worldMatrix.m, translation, rotation, scale);

			// delta rotation from the current rotation
			FVector3 deltaRotation = FVector3(rotation) - transform->GetRotation();
			deltaRotation = transform->GetRotation() + deltaRotation;

			// set the new transform
			transform->SetScale(FVector3(scale));
			transform->SetRotation(FVector3(deltaRotation));
			transform->SetPosition(FVector3(translation));
		}
	}

	ImGui::End();	// Scene end
	ImGui::PopStyleVar();

	ImGui::End(); // dockspace end
}

void GApplication::SetCursorPos(double x, double y)
{
	MouseMovedEvent event(static_cast<float>(x), static_cast<float>(y));

	if (mEventCallback)
		mEventCallback(event);
}