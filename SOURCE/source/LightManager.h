#pragma once
#include <vector>

class Light;
class LightManager
{
public:
	LightManager() = default;
	LightManager(const LightManager& other) = delete;
	LightManager(LightManager&& other) = delete;
	LightManager& operator=(const LightManager& other) = delete;
	LightManager& operator=(LightManager&& other) = delete;
	~LightManager();
	void AddLight(Light* pLight);
	const std::vector<Light*>& GetLights() const { return m_pLights; }
private:
	std::vector<Light*> m_pLights;
};

