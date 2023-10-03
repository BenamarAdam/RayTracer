#pragma once
#include "EMath.h"
#include <string>
#include <vector>

using namespace Elite;
class Parser
{
public:
	static void LoadToBuffers(std::string filePath, std::vector<int>& indexBuffer, std::vector<FPoint3>& vertexBuffer);
};

