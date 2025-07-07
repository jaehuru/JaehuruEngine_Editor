#pragma once

#include "Common/CommonInclude.h"
//imgui
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include "ImGuizmo.h"
#include "ImSequencer.h"
#include "ImZoomSlider.h"
#include "ImCurveEdit.h"
#include "GraphEditor.h"


class GEntity
{
public:
	GEntity();
	virtual ~GEntity();

	wstring& GetName() { return mName; }

	void SetName(const wstring& name) { mName = name; }

private:
	wstring mName;
};