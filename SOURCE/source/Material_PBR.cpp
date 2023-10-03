#pragma once
#include "Material_PBR.h"
#include "BRDF.h"
#include "Structs.h"

Material_PBR::Material_PBR(const RGBColor& color, bool metal, float roughness)
	: m_Color(color)
	, m_Metal(metal)
	, m_Roughness(roughness)
{
}

RGBColor Material_PBR::Shade(const HitRecord& hitRec, const FVector3& light, const FVector3& view) const
{
	return BRDF::CalcCookTorrance(m_Color, m_Metal, m_Roughness, light, view, hitRec.normal);
}

const RGBColor& Material_PBR::GetDiffuseColor() const
{
	return m_Color;
}
