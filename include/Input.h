#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "Export.h"


class GUIHandler;
class Render;

class Input
{
public:
	Input() = delete;


	ENGINE_API static void Initialize();
	ENGINE_API static void Tick(Render& render, GUIHandler& gui_handler, GLFWwindow* window);
	ENGINE_API static void TickTimer();

	ENGINE_API static bool IsKeyPressed(const int32_t key);
	ENGINE_API static bool IsMousePressed(const int32_t key);
	ENGINE_API static void toggleCursorMode();

	ENGINE_API static float GetLastX();
	ENGINE_API static float GetLastY();
	ENGINE_API static int GetFps();
	ENGINE_API static double GetDeltaTime();

};

