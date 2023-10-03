#include "BRDF.h"
RGBColor BRDF::Lambert(const RGBColor& diffColor, float diffReflectance)
{
	return diffColor * diffReflectance / (float)E_PI;
}

RGBColor BRDF::Lambert(const RGBColor& color, const RGBColor& kd)
{
	return color * kd / (float)E_PI;
}

::RGBColor BRDF::Phong(float specRefl, float phongExp, const FVector3& light, const FVector3& view, const FVector3& hitNorm)
{
	FVector3 reflect = light - 2 * Dot(hitNorm, light) * hitNorm;
	float r = Dot(reflect, view);
	float specRef = specRefl * (powf(r, phongExp));
	
	return RGBColor { specRef, specRef, specRef };
}

RGBColor BRDF::CalcCookTorrance(const RGBColor& color, bool metal, float roughness, const FVector3& light, const FVector3& view, const FVector3& hitNorm)
{
	float roughsq = (roughness * roughness);
	RGBColor f0{};

	if(!metal)
	{
		f0 = RGBColor(0.04f, 0.04f, 0.04f);
	}
	else
	{
		f0 = color;
	}

	FVector3 lightview = GetNormalized(view + light);
	float dotnormlight = Clamp(Dot(hitNorm, light), 0.f, 1.f);
	float dotnormview = Clamp(Dot(hitNorm, view), 0.f, 1.f);
	float dotviewlv = Clamp(Dot(view, lightview), 0.f, 1.f);
	float dotnormlv = Clamp(Dot(hitNorm, lightview), 0.f, 1.f);
	
	RGBColor fresnel = f0 + (RGBColor(1, 1, 1) - f0) * powf(1 - dotviewlv, 5);

	float r = roughsq * roughsq;
	float denom = powf((powf(dotnormlv, 2)) * (r - 1) + 1, 2);
	float normDistr = r / ((float)E_PI * denom);
	float kdir = powf(roughsq + 1, 2) / 8.f;
	float geometry = (dotnormview / (dotnormview * (1.f - kdir) + kdir)) * (dotnormlight / (dotnormlight * (1.f - kdir) + kdir));
	
	RGBColor specular{ fresnel * normDistr * geometry };
	specular = RGBColor{ specular / 4.f * dotnormview * dotnormlight };
	RGBColor kd{};
	if (!metal)
	{
		kd = RGBColor(1, 1, 1) - fresnel;
	}
	RGBColor diffuse = BRDF::Lambert(color, kd);
	
	return (diffuse + specular);
}
