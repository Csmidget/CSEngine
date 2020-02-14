#include "glm/gtx/transform.hpp"

#include "CSEngine_Common.h"

#include "Application.h"
#include "Renderer.h"
#include "Input/Input.h"

#include "Transform.h"
#include "Camera.h"

namespace GameEngine
{
	std::weak_ptr<Camera> Camera::mainCamera;
	//==============================================================================
	glm::mat4 Camera::ViewMatrix() const
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

		if (!viewType)
			viewType = CameraViewType::Perspective;

		Renderer::ClearToColour(100.0f / 256.0f, 104.0f / 256.0f, 130.0f / 256.0f, 0.5f);

		float width = Application::Renderer().lock()->ScreenWidth();
		float height = Application::Renderer().lock()->ScreenHeight();

		Resize(width, height);
	}//Camera::OnAwake
	 //==============================================================================
	void Camera::Resize(float _width, float _height)
	{
		switch (viewType)
		{
		case CameraViewType::Perspective:
			projMat = glm::perspective(fovY, _width / _height, near, far);
			break;
		case CameraViewType::Orthographic:
			projMat = glm::ortho(0.0f, _width, 0.0f, _height);
			break;
		}
	}
}
