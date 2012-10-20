
#include "Graphics/TerrainRenderer.h"

#include "Core/TypeGlobals.h"

#include "Core/IGraphics.h"
#include "Core/GameObject.h"
#include "Core/Camera.h"

#include "Graphics/DllMain.h"
#include "Graphics/GraphicsModule.h"

namespace TikiEngine
{
	namespace Components
	{
		using namespace Cloddy::API;
		using namespace Cloddy::API::MeshVisitors;
		using namespace Cloddy::Core::Math::Vectors;

		#pragma region Class
		TerrainRenderer::TerrainRenderer(Engine* engine, GameObject* gameObject)
			: ITerrainRenderer(engine, gameObject), material(0), collisionIndexBuffer(0), collisionVertexBuffer(0), collisionRegions(0)
		{
			/*

			cloddy_IDataset* dataset = cloddy_Dataset::Open();

			DataRegion region;

			dataset->Begin();

			dataset->Get(region);

			dataset->End();

			*/		
			
			
		}

		TerrainRenderer::~TerrainRenderer()
		{
			SafeDelete(&collisionIndexBuffer);
			SafeDelete(&collisionVertexBuffer);

			manager->Shutdown();
			SafeRelease(&material);
			SafeRelease(&layout);
		}
		#pragma endregion
		
		#pragma region Member - Load
		void TerrainRenderer::LoadTerrain(string fileName, int scale, int size)
		{
			int size2 = (engine->graphics->GetViewPort()->Width * engine->graphics->GetViewPort()->Height);

			vertexFormat = cloddy_VertexFormat::P3F()
				->Append(cloddy_VertexFormat::T2F(1, 1))
				->Append(cloddy_VertexFormat::N3F())
				->Append(cloddy_VertexFormat::C1I(cloddy_ColorFormat_RGBA));
			//->Append(cloddy_VertexFormat::X4F_12());

			vertexBuffer = new cloddy_VertexBuffer(engine->graphics->GetDevice(), size2, vertexFormat->GetVertexSize());
			indexBuffer = new cloddy_IndexBuffer(engine->graphics->GetDevice(), size2 * 2);

			callback = new cloddy_TriangulationCallback(engine->graphics->GetDevice(), vertexBuffer, indexBuffer);

			description = new cloddy_CloddyDescription();
			description->SetVertexBuffer(vertexBuffer);
			description->SetIndexBuffer(indexBuffer);
			description->SetVertexFormat(vertexFormat);
			description->SetTriangulationCallback(callback);
			description->EnableLogging();

			manager = new cloddy_CloddyManager(description);
			manager->SetLicence("Data/Cloddy/Licence/licence.dat");
			manager->Initialize();

			datasetElevation = new cloddy_CloddyLocalDataset(fileName.c_str(), true, cloddy_CloddyDatasetConverterType::E16C24);

			//datasetColor = new cloddy_CloddyLocalDataset("Data/Cloddy/Datasets/mars.like.planet.c24.cube.dat", true, cloddy_CloddyDatasetConverterType::C24);
			//datasetElevation = new cloddy_CloddyLocalDataset("Data/Cloddy/Datasets/mars.like.planet.e16.cube.dat", true, cloddy_CloddyDatasetConverterType::E16);
			//datasetDetail = new cloddy_CloddyLocalDataset("Data/Cloddy/Datasets/mars.like.planet.c32.cube.dat", true, cloddy_CloddyDatasetConverterType::C32);

			//heightmap = new TikiHeightmap(8192 + 1);
			//heightmap->SetColor(datasetColor->GetHeightmap());
			//heightmap->SetDetail(datasetDetail->GetHeightmap());
			//heightmap->SetElevation(datasetElevation->GetHeightmap());

			terrainDescription = new cloddy_CloddyRectangularTerrainDescription();
			terrainDescription->SetLightCount(1);
			terrainDescription->SetElevation(32);
			terrainDescription->SetHeightmap(datasetElevation->GetHeightmap()->Scale(scale + 1));
			terrainDescription->SetWidth((float)size);
			terrainDescription->SetHeight((float)size);
			//terrainDescription->set

			terrain = manager->CreateTerrain(terrainDescription);			
			terrain->SetTolerance(0.05f);
		}
		#pragma endregion

		#pragma region Member
		Material* TerrainRenderer::GetMaterial()
		{
			return material;
		}

