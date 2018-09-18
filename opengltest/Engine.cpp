#include "stdafx.h"
#include "Engine.h"

Engine::Engine() : window(width, height) {
	second = Shader("second");
}

Engine::~Engine() {

}

void Engine::init_texture() {
	uint32_t* data = new uint32_t[width * height];
	for (unsigned int i = 0; i < width * height; ++i) {
		data[i] = 0xFF;
	}
	glGenTextures(1, &head_pointer_image);
	glBindTexture(GL_TEXTURE_2D, head_pointer_image);
	glTexImage2D(GL_TEXTURE_2D, 0, // 2D texture, level 0
		GL_R32UI, // 32-bit GLuint per texel
		width, // Width
		height, // Height
		0, // No border
		GL_RED_INTEGER, // Single-channel
		GL_UNSIGNED_INT, // Unsigned int
		data); // No data... yet
	delete[] data;
}

void Engine::bind_texture() {
	glBindImageTexture(0, // Image unit 0
		head_pointer_image,
		0, // Level
		GL_FALSE, 0, // Not layered
		GL_READ_ONLY, // Read and write access
		GL_R32UI); // 32-bit GLuint per pixel
}

void Engine::loop() {
	GLuint vao;
	glCreateVertexArrays(1, &vao);
	glBindVertexArray(vao);

	second.bind();
	init_texture();
	bind_texture();

	while (window.isRunning()) {
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		window.swapBuffers();
	}
}