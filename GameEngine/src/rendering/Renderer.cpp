#include "Rendering/Renderer.h"

#include <fstream>
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Light.h"
#include "Transform.h"
#include "Light.h"
#include "Camera.h"
#include "GameObject.h"
#include "Input/WindowEvent.h"
#include "Debug.h"

namespace GameEngine
{
	namespace Rendering
	{
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
				Debug::LogError("Error: GLEW failed to initialise with message: " , glewGetErrorString(err));
				return false;
			}

			Debug::Log("INFO: Using GLEW " , glewGetString(GLEW_VERSION));
			Debug::Log("INFO: OpenGL Vendor: " , glGetString(GL_VENDOR));
			Debug::Log("INFO: OpenGL Renderer: " , glGetString(GL_RENDERER));
			Debug::Log("INFO: OpenGL Version: " , glGetString(GL_VERSION));
			Debug::Log("INFO: OpenGL Shading Language Version: " , glGetString(GL_SHADING_LANGUAGE_VERSION));

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
				Debug::LogError("ERROR! UNABLE TO LOCATE VERTEX SHADER");
			}

			std::string vertString((std::istreambuf_iterator<char>(vertFile)), std::istreambuf_iterator<char>());
			const char * str = vertString.c_str();

			vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(vertexShaderId, 1, &str, NULL);
			glCompileShader(vertexShaderId);

			std::ifstream fragFile(filePath + "defFrag.shader");
			if (!fragFile)
			{
				Debug::LogError("ERROR! UNABLE TO LOCATE FRAGMENT SHADER");
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
		void Renderer::ProcessWindowEvent(const WindowEvent &event) {

			if (event.type == WINDOWEVENT_RESIZED)
			{
				screenWidth = event.data1;
				screenHeight = event.data2;
				
				glViewport(0, 0, screenWidth, screenHeight);
				Camera::GetMainCamera().lock()->Resize(screenWidth, screenHeight);
			}

		}//Renderer::ProcessWindowEvent
	}
}