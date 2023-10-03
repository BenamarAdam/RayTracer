#pragma once
#include "Material_Lambert.h"
#include "BRDF.h"

Material_Lambert::Material_Lambert(const RGBColor& color, float refl)
	: m_Color(color)
	, m_Reflectance(refl)
{
}

RGBColor Material_Lambert::Shade(const HitRecord& hitRec, const FVector3& light, const FVector3& view) const
{
	return BRDF::Lambert(m_Color, m_Reflectance);
}

const RGBColor& Material_Lambert::GetDiffuseColor() const
{
	return m_Color;
}
