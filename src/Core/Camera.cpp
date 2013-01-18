
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
			: Component(engine, gameObject), renderTarget(0), matrices(), frustum()
		{
			engine->graphics->ScreenSizeChanged.AddHandler(this);

			matrices.ViewMatrix = Matrix::Identity;
			matrices.ViewInverseMatrix = Matrix::Identity;

			this->Handle(
				engine->graphics,
				ScreenSizeChangedArgs(engine->graphics, engine->graphics->GetViewPort())
			);
		}

		Camera::~Camera()
		{
		}
		#pragma endregion

		#pragma region Member
		Ray Camera::ScreenPointToRay(const Vector2& screenPos)
		{
			Vector2 bbDim = engine->graphics->GetViewPort()->GetSize();

			Matrix vp = this->WorldToScreen();

			Vector3 orig = Matrix::Unproject(Vector3(screenPos, 0), 0, 0, bbDim.X, bbDim.Y, -1, 1, vp);
			Vector3 dir = Matrix::Unproject(Vector3(screenPos, 1), 0, 0, bbDim.X, bbDim.Y, -1, 1, vp);

			dir -= orig;
			dir = Vector3::Normalize(dir);

			return Ray(orig, dir);
		}
		Vector3 Camera::GetViewDirection()
		{
			return gameObject->PRS.GetForward();
		}
		#pragma endregion

		#pragma region Member - Get/Set
		bool Camera::GetReady()
		{
			return true;
		}

		Frustum& Camera::GetFrustum()
		{
			return frustum;
		}

		CBMatrices& Camera::GetMatrices()
		{
			return matrices;
		}

		const Matrix Camera::WorldToScreen()
		{
			return Matrix::Transpose(matrices.ViewMatrix) * Matrix::Transpose(matrices.ProjectionMatrix);
		}

		IRenderTarget* Camera::GetRenderTarget()
		{
			return renderTarget;
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
			if (gameObject->PRS.IsDirty())
			{
				// cache non-transposed view
				Matrix view = Matrix::CreateLookAt(
					gameObject->PRS.GPosition(),
					gameObject->PRS.GPosition() + gameObject->PRS.GetForward(),
					Vector3::Up
				);

				matrices.ViewMatrix = Matrix::Transpose(view);
				matrices.ViewInverseMatrix = Matrix::Transpose(Matrix::Invert(view));

				// create frustum from view * re-transposed Proj
				//frustum.Set(
				//	view * Matrix::Transpose(matrices.ProjectionMatrix)
				//);

	/*			frustum.Set(
					view * Matrix::Transpose(matrices.ProjectionMatrix)
					);*/


				frustum.CreatePlanes(view * Matrix::Transpose(matrices.ProjectionMatrix));

				gameObject->PRS.MarkAsClean();
			}
		}
		#pragma endregion

		#pragma region Member - EventHandler
		void Camera::Handle(IGraphics* sender, const ScreenSizeChangedArgs& args)
		{
			matrices.ProjectionMatrix = Matrix::Transpose(
				Matrix::CreatePerspectiveFieldOfView(
					(float)(MATH_PI / 4.0),
					(float)args.CurrentViewPort->Width / args.CurrentViewPort->Height,
					0.01f,
					1000.0f
				)
			);
		}
		#pragma endregion

	}
}
