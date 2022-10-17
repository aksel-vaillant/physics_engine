#include "PhysicEngine.h"
#include "physics/core/Particle.h"

/* ---------- Callbacks ---------- */

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// Shortcuts
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
	//if (key == GLFW_KEY_P && action == GLFW_PRESS) app.uiManager->startSimulation();
	//if (key == GLFW_KEY_R && action == GLFW_PRESS) app.uiManager->resetSimulation();
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	PhysicEngine& app = PhysicEngine::getInstance();

	app.WINDOW_WIDTH = width;
	app.WINDOW_HEIGHT = height;
}

/* ---------- Methods ---------- */

PhysicEngine& PhysicEngine::getInstance() {
	static PhysicEngine instance;
	return instance;
}

void PhysicEngine::initLogger() {
	spdlog::set_level(spdlog::level::debug); // Set global log level to debug
	spdlog::set_pattern("[%^%l%$] %v");
}

void PhysicEngine::initGLFW()
{
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

void PhysicEngine::initOpenGL()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		throw std::runtime_error("Failed to initialize GLAD");
	}
	
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, 0, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void PhysicEngine::initPhysicWorld() {
	
}

void PhysicEngine::initUI()
{
	uiManager = new UIManager();
	uiManager->init(window);

	//Particle* t = physicWorld->particles[0];
	//std::cout << "Position test - " << (*t).getPosition() << std::endl;
}

void PhysicEngine::mainLoop()
{

	physicWorld = new PhysicWorld();

	// Adding a particle
	Particle p(Vector3(1.0f, 100.0f, 1.0f));
	physicWorld->particles.push_back(&p);

	while (!glfwWindowShouldClose(window))
	{
		// Updates
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Integrating the system with our particle
		physicWorld->integrate(deltaTime);
		std::cout << "Position - " << (*physicWorld->particles[0]).getPosition() << std::endl;

		// Render
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		uiManager->render(deltaTime);

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void PhysicEngine::run()
{
	initLogger();
	initGLFW();
	initOpenGL();
	initPhysicWorld();
	initUI();

	spdlog::info("Initialization complete !");

	mainLoop();

	cleanUp();
}

void PhysicEngine::cleanUp()
{
	uiManager->cleanUp();

	glfwDestroyWindow(window);
	glfwTerminate();
}
