#pragma once
#include <GLEW/glew.h>
#include <math.h>

class Vec3;
class Vec4;
class Mat4;

class Vec3 {
public:	
	float x; float y; float z;

	Vec3();
	~Vec3();
	Vec3(float _x, float _y, float _z = 0.0f);
	Vec3(Vec4& v);
	Vec3(Vec4* v);
	
	Vec3& operator=(Vec4& v);
	Vec3& operator*= (float i);
	Vec3& operator+=(Vec3 v);
	Vec3 operator*(float i);
	Vec3 operator+(Vec3 v);
	Vec3 operator-(Vec3 v);
	float length();

	void print();
	
};

class Vec4:public Vec3{
public:
	float w;

	Vec4();
	~Vec4();
	Vec4(float _x, float _y, float _z = 0.0f, float _w = 1.0f);
	Vec4(Vec3& v);
	Vec4(Vec3* v);
	Vec4& operator=(Vec3 v);
	Vec4 operator*(Mat4& m);
	void print();
};

class Mat4 {
public:
	Vec4 x; Vec4 y; Vec4 z; Vec4 w;
	Mat4();
	Mat4(Vec4& _x, Vec4& _y, Vec4& _z, Vec4& _w);

	Vec4 operator*(Vec4 v);
	Mat4 operator*(Mat4 m);

	GLfloat* toGLArray();
	void toGLArray(GLfloat* inArray);

	void print();
};


class MathLib
{
public:
	static float DotProduct(Vec3 v1, Vec3 v2);
	static Mat4 IdentityMatrix();
	
	//trans*scale
	static Mat4 TransformMatrix(float x,float y,float z);
	static Mat4 TransformMatrix(Vec3& v);
	static Mat4 ScaleMatrix(float x,float y, float z);
	static Mat4 ScaleMatrix(Vec3& v);
	
	static Mat4 RotationMatrix(Vec3& v, float angle=0.0f);

	static Mat4 RotationMatrixEuler(Vec3& v);
	
	//view angle max 180 degrees
	static Mat4 PerspectiveMatrix(float angle, float aspectRatio, float near, float far);
};