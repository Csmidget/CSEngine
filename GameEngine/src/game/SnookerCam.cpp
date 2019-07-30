#include "SnookerCam.h"
#include "input/Input.h"
#include "GameObject.h"
#include "Transform.h"
#include "components/Camera.h"

namespace GameEngine
{

	void SnookerCam::OnAwake()
	{
		freeRoam = false;
	}

	void SnookerCam::OnUpdate()
	{
		if (!freeRoam)
		{
			if (Input::KeyDown(KeyCode::KEY1))
			{
				std::shared_ptr<Transform> camTransform = GetTransform().lock();
				camTransform->SetPosition(glm::vec3(0, 0, 0));
				camTransform->SetLocalRotation(glm::vec3(0, 0, 0));
			}
			else if (Input::KeyDown(KeyCode::KEY2))
			{
				std::shared_ptr<Transform> camTransform = GetTransform().lock();
				camTransform->SetPosition(glm::vec3(-13, -8, -15));
				camTransform->SetLocalRotation(glm::vec3(1, 0, -0.785398));
			}
			else if (Input::KeyDown(KeyCode::KEY3))
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