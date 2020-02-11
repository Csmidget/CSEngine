#include "SnookerCam.h"
#include "Input/Input.h"
#include "GameObject.h"
#include "Transform.h"
#include "Rendering/Camera.h"
#include "Application.h"
namespace GameEngine
{

	void SnookerCam::OnAwake()
	{
		freeRoam = false;
	}

	void SnookerCam::OnUpdate()
	{
		std::shared_ptr<Input> input = Application::Input().lock();

		if (!freeRoam)
		{
			if (input->KeyDown(KeyCode::KEY1))
			{
				std::shared_ptr<Transform> camTransform = GetTransform().lock();
				camTransform->SetPosition(glm::vec3(0, 0, 0));
				camTransform->SetLocalRotation(glm::vec3(0, 0, 0));
			}
			else if (input->KeyDown(KeyCode::KEY2))
			{
				std::shared_ptr<Transform> camTransform = GetTransform().lock();
				camTransform->SetPosition(glm::vec3(-13, -8, -15));
				camTransform->SetLocalRotation(glm::vec3(1, 0, -0.785398));
			}
			else if (input->KeyDown(KeyCode::KEY3))
			{
				freeRoam = true;
			}
		}
	}

	void SnookerCam::AttachTo(std::weak_ptr<Transform> _parent)
	{
		GetTransform().lock()->SetParent(_parent);
		GetTransform().lock()->SetLocalPosition(glm::vec3(-4, 0, 1));
		GetTransform().lock()->SetLocalRotation(glm::vec3(1.5708, 0, -1.5708));
	}

}