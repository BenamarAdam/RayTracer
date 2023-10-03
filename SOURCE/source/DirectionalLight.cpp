#pragma once
#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(const FVector3& direction, const RGBColor& color, float intensity)
	: Light(color, intensity)
	, m_Direction(direction)
{
}

RGBColor DirectionalLight::Irradiance(const HitRecord& hitRec)
{
	float lambert = Dot(hitRec.normal, Elite::GetNormalized(m_Direction));
	if (lambert < 0)
	{
		return RGBColor{};
	}
	return m_Color * m_Intensity * lambert;
}

void DirectionalLight::GetShadowRay(const HitRecord& hitRec, Ray& outputRay)
{
	FVector3 shadowDir = m_Direction;
	float tMax = Normalize(shadowDir);

	outputRay.origin = hitRec.hitPos + (0.001f * hitRec.normal);
	outputRay.direction = shadowDir;
	outputRay.tMax = tMax;
}

FVector3 DirectionalLight::GetDirection(const HitRecord& hitRec)
{
	return m_Direction;
}
