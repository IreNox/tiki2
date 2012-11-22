#include "Graphics/AnimationLayer.h"

namespace TikiEngine
{
	namespace Resources
	{
		AnimationLayer::AnimationLayer()
			:	translationX(0), translationY(0), translationZ(0),
				rotationX(0), rotationY(0), rotationZ(0),
				start(-1),
				end(-1),
				lastUpdateTime(-1.0),
				currentTime(0)
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

			if(timeStamps != 0)
			{
				delete timeStamps;
				timeStamps = 0;
			}
		
		}

		void AnimationLayer::Initialize(FbxNode* node, FbxAnimLayer* layer)
		{
			timeStamps = new List<double>();
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

			if(translationX->Keys.Count() == 0)
			{
				AnimationKey* k = new AnimationKey(0.0, trans.arr[0]);
				k->AddRef();
				translationX->Keys.Add(k);
				translationX->InitValue = trans.arr[0];
			}
			if(translationY->Keys.Count() == 0)
			{
				AnimationKey* k = new AnimationKey(0.0, trans.arr[1]);
				k->AddRef();
				translationY->Keys.Add(k);
				translationY->InitValue = trans.arr[1];
			}
			if(translationZ->Keys.Count() == 0)
			{
				AnimationKey* k = new AnimationKey(0.0, trans.arr[2]);
				k->AddRef();
				translationZ->Keys.Add(k);
				translationZ->InitValue = trans.arr[2];
			}


			if(rotationX->Keys.Count() == 0)
			{
				AnimationKey* k = new AnimationKey(0.0, rot.arr[0]);
				k->AddRef();
				rotationX->Keys.Add(k);
				rotationX->InitValue = rot.arr[0];
			}
			if(rotationY->Keys.Count() == 0)
			{
				AnimationKey* k = new AnimationKey(0.0, rot.arr[1]);
				k->AddRef();
				rotationY->Keys.Add(k);
				rotationY->InitValue = rot.arr[1];
			}
			if(rotationZ->Keys.Count() == 0)
			{
				AnimationKey* k = new AnimationKey(0.0, rot.arr[2]);
				k->AddRef();
				rotationZ->Keys.Add(k);
				rotationZ->InitValue = rot.arr[2];
			}
			if(quaternionen.Count() == 0)
			{
				quaternionen.Add(quat);
			}

			translationX->BSV = bsv;
			translationY->BSV = bsv;
			translationZ->BSV = bsv;

			rotationX->BSV = bsv;
			rotationY->BSV = bsv;
			rotationZ->BSV = bsv;
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
			if(timeStamps->Get(0) >= currentTime) 
			{
				left = 0;
				right = -1;
				return;
			}
			//after last element -> return last element
			if(timeStamps->Get(count - 1) <= currentTime)
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
				if(index + shift < count && timeStamps->Get(index + shift) <= currentTime)
					index += shift;
				shift /= 2;
			}
			
			if(timeStamps->Get(index) == currentTime)
			{
				left = right = index;
				return;
			}

			left = index;
			right = index + 1;

			koeff = (currentTime - timeStamps->Get(left)) / (timeStamps->Get(right) - timeStamps->Get(left));
		}

		void AnimationLayer::CreateKeys(List<double>* keyTimes, FbxNode* node)
		{
			translationX = new AnimationCurve();
			translationX->AddRef();
			translationY = new AnimationCurve();
			translationY->AddRef();
			translationZ = new AnimationCurve();
			translationZ->AddRef();

			rotationX = new AnimationCurve();
			rotationX->AddRef();
			rotationY = new AnimationCurve();
			rotationY->AddRef();
			rotationZ = new AnimationCurve();
			rotationZ->AddRef();

			for(int i = 0; i < keyTimes->Count(); i++)
			{
				double time = keyTimes->Get(i);

				FbxTime fbxTime;
				fbxTime.SetSecondDouble(keyTimes->Get(i));

				FbxAMatrix localTransform = node->EvaluateLocalTransform(fbxTime);

				FbxVector4 trans = localTransform.GetT();
				FbxVector4 rot = localTransform.GetR();
				Quaternion quat = FBXConverter::Convert(localTransform.GetQ());


				Vector3 translation = FBXConverter::ConvertDrop(trans);
				Vector3 rotation = FBXConverter::ConvertDrop(rot);

				AddKey(translationX, translation.X, time);
				AddKey(translationY, translation.Y, time);
				AddKey(translationZ, translation.Z, time);

				AddKey(rotationX, rotation.X, time);
				AddKey(rotationY, rotation.Y, time);
				AddKey(rotationZ, rotation.Z, time);

				this->quaternionen.Add(quat);
			}
		}

		void AnimationLayer::AddKey(AnimationCurve* curve, float value, double& time)
		{
			AnimationKey* key = new AnimationKey(time, value);
			key->AddRef();
			curve->Keys.Add(key);
		}

		void AnimationLayer::GetTimeStamps(List<double>* timeStamps, FbxNode* node, FbxAnimLayer* layer)
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

			timeStamps->Sort();

			this->start = timeStamps->Get(0);
			this->end = timeStamps->Get(timeStamps->Count() - 1);

			int bs = 1;
			while(bs*2 < timeStamps->Count())
				bs *= 2;
			bsv = bs;
		}

		void AnimationLayer::Fill(List<double>* keyTimes, FbxAnimCurve* curve)
		{
			if(curve == 0)
				return;

			for(int i = 0; i < curve->KeyGetCount(); i++)
			{
				double time = curve->KeyGetTime(i).GetSecondDouble();
				if(!keyTimes->Contains(time))
					keyTimes->Add(time);
			}
		}

		Vector3 AnimationLayer::LocalTranslation(const double& time)
		{
			if(time == -1.0)
			{
				return Vector3(
					translationX->Evaluate(left, right, koeff),
					translationY->Evaluate(left, right, koeff),
					translationZ->Evaluate(left, right, koeff)
					);
			}
			else
			{

				if(time != lastUpdateTime)
					Update(time);

				return Vector3(
					translationX->Evaluate(left, right, koeff),
					translationY->Evaluate(left, right, koeff),
					translationZ->Evaluate(left, right, koeff)
					);
			}
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