#include "UIManager.h"

#include <spdlog/spdlog.h>

// Icons from FontAwesome
#include "IconsFontAwesome.h"	// From... https://github.com/juliettef/IconFontCppHeaders/

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

void UIManager::render() {
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	// UI INTERFACE
	if (showWindow) {
		ImGui::SetNextWindowSize(ImVec2(300, 220), 0);

		// ImGUI window creation
		ImGui::Begin("Toolbox");

		ImGui::Text("\nPlay with gravity!");
		/*static float sliderGravity = physicsManager->getGravityConstant();
		ImGui::SliderFloat("###sliderGravity", &sliderGravity, 0.0f, 50.0f);

		if (sliderGravity != newGravity) {
			newGravity = sliderGravity;
			if (toggleDebug)
				spdlog::debug("[TOGGLE][DEBUG] Changed gravity to {}", newGravity);
		}*/

		if (ImGui::Button("Start###buttonStart", ImVec2(100, 25))) {
			// When I press the button start
		}

		if (ImGui::Button("Reset###buttonRestart", ImVec2(100, 25))) {
			// When I press the button restart
		}
		
		if (ImGui::Button("Reset & Start", ImVec2(100, 25))) {
		}

		ImGui::Checkbox("Debug", &toggleDebug);
		
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