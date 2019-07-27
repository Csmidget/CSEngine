#include <GameObject.h>
#include <Application.h>
#include <Transform.h>
#include <Collision.h>

#include <Camera.h>
#include <MeshRenderer.h>
#include <SphereCollider.h>
#include <BoxCollider.h>
#include <RigidBody.h>

namespace GameEngine {

	//==============================================================================
	std::shared_ptr<GameObject> GameObject::Create()
	{
		std::shared_ptr<GameObject> rtn = std::make_shared<GameObject>();
		rtn->AddComponent<Transform>();
		rtn->active = true;
		Application::AddGameObject(rtn);
		return rtn;
	}
	//==============================================================================
	void GameObject::Destroy() {
		for (int i = components.size() - 1; i >= 0; i--)
		{
			components[i]->Destroy();
			components.erase(components.begin() + i);
		}
	}//GameObject::Destroy
	//==============================================================================
	void GameObject::Update() {

		for (int i = components.size() - 1; i >= 0; i--)
		{
			if (components[i]->destroyed == true) {
				components[i]->Destroy();
				components.erase(components.begin() + i);
			}
			else {
				components[i]->Update();
			}
		}
	}//GameObject::Update
	//==============================================================================
	void GameObject::Draw() {
		for (int i = components.size() - 1; i >= 0; i--)
		{
			components[i]->Draw();
		}
	}//GameObject::Render
	//==============================================================================
	std::weak_ptr<Transform> GameObject::GetTransform()
	{
		//If we do not have transform cached, cache it.
		if (transform.expired())
		{
			transform = GetComponent<Transform>();
		}

		return transform;
	}//GameObject::GetTransform
	//==============================================================================
	void GameObject::OnCollision(Collision _col)
	{

		for (int i = components.size() - 1; i >= 0; i--)
		{

			if (components[i]->destroyed == true) {
				components[i]->Destroy();
				components.erase(components.begin() + i);
			}
			else {
				components[i]->OnCollision(_col);
			}
		}
	}//GameObject::OnCollision
	//==============================================================================
	std::weak_ptr<GameObject> GameObject::CreateCube(glm::vec3 _pos)
	{
		std::shared_ptr<GameObject> go = Create();
		go->AddComponent<MeshRenderer>().lock()->SetMesh("cube.obj");
		go->AddComponent<BoxCollider>();
		go->AddComponent<RigidBody>();
		go->GetTransform().lock()->Translate(_pos);
		return go;
	}//Application::CreateSphere
	//==============================================================================
	std::weak_ptr<GameObject> GameObject::CreateSphere(glm::vec3 _pos)
	{
		std::shared_ptr<GameObject> go = Create();
		go->AddComponent<MeshRenderer>().lock()->SetMesh("sphere.obj");
		go->AddComponent<SphereCollider>();
		go->AddComponent<RigidBody>();
		go->GetTransform().lock()->Translate(_pos);
		return go;
	}//Application::CreateSphere
	//==============================================================================
	std::weak_ptr<GameObject> GameObject::CreateCapsule(glm::vec3 _pos)
	{
		std::shared_ptr<GameObject> go = Create();
		go->AddComponent<MeshRenderer>().lock()->SetMesh("capsule.obj");
		go->AddComponent<BoxCollider>();
		go->AddComponent<RigidBody>();
		go->GetTransform().lock()->Translate(_pos);
		return go;
	}//Application::CreateSphere
	//==============================================================================
	std::weak_ptr<GameObject> GameObject::CreateCamera(glm::vec3 _pos)
	{
		std::weak_ptr<GameObject> go = GameObject::Create();
		go.lock()->AddComponent<Camera>();
		return go;
	}
	//==============================================================================
}
