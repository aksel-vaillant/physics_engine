#pragma once

// Basics
#include <iostream>						// Standard I/O streams
#include <sstream>
#include <stdlib.h>						// Conversion, random and dynamic memory management
#include <stdio.h>						// I/O operations
using namespace std;

// Graphics
#include "glad/glad.h"					
#include <GLFW/glfw3.h>					// Must be included after glad

// UI
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "ui/UIManager.h"

// Logging
#include "spdlog/spdlog.h"
#include "physics/PhysicWorld.h"

class PhysicEngine
{
	public:		
		const int GL_VERSION_MAJOR = 3, GL_VERSION_MINOR = 3;

		GLFWwindow* window = nullptr;
		UIManager* uiManager = nullptr;
		PhysicWorld* physicWorld = nullptr;

		uint32_t WINDOW_WIDTH = 800;
		uint32_t WINDOW_HEIGHT = 600;

		float deltaTime = 0.0f;					// Time between current frame and last frame
		float lastFrame = 0.0f;					// Time of last frame

		/* ---------- Methods ---------- */

		static PhysicEngine& getInstance();
		void run();
		
	private:
		PhysicEngine(void){}					// private constructor necessary to allow only 1 instance
		PhysicEngine(PhysicEngine const&);		// prevent copies
		void operator=(PhysicEngine const&);	// prevent assignments

		/* ---------- Methods ---------- */
		void initLogger();
		void initGLFW();
		void initOpenGL();		
		void initPhysicWorld();
		void initUI();

		void mainLoop();

		void cleanUp();
};


