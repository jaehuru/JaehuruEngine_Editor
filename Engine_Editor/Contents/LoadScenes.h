#pragma once

#include "Scene/JSceneManager.h"
#include "JLoadingScene.h"


void LoadScenes()
{
	JSceneManager::CreateScene<JLoadingScene>(L"LoadingScene");

	JSceneManager::LoadScene(L"LoadingScene");
}

