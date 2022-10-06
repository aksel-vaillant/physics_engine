# physics_engine

Creation of a physics engine for the video game class at UQAC - Université du Québec à Chicoutimi [CANADA]

Realized by Aksel Vaillant, Clément Le Batard and Juliette Le Meudec

## Configuration

💻 IDE - Visual Studio v.2022    
💿 Platform - Winx64   
📚 Librairies - glfw, glad, glew, glm, imgui and spdlog   

## Librairies    

- GLFW is a lightweight utility library for use with OpenGL    
- GLAD is typically used by selecting the necessary extensions in the web interface, downloading the generated source and header files   
- GLEW is an extension loading library allowing easy management of OpenGL extensions
- GLM is a header only mathematics library for graphics software based on OpenGL
- ImGui is a graphical user interface library for C++ to create content creation tools and visualization / debug tools
- spdlog is an easy and complete logging library with different levels and pattern   

## Files architecture  

With this project, you don't need to configure everything. Everything is already included.   
You will find 3 important folders : lib, res and src.  
- lib contains all our librairies mentionned above.
- res contains all our additional ressources like images, shaders, fonts and so on.
- src contains all the physics engine with systems like UI (User Interface), graphics and finally physics.
