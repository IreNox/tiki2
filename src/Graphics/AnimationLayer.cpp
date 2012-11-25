#include "Graphics/AnimationLayer.h"

namespace TikiEngine
{
	namespace Resources
	{
		AnimationLayer::AnimationLayer()
			:	/*translationX(0), translationY(0), translationZ(0),*/
				start(-1),
				end(-1),
				lastUpdateTime(-1.0),
				currentTime(0)
		{	 
			 
		}

		AnimationLayer::~AnimationLayer()
		{	 
		}

		//void AnimationLayer::Initialize(FbxNode* node, FbxAnimLayer* layer)
		//{
		//	GetTimeStamps(timeStamps, node, layer);
		//	CreateKeys(timeStamps, node);
		//	CreateDefaultValues(node);

		//}

		//void AnimationLayer::CreateDefaultValues(FbxNode* node)
		//{
			//_CrtDbgBreak();
			//FbxAMatrix defaultPosition = node->EvaluateLocalTransform();
			//Vector3 trans = FBXConverter::ConvertDrop(defaultPosition.GetT());
			//Vector3 rot = FBXConverter::ConvertDrop(defaultPosition.GetR());
			//Quaternion quat = FBXConverter::Convert(defaultPosition.GetQ());

			//if(translation.Count() == 0)
			//	translation.Add(trans);

			//if(quaternionen.Count() == 0)
			//	quaternionen.Add(quat);
		//}

		double& AnimationLayer::GCurrentTime()
		{
			return this->currentTime;
		}

		void AnimationLayer::SCurrentTime(double& time)
		{
			this->currentTime = time;
		}

		void AnimationLayer::Reset()
		{
			this->currentTime = this->start;
		}

		void AnimationLayer::Update(TikiAnimation* animation)
		{
			this->transformMatrix = Matrix::CreateFromQuaternion(LocalQuaternion(animation))
				* Matrix::CreateTranslation(LocalTranslation(animation));
		}

		//void AnimationLayer::CreateKeys(List<double>& keyTimes, FbxNode* node)
		//{
			//_CrtDbgBreak();
			//for(int i = 0; i < keyTimes.Count(); i++)
			//{
			//	double time = keyTimes[i];

			//	FbxTime fbxTime;
			//	fbxTime.SetSecondDouble(keyTimes[i]);

			//	FbxAMatrix localTransform = node->EvaluateLocalTransform(fbxTime);

			//	FbxVector4 trans = localTransform.GetT();
			//	FbxVector4 rot = localTransform.GetR();
			//	Quaternion quat = FBXConverter::Convert(localTransform.GetQ());

			//	Vector3 translation = FBXConverter::ConvertDrop(trans);
			//	Vector3 rotation = FBXConverter::ConvertDrop(rot);

			//	this->translation.Add(translation);

			//	this->quaternionen.Add(quat);
			//}
		//}

		//void AnimationLayer::GetTimeStamps(List<double>& timeStamps, FbxNode* node, FbxAnimLayer* layer)
		//{
			//_CrtDbgBreak();
//#if _DEBUG
//			if(node == 0)
//				_CrtDbgBreak();
//#endif
//
//			FbxAnimCurve* curve = node->LclTranslation.GetCurve(layer, FBXSDK_CURVENODE_COMPONENT_X);
//			Fill(timeStamps, curve);
//			curve = node->LclTranslation.GetCurve(layer, FBXSDK_CURVENODE_COMPONENT_Y);
//			Fill(timeStamps, curve);
//			curve = node->LclTranslation.GetCurve(layer, FBXSDK_CURVENODE_COMPONENT_Z);
//			Fill(timeStamps, curve);
//
//			curve = node->LclRotation.GetCurve(layer, FBXSDK_CURVENODE_COMPONENT_X);
//			Fill(timeStamps, curve);
//			curve = node->LclRotation.GetCurve(layer, FBXSDK_CURVENODE_COMPONENT_Y);
//			Fill(timeStamps, curve);
//			curve = node->LclRotation.GetCurve(layer, FBXSDK_CURVENODE_COMPONENT_Z);
//			Fill(timeStamps, curve);
//
//			timeStamps.Sort();
//
//			this->start = timeStamps[0];
//			this->end = timeStamps[timeStamps.Count() - 1];
//
//			int bs = 1;
//			while(bs*2 < timeStamps.Count())
//				bs *= 2;
//			bsv = bs;
		//}

