#pragma once
#include "Material.h"
class Material_Lambert : public Material
{
public:
	Material_Lambert(const RGBColor& color, float refl);
	virtual ~Material_Lambert() = default;
	RGBColor Shade(const HitRecord& hitRec, const FVector3& light, const FVector3& view) const override;
	const RGBColor& GetDiffuseColor() const override;

private:
	RGBColor m_Color;
	float m_Reflectance;
};

