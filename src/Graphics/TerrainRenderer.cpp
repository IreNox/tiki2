
#include "Graphics/TerrainRenderer.h"

#include "Core/TypeGlobals.h"

#include "Core/IGraphics.h"
#include "Core/GameObject.h"
#include "Core/Camera.h"

#include "Graphics/DllMain.h"
#include "Graphics/GraphicsModule.h"

#include "Cloddy/Terrain.h"

namespace TikiEngine
{
	namespace Components
	{
		//Terrain* t = dynamic_cast<Terrain*>((ICloddyTerrain*)terrain);
		//MeshBuilder* builder = new MeshBuilder(100000, 100000, 300000);
		//t->ExportMesh(TerrainMesh_Collision, builder);

		using namespace Cloddy::API;
		using namespace Cloddy::API::MeshVisitors;
		using namespace Cloddy::Core::Math::Vectors;

		#pragma region Class
		TerrainRenderer::TerrainRenderer(Engine* engine, GameObject* gameObject)
			: ITerrainRenderer(engine, gameObject), material(0)
		{
		}

		TerrainRenderer::~TerrainRenderer()
		{
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
			terrainDescription->SetElevation(128);
			terrainDescription->SetHeightmap(datasetElevation->GetHeightmap()->Scale(scale + 1));
			terrainDescription->SetWidth((float)size);
			terrainDescription->SetHeight((float)size);

			terrain = manager->CreateTerrain(terrainDescription);			
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
					{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D10_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
					{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, D3D10_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
					{"NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D10_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
					{"COLOR",    0, DXGI_FORMAT_R8G8B8A8_UNORM,  0, D3D10_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
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

			Vector3 cameraPos = args.CurrentCamera->GetGameObject()->PRS.Position();

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
