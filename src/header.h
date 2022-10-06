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