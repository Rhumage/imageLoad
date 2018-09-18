#include "stdafx.h"
#include "Shader.h"

#include <gl/glew.h>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <cassert>
#include <glm/glm.hpp>

std::string loadShader(const std::string fileName) {
	std::ifstream file;
	file.open("shaders/" + fileName);

	if (!file.is_open()) {
		std::cerr << "Unable to load shader: " << fileName << std::endl;
	}

	std::string output, line;
	while (file.good()) {
		getline(file, line);
		output.append(line + "\n");
	}

	return output;
}

void checkShaderError(GLuint shader, GLuint flag, bool is_program,
	const std::string errorMessage) {
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (is_program) {
		glGetProgramiv(shader, flag, &success);
	}
	else {
		glGetShaderiv(shader, flag, &success);
	}

	if (success == GL_FALSE) {
		if (is_program) {
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		}
		else {
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);
		}

		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}

GLuint createShader(const std::string text, GLenum type) {
	GLuint shader = glCreateShader(type);

	if (shader == 0) {
		std::cerr << "Error compiling shader type " << type << std::endl;
	}

	const GLchar* p[1];
	p[0] = text.c_str();
	GLint lengths[1];
	lengths[0] = (GLint)text.length();

	glShaderSource(shader, 1, p, lengths);
	glCompileShader(shader);

	checkShaderError(shader, GL_COMPILE_STATUS, false, "Error compiling shader!");

	return shader;
}

Shader::Shader() {

}

Shader::Shader(const std::string& path) {
	program = glCreateProgram();

	std::vector<GLuint> shaders;
		shaders.push_back(
			createShader(loadShader(path + ".vs"), GL_VERTEX_SHADER));
		shaders.push_back(
			createShader(loadShader(path + ".fs"), GL_FRAGMENT_SHADER));

	for (const auto& shader : shaders) {
		glAttachShader(program, shader);
	}

	glLinkProgram(program);
	checkShaderError(program, GL_LINK_STATUS, true, "Error linking program");
	glValidateProgram(program);
	checkShaderError(program, GL_LINK_STATUS, true, "Invalid program");

	for (const auto& shader : shaders) {
		glDetachShader(program, shader);
		glDeleteShader(shader);
	}
}


Shader::~Shader() {

}

void Shader::bind() {
	glUseProgram(program);
}
