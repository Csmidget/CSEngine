#ifndef GAME_ENGINE_CAMERA_H
#define GAME_ENGINE_CAMERA_H

#include "Component.h"
#include "glm\glm.hpp"
namespace GameEngine {

	namespace Rendering {
		class Renderer;
	}
	
	//! Component that works with the renderer to present an image of the game.
	class Camera : public Component {

	friend class Rendering::Renderer;

	private:
		//!The Camera that is currently presenting the main window
		static std::weak_ptr<Camera> mainCamera;
		//!Projection matrix of the Camera
		glm::mat4 projMat;

		float fovY;
		//!The near clipping plane of the projection matrix
		float near;
		//!The far clipping plane of the projection matrix
		float far;

		//!Initializes base values. Sets mainCamera if there is none.
		void OnAwake();
		//! Resizes the projection matrix to fit new dimensions. Automatically called on the main camera when window resizes.
		/*!
		\param _width The width of the new matrix.
		\param _height The height of the new matrix.
		*/
		void Resize(float _width, float _height);
		//!<The Y FOV of the projection matrix


	public:
		//!Return a pointer to the mainCamera
		static std::weak_ptr<Camera> GetMainCamera() { return mainCamera; }
		//!Returns a view matrix based on the Camera's current position
		glm::mat4 ViewMatrix() const;
		//!Returns the current projection matrix of this camera
		glm::mat4 ProjectionMatrix() const { return projMat; }

		//! Sets the main camera
		/*!
		\param _camera The camera to set as the mainCamera
		*/
		static void SetMainCamera(std::shared_ptr<Camera> _camera) { mainCamera = _camera; }

		//! Sets the main camera using a pointer to the camera.
		/*!
		\param _camera The camera to set as the mainCamera
		*/
		static void SetMainCamera(Camera *_camera) { mainCamera = std::make_shared<Camera>(*_camera); }
	};//class Camera

}//namespace GameEngine

#endif
