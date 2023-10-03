#pragma once
#include "LightManager.h"
#include "Light.h"

LightManager::~LightManager()
{
	for (int i = 0; i < m_pLights.size(); i++)
	{
		delete m_pLights[i];
		m_pLights[i] = nullptr;
	}

	m_pLights.clear();
}

void LightManager::AddLight(Light* pLight)
{
	if (pLight)
	{
		m_pLights.push_back(pLight);
	}
}
