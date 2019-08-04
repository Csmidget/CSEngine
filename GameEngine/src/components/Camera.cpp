#include "Camera.h"

#include <iostream>
#include "glm/gtx/transform.hpp"

#include "input/Input.h"
#include "Transform.h"
#include "rendering/Renderer.h"
#include "Application.h"

namespace GameEngine
{
	std::weak_ptr<Camera> Camera::mainCamera;
	//==============================================================================
	glm::mat4 Camera::ViewMatrix()
	{
		std::shared_ptr<Transform> t = GetTransform().lock();

		glm::mat4 mat = glm::inverse(t->GetTransMatUnscaled(t->GetPosition(), t->GetRotation()));
		return mat;
	}//Camera::ViewMatrix
	//==============================================================================
	void Camera::OnAwake()
	{
		//Initialize main camera if no main camera is already set.
		if (mainCamera.expired())
		{
			SetMainCamera(shared_from_base<Camera>());
		}

		near = 0.01f;
		far = 1000.0f;
		fovY = 45.0f;

		float width = Application::Renderer().lock()->ScreenWidth();
		float height = Application::Renderer().lock()->ScreenHeight();

		Rendering::Renderer::ClearToColour(100.0f / 256.0f, 104.0f / 256.0f, 130.0f / 256.0f, 0.5f);

		projMat = glm::perspective(fovY, width / height, near, far);
	}//Camera::OnAwake
	 //==============================================================================
	void Camera::Resize(float _width, float _height)
	{
		projMat = glm::perspective(fovY, _width / _height, near, far);
	}

}
