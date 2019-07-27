#include <Application.h>

#include <iostream>
#include <GameObject.h>
#include <Renderer.h>
#include <Input.h>
#include <CollisionControl.h>
#include <RigidBody.h>

namespace GameEngine
{

	std::vector<std::shared_ptr<GameObject>> Application::gameObjects;
	bool Application::run;
	unsigned int Application::currentTicks;
	unsigned int Application::lastTicks;
	int Application::rdt;
	float Application::rdts;

	//==============================================================================

	bool Application::Init(int argc, char* argv[])
	{
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER) < 0)
		{
			std::cout << "Failed to initialise SDL" << std::endl;
			return false;
		}

		run = true;

		if (!Renderer::Init(argc, argv))
		{
			return false;
		}

		CollisionControl::colliders.clear();

		RigidBody::rbInterval = 20;

		//Initialize the main camera
		GameObject::CreateCamera(glm::vec3(0, 0, 0));

		return true;
	}//Application::Init
	//==============================================================================
	void Application::Run()
	{
		while (run)
		{
			RefreshDeltaTime();

			ProcessEvents();

			Update();

			Renderer::Draw();
		}

		Quit();
	}//Application::Run
	//==============================================================================

	void Application::RefreshDeltaTime()
	{
		currentTicks = SDL_GetTicks();
		rdt = (currentTicks - lastTicks);
		rdts = (float)rdt / 1000.0f;
		lastTicks = currentTicks;

		if (rdt < (1.0f / 60.0f))
		{
			SDL_Delay((unsigned int)(1000 / 60 - rdts));
		}
	}//Application::RefreshDeltaTime
	//==============================================================================

	void Application::ProcessEvents()
	{

		SDL_Event event = { 0 };

		Input::RefreshEvents();

		while (SDL_PollEvent(&event))
		{

			switch (event.type)
			{
			case SDL_QUIT:
				run = false;
				break;
			case SDL_KEYDOWN:
			case SDL_KEYUP:
				Input::ProcessKeyEvent(event.key);
				break;
			case SDL_MOUSEBUTTONUP:
			case SDL_MOUSEBUTTONDOWN:
				Input::ProcessMouseButtonEvent(event.button);
				break;
			case SDL_MOUSEWHEEL:
				Input::ProcessMouseWheelEvent(event.wheel);
				break;
			case SDL_MOUSEMOTION:
				Input::ProcessMouseMotionEvent(event.motion);
				break;
			case SDL_CONTROLLERBUTTONUP:
			case SDL_CONTROLLERBUTTONDOWN:
				Input::ProcessControllerButtonEvent(event.cbutton);
				break;
			case SDL_CONTROLLERAXISMOTION:
				Input::ProcessControllerAxisEvent(event.caxis);
				break;
			case SDL_CONTROLLERDEVICEADDED:
				Input::AddController(event.cdevice.which);
				break;
			case SDL_CONTROLLERDEVICEREMOVED:
				Input::RemoveController(event.cdevice.which);
				break;
			case SDL_WINDOWEVENT:
				Renderer::ProcessWindowEvent(event);
				break;
			}
		}

	}//Application::ProcessInput
	//==============================================================================

	void Application::Update()
	{
		for (int i = gameObjects.size() - 1; i >= 0; i--)
		{
			if (gameObjects.at(i)->destroyed)
			{
				gameObjects.erase(gameObjects.begin() + i);
			}
			else
			{
				gameObjects[i]->Update();
			}
		}

		RigidBody::UpdateRigidBodies();

	}//Application::Update
	//==============================================================================
	void Application::Quit()
	{
		for (int i = gameObjects.size() - 1; i >= 0; i--)
		{
			gameObjects[i]->Destroy();
		}

		Renderer::Destroy();

		// Close SDL
		SDL_Quit();

	}//Application::Quit
	//==============================================================================

	void Application::AddGameObject(std::shared_ptr<GameObject> _go)
	{
		gameObjects.push_back(_go);
	}//Application::AddGameObject
	//==============================================================================
	void Application::Draw()
	{
		for (int i = gameObjects.size() - 1; i >= 0; i--)
		{
			gameObjects[i]->Draw();
		}
	}//Application::Draw
	//==============================================================================
	void PrintSDL_GL_Attributes()
	{
		int value = 0;
		SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &value);
		std::cout << "SDL_GL_CONTEXT_MAJOR_VERSION : " << value << std::endl;

		SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &value);
		std::cout << "SDL_GL_CONTEXT_MINOR_VERSION: " << value << std::endl;
	}//PrintSDL_GL_Attributes
	//==============================================================================
	void Application::Destroy(std::shared_ptr<Object> _o)
	{
		Object::Destroy(_o);
	}

}
