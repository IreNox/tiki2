
#include "Game/CameraTPS.h"
#include "Core/GameObject.h"

namespace TikiEngine
{
	namespace Game
	{
		CameraTPS::CameraTPS(Engine* engine, GameObject* gameObject, GameObject* attached)
			: IScript(engine, gameObject), attached(attached), distance(20)
		{
		}

		CameraTPS::~CameraTPS()
		{
		}

		void CameraTPS::Draw(const DrawArgs& args)
		{
		}

		void CameraTPS::Update(const UpdateArgs& args)
		{
			//rot += args.Input.MouseDistance * args.Time.ElapsedTime * 100;
			//
			//if (rot.Y < 0) rot.Y = 0;
			//if (rot.Y > MATH_PIOVER2) rot.Y = MATH_PIOVER2;

			//Vector3 aPos = attached->PRS.GPosition();
			//Vector3 shere = Vector3(
			//	sinf(rot.X),
			//	cosf(rot.Y),
			//	cosf(rot.X)
			//) * distance;

			//gameObject->PRS.SPosition() = aPos + shere;

			////shere = Vector3(
			////	shere.X,
			////	shere.Z,
			////	shere.Y
			////);

			////shere = Vector3::Normalize(-shere);

			//float alpha = Vector3::Angle(shere, Vector3::UnitX);
			//float beta = Vector3::Angle(shere, Vector3::UnitY);
			//float gamma = Vector3::Angle(shere, Vector3::UnitZ);

			////gameObject->PRS.SRotation() = Quaternion::CreateFromYawPitchRoll(
			////	(MATH_TWOPI - atan2(-shere.Z, -shere.X)) - MATH_PIOVER2,
			////	(MATH_TWOPI + shere.Y) - MATH_PIOVER2,
			////	0
			////);

			///*		tmpZaxis.set( direction ).normalizeLocal();
			//tmpXaxis.set( up ).crossLocal( direction ).normalizeLocal();
			//tmpYaxis.set( direction ).crossLocal( tmpXaxis ).normalizeLocal();
			//fromAxes( tmpXaxis, tmpYaxis, tmpZaxis );

			//fromRotationMatrix(xAxis.x, yAxis.x, zAxis.x, xAxis.y, yAxis.y,
			//zAxis.y, xAxis.z, yAxis.z, zAxis.z);*/

			//gameObject->PRS.SRotation() = Quaternion::CreateLookAt(
			//	shere,
			//	Vector3::Up
			//);


			////gameObject->PRS.SRotation() = Quaternion::CreateFromYawPitchRoll(
			////	Vector3(
			////		//MATH_TWOPI - shere.Y,
			////		(MATH_TWOPI - atan2(shere.Z, shere.X)) - MATH_PIOVER2,
			////		shere.X,
			////		shere.Z
			////	)
			////);
		}
	}
}