
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
			engine->graphics->ScreenSizeChanged.AddHandler(this);

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
		Ray Camera::ScreenPointToRay( const Vector2& screenPos )
		{
			Vector2 bbDim = engine->graphics->GetViewPort()->GetSize();

			Matrix vp = Matrix::Transpose(matrices[engine->GetState().UpdateIndex].ViewMatrix) * 
				Matrix::Transpose(matrices[engine->GetState().UpdateIndex].ProjectionMatrix);

			Vector3 orig = Vector3::Unproject(Vector3(screenPos, 0), 0, 0, bbDim.X, bbDim.Y, -1, 1, vp);
			Vector3 dir = Vector3::Unproject(Vector3(screenPos, 1), 0, 0, bbDim.X, bbDim.Y, -1, 1, vp);

			dir -= orig;
			dir = Vector3::Normalize(dir);

			return Ray(orig, dir);
		}
		#pragma endregion

		#pragma region Member - Get/Set
		bool Camera::GetReady()
		{
			return true;
		}

		Frustum* Camera::GetFrustum()
		{
			return &frustum[0];
		}

		CBMatrices* Camera::GetMatrices()
		{
			return &matrices[0];
		}

		Matrix* Camera::GetViewMatrix()
		{
			return &matrices[0].ViewMatrix;
		}

		Matrix* Camera::GetProjectionMatrix()
		{
			return &matrices[0].ProjectionMatrix;
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
			// cache non-transposed view
			Matrix view = Matrix::CreateLookAt(
				gameObject->PRS.GPosition(),
				gameObject->PRS.GPosition() + gameObject->PRS.GetForward(),
				Vector3::Up
			);
			matrices[engine->GetState().UpdateIndex].ViewMatrix = Matrix::Transpose(view);

			// create frustum from view * re-transposed Proj
			frustum[engine->GetState().UpdateIndex].Set(
				view * Matrix::Transpose(matrices[engine->GetState().UpdateIndex].ProjectionMatrix)
			);
		}
		#pragma endregion

		#pragma region Member - EventHandler
		void Camera::Handle(IGraphics* sender, const ScreenSizeChangedArgs& args)
		{
			matrices[0].ProjectionMatrix = matrices[1].ProjectionMatrix = Matrix::Transpose(Matrix::CreatePerspectiveFieldOfView(
				MATH_PI / 4,
				(float)args.CurrentViewPort->Width / args.CurrentViewPort->Height,
				0.01f,
				1000.0f
			));
		}
		#pragma endregion

	}
}
