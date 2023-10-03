#pragma once
#include "EMath.h"
#include "ERGBColor.h"

using namespace Elite;
struct HitRecord;
class BRDF
{
public:
	
	static RGBColor Lambert(const RGBColor& diffColor, float diffReflectance);
	static RGBColor Lambert(const RGBColor& diffColor, const RGBColor& kd);
	static RGBColor Phong(float specRefl, float phongExp, const FVector3& light, const FVector3& view, const FVector3& hitNorm);
	static RGBColor CalcCookTorrance(const RGBColor& color, bool metal, float roughness, const FVector3& light, const FVector3& view, const FVector3& hitNorm);

private:
	static RGBColor Fresnel(float dotnormlv, const RGBColor& f0);
	static float NormalDistr(float dotnormlv, float roughsq);
	static float MaskGeometry(float dotnormview, float k);
	static float ShadowGeometry(float dotnormlight, float k);
	static RGBColor CalculateSpecular(float D, const RGBColor& F, float G, float dotnormlight, float dotnormview);
};

