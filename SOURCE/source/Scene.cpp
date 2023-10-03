#include "Scene.h"

#include <iostream>
#include <SDL_keyboard.h>
#include <SDL_scancode.h>

#include "Camera.h"
#include "DirectionalLight.h"
#include "LightManager.h"
#include "MaterialManager.h"
#include "Material_Lambert.h"
#include "Material_PBR.h"
#include "Plane.h"
#include "PointLight.h"
#include "Sphere.h"
#include "Triangle.h"
#include "TriangleMesh.h"

Scene::Scene(float windowwidth, float windowheight)
	: m_pCamera(new Camera())
	, m_Width{windowwidth}
	, m_Height{windowheight}
	, m_LightManager{new LightManager()}
	, m_MatManager{new MaterialManager()}
{
	Initialize();
}

Scene::~Scene()
{
	delete m_pCamera;
	delete m_LightManager;
	delete m_MatManager;
	for(int i{} ; i < m_Objects.size(); ++i)
	{
		delete m_Objects[i];
	}
}

void Scene::AddObject(Object* obj)
{
	m_Objects.push_back(obj);
}

void Scene::Update(float deltaTime)
{
	m_pCamera->Update(deltaTime);
	for(auto pObj:m_Objects)
	{
		pObj->Update(deltaTime);
	}
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_Q])
	{
		m_Shadows = !m_Shadows;
	}
	if (state[SDL_SCANCODE_E])
	{
		NextRenderMode();
	}
}

void Scene::Initialize()
{
}

void Scene::NextRenderMode()
{
	switch(m_Rendermode)
	{
	case RenderMode::Both:
		m_Rendermode = RenderMode::Irradiance;
		break;
	case RenderMode::Irradiance:
		m_Rendermode = RenderMode::BRDF;
		break;
	case RenderMode::BRDF:
		m_Rendermode = RenderMode::Both;
		break;
	}
}
