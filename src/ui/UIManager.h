#pragma once

#define IMGUI_IMPL_OPENGL_LOADER_GLAD

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

class UIManager {
public:
	UIManager();

	void init(GLFWwindow* window);//, PhysicWorld* physicWorld);
	void render(float dt);
	void cleanUp();	
	
	/* ---------- Variables ---------- */

	bool showWindow = true;

	/* ---------- Getters & Setters ---------- */	
	
	// void setPhysicWorld(PhysicWorld* pWorld) { physicWorld = pWorld; }
	// PhysicWorld* getPhysicWorld() const { return physicWorld; }


private:
	/* ---------- Components ---------- */

	// PhysicWorld* physicWorld = nullptr;

	/* ---------- Variables for UI Components ---------- */
	// real x = 1.f;  real y = 1.f; real z = 1.f;
	float newGravity = 10.0f;
	bool toggleDebug = false;
};

