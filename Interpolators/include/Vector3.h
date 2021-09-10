#pragma once
#include <Defines.h>

struct Vector3
{
	double x{0.0};
	double y{0.0};
	double z{0.0};

	Vector3(double x, double y, double z)
		:
		x{ x },
		y{ y },
		z{ z }
	{}

	Vector3()
		: Vector3(0, 0, 0)
	{}

#pragma region operators 

	Vector3 operator/(double rhs) const { return { x / rhs , y / rhs , z / rhs }; }

	Vector3 operator*(double rhs) const { return { x * rhs ,  y * rhs , z * rhs }; }

	Vector3 operator-(const Vector3& rhs) const { return { x - rhs.x ,y - rhs.y , z - rhs.z }; }

	Vector3 operator+(const Vector3& rhs) const { return { x + rhs.x ,y + rhs.y , z + rhs.z }; }

	bool operator==(const Vector3& rhs) const
	{
		return cmp_floating(this->x, rhs.x) &&
			cmp_floating(this->y, rhs.y) &&
			cmp_floating(this->z, rhs.z);
	}

	bool operator!=(const Vector3& rhs) const
	{
		return !(*this == rhs);
	}

#pragma endregion

};