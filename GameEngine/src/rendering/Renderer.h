#ifndef GAME_ENGINE_RENDERER_H
#define GAME_ENGINE_RENDERER_H

// OpenGL / glew Headers
#define GL3_PROTOTYPES 1

#include "GL/glew.h"
#include <vector>
#include <memory>
#include "SDL/SDL.h"

namespace GameEngine {

	class GameObject;
	class Application;
	
	namespace Rendering
	{

		//!Handles GL context and SDL window
		class Renderer {

			friend class Application;
			
		protected:

			friend std::shared_ptr<Renderer> CreateRenderer();

			float screenWidth;
			float screenHeight;

			//!Initializes GL context and uniforms.
			bool InitGL();

			//!Creates the shaders for the program
			void CreateProgram();

			//!Processes a window event sent from the application (e.g. window resize)
			void ProcessWindowEvent(SDL_Event &event);

			//!Initializes SDL_Window and any other renderer specific functions
			virtual bool Init() = 0;

			//!Destroys the SDL Window and GL context.
			virtual void Destroy() = 0;

			//!Replaces the buffer with the buffer drawn this frame.
			virtual void Update();

			//!Redraws the GL scene. Calls Draw on all GameObjects
			virtual void Draw(std::vector<std::shared_ptr<GameObject>>& _objects);

		private:

			GLuint programId;
			GLuint vertexShaderId;
			GLuint fragmentShaderId;
			GLuint projLoc;
			GLuint viewLoc;

		public:
			virtual GLuint GetProgramId() { return programId; }
			virtual float ScreenWidth() = 0;
			virtual float ScreenHeight() = 0;
			virtual void GetWindowSize(int *w, int *h) = 0;

			//!Clears the GL background to entered color.
			static void ClearToColour(float r, float g, float b, float a);
		};
	}
}//namespace GameEngine

#endif
