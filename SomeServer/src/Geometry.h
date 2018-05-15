#ifndef Geom_H
#define Geom_H

class Point3D
{

	float x, y, z;

public:
	float X()
	{
		return x;
	}
	float Y()
	{
		return y;
	}
	float Z()
	{
		return z;
	}

	Point3D() {}

	Point3D(float xx, float yy, float zz)
	{
		x = xx;
		y = yy;
		z = zz;
	}

	void fill(float xx, float yy, float zz)
	{
		x = xx; y = yy; z = zz;
	}

	void fillX(float xx)
	{
		x = xx;
	}
	void fillY(float yy)
	{
		y = yy;
	}
	void fillZ(float zz)
	{
		z = zz;
	}

	Point3D operator-(Point3D operand)
	{
		return Point3D(this->X() - operand.X(), this->Y() - operand.Y(), this->Z() - operand.Z());
	}

	Point3D operator+(Point3D operand)
	{
		return Point3D(this->X() + operand.X(), this->Y() + operand.Y(), this->Z() + operand.Z());
	}

	Point3D operator/(float s)
	{
		return Point3D(this->X() / s, this->Y() / s, this->Z() / s);
	}
};


#endif