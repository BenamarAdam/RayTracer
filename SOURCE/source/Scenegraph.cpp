#include "Scenegraph.h"

#include <iostream>
#include <SDL_keyboard.h>
#include <SDL_scancode.h>

#include "Scene.h"

Scenegraph::~Scenegraph()
{
	for(int i{}; i < m_Scenes.size(); ++i)
	{
		delete m_Scenes[i];
		m_Scenes[i] = nullptr;
	}
	m_Scenes.clear();
}

void Scenegraph::AddScene(Scene* scene)
{
	if(scene)
	{
		m_Scenes.push_back(scene);
	}
}

void Scenegraph::Update(float deltaTime)
{
	
	m_Scenes[m_CurrentScene]->Update(deltaTime);

}

void Scenegraph::NextScene()
{
	std::cout << "Loading next scene... \n";
	++m_CurrentScene;
	if(m_CurrentScene>=m_Scenes.size())
	{
		m_CurrentScene = 0;
	}
}
