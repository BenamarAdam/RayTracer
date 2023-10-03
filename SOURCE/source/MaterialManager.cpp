#pragma once
#include "MaterialManager.h"
#include "Material.h"

MaterialManager::~MaterialManager()
{
	for (int i = 0; i < m_Materials.size(); ++i)
	{
		delete m_Materials[i];
		m_Materials[i] = nullptr;
	}
	m_Materials.clear();
}

void MaterialManager::AddMaterial(Material* mat)
{
	if (mat)
	{
		m_Materials.push_back(mat);
	}
}
