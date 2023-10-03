#pragma once
#include "TriangleMesh.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include "Parser.h"

TriangleMesh::TriangleMesh(const std::string filepath)
	: Object(FPoint3(), {})
{
	std::vector<int> indexBuffer;
	std::vector<FPoint3> vertexBuffer;
	Parser::LoadToBuffers(filepath, indexBuffer, vertexBuffer);
	for (int i = 0; i < indexBuffer.size(); i += 3)
	{
		m_Triangles.push_back(Triangle{vertexBuffer[indexBuffer[i]],vertexBuffer[indexBuffer[(i + 1)]],vertexBuffer[indexBuffer[(i + 2)]],{},Cullmode::Backface});
	}
}

TriangleMesh::~TriangleMesh()
{
	m_Triangles.clear();
}

bool TriangleMesh::Hit(const Ray& ray, HitRecord& hitRec, bool shadowHit) const
{
	for (const auto& triangle : m_Triangles)
	{
		if (triangle.Hit(ray, hitRec, shadowHit))
		{
			return true;
		}
	}
	return false;
}

