#include "Sphere.h"

Sphere::Sphere(const FPoint3& origin, const RGBColor& color, float radius)
	: Object(origin, color)
	, m_Radius(radius)
{
}

bool Sphere::Hit(const Ray& ray, HitRecord& hitRec, bool shadowHit) const
{
	FVector3 rayS{ ray.origin - m_Origin };

	float a = Dot(ray.direction, ray.direction);
	float b = Dot(2 * ray.direction, rayS);
	float c = (Dot(rayS, rayS)) - (m_Radius * m_Radius);

	float disc = (b * b) - (4 * a * c);
	if (disc > 0)
	{
		float sqDisc = sqrt(disc);
		float t = (-b - sqDisc) / (2 * a);

		if (t < ray.tMin)
		{
			t = (-b + sqDisc) / (2 * a);
		}

		if (t > ray.tMin && t < ray.tMax)
		{
			if (!shadowHit)
			{
				if (!shadowHit)
				{
					hitRec.hitPos = ray.origin + t * ray.direction;
					hitRec.normal = (hitRec.hitPos - m_Origin) / m_Radius;
					hitRec.color = m_Color;
					hitRec.tValue = t;
				}
			}
			return true;
		}
	}
	return false;
}
