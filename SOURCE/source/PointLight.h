#pragma once
#include "Light.h"

class PointLight final : public Light
{
public:
	PointLight(const FPoint3& pos, const RGBColor& color, float intensity);

	RGBColor Irradiance(const HitRecord& hitRec) override;
	void GetShadowRay(const HitRecord& hitRec, Ray& outputRay) override;
	FVector3 GetDirection(const HitRecord& hitRec) override;

private:
	FPoint3 m_Position;
};

