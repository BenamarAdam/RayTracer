#include "MainScene.h"
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

MainScene::MainScene(float windowwidth, float windowheight)
	:Scene(windowwidth,windowheight)
{
	Initialize();
}


void MainScene::Initialize()
{
	
	m_pCamera->Initialize(Elite::FPoint3(0.f, 3.f, 9.f), float(m_Width), float(m_Height), 45.f);

	//--Lights--//
	m_LightManager->AddLight(new PointLight({ 0,5.f,-5.f }, { 1,.61f,.45f }, 50));
	m_LightManager->AddLight(new PointLight({ -2.5f,5.f,5.f }, { 1,.8f,.45f }, 70));
	m_LightManager->AddLight(new PointLight({ 2.5f,2.5f,5.f }, { .34f,.47f,.68f }, 50));

	//--Objects--//
	//Spheres
	AddObject(new Sphere(FPoint3(-1.75f, 1.f, 0.f), { 1,0,0 }, .75f));
	AddObject(new Sphere(FPoint3(0.f, 1.f, 0.f), { 1,0,0 }, .75f));
	AddObject(new Sphere(FPoint3(1.75f, 1.f, 0.f), { 1,0,0 }, .75f));
	AddObject(new Sphere(FPoint3(-1.75f, 3.f, 0.f), { 1,0,0 }, .75f));
	AddObject(new Sphere(FPoint3(0.f, 3.f, 0.f), { 1,0,0 }, .75f));
	AddObject(new Sphere(FPoint3(1.75f, 3.f, 0.f), { 1,0,0 }, .75f));

	//Planes
	AddObject(new Plane({ 0,0,0 }, { 0,1,0 }));
	AddObject(new Plane({ 0,0,-10.f }, { 0,0,1 }));
	AddObject(new Plane({ 0,10.f,0 }, { 0,-1.f,0 }));
	AddObject(new Plane({ 5.f,0,0 }, { -1.f,0,0 }));
	AddObject(new Plane({ -5.f,0,0 }, { 1.f,0,0 }));

	//Triangles
	AddObject(new Triangle(FPoint3(-1.75f, 4.5f, 0.f), 0.6f, {}));
	AddObject(new Triangle(FPoint3(0.f, 4.5f, 0.f), 0.6f, {},Cullmode::Frontface));
	AddObject(new Triangle(FPoint3(1.75f, 4.5f, 0.f), 0.6f, {},Cullmode::NoCulling));

	//Materials
	//Spheres
	m_MatManager->AddMaterial(new Material_PBR(RGBColor{0.972f,0.96f,0.915f}, true, 1.f));
	m_MatManager->AddMaterial(new Material_PBR(RGBColor{ 0.972f,0.96f,0.915f }, true, .6f));
	m_MatManager->AddMaterial(new Material_PBR(RGBColor{ 0.972f,0.96f,0.915f }, true, .1f));
	m_MatManager->AddMaterial(new Material_PBR(RGBColor{ 0.75f,0.75f,.75f }, false, 1.f));
	m_MatManager->AddMaterial(new Material_PBR(RGBColor{ 0.75f,0.75f,.75f }, false, .4f));
	m_MatManager->AddMaterial(new Material_PBR(RGBColor{ 0.75f,0.75f,.75f }, false, .1f));

	//Planes
	m_MatManager->AddMaterial(new Material_Lambert({ .49f,.57f,.57f }, 1.f));
	m_MatManager->AddMaterial(new Material_Lambert({ .49f,.57f,.57f }, 1.f));
	m_MatManager->AddMaterial(new Material_Lambert({ .49f,.57f,.57f }, 1.f));
	m_MatManager->AddMaterial(new Material_Lambert({ .49f,.57f,.57f }, 1.f));
	m_MatManager->AddMaterial(new Material_Lambert({ .49f,.57f,.57f }, 1.f));

	//Triangles
	m_MatManager->AddMaterial(new Material_Lambert({ 1.f,1.f,1.f }, 1.f));
	m_MatManager->AddMaterial(new Material_Lambert({ 1.f,1.f,1.f }, 1.f));
	m_MatManager->AddMaterial(new Material_Lambert({ 1.f,1.f,1.f }, 1.f));


}

