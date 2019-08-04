#ifndef GAME_ENGINE_SDL_RENDERER_H
#define GAME_ENGINE_SDL_RENDERER_H

#include "Renderer.h"
#include "SDL/SDL.h"

namespace GameEngine {
	namespace Rendering {

		class Renderer_SDL : public Renderer{

		private:

			SDL_Window* mainWindow;
			SDL_GLContext mainContext;

			//!Initializes SDL_Window and any other renderer specific functions
			bool Init() override;
			//!Destroys the SDL Window and GL context.
			void Destroy() override;
			//!Replaces the buffer with the buffer drawn this frame.
			void Update() override;
			//!Redraws the GL scene. Calls Draw on all GameObjects
			void Draw(std::vector<std::shared_ptr<GameObject>>& _objects) override;	
		
		public:
			void GetWindowSize(int *w, int *h) override;

			//!Clears the GL background to entered color.
			void ClearToColour(float r, float g, float b, float a);

			float ScreenWidth() override { return screenWidth; }
			float ScreenHeight() override { return screenHeight; }

		};
	}
}
#endif
