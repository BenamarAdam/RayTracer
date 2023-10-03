#include "Camera.h"

#include <iostream>
#include <SDL_keyboard.h>
#include <SDL_mouse.h>
#include <SDL_stdinc.h>


Camera::Camera()
	: m_Position(0.f, 0.f,0.f)
	, m_Width()
	, m_Height()
	, m_Ratio()
	, m_FOV()
	, m_TranslationSpeed(.5f)
	, m_RotationSpeed(0.1f)
	, m_Up(0.f, 1.f, 0.f)
	, m_Right(1.f, 0.f, 0.f)
	, m_Forward(0.f, 0.f, 1.f)
	, m_WorldUp(0.f, 1.f, 0.f)
	, m_LookAt(FMatrix4::Identity())
{
}

void Camera::Initialize(const FPoint3& pos, float width, float height, float fov)
{
	m_Position = pos;
	m_Width = (int)width;
	m_Height = (int)height;
	m_FOV = (float)tan(fov * E_TO_RADIANS / 2.f);
	m_Ratio = width / height;
	UpdateMatrix();
}

void Camera::CalcRay(int xr, int yr, Ray& out)
{
	float yss = (1 - 2 * (yr + 0.5f) / m_Height) * m_FOV;
	float xss = (2 * (xr + 0.5f) / m_Width - 1) * m_Ratio * m_FOV;

	FPoint3 lookAt{ xss, yss, -1 };
	FPoint4 pos = m_LookAt * FPoint4(lookAt, 1.f);
	FVector4 dir = pos - FPoint4(m_Position, 1.f);
	FVector3 newDir = FVector3(GetNormalized(dir));
	out.origin = m_Position;
	out.direction = newDir;
	//return Ray{ m_Position, newDir };
}

void Camera::Update(float deltaTime)
{
	HandleKeys(deltaTime);
}

void Camera::HandleKeys(float deltaTime)
{
	int x{};
	int y{};
	Uint32 mouseState = SDL_GetRelativeMouseState(&x, &y);
	if (x + y != 0)
	{
		if (mouseState == SDL_BUTTON(1))
		{
			FMatrix3 rot = MakeRotation(-x * deltaTime * m_RotationSpeed, m_Up);
			m_Forward = rot * m_Forward;
			m_Position.z += y * m_TranslationSpeed * deltaTime * m_Forward.z;
			m_Position.x += y * m_TranslationSpeed * deltaTime * m_Forward.x;
			UpdateMatrix();
		}
		else if (mouseState == SDL_BUTTON(3))
		{
			FMatrix3 xrot = MakeRotation(-y * m_RotationSpeed * deltaTime, m_Right);
			FMatrix3 yrot = MakeRotation(-x * m_RotationSpeed * deltaTime, m_Up);
			m_Forward = xrot * yrot * m_Forward;
			UpdateMatrix();
		}
		else if (mouseState == SDL_BUTTON(1) + SDL_BUTTON(3))
		{
			m_Position.y -= y * m_TranslationSpeed * deltaTime;
			UpdateMatrix();
		}
	}

	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_UP])
	{
		m_Position.z -= m_TranslationSpeed * deltaTime * m_Forward.z;
		m_Position.x -= m_TranslationSpeed * deltaTime * m_Forward.x;
		UpdateMatrix();
	}
	if (state[SDL_SCANCODE_DOWN])
	{
		m_Position.z += m_TranslationSpeed * deltaTime * m_Forward.z;
		m_Position.x += m_TranslationSpeed * deltaTime * m_Forward.x;
		UpdateMatrix();
	}
	if (state[SDL_SCANCODE_LEFT])
	{
		m_Position.z -= m_TranslationSpeed * deltaTime * m_Right.z;
		m_Position.x -= m_TranslationSpeed * deltaTime * m_Right.x;
		UpdateMatrix();
	}
	if (state[SDL_SCANCODE_RIGHT])
	{
		m_Position.z += m_TranslationSpeed * deltaTime * m_Right.z;
		m_Position.x += m_TranslationSpeed * deltaTime * m_Right.x;
		UpdateMatrix();
	}
	
	//std::cout << m_Position.x << '\t' << m_Position.y << '\t' << m_Position.z << std::endl;
	//std::cout << y * m_TranslationSpeed * deltaTime << std::endl;

}

void Camera::UpdateMatrix()
{
	m_Right = Elite::GetNormalized(Cross(m_WorldUp, m_Forward));
	m_Up = Elite::GetNormalized(Cross(m_Forward, m_Right));

	m_LookAt = Elite::FMatrix4(m_Right, m_Up, m_Forward, FVector4(FVector3(m_Position), 1.f));
}
