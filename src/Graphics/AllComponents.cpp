
#include "Graphics/MeshRenderer.h"
#include "Graphics/ParticleRenderer.h"
#include "Graphics/TerrainRenderer.h"

#include "Graphics/DllMain.h"
#include "Graphics/GraphicsModule.h"

#include "Core/GameObject.h"
#include "Core/Camera.h"
#include "Core/IContentManager.h"

namespace TikiEngine
{
	namespace Components
	{
		#pragma region  MeshRenderer
		#pragma region Class
		MeshRenderer::MeshRenderer(Engine* engine, GameObject* gameObject)
			: IMeshRenderer(engine, gameObject), mesh(0), material(0), decl(0), indexBuffer(0), vertexBuffer(0)
		{
		}

		MeshRenderer::~MeshRenderer()
		{
			SafeRelease(&mesh);
			SafeRelease(&material);

			SafeRelease(&decl);
			SafeRelease(&indexBuffer);
			SafeRelease(&vertexBuffer);
		}
		#pragma endregion

		#pragma region Member
		bool MeshRenderer::GetReady()
		{
			return (mesh != 0 && mesh->GetReady()) && (material != 0 && material->GetReady());
		}
		#pragma endregion

		#pragma region Member - Get/Set
		Mesh* MeshRenderer::GetMesh()
		{
			return mesh;
		}

		Material* MeshRenderer::GetMaterial()
		{
			return material;
		}

		void MeshRenderer::SetMesh(Mesh* mesh)
		{
			SafeRelease(&this->mesh);
			SafeAddRef(mesh, &this->mesh);

			updateData(true, false);
		}

		void MeshRenderer::SetMaterial(Material* material)
		{
			SafeRelease(&this->material);
			SafeAddRef(material, &this->material);

			updateData(false, true);
		}
		#pragma endregion

		#pragma region Member - Draw/Update
		void MeshRenderer::Draw(const DrawArgs& args)
		{			
			if (!this->GetReady()) return;

			material->UpdateDrawArgs(args, gameObject);

			vertexBuffer->Apply();

			if (indexBuffer != 0)
			{
				indexBuffer->Apply();
			}

			DllMain::Context->IASetPrimitiveTopology(
				(D3D11_PRIMITIVE_TOPOLOGY)mesh->GetPrimitiveTopology()
			);

			decl->Apply();
			material->Apply();

			if (indexBuffer != 0)
			{
				DllMain::Context->DrawIndexed(
					indexBuffer->GetElementCount(),
					0,
					0
				);
			}
			else
			{
				DllMain::Context->Draw(
					vertexBuffer->GetElementCount(),
					0
				);
			}
		}

		void MeshRenderer::Update(const UpdateArgs& args)
		{			
			//if (!this->GetReady()) return;
		}
		#pragma endregion

		#pragma region Private Member
		void MeshRenderer::updateData(bool udMesh, bool udMaterial)
		{
			if (!this->GetReady()) return;

			SafeRelease(&decl);

			decl = new VertexDeclaration(
				engine,
				material->GetShader(),
				mesh->GetVertexDeclaration()->GetInternalData(),
				mesh->GetVertexDeclaration()->Count()
			);

			if (udMesh)
			{
				SafeRelease(&indexBuffer);
				SafeRelease(&vertexBuffer);

				UInt32 lenCount;
				void* vertexData = 0;
				mesh->GetVertexData(&vertexData, &lenCount);

				vertexBuffer = new StaticBuffer<D3D11_BIND_VERTEX_BUFFER>(
					engine,
					decl->GetElementSize(),
					lenCount / decl->GetElementSize(),
					vertexData
				);

				UInt32* indexData;
				mesh->GetIndexData(&indexData, &lenCount);

				if (lenCount != 0)
				{
					indexBuffer = new StaticBuffer<D3D11_BIND_INDEX_BUFFER>(
						engine,
						sizeof(UInt32),
						lenCount,
						indexData
					);
				}
			}
		}
		#pragma endregion		
		#pragma endregion

		#pragma region ParticleRenderer
		#pragma region Class
		ParticleRenderer::ParticleRenderer(Engine* engine, GameObject* gameObject)
			: IParticleRenderer(engine, gameObject), shader(0), texture(0), behavior(0)
		{
			shader = engine->content->LoadShader(L"os_particle");
			shader->AddRef();

			decl = new VertexDeclaration(engine, shader, ParticleVertex::Declaration, ParticleVertex::DeclarationCount);
			vertexBuffer = BPoint<DynamicBuffer<ParticleVertex, D3D11_BIND_VERTEX_BUFFER>>(
				[=](){ return new DynamicBuffer<ParticleVertex, D3D11_BIND_VERTEX_BUFFER>(engine); }
			);
		}

