#include "MathLib.h"
#include <iostream>

static double PI = 2 * std::acos(0.0);

Vec3::Vec3() 
{
	x = y = z = 0.0f;
}

Vec3::~Vec3()
{
}

Vec3::Vec3(float _x, float _y, float _z) 
{
	x = _x; y = _y; z = _z;
}

Vec3::Vec3(Vec4 & v)
{
	x = v.x / v.w; y = v.y / v.w; z = v.z / v.w;
}

Vec3::Vec3(Vec4* v)
{
	x = v->x; y = v->y; z = v->z;
}

Vec3 & Vec3::operator=(Vec4& v)
{
	x = v.x / v.w; y = v.y / v.w; z = v.z / v.w;
	return *this;
}

Vec3 & Vec3::operator*=(float i)
{
	x *= i; y *= i; z *= i;
	return *this;
}

Vec3 & Vec3::operator+=(Vec3 v)
{
	x += v.x; y += v.y; z += v.z;
	return *this;
}

Vec3 Vec3::operator*(float i)
{
	return Vec3(x*i, y*i, z*i);
}

Vec3 Vec3::operator+(Vec3 v)
{
	return Vec3(x + v.x, y + v.y, z + v.z);
}

Vec3 Vec3::operator-(Vec3 v)
{
	return Vec3(x - v.x, y - v.y, z - v.z);
}

float Vec3::length()
{
	return std::sqrt(x*x + y*y + z*z);
}

