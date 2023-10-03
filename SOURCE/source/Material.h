#pragma once
#include "EMath.h"
#include "ERGBColor.h"

using namespace Elite;
struct HitRecord;
class Material
{
public:
	Material() = default;
	virtual ~Material() = default;
	Material(const Material& other) = delete;
	Material(Material&& other) = delete;
	Material& operator=(const Material& other) = delete;
	Material& operator=(Material&& other) = delete;

	virtual Elite::RGBColor Shade(const HitRecord& hitRec, const Elite::FVector3& light, const Elite::FVector3& view) const = 0;
	
	virtual const Elite::RGBColor& GetDiffuseColor() const = 0;
};

