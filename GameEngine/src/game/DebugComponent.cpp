#include "CSEngine.h"

#include "Rendering/MeshRenderer.h"

#include "Interaction/RigidBody3D.h"
#include "Interaction/Collision3D.h"

#include "SnookerCam.h"
#include "TableConstrainer.h"

#include "DebugComponent.h"

using namespace GameEngine;
//==============================================================================
void DebugComponent::OnUpdate()
{
	std::shared_ptr<Input> input = Application::Input().lock();

	std::shared_ptr<RigidBody3D> rb = gameObject.lock()->GetComponent<RigidBody3D>().lock();

	float x = input->GetContAnalogueAxis(0, 0, 0);
	float y = input->GetContAnalogueAxis(0, 0, 1);

	if (!freeroam)
	{

		// if (glm::length(rb->GetCurrState().linearMomentum) < 1)
		rb->ApplyForce(glm::vec3(x * 100, -y * 100, 0));
	}
	else
	{
		glm::vec3 rot = GetTransform().lock()->GetTransform().lock()->GetLocalRotation();

		rb->ApplyForce(Transform::RotateVector(glm::vec3(-y * 100, -x * 100, 0), rot));

		x = input->GetContAnalogueAxis(0, 1, 0);
		y = input->GetContAnalogueAxis(0, 1, 1);

		rb->GetTransform().lock()->Rotate(glm::vec3(0, y / 100, -x / 100));

		if (input->KeyHeld(KeyCode::RIGHT))
		{
			GetTransform().lock()->Rotate(glm::vec3(0, 0, -0.01));
		}
		if (input->KeyHeld(KeyCode::LEFT))
		{
			GetTransform().lock()->Rotate(glm::vec3(0, 0, 0.01));
		}
		if (input->KeyHeld(KeyCode::UP))
		{
			GetTransform().lock()->Rotate(glm::vec3(0, -0.01, 0));
		}
		if (input->KeyHeld(KeyCode::DOWN))
		{
			GetTransform().lock()->Rotate(glm::vec3(0, 0.01, 0));
		}

		if (input->KeyHeld(KeyCode::W))
		{
			rb->ApplyForce(Transform::RotateVector(glm::vec3(25, 0, 0), GetTransform().lock()->GetRotation()));
		}
		if (input->KeyHeld(KeyCode::S))
		{
			rb->ApplyForce(Transform::RotateVector(glm::vec3(-25, 0, 0), GetTransform().lock()->GetRotation()));
		}
		if (input->KeyHeld(KeyCode::D))
		{
			rb->ApplyForce(Transform::RotateVector(glm::vec3(0, -25, 0), GetTransform().lock()->GetRotation()));
		}
		if (input->KeyHeld(KeyCode::A))
		{
			rb->ApplyForce(Transform::RotateVector(glm::vec3(0, 25, 0), GetTransform().lock()->GetRotation()));
		}

		if (GetTransform().lock()->GetPosition().z < -19.6f)
		{
			std::shared_ptr<Transform> t = GetTransform().lock();
			rb->SetVelocity(glm::vec3(rb->GetVelocity().x, rb->GetVelocity().y, -rb->GetVelocity().z));
			GetTransform().lock()->SetPosition(glm::vec3(t->GetPosition().x, t->GetPosition().y, -19.59f));
		}

		if (input->MouseButtonDown(MouseCode::MBLEFT) || input->ContButtonDown(0, ControllerCode::CONTA))
		{
			std::shared_ptr<GameObject> go = GameObject::Create();
			go->AddComponent<MeshRenderer>().lock()->SetMesh("capsule.obj");
			go->GetTransform().lock()->SetPosition(GetTransform().lock()->GetPosition());

		}
	}

	if (input->KeyDown(KeyCode::KEY3))
	{
		freeroam = true;
		std::shared_ptr<SnookerCam> camComponent = Camera::GetMainCamera().lock()->GetGameObject().lock()->GetComponent<SnookerCam>().lock();
		camComponent->AttachTo(GetTransform());
		gameObject.lock()->RemoveComponent<TableConstrainer>();

	}
}
//==============================================================================
void DebugComponent::OnAwake()
{
	freeroam = false;

}
