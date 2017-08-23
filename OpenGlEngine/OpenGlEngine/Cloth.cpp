#include "Cloth.h"
#include <iostream>
#include <cstddef>

Cloth::Cloth()
{
	_vboID = 0;
}

Cloth::~Cloth()
{
	if (_vboID != 0)
		glDeleteBuffers(1, &_vboID);
	_verticies.clear();
	_triangles.clear();
	_pairs.clear();
}

void Cloth::init(int x, int y, float width, float length,float height)
{
	
	if (_vboID == 0) {
		glGenBuffers(1, &_vboID);
	}
	_verticies.reserve((x + 1)*(y + 1));
	//all triangles and double sided
	_triangles.reserve(x*y * 6*2);
	//auto temp = _verticies.begin();
	

	for (int i = 0; i <= x; i++) {
		for (int j = 0; j <= y; j++){
			//std::cout << i <<' '<<y+1<<' '<<j<<' '<<  i*(y + 1) + j << std::endl;
			int currentVert = i*(y + 1) + j;
			//_verticies[currentVert]= VertexCloth((float)i / x*width,(float)j/y*length);
			_verticies.push_back(VertexCloth((float)i / x*width, (float)j / y*length,height));
			/*
			if (i != x || j != y) {
				int currentTri = i*y + j;
				_triangles[currentTri * 6] = currentVert; _triangles[currentTri * 6 + 1] = currentVert + 1; _triangles[currentTri * 6 + 2] = currentVert + (y + 1) + 1;
				_triangles[currentTri * 6 + 3] = currentVert; _triangles[currentTri * 6 + 4] = currentVert + (y + 1) + 1; _triangles[currentTri * 6 + 5] = currentVert + (y + 1);
				
				_triangles[currentTri * 6 + x*y] = currentVert; _triangles[currentTri * 6 + 1 + x*y] = currentVert + (y + 1) + 1; _triangles[currentTri * 6 + 2 + x*y] = currentVert + 1;
				_triangles[currentTri * 6 + 3 + x*y] = currentVert; _triangles[currentTri * 6 + 4 + x*y] = currentVert + (y + 1); _triangles[currentTri * 6 + 5 + x*y] = currentVert + (y + 1) + 1;
			}
			*/
			if (i != x && j != y) {
				int currentTri = i*y + j;
				std::cout << currentVert << ' ' << currentTri << std::endl;
				_triangles.push_back(currentVert); _triangles.push_back(currentVert+1); _triangles.push_back(currentVert + (y + 1) + 1);
				_triangles.push_back(currentVert); _triangles.push_back(currentVert + (y + 1) + 1); _triangles.push_back(currentVert + (y + 1));

				_triangles.push_back(currentVert); _triangles.push_back(currentVert + (y + 1) + 1); _triangles.push_back(currentVert + 1);
				_triangles.push_back(currentVert); _triangles.push_back(currentVert + (y + 1)); _triangles.push_back(currentVert + (y + 1) + 1);
			}
		}
	}
	
	//std::cout << _verticies.capacity() << std::endl;
	//vertexData.reserve(_triangles.size());
	//vertexData = new Vertex[_triangles.size()]();
	/*
	for (int i = 0; i < _triangles.size();i++) {
		//std::cout << _triangles[i] << std::endl;
		vertexData[i].position=_verticies[_triangles[i]].position;
		vertexData[i].color.r = 255; vertexData[i].color.b = 0; vertexData[i].color.g = 0; vertexData[i].color.a = 1;
		vertexData[i].position.print();

	}*/
	vertexData = new Vertex[6]();
	vertexData[0].position.x = x + width;
	vertexData[0].position.y = y + height;

	vertexData[1].position.x = x;
	vertexData[1].position.y = y + height;

	vertexData[2].position.x = x;
	vertexData[2].position.y = y;

	vertexData[3].position.x = x;
	vertexData[3].position.y = y;

	vertexData[4].position.x = x + width;
	vertexData[4].position.y = y;

	vertexData[5].position.x = x + width;
	vertexData[5].position.y = y + height;

	for (int i = 0; i < 6; i++) {
		vertexData[i].color.r = 255;
		vertexData[i].color.g = 0;
		vertexData[i].color.b = 0;
		vertexData[i].color.a = 255;
	}

	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Cloth::update()
{
	/*
	for (int i = 0; i < _triangles.size();i++) {
		vertexData[i].position=_verticies[_triangles[i]].position;
	}
	*/
	vertexData = new Vertex[6]();
	vertexData[0].position.x = 1.0f;
	vertexData[0].position.y = 1.0f;

	vertexData[1].position.x = 0.0f;
	vertexData[1].position.y = 1.0f;

	vertexData[2].position.x = 0.0f;
	vertexData[2].position.y = 0.0f;

	vertexData[3].position.x = 0.0f;
	vertexData[3].position.y = 0.0f;

	vertexData[4].position.x = 1.0f;
	vertexData[4].position.y = 0.0f;

	vertexData[5].position.x = 1.0f;
	vertexData[5].position.y = 1.0f;

	//std::cout << "Updating" << std::endl;
	
}

void Cloth::draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	//glBufferSubData(GL_ARRAY_BUFFER,0, sizeof(vertexData), vertexData);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));


	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
