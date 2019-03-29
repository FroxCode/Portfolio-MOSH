//Created by Dsin
#ifndef _VECTOR3C_H_
#define _VECTOR3C_H_
#include <iostream>
using namespace std;

class Vector3c{
public:
	float x; float y; float z;
	Vector3c();
	Vector3c(float x1, float y1, float z1);
	void PrintVect();
	float Length();
	float LengthSq();
	void Normalise();
	
	Vector3c operator +(Vector3c V2);
	Vector3c operator -(Vector3c V2);
	Vector3c operator -();
	float operator *(Vector3c V2);
	Vector3c operator *(float k);
	Vector3c operator *(double k);
	Vector3c operator *(int k);
	Vector3c operator ^(Vector3c V2);
	static float zProduct(Vector3c a, Vector3c b, Vector3c c, Vector3c d);
};
#endif