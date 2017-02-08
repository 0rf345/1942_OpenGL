#ifndef MESH_H
#define MESH_H

#pragma once
#include "glm/glm.hpp"
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <vector>

class Vertex
{
private:
	glm::vec3 pos;
	glm::vec2 texCoord;

public:
	Vertex(const glm::vec3& pos, const glm::vec2 texCoords)
	{
		this->pos = pos;
		this->texCoord = texCoords;
	}
	inline glm::vec3* getPos() {	return &pos; }
	inline glm::vec2* getTexCoord()	{ return &texCoord; }
	inline void setPos(glm::vec3& newPos) { pos = newPos; }
};

class Mesh
{
private:
	Mesh(const Mesh& other);
	void operator=(const Mesh& other);
	GLuint m_vertexArrayObject;

	enum
	{
		POSITION_VB,
		TEXCOORD_VB,
		NUM_BUFFERS
	};

	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	unsigned int m_drawCount;
	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> texCoords;

public:
	Mesh(Vertex* vertices, unsigned int numVertices);
	virtual ~Mesh();
	void Draw();
	void MoveDown();
	void Update(Vertex* vertices);
	void Buffer();
	void UnBuffer();
	glm::vec3* GetPos();
	GLuint getVBpos() {
		return m_vertexArrayBuffers[POSITION_VB];
	}
};

#endif MESH_H

