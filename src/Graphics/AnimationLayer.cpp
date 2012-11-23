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

		void AnimationLayer::Initialize(FbxNode* node, FbxAnimLayer* layer)
		{
			GetTimeStamps(timeStamps, node, layer);
			CreateKeys(timeStamps, node);
			CreateDefaultValues(node);

		}

		void AnimationLayer::CreateDefaultValues(FbxNode* node)
		{
			FbxAMatrix defaultPosition = node->EvaluateLocalTransform();
			Vector3 trans = FBXConverter::ConvertDrop(defaultPosition.GetT());
			Vector3 rot = FBXConverter::ConvertDrop(defaultPosition.GetR());
			Quaternion quat = FBXConverter::Convert(defaultPosition.GetQ());

			if(translationX.Count() == 0)
				translationX.Add(trans.arr[0]);

			if(translationY.Count() == 0)
				translationY.Add(trans.arr[1]);

			if(translationZ.Count() == 0)
				translationZ.Add(trans.arr[2]);


			if(quaternionen.Count() == 0)
				quaternionen.Add(quat);
		}

		double& AnimationLayer::GetCurrentTime()
		{
			return this->currentTime;
		}

		void AnimationLayer::SetCurrentTime(double& time)
		{
			this->currentTime = time;
		}

		void AnimationLayer::Reset()
		{
			this->currentTime = this->start;
		}

		void AnimationLayer::Update(const double& deltaTime)
		{

			this->currentTime += deltaTime;

			if(currentTime >= end)
				currentTime -= end - start;


			if(lastUpdateTime == currentTime)
				return;
			else
				lastUpdateTime = currentTime;

			int count = quaternionen.Count();
			//one element - always the defaultvalue
			if(count == 1)
			{
				left = right = 0;
				return;
			}
			//before first element -> return first element
			if(timeStamps[0] >= currentTime) 
			{
				left = 0;
				right = -1;
				return;
			}
			//after last element -> return last element
			if(timeStamps[count - 1] <= currentTime)
			{
				left = -1;
				right = count -1;
				return;
			}

			int index = 0;
			int shift = bsv;

			//find index of highest value below time
			while(shift != 0)
			{
				if(index + shift < count && timeStamps[index + shift] <= currentTime)
					index += shift;
				shift /= 2;
			}
			
			if(timeStamps[index] == currentTime)
			{
				left = right = index;
				return;
			}

			left = index;
			right = index + 1;

			koeff = (currentTime - timeStamps[left]) / (timeStamps[right] - timeStamps[left]);
		}

		void AnimationLayer::CreateKeys(List<double>& keyTimes, FbxNode* node)
		{
			for(int i = 0; i < keyTimes.Count(); i++)
			{
				double time = keyTimes[i];

				FbxTime fbxTime;
				fbxTime.SetSecondDouble(keyTimes[i]);

				FbxAMatrix localTransform = node->EvaluateLocalTransform(fbxTime);

				FbxVector4 trans = localTransform.GetT();
				FbxVector4 rot = localTransform.GetR();
				Quaternion quat = FBXConverter::Convert(localTransform.GetQ());

				Vector3 translation = FBXConverter::ConvertDrop(trans);
				Vector3 rotation = FBXConverter::ConvertDrop(rot);

				translationX.Add(translation.arr[0]);
				translationY.Add(translation.arr[1]);
				translationZ.Add(translation.arr[2]);

				this->quaternionen.Add(quat);
			}
		}

		void AnimationLayer::GetTimeStamps(List<double>& timeStamps, FbxNode* node, FbxAnimLayer* layer)
		{
			FbxAnimCurve* curve = node->LclTranslation.GetCurve(layer, FBXSDK_CURVENODE_COMPONENT_X);
			Fill(timeStamps, curve);
			curve = node->LclTranslation.GetCurve(layer, FBXSDK_CURVENODE_COMPONENT_Y);
			Fill(timeStamps, curve);
			curve = node->LclTranslation.GetCurve(layer, FBXSDK_CURVENODE_COMPONENT_Z);
			Fill(timeStamps, curve);

			curve = node->LclRotation.GetCurve(layer, FBXSDK_CURVENODE_COMPONENT_X);
			Fill(timeStamps, curve);
			curve = node->LclRotation.GetCurve(layer, FBXSDK_CURVENODE_COMPONENT_Y);
			Fill(timeStamps, curve);
			curve = node->LclRotation.GetCurve(layer, FBXSDK_CURVENODE_COMPONENT_Z);
			Fill(timeStamps, curve);

			timeStamps.Sort();

			this->start = timeStamps[0];
			this->end = timeStamps[timeStamps.Count() - 1];

			int bs = 1;
			while(bs*2 < timeStamps.Count())
				bs *= 2;
			bsv = bs;
		}

		void AnimationLayer::Fill(List<double>& keyTimes, FbxAnimCurve* curve)
		{
			if(curve == 0)
				return;

			for(int i = 0; i < curve->KeyGetCount(); i++)
			{
				double time = curve->KeyGetTime(i).GetSecondDouble();
				if(!keyTimes.Contains(time))
					keyTimes.Add(time);
			}
		}

		Vector3 AnimationLayer::LocalTranslation(const double& time)
		{
			if(time == -1.0)
			{
				return Vector3(
					this->Evaluate(translationX),
					this->Evaluate(translationY),
					this->Evaluate(translationZ)
					);
			}
			else
			{

				if(time != lastUpdateTime)
					Update(time);

				return Vector3(
					this->Evaluate(translationX),
					this->Evaluate(translationY),
					this->Evaluate(translationZ)
					);
			}
		}
		float AnimationLayer::Evaluate(List<float>& list)
		{
			if(left == right)
				return list[left];
			if(right == -1)
				return list[left];
			if(left == -1)
				return list[right];

			return list[left] * (1 - koeff) + list[right] * koeff;
		}

		Quaternion AnimationLayer::LocalQuaternion(const double& time)
		{
			if(time == -1.0)
			{
				if(left == right)
					return this->quaternionen.Get(left);
				if(right == -1)
					return this->quaternionen.Get(left);
				if(left == -1)
					return this->quaternionen.Get(right);

				return Quaternion::Slerp(quaternionen.Get(left), quaternionen.Get(right), koeff);
			}
			else
			{
				if(time != lastUpdateTime)
					Update(time);

				if(left == right)
					return this->quaternionen.Get(left);
				if(right == -1)
					return this->quaternionen.Get(left);
				if(left == -1)
					return this->quaternionen.Get(right);

				return Quaternion::Slerp(quaternionen.Get(left), quaternionen.Get(right), koeff);
			}
		}

		Matrix AnimationLayer::LocalTransform(const double& time)
		{
			if(time == -1.0)
			{
				return Matrix::CreateFromQuaternion(LocalQuaternion())
					 * Matrix::CreateTranslation(LocalTranslation());
			}
			else
			{
				if(time != lastUpdateTime)
					Update(time);

				return Matrix::CreateFromQuaternion(LocalQuaternion(time)) *
					Matrix::CreateTranslation(LocalTranslation(time));
			}
		}
	}
}