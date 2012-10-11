
#include "Core/Engine.h"
#include "Core/Camera.h"

#include "Core/DrawArgs.h"
#include "Core/UpdateArgs.h"

#include "Core/GameObject.h"

#include "Core/IGraphics.h"

namespace TikiEngine
{
	namespace Components
	{
		#pragma region Class
		Camera::Camera(Engine* engine, GameObject* gameObject)
			: Component(engine, gameObject, CT_Camera), renderTarget(0), matrices()
		{
			ViewPort* vp = &engine->GetEngineDescription()->Graphics.ViewPort;

			this->matrices.ProjectionMatrix = Matrix::Transpose(Matrix::CreatePerspectiveFieldOfView(
				MATH_PI / 4,				
				(float)vp->Width / vp->Width,
				0.01f,
				1000.0f
			));
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
			this->matrices.ViewMatrix = Matrix::Transpose(Matrix::CreateLookAt(
				gameObject->PRS.Position(),
				gameObject->PRS.Position() + gameObject->PRS.GetForward(),
				Vector3::Up
			));
		}
		#pragma endregion

		Ray Camera::ScreenPointToRay( const Vector2& screenPos )
		{
			Vector2 bbDim = engine->graphics->GetViewPort()->GetSize();
			
			Matrix vp = Matrix::Transpose(matrices.ViewMatrix) * 
					    Matrix::Transpose(matrices.ProjectionMatrix);

			Vector3 orig = Vector3::Unproject(Vector3(screenPos, 0), 0, 0, bbDim.X, bbDim.Y, -1, 1, vp);
			Vector3 dir = Vector3::Unproject(Vector3(screenPos, 1), 0, 0, bbDim.X, bbDim.Y, -1, 1, vp);

			dir -= orig;
			dir = Vector3::Normalize(dir);

			return Ray(orig, dir);
		}

	}
}
