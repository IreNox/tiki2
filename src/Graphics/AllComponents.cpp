
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
			if (!this->GetReady() || args.Mode == DM_Shadows) return;

			material->UpdateDrawArgs(args, gameObject);

			vertexBuffer->Apply();

			if (indexBuffer != 0)
			{
				indexBuffer->Apply();
			}

			DllMain::Context->IASetPrimitiveTopology(
				(D3D_PRIMITIVE_TOPOLOGY)mesh->GetPrimitiveTopology()
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

				vertexBuffer = new StaticBuffer<TIKI_VERTEX_BUFFER>(
					engine,
					decl->GetElementSize(),
					lenCount / decl->GetElementSize(),
					vertexData
				);

				UInt32* indexData;
				mesh->GetIndexData(&indexData, &lenCount);

				if (lenCount != 0)
				{
					indexBuffer = new StaticBuffer<TIKI_INDEX_BUFFER>(
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
			vertexBuffer = new DynamicBuffer<ParticleVertex, TIKI_VERTEX_BUFFER>(engine);
		}

		ParticleRenderer::~ParticleRenderer()
		{
			SafeRelease(&decl);
			SafeRelease(&shader);
			SafeRelease(&texture);
			SafeRelease(&behavior);
			SafeRelease(&vertexBuffer);
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
		}

		ParticleEffect* ParticleRenderer::GetParticleEffect()
		{
			return behavior;
		}

		void ParticleRenderer::SetParticleEffect(ParticleEffect* behavior)
		{
			SafeChangeRef(&this->behavior, behavior);
		}
		#pragma endregion

		#pragma region Member - Draw
		void ParticleRenderer::Draw(const DrawArgs& args)
		{
			if (args.Mode != DM_Geometry) return;

			UInt32 count = behavior->GParticleUsed();
			if (count == 0) return;

			DllMain::ModuleGraphics->SetStateAlphaBlend(BSM_Particles);
			DllMain::ModuleGraphics->SetStateDepthEnabled(false);

			decl->Apply();

			switch (behavior->GRenderType())
			{
			case PRT_PointList:
				DllMain::Context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_POINTLIST);
				break;
			case PRT_LineList:
				DllMain::Context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);
				break;
			case PRT_LineStrip:
				DllMain::Context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINESTRIP);
				break;
			}

			vertexBuffer->Apply();

			if (texture)
				shader->SetTexture("tex", texture);

			shader->SelectSubByIndex(
				behavior->GRenderType()
			);
			shader->Apply();
			shader->ApplyVars(gameObject, 0, Matrix::Identity);

			DllMain::Context->Draw(count, 0);

			DllMain::ModuleGraphics->SetStateDepthEnabled(true);
			DllMain::ModuleGraphics->SetStateAlphaBlend(BSM_Disable);
		}
		#pragma endregion

		#pragma region Member - Update
		void ParticleRenderer::Update(const UpdateArgs& args)
		{
			if (!this->GetReady()) return;

			behavior->Update(args);

			int count = behavior->GParticleUsed();
			if (count == 0) return;

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
		using namespace Cloddy::API::Geometries;

		#pragma region Class
		TerrainRenderer::TerrainRenderer(Engine* engine, GameObject* gameObject)
			: ITerrainRenderer(engine, gameObject), material(0), collisionIndexBuffer(0), collisionVertexBuffer(0),
			  collisionRegions(0), layout(0)
#if _DEBUG
			  , drawCollider(false), useCloddy(true)
#endif
		{
		}

		TerrainRenderer::~TerrainRenderer()
		{
			SafeDelete(&collisionIndexBuffer);
			SafeDelete(&collisionVertexBuffer);
			SafeRelease(&material);
			SafeRelease(&layout);

			if (terrain != 0)
			{
				terrain->Dispose();
				terrain = 0;
			}

			if (manager != 0)
			{
				manager->Shutdown();
				manager = 0;
			}

			vertexFormat = 0;

			indexBuffer = 0;
			vertexBuffer = 0;

			if (callback != 0)
			{
				callback->Dispose();
				callback = 0;
			}

			terrainDescription = 0;
		}
		#pragma endregion

		#pragma region Member - Load
		void TerrainRenderer::LoadTerrain(string fileName, int scale, int size, float elevation
#if _DEBUG
			, bool useCloddy
#endif		
		)
		{
			this->size = size;
			this->scale = scale;
			this->elevation = elevation;
			this->fileName = fileName;

#if _DEBUG
			this->useCloddy = useCloddy;

			if (useCloddy) {
#endif

			datasetSample = new cloddy_CloddyLocalDataset(fileName.c_str(), true, cloddy_CloddyDatasetConverterType::E16C24);
			heightmap = datasetSample->GetHeightmap();
				
			vertexFormat = cloddy_VertexFormat::P3F()
				->Append(cloddy_VertexFormat::T2F(1, 1))
				->Append(cloddy_VertexFormat::N3F())
				->Append(cloddy_VertexFormat::C1I(cloddy_ColorFormat_RGBA));
			//->Append(cloddy_VertexFormat::X4F_12());

			datasetDraw = new cloddy_CloddyLocalDataset(fileName.c_str(), true, cloddy_CloddyDatasetConverterType::E16C24);
			
			int size2 = (engine->graphics->GetViewPort()->Width * engine->graphics->GetViewPort()->Height);
			vertexBuffer = new cloddy_VertexBuffer(engine->graphics->GetDevice(), size2, vertexFormat->GetVertexSize());
			indexBuffer = new cloddy_IndexBuffer(engine->graphics->GetDevice(), size2 * 3);

			callback = new cloddy_TriangulationCallback(engine->graphics->GetDevice(), vertexBuffer, indexBuffer);

			description = new cloddy_CloddyDescription();
			description->SetVertexBuffer(vertexBuffer);
			description->SetIndexBuffer(indexBuffer);
			description->SetVertexFormat(vertexFormat);
			description->SetTriangulationCallback(callback);
			//description->EnableLogging();

			Stream* stream = engine->content->LoadData(L"Data/terrain/Licence/licence.dat");

			UInt32 len = (UInt32)stream->GetLength();
			Byte* data = new Byte[len];

			stream->Read(data, 0, len);
			SafeRelease(&stream);

			CodeX::Ptr<ByteBuffer> licBuffer = ByteBuffer::Raw(len);
			licBuffer->SetRawPointer(data);

			manager = new cloddy_CloddyManager(description);
			manager->SetLicence(licBuffer);
			manager->Initialize();

			delete[](data);
			
			terrainDescription = new cloddy_CloddyRectangularTerrainDescription();
			terrainDescription->SetLightCount(1);
			terrainDescription->SetElevation(elevation);
			terrainDescription->SetHeightmap(datasetDraw->GetHeightmap()->Scale(scale + 1)); // anpassen für perfekte aussehen
			terrainDescription->SetWidth((float)size);
			terrainDescription->SetHeight((float)size);
			terrainDescription->SetHandedness(Handedness_RightHanded);
			//terrainDescription->set

			terrain = manager->CreateTerrain(terrainDescription);			
			terrain->SetTolerance(2.5f);
#if _DEBUG
			}
#endif
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
#if TIKI_DX10
				D3D10_INPUT_ELEMENT_DESC layoutDescription[] =
				{
					{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D10_APPEND_ALIGNED_ELEMENT, D3D10_INPUT_PER_VERTEX_DATA, 0 },
					{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, D3D10_APPEND_ALIGNED_ELEMENT, D3D10_INPUT_PER_VERTEX_DATA, 0 },
					{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D10_APPEND_ALIGNED_ELEMENT, D3D10_INPUT_PER_VERTEX_DATA, 0 },
					{ "COLOR",    0, DXGI_FORMAT_R8G8B8A8_UNORM,  0, D3D10_APPEND_ALIGNED_ELEMENT, D3D10_INPUT_PER_VERTEX_DATA, 0 },
				};
#else
				D3D11_INPUT_ELEMENT_DESC layoutDescription[] =
				{
					{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D10_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
					{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, D3D10_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
					{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D10_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
					{ "COLOR",    0, DXGI_FORMAT_R8G8B8A8_UNORM,  0, D3D10_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				};
#endif

				Shader* shader = (Shader*)material->GetShader();
				shader->CreateLayout(layoutDescription, 4, &layout, &tmp);
			}
		}

		float TerrainRenderer::SampleHeight(const Vector3& position)
		{
			double height = 0;

#if _DEBUG
			if (useCloddy) {
#endif
			HeightmapSample sam;

			float s = (float)size;
			float w = (float)heightmap->GetWidth();
			float h = (float)heightmap->GetHeight();

			Vector3 pos = position * (w / s);
			pos = pos + Vector3(w / 2, 0, h / 2);

			heightmap->Get(
				(int32)pos.X,
				(int32)pos.Z,
				&sam
			);

			height = ((double)sam.Elevation / 1073741823) * elevation;
#if _DEBUG
			}
#endif

			return (float)height;
		}

		bool TerrainRenderer::GetReady()
		{
			return (material != 0);
		}
		#pragma endregion

		#pragma region Member - Collision
		void TerrainRenderer::UpdateCollider(IHeightFieldCollider* collider)
		{
			UInt32 i = 0;
			UInt32 w = heightmap->GetWidth() / 20;
			UInt32 h = heightmap->GetHeight() / 20;
			UInt32 c = w * h;
			
			UInt16* height = new UInt16[c];
			HeightmapSample sam;

			while (i < c)
			{
				UInt32 x = (w - (i % w)) * 20;
				UInt32 y = (i / w) * 20;

				heightmap->Get(x, y, &sam);

				height[i] = (UInt16)(((double)sam.Elevation / 1073741823) * 65536);

				i++;
			}

			float s = (float)size;

			HeightFieldDesc desc;
			desc.Columns = w;
			desc.Rows = h;
			desc.ColumnScale = s / w;
			desc.RowScale = s / h;
			desc.HeightScale = elevation;

			collider->SetCenter(Vector3(-s / 2, 0, -s / 2));
			collider->SetHeightField(height, desc);
			delete[](height);
		}
		#pragma endregion

		#pragma region Member - Draw/Update
		void TerrainRenderer::Draw(const DrawArgs& args)
		{
			if (!this->GetReady() || args.Mode == DM_Shadows) return;

			material->UpdateDrawArgs(args, gameObject);
			material->Apply();

			DllMain::Context->IASetInputLayout(layout);

			Matrix world;
			gameObject->PRS.FillWorldMatrix(&world);

			Light* light = (args.Lights.MainLightIndex >= 0 ? args.Lights.SceneLights->Get(args.Lights.MainLightIndex) : 0);

			Vector3 cameraPos = args.CurrentCamera->GetGameObject()->PRS.GPosition();

#if _DEBUG
			if (!drawCollider && useCloddy) {
#endif

			manager->BeginTriangulation();
			terrain->SetTransform(cloddy_Mat4F(world.n));
			terrain->SetCameraPosition(cloddy_Vec3F(cameraPos.arr));

			if (light)
			{
				Vector3 lightD = light->GetGameObject()->PRS.GetForward();
				//lightD.X = -lightD.X;
				lightD.Z = -lightD.Z;

				terrain->SetLight(0, cloddy_Vec3F(lightD.arr), toCloddyColor(light->GetColor()));
				terrain->EnableLight(0);
			}
			else
			{
				terrain->DisableLight(0);
			}

			terrain->Triangulate(
				cloddy_Mat4F((float*)args.CurrentCamera->GetViewMatrix().n),
				cloddy_Mat4F((float*)args.CurrentCamera->GetProjectionMatrix().n)
			);
			manager->EndTriangulation();

#if _DEBUG
			}
			else if (collisionIndexBuffer != 0 && collisionIndexBuffer->indexCount != 0 && useCloddy)
			{
				DllMain::Context->IASetIndexBuffer(collisionIndexBuffer->indexBuffer->GetBuffer(), DXGI_FORMAT_R32_UINT, 0);

				UInt32 offset = 0;
				UInt32 stride = sizeof(CloddyVertex);
				TDX_Buffer* buffer = collisionVertexBuffer->vertexBuffer->GetBuffer();

				DllMain::Context->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);
				DllMain::Context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

				DllMain::Context->DrawIndexed(collisionIndexBuffer->indexCount, 0, 0);
			}
#endif
		}

		void TerrainRenderer::Update(const UpdateArgs& args)
		{
#if _DEBUG
			if (useCloddy) {
#endif
			manager->Update(70.0f, engine->graphics->GetViewPort()->Height);
#if _DEBUG
			}
#endif
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