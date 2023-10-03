#pragma once
#include "EMath.h"
#include "ERGBColor.h"

using namespace Elite;
struct Ray {
	FPoint3 origin = {};
	FVector3 direction = {};
	float tMin = 0.0001f;
	float tMax = FLT_MAX;
};

struct HitRecord
{
	FPoint3 hitPos = {};
	FVector3 normal = {};
	RGBColor color = {};
	float tValue = {};
	float tClosest = FLT_MAX;
};
