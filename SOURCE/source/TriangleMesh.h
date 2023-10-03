#pragma once
#include "Triangle.h"
#include <string>
#include <vector>

class TriangleMesh : public Object
{
public:
	TriangleMesh(const std::string filepath);
	virtual ~TriangleMesh();
	TriangleMesh(const TriangleMesh& other) = delete;
	TriangleMesh(TriangleMesh&& other) = delete;
	TriangleMesh& operator=(const TriangleMesh& other) = delete;
	TriangleMesh& operator=(TriangleMesh&& other) = delete;

	void Update(float deltaTime) override {}
	bool Hit(const Ray& ray, HitRecord& hitRec, bool shadowHit = false) const override;
private:
	std::vector<Triangle> m_Triangles;
};

