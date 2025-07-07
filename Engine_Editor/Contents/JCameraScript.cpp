#include "JCameraScript.h"
//Engine
#include "Helpers/Input.h"
#include "Component/Transform/JTransform.h"
#include "Helpers/Time.h"
#include "Actor/AActor.h"


JCameraScript::JCameraScript()
{

}

JCameraScript::~JCameraScript()
{

}

void JCameraScript::Initialize()
{

}

void JCameraScript::Update()
{
	JTransform* transform = GetOwner()->GetComponent<JTransform>();
	FVector3 pos = transform->GetPosition();

	if (Input::GetKey(EKeyCode::A))
		pos += 20.0f * -transform->Right() * Time::DeltaTime();
	if (Input::GetKey(EKeyCode::W))
		pos += 20.0f * transform->Foward() * Time::DeltaTime();
	if (Input::GetKey(EKeyCode::D))
		pos += 20.0f * transform->Right() * Time::DeltaTime();
	if (Input::GetKey(EKeyCode::S))
		pos += 20.0f * -transform->Foward() * Time::DeltaTime();
	if (Input::GetKey(EKeyCode::E))
		pos += 20.0f * transform->Up() * Time::DeltaTime();
	if (Input::GetKey(EKeyCode::Q))
		pos += 20.0f * -transform->Up() * Time::DeltaTime();

	transform->SetPosition(pos);
}

void JCameraScript::LateUpdate()
{

}

void JCameraScript::Render()
{

}