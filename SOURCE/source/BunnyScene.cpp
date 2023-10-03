#include "BunnyScene.h"
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

BunnyScene::BunnyScene(float windowwidth, float windowheight)
	: Scene(windowwidth,windowheight)
{
	Initialize();
}



void BunnyScene::Initialize()
{

	m_pCamera->Initialize(Elite::FPoint3(0.f, 3.f, 9.f), float(m_Width), float(m_Height), 45.f);

	//--Lights--//
	m_LightManager->AddLight(new PointLight({ 0,5.f,-5.f }, { 1,.61f,.45f }, 30));
	m_LightManager->AddLight(new PointLight({ -2.5f,5.f,5.f }, { 1,1.f,1.f }, 70));
	m_LightManager->AddLight(new PointLight({ 2.5f,2.5f,5.f }, { .34f,.47f,.68f }, 30));

	//--Objects--//
	//Spheres
	AddObject(new TriangleMesh("./Resources/lowpoly_bunny.obj"));

	//Planes
	AddObject(new Plane({ 0,0,0 }, { 0,1,0 }));
	AddObject(new Plane({ 0,0,-10.f }, { 0,0,1 }));
	AddObject(new Plane({ 0,10.f,0 }, { 0,-1.f,0 }));
	AddObject(new Plane({ 5.f,0,0 }, { -1.f,0,0 }));
	AddObject(new Plane({ -5.f,0,0 }, { 1.f,0,0 }));

	//Materials
	m_MatManager->AddMaterial(new Material_Lambert({ .49f,.57f,.57f }, 1.f));

	//Planes
	m_MatManager->AddMaterial(new Material_Lambert({ .49f,.57f,.57f }, 1.f));
	m_MatManager->AddMaterial(new Material_Lambert({ .49f,.57f,.57f }, 1.f));
	m_MatManager->AddMaterial(new Material_Lambert({ .49f,.57f,.57f }, 1.f));
	m_MatManager->AddMaterial(new Material_Lambert({ .49f,.57f,.57f }, 1.f));
	m_MatManager->AddMaterial(new Material_Lambert({ .49f,.57f,.57f }, 1.f));

}

