#ifndef SHADER_H
#define SHADER_H

#pragma once
#include <string>
#include <GL\glew.h>
#include <fstream>
#include <iostream>
#include <GLFW\glfw3.h>

class Shader
{
private:
	static const unsigned int NUM_SHADERS = 2;
	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
	Shader(const Shader& other) {}
	void operator=(const Shader& other) {}
	
public:
	Shader(const std::string& fileName);
	void Bind();
	virtual ~Shader();
};
#endif SHADER_H