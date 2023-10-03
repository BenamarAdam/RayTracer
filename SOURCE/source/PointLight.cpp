#pragma once
#include "PointLight.h"

PointLight::PointLight(const FPoint3& pos, const RGBColor& color, float intensity)
    : Light(color, intensity)
    , m_Position(pos)
{
}

RGBColor PointLight::Irradiance(const HitRecord& hitRec)
{
    FVector3 dir{ m_Position - hitRec.hitPos };
    float lambert = Dot(hitRec.normal, GetNormalized(dir));
    if (lambert < 0)
    {
        return RGBColor{};
    }
    return (m_Color * m_Intensity / SqrMagnitude(dir) * lambert);
}

void PointLight::GetShadowRay(const HitRecord& hitRec, Ray& outputRay)
{
    FVector3 shadowDir = m_Position - hitRec.hitPos;
    float tMax = Normalize(shadowDir);

    outputRay.origin = hitRec.hitPos + (0.001f * hitRec.normal);
    outputRay.direction = shadowDir;
    outputRay.tMax = tMax;
}

FVector3 PointLight::GetDirection(const HitRecord& hitRec)
{
    return GetNormalized(FVector3(m_Position - hitRec.hitPos));
}
