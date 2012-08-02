
#include "Core/Engine.h"
#include "Core/Camera.h"

#include "Core/DrawArgs.h"
#include "Core/UpdateArgs.h"

namespace TikiEngine
{
	namespace Components
	{
		#pragma region Class
		Camera::Camera(Engine* engine, GameObject* gameObject)
			: Component(engine, gameObject, CT_Camera)
		{
			//D3DXMATRIX matrix;
			//D3D11_VIEWPORT* vp = engine->graphics->GetViewPort();

			//D3DXMatrixPerspectiveFovLH(
			//	&matrix,
			//	D3DX_PI / 4,
			//	(vp->Width / vp->Height),
			//	0.01f,
			//	10000.0f
			//);

			//D3DXMatrixPerspectiveOffCenterLH(
			//	&matrix,
			//	0,
			//	vp->Width,
			//	vp->Height,
			//	0,
			//	0.01f,
			//	100.0f
			//);

			ViewPort* vp = &engine->GetEngineDescription()->Graphics.ViewPort;

			this->matrices.ProjectionMatrix = Matrix::Transpose(Matrix::CreatePerspectiveFieldOfView(
				MATH_PI / 4,				
				(vp->Width / vp->Width),
				0.01f,
				1000.0f
			));

			//this->matrixBuffer = new ConstantBuffer<Matrices>(engine);
		}

		Camera::~Camera()
		{
		}
		#pragma endregion

		#pragma region Member - Get
		bool Camera::GetReady()
		{
			return true;
		}

		Matrices* Camera::GetMatrices()
		{
			return &matrices;
		}

		Matrix* Camera::GetViewMatrix()
		{
			return &matrices.ViewMatrix;
		}

		Matrix* Camera::GetProjectionMatrix()
		{
			return &matrices.ProjectionMatrix;
		}

		IRenderTarget* Camera::GetRenderTarget()
		{
			return renderTarget;
		}
		#pragma endregion

		#pragma region Member - Set
		void Camera::SetProjectionMatrix(const Matrix& projection)
		{
			matrices.ProjectionMatrix = projection;
		}

		void Camera::SetRenderTarget(IRenderTarget* renderTarget)
		{
			this->renderTarget = renderTarget;
		}
		#pragma endregion

		#pragma region Member - Update
		void Camera::Draw(const DrawArgs& args)
		{
		}

		void Camera::Update(const UpdateArgs& args)
		{
			//D3DXMATRIX matrix;

			float g_fX = x;
			float g_fY = y;
			float g_fEyeDistance = 5;

			x += args.Input.MouseDistance.X;
			y += args.Input.MouseDistance.Y;

			Vector3 g_vAt = Vector3(0.01f, 0.01f, 0.01f);
			Vector3 g_vUp = Vector3(0.0f, 1.0f, 0.0f);
			//float g_fEyeDistance = 5.0f;

			Vector3 g_vEye = Vector3(
				sinf(g_fX) * g_fEyeDistance,
				cosf(g_fY) * g_fEyeDistance,
				(cosf(g_fX) * sinf(g_fY)) * g_fEyeDistance
			);

			//D3DXMatrixLookAtLH(
			//	&matrix,
			//	&g_vEye,
			//	&g_vAt,
			//	&g_vUp
			//);

			//D3DXMatrixLookAtLH(
			//	&matrix,
			//	this->PRS.Position.ToD3DXVector3(),
			//	&D3DXVECTOR3(0, 0, 0),
			//	&D3DXVECTOR3(0, 1, 0)
			//);

			this->matrices.ViewMatrix = Matrix::Transpose(Matrix::CreateLookAt(
				g_vEye,
				g_vAt,
				g_vUp
			));

			//Matrices* data = matrixBuffer->Map();
			//data->ViewMatrix = matrices.ViewMatrix.Transpose();
			//data->ProjectionMatrix = matrices.ProjectionMatrix.Transpose();
			//matrixBuffer->Unmap();
		}
		#pragma endregion
	}
}