		ParticleRenderer::~ParticleRenderer()
		{
			SafeRelease(&decl);
			SafeRelease(&shader);
			SafeRelease(&texture);
			SafeRelease(&behavior);
		}
		#pragma endregion

		#pragma region Member - Get/Set
		bool ParticleRenderer::GetReady()
		{
			return (texture != 0) && (behavior != 0);
		}

		ITexture* ParticleRenderer::GetTexture()
		{
			return texture;
		}

		void ParticleRenderer::SetTexture(ITexture* texture)
		{
			SafeRelease(&this->texture);
			SafeAddRef(texture, &this->texture);

			if (texture)
			{
				shader->SetTexture("tex", texture);
			}
		}

		ParticleEffect* ParticleRenderer::GetParticleEffect()
		{
			return behavior;
		}

		void ParticleRenderer::SetParticleEffect(ParticleEffect* behavior)
		{
			SafeRelease(&this->behavior);
			SafeAddRef(behavior, &this->behavior);

			if (behavior != 0)
			{
				shader->SelectSubByIndex(
					behavior->GRenderType()
					);
			}
		}
		#pragma endregion

		#pragma region Member - Draw
		void ParticleRenderer::Draw(const DrawArgs& args)
		{
			DllMain::ModuleGraphics->SetStateAlphaBlend(true);
			DllMain::ModuleGraphics->SetStateDepthEnabled(false);

			decl->Apply();

			UInt32 stride = sizeof(ParticleVertex);
			UInt32 offset = 0;
			ID3D11Buffer* buffer = vertexBuffer->GetBuffer();

			switch (behavior->GRenderType())
			{
			case PRT_PointList:
				DllMain::Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
				break;
			case PRT_LineList:
				DllMain::Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
				break;
			case PRT_LineStrip:
				DllMain::Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
				break;
			}

			DllMain::Context->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);

			shader->Apply();
			shader->ApplyVars(gameObject, 0);

			DllMain::Context->Draw(behavior->GParticleUsed(), 0);

			DllMain::ModuleGraphics->SetStateDepthEnabled(true);
			DllMain::ModuleGraphics->SetStateAlphaBlend(false);
		}
		#pragma endregion

		#pragma region Member - Update
		void ParticleRenderer::Update(const UpdateArgs& args)
		{
			if (!this->GetReady()) return;

			behavior->Update(args);

			int count = behavior->GParticleUsed();
			const Particle* particles = behavior->GParticles();
			ParticleVertex* vertices = vertexBuffer->Map(count);

			int i = 0;
			while (i < count)
			{
				memcpy(&vertices[i], &particles[i], sizeof(ParticleVertex));

				i++;
			}

			vertexBuffer->Unmap();
		}
		#pragma endregion
		#pragma endregion

		#pragma region TerrainRenderer
		using namespace Cloddy::API;
		using namespace Cloddy::API::MeshVisitors;
		using namespace Cloddy::Core::Math::Vectors;

		#pragma region Class
		TerrainRenderer::TerrainRenderer(Engine* engine, GameObject* gameObject)
			: ITerrainRenderer(engine, gameObject), material(0), collisionIndexBuffer(0), collisionVertexBuffer(0),
			  collisionRegions(0), layout(0)
		{
		}

		TerrainRenderer::~TerrainRenderer()
		{
			SafeDelete(&collisionIndexBuffer);
			SafeDelete(&collisionVertexBuffer);
			SafeRelease(&material);
			SafeRelease(&layout);

			terrain = 0;

			if (manager != 0)
			{
				manager->Shutdown();
				manager = 0;
			}

			vertexFormat = 0;

			indexBuffer = 0;
			vertexBuffer = 0;

			callback = 0;

			terrainDescription = 0;

			datasetElevation = 0;
		}
		#pragma endregion

		#pragma region Member - Load
		void TerrainRenderer::LoadTerrain(string fileName, int scale, int size, float elevation)
		{
			this->size = size;
			this->scale = scale;
			this->elevation = elevation;

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
			terrainDescription->SetElevation(elevation);
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
		void TerrainRenderer::UpdateCollider(ITriangleMeshCollider* collider, List<Vector3>* poi)
		{
			if (collisionIndexBuffer == 0)
			{
				collisionIndexBuffer = new TerrainIndexBuffer(poi->Count() * 1000);
			}

			if (collisionVertexBuffer == 0)
			{
				collisionVertexBuffer = new TerrainVertexBuffer(poi->Count() * 500);
			}

			while (collisionRegions < poi->Count())
			{
				terrain->AddCollisionRegion(cloddy_Vec::To3D(Vec3F::Zero), 0.5f);
				collisionRegions++;
			}

			UInt32 i = 0;
			while (i < poi->Count())
			{
				terrain->UpdateCollisionRegion(i, cloddy_Vec::To3D(cloddy_Vec3F(poi->Get(i).arr)), 10.0f);
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
		#pragma endregion
	}
}