		//void AnimationLayer::Fill(List<double>& keyTimes, FbxAnimCurve* curve)
		//{
		//	if(curve == 0)
		//		return;

		//	for(int i = 0; i < curve->KeyGetCount(); i++)
		//	{
		//		double time = curve->KeyGetTime(i).GetSecondDouble();
		//		if(!keyTimes.Contains(time))
		//			keyTimes.Add(time);
		//	}
		//}

		Vector3 AnimationLayer::LocalTranslation(TikiAnimation* animation)
		{
			if(animation->Left == animation->Right)
				return translation[animation->Left];
			if(animation->Right == -1)
				return translation[animation->Left];
			if(animation->Left == -1)
				return translation[animation->Right];

			return Vector3::Lerp(translation[animation->Left], translation[animation->Right], animation->Koeff);
		}

		Quaternion AnimationLayer::LocalQuaternion(TikiAnimation* animation)
		{
			if(animation->Left == animation->Right)
				return quaternionen[animation->Left];
			if(animation->Right == -1)
				return quaternionen[animation->Left];
			if(animation->Left == -1)
				return quaternionen[animation->Right];

			return Quaternion::Slerp(quaternionen.Get(animation->Left), quaternionen.Get(animation->Right), animation->Koeff);

		}

		Vector3 AnimationLayer::LocalTranslation(const double& time)
		{
			if(time == -1.0)
			{
				if(left == right)
					return translation[left];
				if(right == -1)
					return translation[left];
				if(left == -1)
					return translation[right];
				
				return Vector3::Lerp(translation[left], translation[right], koeff);
			}
			else
			{
				if(left == right)
					return translation[left];
				if(right == -1)
					return translation[left];
				if(left == -1)
					return translation[right];

				return Vector3::Lerp(translation[left], translation[right], koeff);
			}
		}

		Quaternion AnimationLayer::LocalQuaternion(const double& time)
		{
			_CrtDbgBreak(); //NYI
			return Quaternion();
			//if(time == -1.0)
			//{
			//	if(left == right)
			//		return this->quaternionen.Get(left);
			//	if(right == -1)
			//		return this->quaternionen.Get(left);
			//	if(left == -1)
			//		return this->quaternionen.Get(right);

			//	return Quaternion::Slerp(quaternionen.Get(left), quaternionen.Get(right), koeff);
			//}
			//else
			//{
			//	if(time != lastUpdateTime)
			//		Update(time);

			//	if(left == right)
			//		return this->quaternionen.Get(left);
			//	if(right == -1)
			//		return this->quaternionen.Get(left);
			//	if(left == -1)
			//		return this->quaternionen.Get(right);

			//	return Quaternion::Slerp(quaternionen.Get(left), quaternionen.Get(right), koeff);
			//}
		}

		Matrix AnimationLayer::LocalTransform(const double& time)
		{
			return transformMatrix;
			//if(time == -1.0)
			//{
			//	return Matrix::CreateFromQuaternion(LocalQuaternion())
			//		 * Matrix::CreateTranslation(LocalTranslation());
			//}
			//else
			//{
			//	if(time != lastUpdateTime)
			//		Update(time);

			//	return Matrix::CreateFromQuaternion(LocalQuaternion(time)) *
			//		Matrix::CreateTranslation(LocalTranslation(time));
			//}
		}

		List<Vector3>& AnimationLayer::GetTranslation()
		{
			return this->translation;
		}

		List<Quaternion>& AnimationLayer::GetQuaternion()
		{
			return this->quaternionen;
		}
	}
}