#pragma once
#include <stdio.h>
#include <math.h>

constexpr float PI = 3.14159f;
constexpr float FL_EPSILON = 1.192092896e-07F;

struct Vector
{
	float x;
	float y;
	float z;
};

float Rad2Deg(float radians);

Vector Rad2Vec(float pitch, float yaw);

void VectorNormalize(Vector& vec);

