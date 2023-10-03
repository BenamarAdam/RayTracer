#pragma once
#include "Material_Phong.h"
#include "BRDF.h"
#include "Structs.h"

Material_Phong::Material_Phong(const RGBColor& diffColor, float diffRefl, float specRefl, float phongExp)
	: m_DiffColor(diffColor)
	, m_DiffReflectance(diffRefl)
	, m_SpecReflectance(specRefl)
	, m_PhongExp(phongExp)
{
}

::RGBColor Material_Phong::Shade(const HitRecord& hitRec, const FVector3& light, const FVector3& view) const
{
	return BRDF::Lambert(m_DiffColor, m_DiffReflectance) + BRDF::Phong(m_SpecReflectance, m_PhongExp, light, view, hitRec.normal);
}

const ::RGBColor& Material_Phong::GetDiffuseColor() const
{
	return m_DiffColor;
}
