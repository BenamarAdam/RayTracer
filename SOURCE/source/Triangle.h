#pragma once
#include "Object.h"
#include <vector>

enum class Cullmode
{
	Frontface = 0,
	Backface = 1,
	NoCulling = 2
};

class Triangle : public Object
{
public:
	Triangle(const FPoint3& center, float size, const RGBColor& color, Cullmode cullmode = Cullmode::Backface);
	Triangle(const FPoint3& v0, const FPoint3& v1, const FPoint3& v2, const RGBColor& color, Cullmode cullmode = Cullmode::Backface);
	Triangle(const Triangle& other) = default;
	virtual ~Triangle() = default;
	Triangle(Triangle&& other) noexcept = default;
	Triangle& operator=(const Triangle& other) = default;
	Triangle& operator=(Triangle&& other) = default;

	void Update(float deltaTime) override;
	bool Hit(const Ray& ray, HitRecord& hitRec, bool shadowHit = false) const override;

private:
	std::vector<FPoint3> m_Vertices;
	FVector3 m_Normal;
	float m_NormalLength;
	Cullmode m_Cullmode;
};

