#pragma once
#include "Scene.h"


class MainScene : public Scene
{
public:

	MainScene(float width, float height);
	virtual ~MainScene() =default;
	
private:
	void Initialize() override;
};
