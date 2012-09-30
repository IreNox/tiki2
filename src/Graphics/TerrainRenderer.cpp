
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
		#pragma region Class
		TerrainRenderer::TerrainRenderer(Engine* engine, GameObject* gameObject)
			: ITerrainRenderer(engine, gameObject), material(0)
		{
			int size = (engine->graphics->GetViewPort()->Width * engine->graphics->GetViewPort()->Height) / 2;

			vertexFormat = cloddy_VertexFormat::P3F()
				  ->Append(cloddy_VertexFormat::T2F(1, 1))
				  ->Append(cloddy_VertexFormat::N3F())
				  ->Append(cloddy_VertexFormat::C1I(cloddy_ColorFormat_RGBA));
				  //->Append(cloddy_VertexFormat::X4F_12());

			vertexBuffer = new cloddy_VertexBuffer(engine->graphics->GetDevice(), size, vertexFormat->GetVertexSize());
			indexBuffer = new cloddy_IndexBuffer(engine->graphics->GetDevice(), size);

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

			//datasetColor = new cloddy_CloddyLocalDataset("Data/Cloddy/Datasets/mars.like.planet.c24.cube.dat", true, cloddy_CloddyDatasetConverterType::C24);
			//datasetElevation = new cloddy_CloddyLocalDataset("Data/Cloddy/Datasets/mars.like.planet.e16.cube.dat", true, cloddy_CloddyDatasetConverterType::E16);
			datasetElevation = new cloddy_CloddyLocalDataset("Data/Cloddy/Datasets/terrain.E16C24.rect.dat", true, cloddy_CloddyDatasetConverterType::E16C24);
			//datasetDetail = new cloddy_CloddyLocalDataset("Data/Cloddy/Datasets/mars.like.planet.c32.cube.dat", true, cloddy_CloddyDatasetConverterType::C32);

			heightmap = new TikiHeightmap(8192 + 1);
			//heightmap->SetColor(datasetColor->GetHeightmap());
			//heightmap->SetDetail(datasetDetail->GetHeightmap());
			heightmap->SetElevation(datasetElevation->GetHeightmap());

			terrainDescription = new cloddy_CloddyRectangularTerrainDescription();
			terrainDescription->SetLightCount(1);
			terrainDescription->SetElevation(128);
			terrainDescription->SetHeightmap(heightmap);
			terrainDescription->SetWidth(2048.0f);
			terrainDescription->SetHeight(2048.0f);

			terrain = manager->CreateTerrain(terrainDescription);
		}

		TerrainRenderer::~TerrainRenderer()
		{
			manager->Shutdown();
			SafeRelease(&material);
			SafeRelease(&layout);
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
					{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D10_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
					{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D10_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
					{"COLOR", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, D3D10_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
				};

				Shader* shader = (Shader*)material->GetShader();
				shader->CreateLayout(layoutDescription, 4, &layout, &tmp);
			}
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

			Vector3 cameraPos = args.CurrentCamera->GetGameObject()->PRS.Position;
			Vector3 lightDirection = args.AllLights->Get(0)->GetGameObject()->PRS.GetForward();

			manager->BeginTriangulation();
			terrain->SetTransform(cloddy_Mat4F(world.n));
			terrain->SetCameraPosition(cloddy_Vec3F(cameraPos.arr));
			terrain->SetLight(0, cloddy_Vec3F(lightDirection.arr), Cloddy::API::Util::Colors::Color::White);
			terrain->EnableLight(0);
			terrain->Triangulate(cloddy_Mat4F(args.CurrentCamera->GetViewMatrix()->n), cloddy_Mat4F(args.CurrentCamera->GetProjectionMatrix()->n));
			manager->EndTriangulation();
		}

		void TerrainRenderer::Update(const UpdateArgs& args)
		{
			manager->Update(70.0f, engine->graphics->GetViewPort()->Height);
		}
		#pragma endregion
	}
}