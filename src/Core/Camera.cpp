
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
			: Component(engine, gameObject), renderTarget(0), matrices()
		{
			ViewPort* vp = engine->graphics->GetViewPort();

			this->matrices.ProjectionMatrix = Matrix::Transpose(Matrix::CreatePerspectiveFieldOfView(
				MATH_PI / 4,
				(float)vp->Width / vp->Height,
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

		CBMatrices* Camera::GetMatrices()
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

		Frustum* Camera::GetFrustum()
		{
			return &frustum;
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
			// cache non-transposed view
			Matrix view = Matrix::CreateLookAt(
				gameObject->PRS.GPosition(),
				gameObject->PRS.GPosition() + gameObject->PRS.GetForward(),
				Vector3::Up
			);
			this->matrices.ViewMatrix = Matrix::Transpose(view);

			// create frustum from view * re-transposed Proj
			frustum.Set(view * Matrix::Transpose(matrices.ProjectionMatrix));
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
