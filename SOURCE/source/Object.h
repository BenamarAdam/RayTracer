#pragma once
#include "EMath.h"
#include "ERGBColor.h"
#include "Structs.h"

struct Ray;
struct HitRecord;

using namespace Elite;
class Object
{
public:

	virtual ~Object() = default;

	virtual void Update(float deltaTime) = 0;
	virtual bool Hit(const Ray& ray, HitRecord& hitRec, bool shadowHit = false) const = 0;

	virtual RGBColor GetColor() { return m_Color; }
protected:
	Object(const FPoint3 origin, const RGBColor color);

	FPoint3 m_Origin;
	RGBColor m_Color;
};
