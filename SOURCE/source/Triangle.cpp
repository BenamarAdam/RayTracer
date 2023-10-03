#pragma once
#include "Triangle.h"

#include <iostream>


Triangle::Triangle(const FPoint3& center, float size, const RGBColor& color, Cullmode cullmode)
    : Object(center, color)
    , m_Vertices(3)
    , m_Normal()
    , m_NormalLength()
	, m_Cullmode(cullmode)
{
    m_Vertices[0] = FPoint3{ center.x - size, center.y + size, center.z };
    m_Vertices[1] = FPoint3{ center.x - size, center.y - size, center.z };
    m_Vertices[2] = FPoint3{ center.x + size, center.y - size, center.z };    
    m_Normal = Cross(FVector3(m_Vertices[2] - m_Vertices[0]), FVector3(m_Vertices[1] - m_Vertices[0]));
    m_NormalLength = Normalize(m_Normal);
    m_Origin = center;
}

Triangle::Triangle(const FPoint3& v0, const FPoint3& v1, const FPoint3& v2, const RGBColor& color, Cullmode cullmode)
    : Object(FPoint3(), color)
    , m_Vertices(3)
    , m_Normal()
    , m_NormalLength()
	, m_Cullmode(cullmode)
{
    m_Vertices[0] = v0;
    m_Vertices[1] = v1;
    m_Vertices[2] = v2;
    m_Normal = Cross(FVector3(m_Vertices[2] - m_Vertices[0]), FVector3(m_Vertices[1] - m_Vertices[0]));
    m_NormalLength = Normalize(m_Normal);
    m_Origin.x = (v0.x + v1.x + v2.x) / 3.f;
    m_Origin.y = (v0.y + v1.y + v2.y) / 3.f;
    m_Origin.z = (v0.z + v1.z + v2.z) / 3.f;
}

void Triangle::Update(float deltaTime)
{
    FMatrix4 toOrigin = MakeTranslation(-FVector3(m_Origin));
    FMatrix3 rot = MakeRotationY(deltaTime);
    FMatrix4 toLoc = MakeTranslation(FVector3(m_Origin));

    for (int i = 0; i < 3; ++i)
    {
        m_Vertices[i] = FPoint3(toOrigin * FPoint4(m_Vertices[i], 1.f));
        m_Vertices[i] = FPoint3(rot * FVector3(m_Vertices[i]));
        m_Vertices[i] = FPoint3(toLoc * FPoint4(m_Vertices[i], 1.f));
    }
    m_Normal = Cross(FVector3(m_Vertices[2] - m_Vertices[0]), FVector3(m_Vertices[1] - m_Vertices[0]));
    m_NormalLength = Normalize(m_Normal);
}

bool Triangle::Hit(const Ray& ray, HitRecord& hitRec, bool shadowHit) const
{
    float dot = Dot(m_Normal, ray.direction);

    if (!shadowHit)
    {
        if (m_Cullmode == Cullmode::Frontface && dot < 0)
        {
            return false;
        }
        if (m_Cullmode == Cullmode::Backface && dot > 0)
        {
            return false;
        }
    }
    else
    {
        if (m_Cullmode == Cullmode::Frontface && dot > 0)
        {
            return false;
        }
        if (m_Cullmode == Cullmode::Backface && dot < 0)
        {
            return false;
        }
    }

    if (dot >= 0 - FLT_EPSILON && dot <= 0 + FLT_EPSILON)
    {
        return false;
    }
    float t = Dot(FVector3{ m_Origin - ray.origin }, m_Normal) / Dot(ray.direction, m_Normal);

    if (t < ray.tMin || t > ray.tMax)
    {
        return false;
    }

    FPoint3 intersect = ray.origin + t * ray.direction;
    FVector3 edge1 = m_Vertices[1] - m_Vertices[0];
    FVector3 dist{ intersect- m_Vertices[0] };
       
    if (bool insideTriangle = (Dot(Cross(dist, edge1), m_Normal) > 0))
    {
        FVector3 edge2 = m_Vertices[2] - m_Vertices[1];
        dist = intersect - m_Vertices[1];

        insideTriangle = (Dot(Cross(dist, edge2), m_Normal) > 0);
        if (insideTriangle)
        {
            FVector3 edge3 = m_Vertices[0] - m_Vertices[2];
            dist = intersect - m_Vertices[2];

            insideTriangle = (Dot(Cross(dist, edge3), m_Normal) > 0);
            if (insideTriangle)
            {
                if (!shadowHit)
                {
                    hitRec.hitPos = intersect;
                    hitRec.tValue = t;
                    hitRec.color = m_Color;
                    hitRec.normal = m_Normal;
                }
                return true;
            }
        }
    }
    return false;
}
