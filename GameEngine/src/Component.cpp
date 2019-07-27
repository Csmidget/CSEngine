#include <Component.h>

#include <Application.h>
#include <Renderer.h>
#include <Input.h>
#include <GameObject.h>
#include <Collision.h>

namespace GameEngine
{
	//==============================================================================
	Component::Component()
	{

	}//Component::Component
	//==============================================================================
	void Component::Start()
	{
		OnStart();
	}//Component::Start
	//==============================================================================
	void Component::Draw()
	{
		OnDraw();
	}//Component::OnDraw
	//==============================================================================
	void Component::Awake()
	{
		OnAwake();
	}//Component::Awake
	//==============================================================================
	void Component::Destroy()
	{
		OnDestroy();
	}//Component::Destroy
	//==============================================================================
	void Component::Update()
	{
		OnUpdate();
	}//Component::Update
	//==============================================================================
	void Component::OnDestroy()
	{
	}//Component::OnDestroy
	//==============================================================================
	void Component::OnAwake()
	{

	}//Component::OnAwake
	//==============================================================================
	void Component::OnUpdate()
	{

	}//Component::OnUpdate
	//==============================================================================
	void Component::OnStart()
	{

	}//Component::OnStart
	//==============================================================================
	void Component::OnDraw()
	{

	}//Component::OnDraw
	//==============================================================================
	std::weak_ptr<Transform> Component::GetTransform()
	{
		return gameObject.lock()->GetTransform();
	}//Component::GetTransform
	 //==============================================================================
	void Component::OnCollision(Collision _col)
	{

	}//Component::OnCollision

}
