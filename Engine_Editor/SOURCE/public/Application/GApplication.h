#pragma once

#include "Entity/GEntity.h"
//Core
#include "Event/IEvent.h"

class GEditorWindow;
class RRenderTarget;
class GImguiEditor;
class KeyPressedEvent;

class GApplication
{
public:
	enum class EState
	{
		Disable,
		Active,
		Destroy,
	};

	template <typename T>
	T* GetWindow(const wstring& name)
	{
		auto iter = mEditorWindows.find(name);
		if (iter == mEditorWindows.end())
			return nullptr;

		return dynamic_cast<T*>(iter->second);
	}

	static bool		Initialize();
	static void		Update();
	static void		OnGUI();
	static void		Run();
	static void		Release();

	static void		OnEvent(IEvent& e);

	static void		OpenProject();
	static void		NewScene();
	static void		SaveScene();
	static void		SaveSceneAs();
	static void		OpenScene(const filesystem::path& path);

	static void		OnImGuiRender();

	//Event
	static void		SetKeyPressed(int keyCode, int scancode, int action, int mods);
	static void		SetCursorPos(double x, double y);

	static bool		OnKeyPressed(KeyPressedEvent& e);

	static void		SetGuizmoType(int type) { mGuizmoType = type; }

private:
	static RRenderTarget*		mFrameBuffer;
	static GImguiEditor*		mImguiEditor;

	static map<wstring, GEditorWindow*> mEditorWindows;

	static ImGuiWindowFlags		mFlag;
	static ImGuiDockNodeFlags	mDockspaceFlags;
	static EState				mState;
	static bool					mFullScreen;
	static FVector2				mViewportBounds[2];
	static FVector2				mViewportSize;
	static bool					mViewportFocused;
	static bool					mViewportHovered;
	static int					mGuizmoType;

	static EventCallbackFn		mEventCallback;
};