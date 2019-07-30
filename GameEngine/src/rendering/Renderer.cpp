#include "rendering/Renderer.h"

#include <fstream>
#include <iostream>
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "rendering/Light.h"
#include "Transform.h"
//#include "Application.h"
#include "rendering/Light.h"
#include "components/Camera.h"
#include "GameObject.h"
#include "rendering/SDL_Renderer.h"

namespace GameEngine
{
	namespace Rendering
	{
		std::shared_ptr<Renderer> CreateRenderer()
		{
			std::shared_ptr<Renderer> renderer{ std::make_shared<SDL_Renderer>() };
			renderer->Init();
			return renderer;
		}

		//==============================================================================
		void Renderer::Update()
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}//Renderer::Update

		//==============================================================================
		//Initialize Glew and print out important info
		bool Renderer::InitGL()
		{
			//Temporary workaround to access core openGL. Enabling glew experimental features
			glewExperimental = GL_TRUE;

			GLenum err = glewInit();
			if (GLEW_OK != err)
			{
				std::cerr << "Error: GLEW failed to initialise with message: " << glewGetErrorString(err) << std::endl;
				return false;
			}
			std::cout << "INFO: Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;

			std::cout << "INFO: OpenGL Vendor: " << glGetString(GL_VENDOR) << std::endl;
			std::cout << "INFO: OpenGL Renderer: " << glGetString(GL_RENDERER) << std::endl;
			std::cout << "INFO: OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
			std::cout << "INFO: OpenGL Shading Language Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

			return true;

		}//Renderer::InitGL
		//==============================================================================
		void Renderer::Draw(std::vector<std::shared_ptr<GameObject>>& _objects)
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			Light::UpdateLight();

			glUniformMatrix4fv(projLoc, 1, 0, glm::value_ptr(Camera::GetMainCamera().lock()->ProjectionMatrix()));
			glUniformMatrix4fv(viewLoc, 1, 0, glm::value_ptr(Camera::GetMainCamera().lock()->ViewMatrix()));

			for (auto gameObject : _objects)
			{
				gameObject->Draw();
			}
			
		}//Renderer::Draw
		//==============================================================================
		void Renderer::CreateProgram()
		{

			std::string filePath = "";
			std::ifstream vertFile("defVert.shader");

			if (!vertFile)
			{
				filePath = "Shaders\\";
				vertFile.open(filePath + "defVert.shader");
			}
			if (!vertFile)
			{
				filePath = "..\\Shaders\\";
				vertFile.open(filePath + "defVert.shader");
			}

			if (!vertFile)
			{
				std::cerr << "ERROR! UNABLE TO LOCATE VERTEX SHADER" << std::endl;
			}

			std::string vertString((std::istreambuf_iterator<char>(vertFile)), std::istreambuf_iterator<char>());
			const char * str = vertString.c_str();

			vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(vertexShaderId, 1, &str, NULL);
			glCompileShader(vertexShaderId);

			std::ifstream fragFile(filePath + "defFrag.shader");
			if (!fragFile)
			{
				std::cerr << "ERROR! UNABLE TO LOCATE FRAGMENT SHADER" << std::endl;
			}
			std::string fragString((std::istreambuf_iterator<char>(fragFile)), std::istreambuf_iterator<char>());
			str = fragString.c_str();

			fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(fragmentShaderId, 1, &str, NULL);
			glCompileShader(fragmentShaderId);

			programId = glCreateProgram();
			glAttachShader(programId, vertexShaderId);
			glAttachShader(programId, fragmentShaderId);
			glLinkProgram(programId);
			glUseProgram(programId);

			projLoc = glGetUniformLocation(programId, "projMat");
			viewLoc = glGetUniformLocation(programId, "viewMat");
			Light::Init(glGetUniformLocation(programId, "worldSpaceLightPos"));

		}//Renderer::CreateProgram

		//==============================================================================
		void Renderer::ClearToColour(float r, float g, float b, float a)
		{
			glClearColor(r, g, b, a);
			glClear(GL_COLOR_BUFFER_BIT);
		}//Renderer::ClearToColour

		//==============================================================================
		void Renderer::ProcessWindowEvent(SDL_Event &event) {

			if (event.window.event == SDL_WINDOWEVENT_RESIZED)
			{

				screenWidth = event.window.data1;
				screenHeight = event.window.data2;

				glViewport(0, 0, screenWidth, screenHeight);
				Camera::GetMainCamera().lock()->Resize(screenWidth, screenHeight);
			}

		}//Renderer::ProcessWindowEvent
	}
}