#include "CSEngine_Common.h" 

#include "SFML/Graphics.hpp"
#include <SFML/OpenGL.hpp>

#include "Renderer.h"
#include "Renderer_SFML.h"

namespace CSEngine
{

	//void Print_SFML_GL_Attributes()
	//{
	//	int value = 0;
	//	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &value);
	//	Debug::Log("SDL_GL_CONTEXT_MAJOR_VERSION: ", value);
	//
	//	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &value);
	//	Debug::Log("SDL_GL_CONTEXT_MINOR_VERSION: ", value);
	//}//Print_SDL_GL_Attributes

	bool Renderer_SFML::Init()
	{
		//Initialization

		std::string programName = "Game Engine";


		// Major version number (4):
	//	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	//	// Minor version number (3):
	//	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		//OpenGL CORE, important for AnTweakBar
	//	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        

		//Create SFML window
		int winPosX = 100;
		int winPosY = 100;
		screenWidth = 1024;
		screenHeight = 576;

		mainWindow.create(sf::VideoMode(screenWidth, screenHeight), "CSEngine (SFML)", sf::Style::Resize, sf::ContextSettings());
		mainWindow.setActive(true);
		//mainWindow = SDL_CreateWindow(programName.c_str(),
		//	winPosX, winPosY,
		//	screenWidth, screenHeight,
		//	SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);


		// Now that the SDL renderer is created for the window, we can create an OpenGL context for it!
		// This will allow us to actually use OpenGL to draw to the window
		//SDL_GLContext glcontext = SDL_GL_CreateContext(mainWindow);
		
		// Call our initialisation function to set up GLEW and print out some GL info to console
		if (!InitGL())
		{
			return false;
		}

		// Sync with monitor refresh
		mainWindow.setVerticalSyncEnabled(true);

		// Enable the depth test to make sure triangles in front are always in front no matter the order they are drawn
		// When you do this, don't forget to clear the depth buffer at the start of each frame - otherwise you just get an empty screen!
		glEnable(GL_DEPTH_TEST);

		CreateProgram();

		//Print_SDL_GL_Attributes();

		return true;
	}//Renderer_SDL::Init

	//==============================================================================
	void Renderer_SFML::Destroy()
	{
		mainWindow.close();
	}//Renderer_SDL::Destroy

	//==============================================================================
	void Renderer_SFML::Update()
	{
		Renderer::Update();

		//Presents the rendered image to the window
		
		mainWindow.display();
	}//Renderer_SDL::Update

	//==============================================================================
	void Renderer_SFML::Draw(std::vector<std::shared_ptr<GameObject>>& _objects)
	{
		Renderer::Draw(_objects);

		mainWindow.display();
	}//Renderer_SDL::Draw

	//==============================================================================
	void Renderer_SFML::GetWindowSize(int* w, int* h) const
	{
		mainWindow.getSize();
	//	SDL_GetWindowSize(mainWindow, w, h);
	}//Renderer_SDL::GetWindowSize
	//==============================================================================

}