void Vec3::print() 
{
	std::cout << x << ' ' << y << ' ' << z << std::endl;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Vec4::Vec4()
{
	x = y = z = 0.0f;
	w = 1.0f;
}

Vec4::~Vec4()
{
}

Vec4::Vec4(float _x, float _y, float _z, float _w)
{
	x = _x; y = _y; z = _z; w = _w;
}

Vec4::Vec4(Vec3 & v)
{
	x = v.x; y = v.y; z = v.z; w = 1.0f;
}

Vec4::Vec4(Vec3 * v)
{
	x = v->x; y = v->y; z = v->z; w = 1.0f;
}

Vec4 & Vec4::operator=(Vec3 v)
{
	x = v.x; y = v.y; z = v.z; w = 1.0f;
	return *this;
}

Vec4 Vec4::operator*(Mat4& m)
{
	return Vec4(
		this->x*m.x.x + this->y*m.x.y + this->z*m.x.z + this->w*m.x.w,
		this->x*m.y.x + this->y*m.y.y + this->z*m.y.z + this->w*m.y.w,
		this->x*m.z.x + this->y*m.z.y + this->z*m.z.z + this->w*m.z.w,
		this->x*m.w.x + this->y*m.w.y + this->z*m.w.z + this->w*m.w.w
	);
}

void Vec4::print()
{
	std::cout << x << ' ' << y << ' ' << z << ' ' << w << std::endl;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Mat4::Mat4()
{
	x = Vec4(0.0f, 0.0f, 0.0f, 0.0f);
	y = Vec4(0.0f, 0.0f, 0.0f, 0.0f);
	z = Vec4(0.0f, 0.0f, 0.0f, 0.0f);
	w = Vec4(0.0f, 0.0f, 0.0f, 0.0f);
}

Mat4::Mat4(Vec4& _x, Vec4& _y, Vec4& _z, Vec4& _w) {
	x = _x;
	y = _y;
	z = _z;
	w = _w;
}

Vec4 Mat4::operator*(Vec4 v)
{
	return Vec4(
		this->x.x*v.x + this->y.x*v.y + this->z.x*v.z + this->w.x*v.w,
		this->x.y*v.x + this->y.y*v.y + this->z.y*v.z + this->w.y*v.w,
		this->x.z*v.x + this->y.z*v.y + this->z.z*v.z + this->w.z*v.w,
		this->x.w*v.x + this->y.w*v.y + this->z.w*v.z + this->w.w*v.w
	);
}

Mat4 Mat4::operator*(Mat4 m)
{
	return Mat4(
		this->operator*(m.x),
		this->operator*(m.y),
		this->operator*(m.z),
		this->operator*(m.w)
	);
}

GLfloat * Mat4::toGLArray()
{
	GLfloat glArray[16] = {
		x.x,x.y,x.z,x.w,
		y.x,y.y,y.z,y.w,
		z.x,z.y,z.z,z.w,
		w.x,w.y,w.z,w.w
	};
	return glArray;
}

void Mat4::toGLArray(GLfloat * inArray)
{
	inArray[0] = x.x; inArray[1] = x.y; inArray[2] = x.z; inArray[3] = x.w;
	inArray[4] = y.x; inArray[5] = y.y; inArray[6] = y.z; inArray[7] = y.w;
	inArray[8] = z.x; inArray[9] = z.y; inArray[10] = z.z; inArray[11] = z.w;
	inArray[12] = w.x; inArray[13] = w.y; inArray[14] = w.z; inArray[15] = w.w;
}

void Mat4::print()
{
	std::cout 
		<< x.x << ' ' << y.x << ' ' << z.x << ' ' << w.x << std::endl
		<< x.y << ' ' << y.y << ' ' << z.y << ' ' << w.y << std::endl
		<< x.z << ' ' << y.z << ' ' << z.z << ' ' << w.z << std::endl
		<< x.w << ' ' << y.w << ' ' << z.w << ' ' << w.w << std::endl;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

float MathLib::DotProduct(Vec3 v1, Vec3 v2)
{
	return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

Mat4 MathLib::IdentityMatrix()
{
	return Mat4(
		Vec4(1.0f, 0.0f, 0.0f, 0.0f),
		Vec4(0.0f, 1.0f, 0.0f, 0.0f),
		Vec4(0.0f, 0.0f, 1.0f, 0.0f),
		Vec4(0.0f, 0.0f, 0.0f, 1.0f));
}

Mat4 MathLib::TransformMatrix(float x, float y, float z)
{
	return Mat4(
		Vec4(1.0f, 0.0f, 0.0f, 0.0f),
		Vec4(0.0f, 1.0f, 0.0f, 0.0f),
		Vec4(0.0f, 0.0f, 1.0f, 0.0f),
		Vec4(x, y, z, 1.0f));
}

Mat4 MathLib::TransformMatrix(Vec3& v)
{
	return Mat4(
		Vec4(1.0f, 0.0f, 0.0f, 0.0f),
		Vec4(0.0f, 1.0f, 0.0f, 0.0f),
		Vec4(0.0f, 0.0f, 1.0f, 0.0f),
		Vec4(v.x, v.y, v.z, 1.0f));
}

Mat4 MathLib::ScaleMatrix(float x, float y, float z)
{
	return Mat4(
		Vec4(x, 0.0f, 0.0f, 0.0f),
		Vec4(0.0f, y, 0.0f, 0.0f),
		Vec4(0.0f, 0.0f, z, 0.0f),
		Vec4(0.0f, 0.0f, 0.0f, 1.0f));
}

Mat4 MathLib::ScaleMatrix(Vec3& v)
{
	return Mat4(
		Vec4(v.x, 0.0f, 0.0f, 0.0f),
		Vec4(0.0f, v.y, 0.0f, 0.0f),
		Vec4(0.0f, 0.0f, v.z, 0.0f),
		Vec4(0.0f, 0.0f, 0.0f, 1.0f));
}

Mat4 MathLib::RotationMatrix(Vec3& v, float angle)
{
	float c = std::cosf(angle / 360.0f*PI);
	float s = std::sinf(angle / 360.0f*PI);
	float t = 1.0f - c;
	if (v.x*v.x + v.y*v.y + v.z*v.z != 1.0f) {
		v *= 1.0f / v.length();
	}
	return Mat4(
		Vec4(t*v.x*v.x + c, t*v.x*v.y - s*v.z, t*v.x*v.z + s*v.y, 0.0f),
		Vec4(t*v.x*v.y + s*v.z, t*v.y*v.y + c, t*v.y*v.z - s*v.x, 0.0f),
		Vec4(t*v.x*v.z - s*v.y, t*v.y*v.z + s*v.x, t*v.z*v.z + c, 0.0f),
		Vec4(0.0f, 0.0f, 0.0f, 1.0f)
	);
}

Mat4 MathLib::RotationMatrixEuler(Vec3 & v)
{
	return Mat4();
}

Mat4 MathLib::PerspectiveMatrix(float angle, float aspectRatio, float near, float far)
{
	while (angle > 180.0f) {
		angle -= 180.0f;
	}
	while (angle < 0.0f) {
		angle += 180.0f;
	}
	float f = 1 / std::tan(angle / 360.0f*PI);
	return Mat4(
		Vec4(f / aspectRatio, 0.0f, 0.0f, 0.0f),
		Vec4(0.0f, f, 0.0f, 0.0f),
		Vec4(0.0f, 0.0f, (near + far) / (near - far), -1),
		Vec4(0.0f, 0.0f, (2.0f*near*far) / (near - far), 0.0f)
	);
}
