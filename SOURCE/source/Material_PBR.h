#pragma once
#include "Material.h"

class Material_PBR : public Material
{
public:
	Material_PBR(const RGBColor& color, bool metal, float roughness);
	RGBColor Shade(const HitRecord& hitRec, const FVector3& light, const FVector3& view) const override;
	const RGBColor& GetDiffuseColor() const override;

private:
	RGBColor m_Color;
	bool m_Metal;
	float m_Roughness;

};

