#pragma once
#include <GLEW\glew.h>
#include "Vertex.h"
class Sprite
{
public:
	Sprite();
	~Sprite();

	void init(float x, float y, float width, float height);

	void draw();

private:
	float _x;
	float _y;
	float _height;
	float _width;
	GLuint _vboID;
	Vertex vertexData[6];
};

