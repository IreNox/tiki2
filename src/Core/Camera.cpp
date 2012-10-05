
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
				gameObject->PRS.Position,
				gameObject->PRS.Position + gameObject->PRS.GetForward(),
				Vector3::Up
			));
		}

#pragma endregion

    Ray Camera::ScreenPointToRay( const Vector3& screenPos )
    {
      // it is important that the width and height values above are correct. 
      // We need to use the size of the back buffer which may not be the same as the window size
      Vector2 bbDim = engine->graphics->GetViewPort()->GetSize();

      Vector3 v;
      v.X =  ( ( ( 2.0f * screenPos.X) / bbDim.X) - 1) / matrices.ProjectionMatrix.M11;
      v.Y = -( ( ( 2.0f * screenPos.Y) / bbDim.Y) - 1) / matrices.ProjectionMatrix.M22;
      v.Z = 1.0f;

      Matrix m = Matrix::Invert(matrices.ViewMatrix);

      // The direction is a vector defining the direction from the eye through the screen into the 3D world
      Vector3 dir(v.X * m.M11 + v.Y * m.M21 + v.Z * m.M31,
                  v.X * m.M12 + v.Y * m.M22 + v.Z * m.M32,
                  v.X * m.M13 + v.Y * m.M23 + v.Z * m.M33);
      
      Vector3 orig(m.M41, m.M42, m.M43);

      return Ray(orig, dir);
    }

	}
}
