#include "ClothObject.h"
#include <iostream>
#include <cstddef>

float springConst = 5000.0f;

ClothObject::ClothObject()
{
	_vboID = 0;
}


ClothObject::~ClothObject()
{
	if (_vboID != 0)
		glDeleteBuffers(1, &_vboID);
}

void ClothObject::init(int x, int y, float width, float length, float height)
{
	if (_vboID == 0) {
		glGenBuffers(1, &_vboID);
	}
	_x = x; _y = y;
	verticies.reserve((x + 1)*(y + 1));
	triangles.reserve(x*y * 12);

	std::cout << "loading triangles" << std::endl;

	for (int i = 0; i <= x; i++) {
		for (int j = 0; j <= y; j++) {
			int currentVer = i*(y + 1) + j;
			//std::cout << currentVer << std::endl;

			verticies.push_back(VertexCloth(((float)i / x - 0.5f)*length, height, ((float)j / y - 0.5f)*width));
			//verticies[verticies.size() - 1].position.print();
			if (i != x &&j != y) {
				
				triangles.push_back(currentVer); triangles.push_back(currentVer + 1); triangles.push_back(currentVer + (y + 1) + 1);
				triangles.push_back(currentVer); triangles.push_back(currentVer + (y + 1) + 1); triangles.push_back(currentVer + (y + 1));
				//other side
				triangles.push_back(currentVer); triangles.push_back(currentVer + 1); triangles.push_back(currentVer + (y + 1));
				triangles.push_back(currentVer + 1); triangles.push_back(currentVer + (y + 1) + 1); triangles.push_back(currentVer + (y + 1));
			}
		}
	}

	std::cout << "loading colors" << std::endl;

	vertexData.reserve(triangles.size());
	for (int i = 0; i < triangles.size(); i++) {
		vertexData.push_back(Vertex());
		vertexData[i].color.r = 255;
		vertexData[i].color.g = 0;
		vertexData[i].color.b = 0;
		vertexData[i].color.a = 255;

		vertexData[i].position = (verticies[triangles[i]].position);
		//vertexData[i].position.print();
	}

	std::cout << "loading pairs" << std::endl;

	for (int i = 0; i < triangles.size() / 3; i++) {
		bool tof1 = true; bool tof2 = true; bool tof3 = true;
		unsigned int tri1 = triangles[3 * i];
		unsigned int tri2 = triangles[3 * i + 1];
		unsigned int tri3 = triangles[3 * i + 2];

		for (int j = 0; j < pairs.size(); j++) {
			x = pairs[j].pair1; y = pairs[j].pair2;
			//1,2---2,3---1,3
			if ((x == tri1 && y == tri2) ||
				(x == tri2 && y == tri1)) {
				tof1 = false;
			}
			if ((x == tri2 && y == tri3) ||
				x == tri3 && y == tri2) {
				tof2 = false;
			}
			if ((x == tri1 && y == tri2) ||
				x == tri3 && y == tri1) {
				tof3 = false;
			}
		}
		//std::cout << tof1 << ' ' << tof2 << ' ' << tof3 << std::endl;
		if (tof1) {
			pairs.push_back(Pairs(tri1,tri2,(verticies[tri1].position-verticies[tri2].position).length()));
		}
		if (tof2) {
			pairs.push_back(Pairs(tri2, tri3, (verticies[tri2].position - verticies[tri3].position).length()));
		}
		if (tof3) {
			pairs.push_back(Pairs(tri1, tri3, (verticies[tri1].position - verticies[tri3].position).length()));
		}
	}

	std::cout << "done" << std::endl;

	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*triangles.size(), &vertexData.front(), GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ClothObject::update()
{
	for (int i = 0; i < verticies.size(); i++) {
		//gravity
		verticies[i].accel = Vec3(0.0f, -10.0f, 0.0f);
		//drag force
		//-1000.0f is 100% speed reduction
		verticies[i].accel += verticies[i].delta*-0.5f;
		//(verticies[i].delta*-5.0f).print();
	}

	//spring force
	for (int i = 0; i < pairs.size(); i++) {
		Vec3 force = verticies[pairs[i].pair1].position - verticies[pairs[i].pair2].position;
		float mag = force.length();

		if (mag != 0.0f) {
			force *= (1.0f / mag)*(mag - pairs[i].length)*springConst;
			verticies[pairs[i].pair1].accel += force*-1.0f;
			verticies[pairs[i].pair2].accel += force;
		}
		//std::cout << mag << ' '<<pairs[i].length<<' ';
		//(force*springConst).print();
	}

	for (int i = 0; i < verticies.size(); i++) {
		verticies[i].delta += verticies[i].accel*0.001f;

		//collision math
	}

	for (int i = 0; i < verticies.size(); i++) {
		if (i <= _y) {
			verticies[i].delta= Vec3(0.0f,0.0f,0.0f);
		}
		verticies[i].position += verticies[i].delta*0.001f;
		//std::cout << verticies[i].accel.y << ' ' << verticies[i].delta.y << ' ' << verticies[i].position.y << '\n';
	}
	//std::cout<<'\n'<<std::endl;
}

void ClothObject::draw()
{
	for (int i = 0; i < triangles.size(); i++) {
		vertexData[i].position = (verticies[triangles[i]]).position;
	}

	//std::cout << triangles.size() << std::endl;
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	//glBufferSubData(GL_ARRAY_BUFFER,0, sizeof(vertexData), vertexData);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*triangles.size(), &vertexData.front(), GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));


	glDrawArrays(GL_TRIANGLES, 0, triangles.size());
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
