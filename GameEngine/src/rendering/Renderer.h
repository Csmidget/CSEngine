#ifndef GAME_ENGINE_RENDERER_H
#define GAME_ENGINE_RENDERER_H

// OpenGL / glew Headers
#define GL3_PROTOTYPES 1

#include <GL/glew.h>
#include <SDL/SDL.h>


namespace GameEngine {

	//!Handles GL context and SDL window
	class Renderer {

		friend class Application;

	private:

		static SDL_Window* mainWindow;
		static SDL_GLContext mainContext;

		//!Initializes GL context and uniforms.
		static bool InitGL();

		//!Initializes SDL_Window and any other renderer specific functions
		static bool Init(int argc, char* argv[]);
		//!Destroys the SDL Window and GL context.
		static void Destroy();
		//!Replaces the buffer with the buffer drawn this frame.
		static void Update();
		//!Redraws the GL scene. Calls Draw on all GameObjects
		static void Draw();
		//!Processes a window event sent from the application (e.g. window resize)
		static void ProcessWindowEvent(SDL_Event &event);
		//!Sets the dimensions of the window to match newly resized window.
		static void SetWindowDimensions();

		static float screenWidth;
		static float screenHeight;

		static GLuint programId;
		static GLuint vertexShaderId;
		static GLuint fragmentShaderId;
		static GLuint projLoc;
		static GLuint viewLoc;

		//!Creates the shaders for the program
		static void CreateProgram();

	public:
		static void GetWindowSize(int *w, int *h);
		static GLuint GetProgramId() { return programId; }

		//!Clears the GL background to entered color.
		static void ClearToColour(float r, float g, float b, float a);

		static float GetScreenWidth() { return screenWidth; }
		static float GetScreenHeight() { return screenHeight; }

	};

}//namespace GameEngine

#endif
