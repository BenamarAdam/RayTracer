#include "Plane.h"

Plane::Plane(const FPoint3& origin, const FVector3& dir, const RGBColor& color)
	: Object(origin, color)
	, m_Direction(GetNormalized(dir))
{
}

bool Plane::Hit(const Ray& ray, HitRecord& hitRec, bool shadowHit) const
{
	float dot = Dot(ray.direction, m_Direction);
	
	float t = Dot((m_Origin - ray.origin), m_Direction) / dot;
	if (t > ray.tMin && t < ray.tMax)
	{
		if (!shadowHit)
		{
			hitRec.hitPos = ray.origin + t * ray.direction;
			hitRec.color = m_Color;
			hitRec.normal = m_Direction;
			hitRec.tValue = t;
		}
		return true;
	}
	else
	{
		return false;
	}
}
