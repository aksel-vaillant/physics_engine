#pragma once

#define IMGUI_IMPL_OPENGL_LOADER_GLAD

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

class UIManager {
public:
	UIManager() {};

	void init(GLFWwindow* window);
	void render();
	void cleanUp();	
	
	/* ---------- Variables ---------- */

	bool showWindow = true;

private:

	float newGravity = 10.0f;
	bool toggleDebug = false;
};

