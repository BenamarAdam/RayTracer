#pragma once
#include <vector>

class Material;
class MaterialManager
{
public:
	MaterialManager() = default;
	MaterialManager(const MaterialManager& other) = delete;
	MaterialManager(MaterialManager&& other) = delete;
	MaterialManager& operator=(const MaterialManager& other) = delete;
	MaterialManager& operator=(MaterialManager&& other) = delete;
	~MaterialManager();
	
	void AddMaterial(Material* pMaterial);
	const std::vector<Material*>& GetMaterials() const { return m_Materials; }

private:
	std::vector<Material*> m_Materials;
};

