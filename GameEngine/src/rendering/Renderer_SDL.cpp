#include "Renderer_SDL.h"

namespace GameEngine
{
	namespace Rendering
	{

		bool Renderer_SDL::Init()
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
		void Renderer_SDL::Destroy()
		{
			// Delete our OpengL context
			SDL_GL_DeleteContext(mainContext);

			// Destroy our window
			SDL_DestroyWindow(mainWindow);
		}//Renderer::Destroy

		//==============================================================================
		void Renderer_SDL::Update()
		{
			Renderer::Update();

			//Presents the rendered image to the window
			SDL_GL_SwapWindow(mainWindow);
		}//Renderer::Update

		//==============================================================================
		void Renderer_SDL::Draw(std::vector<std::shared_ptr<GameObject>>& _objects)
		{
			Renderer::Draw(_objects);

			SDL_GL_SwapWindow(mainWindow);

		}//Renderer::Draw

				//==============================================================================
		void Renderer_SDL::GetWindowSize(int *w, int *h)
		{
			SDL_GetWindowSize(mainWindow, w, h);
		}//Renderer::GetWindowSize

	}
}
