#pragma once
#include "Core/RectangleF.h"
#include "Core/Frustum.h"
#include "Core/IBoundingBox.h"

namespace TikiEngine
{
	class GameObject;

	class Bounding : public IBoundingBox
	{
	public:

		Vector3 Min,Max;

		Bounding(Engine* engine) : IBoundingBox(engine), Min(Vector3::Zero), Max(Vector3::Zero){}
		virtual ~Bounding() {}
		
		Vector3 GetMin() const { return Min;} 
		Vector3 GetMax() const { return Max;}

		Vector3 GetVertexP( const Vector3& normal)
		{
			Vector3 p = Min;
			if (normal.X >= 0) p.X = Max.X;
			if (normal.Y >= 0) p.Y = Max.Y;
			if (normal.Z >= 0) p.Z = Max.Z;
			return p;
		}

		Vector3 GetVertexN( const Vector3& normal)
		{
			Vector3 n = Max; 
			if (normal.X >= 0) n.X = Min.X;
			if (normal.Y >= 0) n.Y = Min.Y;
			if (normal.Z >= 0) n.Z = Min.Z;
			return n;
		}

		void Set( const Vector3& min, const Vector3& max)
		{
			this->Min = min;
			this->Max = max;
		}

		bool Intersects(IBoundingBox* b) { return true;}

		bool Contains(const Vector3& p) { return true; }
#if _DEBUG
		void DrawDebug(Color color) 
		{
			engine->graphics->DrawLine(Vector3(Min.X, Min.Y, Min.Z), Vector3(Max.X, Min.Y, Min.Z), color);
			engine->graphics->DrawLine(Vector3(Min.X, Min.Y, Max.Z), Vector3(Max.X, Min.Y, Max.Z), color);
			engine->graphics->DrawLine(Vector3(Min.X, Min.Y, Min.Z), Vector3(Min.X, Min.Y, Max.Z), color);
			engine->graphics->DrawLine(Vector3(Max.X, Min.Y, Min.Z), Vector3(Max.X, Min.Y, Max.Z), color);

			engine->graphics->DrawLine(Vector3(Min.X, Max.Y, Min.Z), Vector3(Max.X, Max.Y, Min.Z), color);
			engine->graphics->DrawLine(Vector3(Min.X, Max.Y, Max.Z), Vector3(Max.X, Max.Y, Max.Z), color);
			engine->graphics->DrawLine(Vector3(Min.X, Max.Y, Min.Z), Vector3(Min.X, Max.Y, Max.Z), color);
			engine->graphics->DrawLine(Vector3(Max.X, Max.Y, Min.Z), Vector3(Max.X, Max.Y, Max.Z), color);

			engine->graphics->DrawLine(Vector3(Min.X, Min.Y, Min.Z), Vector3(Min.X, Max.Y, Min.Z), color);
			engine->graphics->DrawLine(Vector3(Max.X, Min.Y, Min.Z), Vector3(Max.X, Max.Y, Min.Z), color);
			engine->graphics->DrawLine(Vector3(Min.X, Min.Y, Max.Z), Vector3(Min.X, Max.Y, Max.Z), color);
			engine->graphics->DrawLine(Vector3(Max.X, Min.Y, Max.Z), Vector3(Max.X, Max.Y, Max.Z), color);
		}
#endif

		void* GetNativeResource() { return 0; }
		bool GetReady() { return true; }

		void loadFromStream( wcstring fileName, Stream* stream ) {}
		void saveToStream( wcstring fileName, Stream* stream) {}
	};

	class SceneGraphElement
	{
	public:
		SceneGraphElement();
		~SceneGraphElement();

		void SetGameObject( GameObject* go );
		void SetBounds( float width, float height );

		void Update(const UpdateArgs& args);

		bool IsInsideFrustum( Frustum& frustum );

		inline void SetDynamic(){ this->isDynamic = true; }
		inline bool IsDynamic(){ return this->isDynamic; }
		inline float Radius(){ return this->radius; }
		inline bool IsVisible(){ return visibleTimer <= 1.0; }
		inline void MarkVisible(){ visibleTimer = 0.0; }

		bool IsCulled;

		RectangleF Bounds;

		IBoundingBox* boundingBox;

	private:
		GameObject* go;
		

		float width;
		float height;
		float radius;
		bool isDynamic;
		double visibleTimer;

		Vector3 min;
		Vector3 max;
	};
}