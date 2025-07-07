#include "JLoadingScene.h"
#include "JPlayScene.h"
//Engine
#include "HighLevelInterface/IApplication.h"
#include "Renderer/RRenderer.h"
#include "Scene/JSceneManager.h"
#include "Resource/RResources.h"
#include "Resource/RTexture.h"

extern IApplication application;

JLoadingScene::JLoadingScene() :
	mbLoadCompleted(false),
	mMutualExclusion(),
	mResourcesLoadThread()
{

}

JLoadingScene::~JLoadingScene()
{
	delete mResourcesLoadThread;
	mResourcesLoadThread = nullptr;
}

void JLoadingScene::Initialize()
{
	mResourcesLoadThread = new thread(&JLoadingScene::resourcesLoad, this, ref(mMutualExclusion));
}

void JLoadingScene::Update()
{

}

void JLoadingScene::LateUpdate()
{

}

void JLoadingScene::Render()
{
	if (mbLoadCompleted)
	{
		mResourcesLoadThread->join();

		JSceneManager::LoadScene(L"PlayScene");
	}
}

void JLoadingScene::OnEnter()
{

}

void JLoadingScene::OnExit()
{

}

void JLoadingScene::resourcesLoad(mutex& m)
{
	while (true)
	{
		if (application.IsLoaded() == true)
			break;
	}

	m.lock();
	{
		RResources::Load<RTexture>(L"Player", L"../Resources/CloudOcean.png");
		JSceneManager::CreateScene<JPlayScene>(L"PlayScene");
	}
	m.unlock();

	JSceneManager::SetActiveScene(L"LoadingScene");
	mbLoadCompleted = true;
}