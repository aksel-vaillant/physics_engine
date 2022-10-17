#include "UIManager.h"

#include <spdlog/spdlog.h>

// Icons from FontAwesome
#include "IconsFontAwesome.h"	// From... https://github.com/juliettef/IconFontCppHeaders/
#include <iostream>

UIManager::UIManager()
{
}

void UIManager::init(GLFWwindow* window) {
	// ImGUI Initialization
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontDefault();
	
	//Merge in icons from Font Awesome
	static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
	ImFontConfig icons_config; icons_config.MergeMode = true; icons_config.PixelSnapH = true;
	io.Fonts->AddFontFromFileTTF("res/fonts/" FONT_ICON_FILE_NAME_FAS, 16.0f, &icons_config, icons_ranges);

	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

void UIManager::render(float dt) {
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	static bool hasBeenPressed = false;

	// UI INTERFACE
	if (showWindow) {
		ImGui::SetNextWindowSize(ImVec2(300, 220), 0);

		// ImGUI window creation
		ImGui::Begin("Toolbox");

		// ImGui::SliderFloat("X", &x, 1.f, 100.f);
		// ImGui::SliderFloat("Y", &y, 1.f, 100.f);
		// ImGui::SliderFloat("Z", &z, 1.f, 100.f);

		//(*physicWorld->particles[0]).setPosition(Vector3(x));

		if (ImGui::Button("Start")) {
			hasBeenPressed = !hasBeenPressed;
		}
	
		if (hasBeenPressed) {
			//physicWorld->integrate(dt);
		}
		if (ImGui::Button("Restart")) {
			// Vector3 initPos = Vector3(1.f, 100.f, 1.f);
			// (*physicWorld->particles[0]).setPosition(initPos);
		}

		ImGui::Checkbox("Debug", &toggleDebug);
		if (toggleDebug) {
			// std::cout << "Position - " << (*physicWorld->particles[0]).getPosition().y << std::endl;
		}
		
		// Ends the window
		ImGui::End();
	}
	
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UIManager::cleanUp() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}