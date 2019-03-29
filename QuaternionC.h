//Created by Dsin
#ifndef _QUATERNIONC_H_
#define _QUATERNIONC_H_
#include <cmath>
#include <array>
#include <iostream>
using namespace std;
#include "Vector3c.h"

class QuaternionC
{
	//Variables and properties of a quaternion
public:
	double W() const { return w; }
	void W(const double& W) { w = W; }
	
	double X() const { return x; }
	void X(const double& X) { x = X; }

	double Y() const { return y; }
	void Y(const double& Y) { y = Y; }

	double Z() const { return z; }
	void Z(const double& Z) { z = Z; }

	//default Zero quaternion
	QuaternionC::QuaternionC();
	
	//overloaded constructor taking in values for the quaternion
	QuaternionC(double _W, double _X, double _Y, double _Z);
	
	QuaternionC operator +(QuaternionC Q2);
	QuaternionC operator -(QuaternionC Q1);
	QuaternionC operator *(QuaternionC Q2);
	double Modulus(QuaternionC Q1);
	QuaternionC Conjugate(QuaternionC Q1);
	QuaternionC Scale(QuaternionC Q1, double s);
	QuaternionC Normalise(QuaternionC Q1);
	Vector3c Rotation(QuaternionC Q1, Vector3c V, double _angle);

private:
	double w; double x; double y; double z;
};
#endif