#pragma once

#include <GLFW/glfw3.h>

#include "Export.h"

struct WindowData
{
	/*GLFWimage* icon;*/
	const char* title;
	int width;
	int height;
	float aspectRatio;
	bool vsync;
	bool fullscreen;

};

class Window
{
private:
	static GLFWwindow* window;
	static WindowData windowData;


public:
	Window() = delete;


	static ENGINE_API void Initialize();
	static ENGINE_API void SetVSync(bool state);
	static ENGINE_API bool ShouldClose();
	static ENGINE_API void SwapBuffers();
	static ENGINE_API void Resize(int width, int height);



	static ENGINE_API GLFWwindow* GetWindow();
	static ENGINE_API bool GetVSync();
	static ENGINE_API WindowData GetWindowData();
	static ENGINE_API int GetWindowWidth();
	static ENGINE_API int GetWindowHeight();
	static ENGINE_API float GetAspectRatio();
};

