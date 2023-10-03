#pragma once
#include <memory>
#include <vector>

#include "Scene.h"


class BunnyScene : public Scene
{
public:

	BunnyScene(float width, float height);
	virtual ~BunnyScene() = default;
private:
	void Initialize() override;
};
