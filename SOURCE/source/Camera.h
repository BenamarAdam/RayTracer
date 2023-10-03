#pragma once
#include "EMath.h"
#include "Structs.h"

using namespace Elite;
class Camera
{
public:
	Camera();
	~Camera() = default;

	void Initialize(const FPoint3& pos, float width, float height, float fov);

	void CalcRay(int xr, int yr,Ray& out);

	void Update(float deltaTime);
	void HandleKeys(float deltaTime);

private:

	void UpdateMatrix();
	
	float m_FOV;
	float m_TranslationSpeed;
	float m_RotationSpeed;
	float m_Ratio;
	int m_Height;
	int m_Width;

	FVector3 m_Right;
	FVector3 m_Up;
	FVector3 m_WorldUp;
	FVector3 m_Forward;
	FPoint3 m_Position;
	FMatrix4 m_LookAt;


};

