#include "rendering/Renderer.h"

#include <fstream>
#include <iostream>
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"


#include "rendering/Light.h"
#include "Transform.h"
#include "Application.h"
#include "rendering/Light.h"
#include "components/Camera.h"


namespace GameEngine
{

	SDL_Window* Renderer::mainWindow;
	SDL_GLContext Renderer::mainContext;
	GLuint Renderer::programId;
	GLuint Renderer::vertexShaderId;
	GLuint Renderer::fragmentShaderId;
	GLuint Renderer::projLoc;
	GLuint Renderer::viewLoc;
	float Renderer::screenHeight;
	float Renderer::screenWidth;



	//==============================================================================
	bool Renderer::Init(int argc, char* argv[])
	{
		//Initialization

		std::string programName = "Game Engine";

		// Major version number (4):
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		// Minor version number (3):
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		//OpenGL CORE, important for AnTweakBar
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		//Create SDL window
		int winPosX = 100;
		int winPosY = 100;
		screenWidth = 1024;
		screenHeight = 576;
		mainWindow = SDL_CreateWindow(programName.c_str(),
			winPosX, winPosY,
			screenWidth, screenHeight,
			SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);


		// Now that the SDL renderer is created for the window, we can create an OpenGL context for it!
		// This will allow us to actually use OpenGL to draw to the window
		SDL_GLContext glcontext = SDL_GL_CreateContext(mainWindow);

		// Call our initialisation function to set up GLEW and print out some GL info to console
		if (!InitGL())
		{
			return false;
		}

		// Sync with monitor refresh
		SDL_GL_SetSwapInterval(1);

		// Enable the depth test to make sure triangles in front are always in front no matter the order they are drawn
		// When you do this, don't forget to clear the depth buffer at the start of each frame - otherwise you just get an empty screen!
		glEnable(GL_DEPTH_TEST);

		CreateProgram();

		return true;
	}//Renderer::Init
	//==============================================================================
	void Renderer::Destroy()
	{
		// Delete our OpengL context
		SDL_GL_DeleteContext(mainContext);

		// Destroy our window
		SDL_DestroyWindow(mainWindow);
	}//Renderer::Destroy
	//==============================================================================
	void Renderer::Update()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Presents the rendered image to the window
		SDL_GL_SwapWindow(mainWindow);
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
	void Renderer::Draw()
	{

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Light::UpdateLight();

		glUniformMatrix4fv(projLoc, 1, 0, glm::value_ptr(Camera::GetMainCamera().lock()->ProjectionMatrix()));
		glUniformMatrix4fv(viewLoc, 1, 0, glm::value_ptr(Camera::GetMainCamera().lock()->ViewMatrix()));
		Application::Draw();

		SDL_GL_SwapWindow(mainWindow);

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
	void Renderer::GetWindowSize(int *w, int *h)
	{
		SDL_GetWindowSize(mainWindow, w, h);
	}//Renderer::GetWindowSize
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