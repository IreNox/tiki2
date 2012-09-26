
#include "Graphics/TerrainRenderer.h"

#include "Core/IGraphics.h"
#include "Core/GameObject.h"
#include "Core/Camera.h"

namespace TikiEngine
{
	namespace Components
	{
		TerrainRenderer::TerrainRenderer(Engine* engine, GameObject* gameObject)
			: ITerrainRenderer(engine, gameObject)
		{
			int size = (engine->graphics->GetViewPort()->Width * engine->graphics->GetViewPort()->Height) / 2;

			vertexFormat = cloddy_VertexFormat::P3F()->Append(cloddy_VertexFormat::N3F())->Append(cloddy_VertexFormat::C1I(cloddy_ColorFormat_RGBA))->Append(cloddy_VertexFormat::X4F_12());

			vertexBuffer = new cloddy_VertexBuffer(engine->graphics->GetDevice(), size, vertexFormat->GetVertexSize());
			indexBuffer = new cloddy_IndexBuffer(engine->graphics->GetDevice(), size);

			callback = new cloddy_TriangulationCallback(engine->graphics->GetDevice(), vertexBuffer, indexBuffer);

			description = cloddy_CloddyDescription();
			description.SetVertexBuffer(vertexBuffer);
			description.SetIndexBuffer(indexBuffer);
			description.SetVertexFormat(vertexFormat);
			description.SetTriangulationCallback(callback);
			description.EnableLogging();

			manager = new cloddy_CloddyManager(&description);
			manager->SetLicence("Data/Cloddy/Licence/licence.dat");
			manager->Initialize();

			datasetColor = new cloddy_CloddyLocalDataset("Data/Cloddy/Datasets/mars.like.planet.c24.cube.dat", true, cloddy_CloddyDatasetConverterType::C24);
			datasetElevation = new cloddy_CloddyLocalDataset("Data/Cloddy/Datasets/mars.like.planet.e16.cube.dat", true, cloddy_CloddyDatasetConverterType::E16);
			datasetDetail = new cloddy_CloddyLocalDataset("Data/Cloddy/Datasets/mars.like.planet.c32.cube.dat", true, cloddy_CloddyDatasetConverterType::X32);

			heightmap = new TikiHeightmap(8192 + 1);
			heightmap->SetColor(datasetColor->GetHeightmap());
			heightmap->SetDetail(datasetDetail->GetHeightmap());
			heightmap->SetElevation(datasetElevation->GetHeightmap());

			terrainDescription = cloddy_CloddySphericalTerrainDescription();
			terrainDescription.SetLightCount(1);
			terrainDescription.SetElevation(32);
			terrainDescription.SetHeightmap(heightmap);

			terrain = manager->CreateTerrain(&terrainDescription);
		}

		TerrainRenderer::~TerrainRenderer()
		{
		}

		void TerrainRenderer::Draw(const DrawArgs& args)
		{
			Matrix world;
			gameObject->PRS.FillWorldMatrix(&world);

			Vector3 cameraPos = args.CurrentCamera->GetGameObject()->PRS.Position;
			Vector3 lightDirection = args.AllLights->Get(0)->GetGameObject()->PRS.GetForward();

			return;

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

		bool TerrainRenderer::GetReady()
		{
			return true;
		}
	}
}