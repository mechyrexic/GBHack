#include "maths.h"


float Rad2Deg(float radians)
{
	return (radians * (180 / PI));
}

Vector Rad2Vec(float pitch, float yaw)
{
	Vector vec;
	float    sp, sy, cp, cy;
	sp = sinf(pitch);
	sy = sinf(yaw);
	cp = cosf(pitch);
	cy = cosf(yaw);

	vec.x = cp * cy;
	vec.y = cp * sy;
	vec.z = -sp;
	
	return vec;
}

void VectorNormalize(Vector& vec)
{
	float radius = sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);

	// FL_EPSILON is added to the radius to eliminate the possibility of divide by zero.
	float iradius = 1.f / (radius + FL_EPSILON);

	vec.x *= iradius;
	vec.y *= iradius;
	vec.z *= iradius;
}