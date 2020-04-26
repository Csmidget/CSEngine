#include "CSEngine_Common.h" 

#include "Renderer.h"
#include "Input.h"
#include "CollisionControl3D.h"
#include "RigidBody3D.h"

#include "Application.h"

namespace CSEngine
{
	std::vector<std::shared_ptr<GameObject>> Application::gameObjects;
	bool Application::run;
	int Application::rdt;
	float Application::rdts;
	std::shared_ptr<Renderer> Application::renderer;
	std::shared_ptr<Input> Application::input;
	
	//==============================================================================

	bool Application::Init(int argc, char* argv[])
	{
		run = true;

		renderer = RendererFactory::CreateRenderer();
		input = CreateInput();

		CollisionControl3D::colliders.clear();

		RigidBody3D::rbInterval = 20;

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
		rdt = input->UpdateDeltaTime();
		rdts = (float)rdt / 1000.0f;
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

		RigidBody3D::UpdateRigidBodies();

	}//Application::Update
	//==============================================================================
	void Application::Quit()
	{
		for (int i = gameObjects.size() - 1; i >= 0; i--)
		{
			gameObjects[i]->Destroy();
		}

		renderer->Destroy();
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
