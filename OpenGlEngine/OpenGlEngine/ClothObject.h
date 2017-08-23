#pragma once
#include <GLEW\glew.h>
#include <vector>
#include "Vertex.h"

struct Pairs;
struct VertexCloth;

struct VertexCloth
{
public:
	VertexCloth(float posX = 0.0f, float posY = 0.0f, float posZ = 0.0f) {
		position = Vec3(posX, posY, posZ);
		delta = Vec3();
		accel = Vec3();
	}
	Vec3 position;
	Vec3 delta;
	Vec3 accel;
};


struct Pairs
{
public:
	unsigned int pair1;
	unsigned int pair2;
	float length;

	Pairs(int p1 = 0, int p2 = 0, float l = 0.0f) {
		pair1 = p1;
		pair2 = p2;
		length = l;
	}

};

class ClothObject
{
public:
	ClothObject();
	~ClothObject();
	void init(int x, int y, float width, float length, float height);

	void update();
	void draw();

private:
	GLuint _vboID;

	std::vector<VertexCloth> verticies;
	std::vector<unsigned int> triangles;
	std::vector<Pairs> pairs;

	std::vector<Vertex> vertexData;

	int _x;
	int _y;
};

