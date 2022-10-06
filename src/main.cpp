#pragma once
#include "header.h"

class MainApp {
public:

	static MainApp& getInstance() {
		static MainApp instance;
		return instance;
	}

	/* ---------- Callbacks ---------- */

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{			
		// Shortcuts
		if(key == GLFW_KEY_SPACE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
		//if (key == GLFW_KEY_P && action == GLFW_PRESS) app.uiManager->startSimulation();
		//if (key == GLFW_KEY_R && action == GLFW_PRESS) app.uiManager->resetSimulation();
	}

	static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
		MainApp& app = MainApp::getInstance();

		app.WINDOW_WIDTH = width;
		app.WINDOW_HEIGHT = height;
	}

	const int GL_VERSION_MAJOR = 3, GL_VERSION_MINOR = 3;

public:

	void run() {
		initLogger();
		initGLFW();
		initOpenGL();
		initUI();

		spdlog::info("Initialization complete !");

		mainLoop();

		cleanUp();
	}

	/* ---------- VARIABLES ---------- */
	GLFWwindow* window;
	UIManager* uiManager;

	uint32_t WINDOW_WIDTH = 1080;
	uint32_t WINDOW_HEIGHT = 920;
	
	float deltaTime = 0.0f;	// Time between current frame and last frame
	float lastFrame = 0.0f; // Time of last frame

private:
	MainApp(void) {}				// private constructor necessary to allow only 1 instance
	MainApp(MainApp const&);		// prevent copies
	void operator=(MainApp const&); // prevent assignments

	/* ---------- METHODS ---------- */
	void initLogger() {
		spdlog::set_level(spdlog::level::debug); // Set global log level to debug
		spdlog::set_pattern("[%^%l%$] %v");
	}

	void initGLFW() {
		glfwInit();
		window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL Game Engine", nullptr, nullptr);

		// Set all the required options for GLFW
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GL_VERSION_MAJOR);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GL_VERSION_MINOR);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, true);
		glfwSwapInterval(1); // Enable vsync

		glfwMakeContextCurrent(window);

		glfwSetKeyCallback(window, key_callback);
		glfwSetWindowSizeCallback(window, framebuffer_size_callback);
	}

	void initOpenGL() {
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			throw std::runtime_error("Failed to initialize GLAD");
		}

		glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glEnable(GL_DEPTH_TEST);
	}

	void initUI() {
		uiManager = new UIManager();
		uiManager->init(window);
	}

	void mainLoop() {
		while (!glfwWindowShouldClose(window))
		{
			// Updates
			float currentFrame = (float) glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			// Render
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			uiManager->render();

			// Swap the back buffer with the front buffer
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}

	void cleanUp() {
		uiManager->cleanUp();

		glfwDestroyWindow(window);
		glfwTerminate();
	}
};

int main()
{
	MainApp& app = MainApp::getInstance();

	try {
		app.run();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}