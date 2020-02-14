#include "CSEngine.h" 

#include "Interaction/Collision3D.h"
#include "Interaction/RigidBody3D.h"
#include "Rendering/Light.h"
#include "Rendering/MeshRenderer.h"

#include "SnookerCam.h"
#include "TableConstrainer.h"
#include "DebugComponent.h"
#include "Program.h"

using namespace GameEngine;

void Program::Init()
{
	//Called before main game loop is initialized. Game initialization goes here!

	std::shared_ptr<GameObject> go = GameObject::Create();

	std::shared_ptr<MeshRenderer> mr = go->AddComponent<MeshRenderer>().lock();

	//Initialize snooker mat background
	mr->SetAutoScale(false);
	mr->SetMesh("snookerMat.obj");
	go->GetTransform().lock()->SetPosition(glm::vec3(0, 0, -20));
	go->GetTransform().lock()->SetLocalScale(glm::vec3(2, 0, 2));
	go->GetTransform().lock()->Rotate(glm::vec3(-1.5708, 0, 0));

	//!Create player controlled sphere
	go = GameObject::CreateSphere(glm::vec3(-5, 0, -19.5)).lock();
	go->GetComponent<RigidBody3D>().lock()->lockRotation = true;
	go->AddComponent<DebugComponent>();
	go->AddComponent<TableConstrainer>();

	std::shared_ptr<GameObject> go2 = GameObject::Create();
	go2->GetTransform().lock()->SetLocalPosition(glm::vec3(0, 0, 1));
	go2->GetTransform().lock()->SetParent(go->GetTransform());
	Light::SetParent(go2->GetTransform());

	//!Create other objects
	GameObject::CreateSphere((glm::vec3(0, 0, -19.5))).lock()->AddComponent<TableConstrainer>();

	GameObject::CreateSphere((glm::vec3(0.9, 0.9, -19.5))).lock()->AddComponent<TableConstrainer>();
	GameObject::CreateSphere((glm::vec3(0.9, -0.9, -19.5))).lock()->AddComponent<TableConstrainer>();

	GameObject::CreateSphere((glm::vec3(1.8, 1.8, -19.5))).lock()->AddComponent<TableConstrainer>();
	GameObject::CreateCube((glm::vec3(1.8, 0, -19.5))).lock()->AddComponent<TableConstrainer>();
	GameObject::CreateSphere((glm::vec3(1.8, -1.8, -19.5))).lock()->AddComponent<TableConstrainer>();

	GameObject::CreateCube((glm::vec3(2.8, 2.8, -19.5))).lock()->AddComponent<TableConstrainer>();
	GameObject::CreateSphere((glm::vec3(2.7, 0.9, -19.5))).lock()->AddComponent<TableConstrainer>();
	GameObject::CreateSphere((glm::vec3(2.7, -0.9, -19.5))).lock()->AddComponent<TableConstrainer>();
	GameObject::CreateCube((glm::vec3(2.8, -2.8, -19.5))).lock()->AddComponent<TableConstrainer>();

	//!Assign main camera the SnookerCam component
	Camera::GetMainCamera().lock()->GetGameObject().lock()->AddComponent<SnookerCam>();
}//Program::Init