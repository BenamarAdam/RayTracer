#pragma once
#include "Object.h"

using namespace Elite;
class Sphere: public Object
{
public:
	Sphere(const FPoint3& origin, const RGBColor& color, float radius);
	virtual ~Sphere() = default;
	Sphere(const Sphere& other) = delete;
	Sphere(Sphere&& other) noexcept = delete;
	Sphere& operator=(const Sphere& other) = delete;
	Sphere& operator=(Sphere&& other) noexcept = delete;

	void Update(float deltaTime) override {}
	bool Hit(const Ray& ray, HitRecord& hitRec, bool shadowHit = false) const override;

private:
	float m_Radius;
};

