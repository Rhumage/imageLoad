#pragma once

#include "Window.h"
#include "Shader.h"

class Engine {
	static constexpr uint32_t width = 1920;
	static constexpr uint32_t height = 1080;

	Window window;
	Shader second;
	GLuint head_pointer_image;

public:
	Engine();
	~Engine();

	void init_texture();
	void bind_texture();
	void loop();
};

