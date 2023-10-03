#pragma once
#include "Light.h"

class DirectionalLight : public Light
{
public:
	DirectionalLight(const FVector3& direction, const RGBColor& color, float intensity);

	RGBColor Irradiance(const HitRecord& hitRec) override;
	void GetShadowRay(const HitRecord& hitRec, Ray& outputRay) override;;
	FVector3 GetDirection(const HitRecord& hitRec) override;

private:
	FVector3 m_Direction;
};

