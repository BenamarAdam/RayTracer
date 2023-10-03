#pragma once
#include "Material.h"

class Material_Phong : public Material
{
public:
	Material_Phong(const RGBColor& color, float diffRefl, float specRefl, float phongExp);
	virtual ~Material_Phong() = default;

	RGBColor Shade(const HitRecord& hitRec, const FVector3& light, const FVector3& view) const override;
	const RGBColor& GetDiffuseColor() const override;

private:
	RGBColor m_DiffColor;
	float m_DiffReflectance;
	float m_SpecReflectance;
	float m_PhongExp;
};

