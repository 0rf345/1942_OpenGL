#ifndef TEXTURE_H
#define TEXTURE_H

#pragma once
#include <string>
#include <GL\glew.h>
#include <iostream>
#include <cassert>

class Texture
{
public:
	Texture(const std::string& fileName);

	void Bind(unsigned int unit);

	virtual ~Texture();
protected:
private:
	Texture(const Texture& texture) {}
	void operator=(const Texture& texture) {}

	GLuint m_texture;
};

#endif