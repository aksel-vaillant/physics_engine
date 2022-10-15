#pragma once
#include "PhysicEngine.h"

int main()
{
	PhysicEngine& app = PhysicEngine::getInstance();

	try {
		app.run();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}