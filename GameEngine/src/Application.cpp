#include "Application.h"

#include "GameObject.h"
#include "rendering/Renderer.h"
#include "rendering/RendererFactory.h"
#include "input/Input.h"
#include "interaction/CollisionControl.h"
#include "interaction/RigidBody.h"
#include "Debug.h"

namespace GameEngine
{
	std::vector<std::shared_ptr<GameObject>> Application::gameObjects;
	bool Application::run;
	unsigned int Application::currentTicks;
	unsigned int Application::lastTicks;
	int Application::rdt;
	float Application::rdts;
	std::shared_ptr<Rendering::Renderer> Application::renderer;
	std::shared_ptr<Input> Application::input;
	
	//==============================================================================

	bool Application::Init(int argc, char* argv[])
	{
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER) < 0)
		{
			Debug::LogError("Failed to initialise SDL");
			return false;
		}

		run = true;

		renderer = Rendering::RendererFactory::CreateRenderer();
		input = CreateInput();

		//if (!Rendering::Renderer::Init(argc, argv))
		//{
		//	return false;
		//}

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

			input->ProcessEvents();

			Update();

			renderer->Draw(gameObjects);
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

		renderer->Destroy();

		// Close SDL
		SDL_Quit();

	}//Application::Quit
	//==============================================================================

	void Application::AddGameObject(std::shared_ptr<GameObject> _go)
	{
		gameObjects.push_back(_go);
	}//Application::AddGameObject
	//==============================================================================
	void Application::Destroy(std::shared_ptr<Object> _o)
	{
		Object::Destroy(_o);
	}

}
