#pragma once
#include "EMath.h"
#include "ERGBColor.h"
#include "Structs.h"

class Light
{
public:
	Light(const RGBColor& color, float intensity);
	Light(const Light& other) = delete;
	Light(Light&& other) = delete;
	Light& operator=(const Light& other) = delete;
	Light& operator=(Light&& other) = delete;
	~Light() = default;
	
	virtual RGBColor Irradiance(const HitRecord& hitRec) = 0;
	virtual void GetShadowRay(const HitRecord& hitRec, Ray& outputRay) = 0;

	virtual FVector3 GetDirection(const HitRecord& hitRec) = 0;
	float GetIntensity() const { return m_Intensity; }
	const RGBColor& GetColor() const { return m_Color; }

	bool GetIsActive() const { return m_IsActive; }
	void SetActive(bool isActive) { m_IsActive = isActive; }

protected:
	RGBColor m_Color;
	float m_Intensity;
	bool m_IsActive;
};

