#ifndef GAME_ENGINE_RENDERER_H
#define GAME_ENGINE_RENDERER_H

// OpenGL / glew Headers
#define GL3_PROTOTYPES 1

namespace CSEngine {

	class GameObject;
	class Input_SDL;
	class Application;
	struct WindowEvent;

	class RendererFactory;

	//!Handles GL context and SDL window
	class Renderer {

		friend class Application;

	protected:

		friend RendererFactory;

		short screenWidth;
		short screenHeight;

		//!Initializes GL context and uniforms.
		bool InitGL();

		//!Creates the shaders for the program
		void CreateProgram();

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
		virtual GLuint GetProgramId() const { return programId; }
		virtual float ScreenWidth() const = 0;
		virtual float ScreenHeight() const = 0;
		virtual void GetWindowSize(int* w, int* h) const = 0;

		//!Clears the GL background to entered color.
		static void ClearToColour(float r, float g, float b, float a);

		//!Processes a window event sent from input (e.g. window resize)
		void ProcessWindowEvent(const WindowEvent& event);
	};

	class RendererFactory
	{
		friend class Application;

		static std::shared_ptr<Renderer> CreateRenderer();
	};

}//namespace CSEngine

#endif
