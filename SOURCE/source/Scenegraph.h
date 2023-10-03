#pragma once
#include <vector>
class Scene;

class Scenegraph
{
public:
	Scenegraph() = default;
	~Scenegraph();
	Scenegraph(const Scenegraph& other) = delete;
	Scenegraph(Scenegraph&& other) noexcept = delete;
	Scenegraph& operator=(const Scenegraph& other) = delete;
	Scenegraph& operator=(Scenegraph&& other) noexcept = delete;

	void Update(float deltaTime);
	void AddScene(Scene* scene);
	void NextScene();
	Scene* GetCurrentScene() {
		return m_Scenes[m_CurrentScene];
	}
private:
	int m_CurrentScene=0;
	std::vector<Scene*> m_Scenes;
};

