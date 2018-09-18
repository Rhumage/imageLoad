#pragma once

#include <string>
#include <gl/glew.h>

class Shader {
	GLuint program;

public:
	Shader();
	Shader(const std::string& path);
	~Shader();

	void bind();
};

