#pragma once
#include "Light.h"

Light::Light(const RGBColor& color, float intensity)
	: m_Color(color)
	, m_Intensity(intensity)
	, m_IsActive(true)
{
}
