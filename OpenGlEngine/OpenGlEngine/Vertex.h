#pragma once
#include <GLEW\glew.h>
#include "MathLib.h"

struct Vertex
{
	Vec3 position;

	struct Color
	{
		GLubyte r=255;
		GLubyte g=255;
		GLubyte b=255;
		GLubyte a=255;
	} color;

};