		void TerrainRenderer::SetMaterial(Material* mat)
		{
			SafeRelease(&material);
			SafeAddRef(mat, &material);

			if (this->GetReady())
			{
				UInt32 tmp;
				D3D11_INPUT_ELEMENT_DESC layoutDescription[] =
				{
					{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D10_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
					{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, D3D10_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
					{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D10_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
					{ "COLOR",    0, DXGI_FORMAT_R8G8B8A8_UNORM,  0, D3D10_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				};

				Shader* shader = (Shader*)material->GetShader();
				shader->CreateLayout(layoutDescription, 4, &layout, &tmp);
			}
		}

		float TerrainRenderer::SampleHeight(const Vector3& position)
		{
			Vec3F asd = Vec3F((float*)position.arr);
			asd.Y = 10000.0f;

			return terrain->GetAltitude(asd, 0);
		}

		bool TerrainRenderer::GetReady()
		{
			return (material != 0);
		}
		#pragma endregion

		#pragma region Member - Collision
		void TerrainRenderer::UpdateCollider(ITriangleMeshCollider* collider, List<GameObject*>* poi)
		{
			if (collisionIndexBuffer == 0)
			{
				collisionIndexBuffer = new TerrainIndexBuffer(225000);
			}

			if (collisionVertexBuffer == 0)
			{
				collisionVertexBuffer = new TerrainVertexBuffer(75000);
			}

			while (collisionRegions < poi->Count())
			{
				terrain->AddCollisionRegion(cloddy_Vec::To3D(Vec3F::Zero), 0.5f);
				collisionRegions++;
			}
			
			UInt32 i = 0;
			while (i < poi->Count())
			{
				Vector3 pos = poi->Get(i)->PRS.GPosition();
				terrain->UpdateCollisionRegion(i, cloddy_Vec::To3D(cloddy_Vec3F(pos.arr)), 10.0f);
				i++;
			}
			
			CloddyCollisionMeshInfo info = terrain->GenerateCollisionMesh(collisionVertexBuffer, collisionIndexBuffer, false, 0.5f);

			collisionIndexBuffer->indexCount = (info.GetIndexCount() * 3) - 6;

			collider->SetMeshData(
				collisionIndexBuffer->GetDataList(),
				(info.GetIndexCount() * 3) - 6,
				collisionVertexBuffer->GetData(),
				info.GetVertexCount()
			);
		}
		#pragma endregion

		#pragma region Member - Draw/Update
		void TerrainRenderer::Draw(const DrawArgs& args)
		{
			if (!this->GetReady()) return;

			material->UpdateDrawArgs(args, gameObject);
			material->Apply();

			DllMain::Context->IASetInputLayout(layout);

			Matrix world;
			gameObject->PRS.FillWorldMatrix(&world);

			Light* light = (args.Lights.MainLightIndex >= 0 ? args.Lights.SceneLights->Get(args.Lights.MainLightIndex) : 0);

			Vector3 cameraPos = args.CurrentCamera->GetGameObject()->PRS.GPosition();

			//terrain->UpdateCollisionRegion(0, cloddy_Vec::To3D(cloddy_Vec3F(cameraPos.arr)), 1.5f);

			manager->BeginTriangulation();
			terrain->SetTransform(cloddy_Mat4F(world.n));
			terrain->SetCameraPosition(cloddy_Vec3F(cameraPos.arr));

			if (light)
			{
				terrain->SetLight(0, cloddy_Vec3F(light->GetGameObject()->PRS.GetForward().arr), toCloddyColor(light->GetColor()));
				terrain->EnableLight(0);
			}
			else
			{
				terrain->DisableLight(0);
			}

			terrain->Triangulate(cloddy_Mat4F(args.CurrentCamera->GetViewMatrix()->n), cloddy_Mat4F(args.CurrentCamera->GetProjectionMatrix()->n));
			manager->EndTriangulation();

			//if (collisionIndexBuffer != 0 && collisionIndexBuffer->indexCount != 0)
			//{
			//	DllMain::Context->IASetIndexBuffer(collisionIndexBuffer->indexBuffer->GetBuffer(), DXGI_FORMAT_R32_UINT, 0);

			//	UInt32 offset = 0;
			//	UInt32 stride = sizeof(CloddyVertex);
			//	ID3D11Buffer* buffer = collisionVertexBuffer->vertexBuffer->GetBuffer();

			//	DllMain::Context->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);
			//	DllMain::Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

			//	DllMain::Context->DrawIndexed(collisionIndexBuffer->indexCount, 0, 0);
			//}
		}

		void TerrainRenderer::Update(const UpdateArgs& args)
		{
			manager->Update(70.0f, engine->graphics->GetViewPort()->Height);
		}
		#pragma endregion

		#pragma region Private Member
		CodeX::int32 TerrainRenderer::toCloddyColor(Color c)
		{
			CodeX::int32 a = (int)(c.A * 255.0f);
			CodeX::int32 r = (int)(c.R * 255.0f);
			CodeX::int32 g = (int)(c.G * 255.0f);
			CodeX::int32 b = (int)(c.B * 255.0f);

			return Cloddy::API::Util::Colors::Color::FromRGB(a, r, g ,b);
		}
		#pragma endregion
	}
}
