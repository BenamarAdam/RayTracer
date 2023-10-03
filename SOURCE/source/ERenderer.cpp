//External includes
#include "SDL.h"
#include "SDL_surface.h"

//Project includes
#include "ERenderer.h"

#include "Camera.h"
#include "ERGBColor.h"
#include "Light.h"
#include "LightManager.h"
#include "Material.h"
#include "MaterialManager.h"
#include "Object.h"
#include "Scene.h"
#include "Structs.h"

Elite::Renderer::Renderer(SDL_Window * pWindow)
{
	//Initialize
	m_pWindow = pWindow;
	m_pFrontBuffer = SDL_GetWindowSurface(pWindow);
	int width, height = 0;
	SDL_GetWindowSize(pWindow, &width, &height);
	m_Width = static_cast<uint32_t>(width);
	m_Height = static_cast<uint32_t>(height);
	m_pBackBuffer = SDL_CreateRGBSurface(0, m_Width, m_Height, 32, 0, 0, 0, 0);
	m_pBackBufferPixels = (uint32_t*)m_pBackBuffer->pixels;
}

void Elite::Renderer::Render(Scene* scene)
{
	SDL_LockSurface(m_pBackBuffer);

	const auto& pObjects = scene->GetObjects();
	auto pCamera = scene->GetCamera();

	Ray ray;

	//Loop over all the pixels
	for (uint32_t r = 0; r < m_Height; ++r)
	{
		for (uint32_t c = 0; c < m_Width; ++c)
		{
			HitRecord hitRec{};
			RGBColor color{};
			
			for(size_t i=0; i < pObjects.size(); ++i)
			{
				pCamera->CalcRay(c, r, ray);
				//ray.origin = FPoint3{ float(c),float(r) };
				//ray.direction = FVector3{ 0,0,1 };
				if (pObjects[i]->Hit(ray, hitRec))
				{
					if(hitRec.tValue < hitRec.tClosest)
					{
						hitRec.tClosest = hitRec.tValue;

						color = pObjects[i]->GetColor();

						color = Shading(scene, ray, hitRec, scene->GetMaterialManager()->GetMaterials()[i]);
					}
				}
			}
			if (color.r > 1.f || color.g > 1.f || color.b > 1.f)
			{
				color.MaxToOne();
			}

			m_pBackBufferPixels[c + (r * m_Width)] = SDL_MapRGB(m_pBackBuffer->format,
				static_cast<uint8_t>(color.r * 255),
				static_cast<uint8_t>(color.g * 255),
				static_cast<uint8_t>(color.b * 255));
		}
	}

	SDL_UnlockSurface(m_pBackBuffer);
	SDL_BlitSurface(m_pBackBuffer, 0, m_pFrontBuffer, 0);
	SDL_UpdateWindowSurface(m_pWindow);
}

bool Elite::Renderer::SaveBackbufferToImage() const
{
	return SDL_SaveBMP(m_pBackBuffer, "BackbufferRender.bmp");
}

RGBColor Renderer::Shading(Scene* scene, Ray& cameraRay, HitRecord& hitRec,Material* mat)
{
	Ray shadowRay;
	RGBColor color = RGBColor{};
	for(auto pLight: scene->GetLightManager()->GetLights())
	{
		if (pLight->GetIsActive())
		{
			if(scene->ShadowsActive())
			{
				pLight->GetShadowRay(hitRec, shadowRay);

				bool hit = false;

				for(auto object:scene->GetObjects())
				{
					if (object->Hit(shadowRay, hitRec,true))
					{
						hit = true;
						break;
					}

				}

				if (hit)//blocked
				{
					continue;
				}
			}
			switch(scene->GetRenderMode())
			{
			case RenderMode::Both:
				color += pLight->Irradiance(hitRec) * mat->Shade(hitRec, pLight->GetDirection(hitRec), -cameraRay.direction);
				break;
			case RenderMode::Irradiance:
				color += pLight->Irradiance(hitRec);
				break;
			case RenderMode::BRDF:
				color += mat->Shade(hitRec, pLight->GetDirection(hitRec), -cameraRay.direction);
				break;
			}
		}
	}
	return color;
}
