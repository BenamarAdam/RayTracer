#pragma once
#include "Parser.h"
#include <iostream>
#include <fstream>
#include <sstream>

void Parser::LoadToBuffers(std::string filePath, std::vector<int>& indexBuffer, std::vector<Elite::FPoint3>& vertexBuffer)
{
	std::ifstream file;
	file.open(filePath, std::ios::in);

	if (!file.is_open())
	{
		std::cout << "Parsing failed"<< "\n";
		return;
	}

	std::string line;
	while (!file.eof())
	{
		std::getline(file, line);
		std::stringstream ss{ line };

		if (line[0] == 'v')
		{
			FPoint3 vert;
			ss >> line >> vert.x >> vert.y >> vert.z;
			vertexBuffer.push_back(vert);
		}
		else if (line[0] == 'f')
		{
			int indices[3];
			ss >> line;
			for (unsigned int i = 0; i < 3; ++i)
			{
				ss >> indices[i];
				indexBuffer.push_back(indices[i] - 1);
			}
		}
	}
}