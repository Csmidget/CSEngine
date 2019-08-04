#ifndef GAME_ENGINE_WINDOW_EVENT_H
#define GAME_ENGINE_WINDOW_EVENT_H

namespace GameEngine
{
	typedef enum
	{
		WINDOWEVENT_NONE,           /**< Never used */
		WINDOWEVENT_SHOWN,          /**< Window has been shown */
		WINDOWEVENT_HIDDEN,         /**< Window has been hidden */
		WINDOWEVENT_EXPOSED,        /**< Window has been exposed and should be
										 redrawn */
		WINDOWEVENT_MOVED,          /**< Window has been moved to data1, data2
									 */
		WINDOWEVENT_RESIZED,        /**< Window has been resized to data1xdata2 */
		WINDOWEVENT_SIZE_CHANGED,   /**< The window size has changed, either as
										 a result of an API call or through the
										 system or user changing the window size. */
		WINDOWEVENT_MINIMIZED,      /**< Window has been minimized */
		WINDOWEVENT_MAXIMIZED,      /**< Window has been maximized */
		WINDOWEVENT_RESTORED,       /**< Window has been restored to normal size
										 and position */
		WINDOWEVENT_ENTER,          /**< Window has gained mouse focus */
		WINDOWEVENT_LEAVE,          /**< Window has lost mouse focus */
		WINDOWEVENT_FOCUS_GAINED,   /**< Window has gained keyboard focus */
		WINDOWEVENT_FOCUS_LOST,     /**< Window has lost keyboard focus */
		WINDOWEVENT_CLOSE,          /**< The window manager requests that the window be closed */
		WINDOWEVENT_TAKE_FOCUS,     /**< Window is being offered a focus (should SetWindowInputFocus() on itself or a subwindow, or ignore) */
		WINDOWEVENT_HIT_TEST        /**< Window had a hit test that wasn't SDL_HITTEST_NORMAL. */
	} WindowEventID;
	
	//To be expanded?
	struct WindowEvent
	{
		WindowEventID type;
		int data1;
		int data2;
	};
}

#endif