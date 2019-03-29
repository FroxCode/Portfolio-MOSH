
/*  Dale Sinnott
*  Quaternion Class
*  Mathematical functions for quaternions
*/
#include "QuaternionC.h"
	//default Zero quaternion
QuaternionC::QuaternionC()
{
	w = 0.0;
	x = 0.0;
	y = 0.0;
	z = 0.0;
}
//overloaded constructor taking in values for the quaternion
QuaternionC::QuaternionC(double _W, double _X, double _Y, double _Z)
{
	w = _W;
	x = _X;
	y = _Y;
	z = _Z;
}
QuaternionC QuaternionC::operator +(QuaternionC Q2)
{ //adds the corresponding components of both quaternions and returns the summed quaternion (w1 + w2, x1 + x2, y1 + y2, z1 + z2)
	return QuaternionC(this->w + Q2.w, this->x + Q2.x, this->y + Q2.y, this->z + Q2.z);
}
QuaternionC QuaternionC::operator -(QuaternionC Q1)
{ //returns the matrix with all values inversed 
	return QuaternionC(-Q1.w, -Q1.x, -Q1.y, -Q1.z);
}
QuaternionC QuaternionC::operator *(QuaternionC Q2)
{ //Cross Product returns a quaternion from Q1.w(Q2) + Q1.x(Q2) + Q1.y(Q2) + Q1.z(Q2) , where all corresponding components w,x,y,z are simplified
	return QuaternionC((this->w * Q2.w) + -(this->x * Q2.x) + -(this->y * Q2.y) + -(this->z * Q2.z),
		(this->w * Q2.x) + (this->x * Q2.w) + (this->y * Q2.z) + -(this->z * Q2.y),
		(this->w * Q2.y) + -(this->x * Q2.z) + (this->y * Q2.w) + (this->z * Q2.x),
		(this->w * Q2.z) + (this->x * Q2.y) + -(this->y * Q2.x) + (this->z * Q2.w));
}
double QuaternionC::Modulus(QuaternionC Q1)
{ //returns modulus of Q1 (Square root of all components squared and summed)
	double mod;
	mod = sqrt((Q1.w * Q1.w) + (Q1.x * Q1.x) + (Q1.y * Q1.y) + (Q1.z * Q1.z));
	return mod;
}
QuaternionC QuaternionC::Conjugate(QuaternionC Q1)
{ //returns quaternion with all values inversed apart from the first value
	return QuaternionC(Q1.w, -Q1.x, -Q1.y, -Q1.z);
}
QuaternionC QuaternionC::Scale(QuaternionC Q1, double s)
{ //scales all components of Q1 by a scalar number
	return QuaternionC(Q1.w * s, Q1.x * s, Q1.y * s, Q1.z * s);
}
QuaternionC QuaternionC::Normalise(QuaternionC Q1)
{ //returns a normalised quaternion
	double magnitude = sqrt(Q1.w * Q1.w + Q1.x * Q1.x + Q1.y * Q1.y + Q1.z * Q1.z); //get magnitude (Square root of sum of all components squared
	return QuaternionC(Q1.w / magnitude, Q1.x / magnitude, Q1.y / magnitude, Q1.z / magnitude); //normalise the quaternion (all components divided by the magnitude)
}
Vector3c QuaternionC::Rotation(QuaternionC Q1, Vector3c V, double _angle)	
{ //rotates a point V about a quaternion Q1 at angle in degrees _angle
	QuaternionC P = QuaternionC::Normalise(Q1); //normalise for axis rotation
	double angle = _angle * (3.14 / 180); //angle in degrees, converted to radians
	P = QuaternionC(cos(angle / 2), P.x * sin(angle / 2), P.y * sin(angle / 2), P.z * sin(angle / 2)); //point P
	QuaternionC R = QuaternionC(0, V.x, V.y, V.z); //point R
	QuaternionC pConj = QuaternionC::Conjugate(P); //point P' (conjugate of P)
	P = (P*R)*pConj; //P.R.P'
	return Vector3c(P.x, P.y, P.z);
}
