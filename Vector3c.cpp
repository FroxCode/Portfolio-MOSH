//Created by Dsin
#include "Vector3c.h"

Vector3c::Vector3c()
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
}
Vector3c::Vector3c(float x1, float y1, float z1) :
x(x1),
y(y1),
z(z1)

{

}
void Vector3c::PrintVect()
{
	cout << "Vector : (" << this->x << ", " << this->y << ", " << this->z << " )" << endl;
}
float Vector3c::Length()
{
	return (float)sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}
float Vector3c::LengthSq()
{
	return(this->x * this->x + this->y * this->y + this->z * this->z);
}
void Vector3c::Normalise()
{
	if (this->Length() > 0.0)
	{
		double mag = this->Length();
		this->x /= mag;
		this->y /= mag;
		this->z /= mag;
	}
}
Vector3c Vector3c::operator +(Vector3c V2)
{
	return (Vector3c::Vector3c(this->x + V2.x, this->y + V2.y, this->z + V2.z));
}
Vector3c Vector3c::operator-(Vector3c V2)
{
	return (Vector3c::Vector3c(this->x - V2.x, this->y - V2.y, this->z - V2.z));
}
Vector3c Vector3c::operator-()
{
	return (Vector3c::Vector3c(this->x * -1.0, this->y * -1.0, this->z * -1.0));
}
float Vector3c::operator*(Vector3c V2)
{
	return (this->x * V2.x + this->y * V2.y + this->z * V2.z);
}
Vector3c Vector3c::operator*(double k)
{
	return (Vector3c::Vector3c(this->x * k, this->y * k, this->z * k));
}
Vector3c Vector3c::operator*(float k)
{
	return (Vector3c::Vector3c(this->x * k, this->y * k, this->z * k));
}
Vector3c Vector3c::operator*(int k)
{
	return (Vector3c::Vector3c(this->x * k, this->y * k, this->z * k));
}
Vector3c Vector3c::operator^(Vector3c V2)
{
	return (Vector3c::Vector3c(this->y * V2.z - this->z * V2.y, this->z * V2.x - this->x * V2.z, this->x * V2.y - this->y * V2.x));
}
static double zProduct(Vector3c a, Vector3c b, Vector3c c, Vector3c d)
{
	return ((a - b ) ^ (c - d)).z;
}

