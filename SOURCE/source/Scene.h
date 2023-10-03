#pragma once
#include <memory>
#include <vector>


class MaterialManager;
class LightManager;
class Camera;
class Object;

enum class RenderMode
{
	Both,
	Irradiance,
	BRDF
};
class Scene
{
public:

	Scene(float width, float height);
	virtual ~Scene();   
	Scene(const Scene& other) = delete;
	Scene(Scene&& other) noexcept = delete;
	Scene& operator=(const Scene& other) = delete;
	Scene& operator=(Scene&& other) noexcept = delete;
	void AddObject(Object* obj);

	std::vector<Object*>& GetObjects() { return m_Objects; }
	Camera* GetCamera() { return m_pCamera; }

	LightManager* GetLightManager() { return m_LightManager; }
	MaterialManager* GetMaterialManager() { return m_MatManager; }
	void Update(float deltaTime);

	void NextRenderMode();
	RenderMode GetRenderMode() { return m_Rendermode; }

	bool ShadowsActive() { return m_Shadows; }
protected:
	virtual void Initialize() = 0;
	std::vector<Object*> m_Objects;
	Camera* m_pCamera;
	LightManager* m_LightManager;
	MaterialManager* m_MatManager;
	float m_Width;
	float m_Height;
	bool m_Shadows = true;
	RenderMode m_Rendermode = RenderMode::Both;
};
