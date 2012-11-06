#include "Graphics/TikiAnimationCurve.h"

namespace TikiEngine
{
	namespace Resources
	{
		TikiAnimationCurve::TikiAnimationCurve(FbxNode* node)
			:node(node)
		{
			this->initTranslation = FBXConverter::Convert(node->LclTranslation.Get());
			this->initRotation = FBXConverter::Convert(node->LclRotation.Get());
		}

		TikiAnimationCurve::~TikiAnimationCurve()
		{

		}
		Vector3 TikiAnimationCurve::LocalTranslation(const double &time)
		{
			if(time == -1.0)
				return initTranslation;

			Vector3 tmp;
			
			int xCount = translationX.Count();
			int yCount = translationY.Count();
			int zCount = translationZ.Count();

			return tmp;
		}
		Vector3 TikiAnimationCurve::LocalRotation(const double &time)
		{
			if(time == -1.0)
				return initRotation;

			return Vector3();
		}
		void GetKeysByTime(List<TikiAnimationKey>& list, double& time, TikiAnimationKey& left, TikiAnimationKey& right)
		{
			int keyCount = list.Count();
			int index = 0;
			for(int i = 0; i < keyCount; i++)
			{
				if(list[i].Time() <= time)
				{
					index = i;
				}
				else
				{
					break;
				}
			}
			TikiAnimationKey tmp = list[index];
			if(tmp.Time() == time)
			{
				left = right = tmp;
			}
			else
			{
				left = tmp;
				right = list[(index + 1) % keyCount];
			}
		}

		void TikiAnimationCurve::SetAnimation(FbxAnimLayer* layer)
		{
			this->translationX.Clear();
			this->translationY.Clear();
			this->translationZ.Clear();
			this->rotationX.Clear();
			this->rotationY.Clear();
			this->rotationZ.Clear();

			FbxAnimCurve* curve = this->node->LclTranslation.GetCurve(layer, FBXSDK_CURVENODE_COMPONENT_X);
			this->FillCurve(translationX, curve);

			curve = this->node->LclTranslation.GetCurve(layer, FBXSDK_CURVENODE_COMPONENT_Y);
			this->FillCurve(translationY, curve);

			curve = this->node->LclTranslation.GetCurve(layer, FBXSDK_CURVENODE_COMPONENT_Z);
			this->FillCurve(translationZ, curve);

			curve = this->node->LclRotation.GetCurve(layer, FBXSDK_CURVENODE_COMPONENT_X);
			this->FillCurve(rotationX, curve);

			curve = this->node->LclRotation.GetCurve(layer, FBXSDK_CURVENODE_COMPONENT_Y);
			this->FillCurve(rotationY, curve);

			curve = this->node->LclRotation.GetCurve(layer, FBXSDK_CURVENODE_COMPONENT_Z);
			this->FillCurve(rotationZ, curve);
		}

		void TikiAnimationCurve::FillCurve(List<TikiAnimationKey>& list, FbxAnimCurve* curve)
		{
			if(curve == 0)
				return;
			for(int i = 0; i < curve->KeyGetCount(); i++)
			{
				double time = curve->KeyGetTime(i).GetSecondDouble();
				float keyValue = static_cast<float>(curve->KeyGetValue(i));

				TikiAnimationKey key(time, keyValue);
				list.Add(key);
			}
		}
	}
}

