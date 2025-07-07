#include "JPlayScene.h"
#include "APlayer.h"
#include "JCameraScript.h"
//Engine
#include "Graphics/RGraphicDevice_DX11.h"
#include "Object/JObject.h"
#include "Component/SpriteRenderer/JSpriteRenderer.h"
#include "Resource/RResources.h"
#include "Resource/RMaterial.h"
#include "Resource/RTexture.h"
#include "Component/Camera/JCamera.h"
#include "Renderer/RRenderer.h"


JPlayScene::JPlayScene() : 
	mPlayer(nullptr)
{

}

JPlayScene::~JPlayScene()
{

}

void JPlayScene::Initialize()
{
	JScene::Initialize();

	// main camera
	AActor* camera = Instantiate<AActor>(ELayerType::None, FVector3(0.0f, 0.0f, -10.0f));
	JCamera* cameraComp = camera->AddComponent<JCamera>();
	cameraComp->SetProjectionType(JCamera::EProjectionType::Orthographic);

	JCameraScript* cameraScript = camera->AddComponent<JCameraScript>();
	renderer::mainCamera = cameraComp;
	cameraComp->SetSize(200.0f);

	mPlayer = Instantiate<APlayer>(ELayerType::Player);
	JDontDestroyOnLoad(mPlayer);

	JSpriteRenderer* sr = mPlayer->AddComponent<JSpriteRenderer>();
	sr->SetMaterial(RResources::Find<RMaterial>(L"SpriteMaterial"));
	sr->SetSprite(RResources::Find<RTexture>(L"Player"));
}

void JPlayScene::Update()
{
	JScene::Update();
}

void JPlayScene::LateUpdate()
{
	JScene::LateUpdate();
}

void JPlayScene::Render()
{
	JScene::Render();
}

void JPlayScene::OnEnter()
{
	JScene::OnEnter();
}

void JPlayScene::OnExit()
{
	JScene::OnExit();
}