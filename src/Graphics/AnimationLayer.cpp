#include "Graphics/AnimationLayer.h"

namespace TikiEngine
{
	namespace Resources
	{
		AnimationLayer::AnimationLayer(double& start, double& end)
			:	translationX(0), translationY(0), translationZ(0),
				rotationX(0), rotationY(0), rotationZ(0),
				preRotation(),
				postRotationInverse(),
				start(start),
				end(end)
		{	 
			 
		}

		AnimationLayer::~AnimationLayer()
		{	 
			SafeRelease(&translationX);
			SafeRelease(&translationY);
			SafeRelease(&translationZ);
			SafeRelease(&rotationX);
			SafeRelease(&rotationY);
			SafeRelease(&rotationZ);
		}

		void AnimationLayer::Initialize(FbxNode* node, FbxAnimLayer* layer)
		{
			Vector3 preRot = FBXConverter::Convert(node->PreRotation.Get());
			Vector3 postRot = FBXConverter::Convert(node->PostRotation.Get());

			preRotation = Matrix::CreateFromXYZDegrees(preRot);
			postRotationInverse = Matrix::CreateFromXYZDegrees(postRot).Invert();

			Vector3 initTranslation = FBXConverter::Convert(node->LclTranslation.Get());
			Vector3 initRotation = FBXConverter::Convert(node->LclRotation.Get());

			FbxAnimCurve* curve = node->LclTranslation.GetCurve(layer, FBXSDK_CURVENODE_COMPONENT_X);
			translationX = Fill(curve, initTranslation.X);

			curve = node->LclTranslation.GetCurve(layer, FBXSDK_CURVENODE_COMPONENT_Y);
			translationY = Fill(curve, initTranslation.Y);

			curve = node->LclTranslation.GetCurve(layer, FBXSDK_CURVENODE_COMPONENT_Z);
			translationZ = Fill(curve, initTranslation.Z);


			curve = node->LclRotation.GetCurve(layer, FBXSDK_CURVENODE_COMPONENT_X);
			rotationX = Fill(curve, initRotation.X);

			curve = node->LclRotation.GetCurve(layer, FBXSDK_CURVENODE_COMPONENT_Y);
			rotationY = Fill(curve, initRotation.Y);

			curve = node->LclRotation.GetCurve(layer, FBXSDK_CURVENODE_COMPONENT_Z);
			rotationZ = Fill(curve, initRotation.Z);

		}

		AnimationCurve* AnimationLayer::Fill(FbxAnimCurve* curve, float init)
		{
			AnimationCurve* tikiCurve = new AnimationCurve(init, this->start, this->end);
			tikiCurve->AddRef();

			if(curve == 0)
				return tikiCurve;


			for(int i = 0; i < curve->KeyGetCount(); i++)
			{
				double time = curve->KeyGetTime(i).GetSecondDouble();
				float keyValue = static_cast<float>(curve->KeyGetValue(i));
				AnimationKey* key = new AnimationKey(time, keyValue);
				key->AddRef();
				tikiCurve->Keys.Add(key);
			}

			int bsv = 1;
			while(bsv*2 < tikiCurve->Keys.Count())
				bsv *= 2;
			tikiCurve->BSV = bsv;

			return tikiCurve;
		}

		Vector3 AnimationLayer::LocalTranslation(const double& time)
		{
			return Vector3(
				translationX->Evaluate(time),
				translationY->Evaluate(time),
				translationZ->Evaluate(time)
				);
		}
		Vector3 AnimationLayer::LocalRotation(const double& time)
		{
			return Vector3(
				rotationX->Evaluate(time),
				rotationY->Evaluate(time),
				rotationZ->Evaluate(time)
				);
		}
		Matrix AnimationLayer::LocalTransform(const double& time)
		{
			return postRotationInverse *
				Matrix::CreateFromXYZDegrees(LocalRotation(time)) *
				preRotation *
				Matrix::CreateTranslation(LocalTranslation(time));
		}
	}
}