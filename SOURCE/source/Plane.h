#pragma once
#include "Object.h"

using namespace Elite;
class Plane: public Object
{
public:
	Plane(const FPoint3& origin, const FVector3& dir, const RGBColor& color = RGBColor{ 1.f, 1.f, 1.f });
	virtual ~Plane() = default;
	Plane(const Plane& other) = delete;
	Plane(Plane&& other) noexcept = delete;
	Plane& operator=(const Plane& other) = delete;
	Plane& operator=(Plane&& other) noexcept = delete;

	void Update(float deltaTime) override{}
	bool Hit(const Ray& ray, HitRecord& hitRec, bool shadowHit = false) const override;

private:
	FVector3 m_Direction;
};

