
#include "Graphics/MeshRenderer.h"
#include "Graphics/ParticleRenderer.h"
#include "Graphics/TerrainRenderer.h"

#include "Graphics/DllMain.h"
#include "Graphics/DXGraphicsModule.h"

#include "Core/GameObject.h"
#include "Core/Camera.h"
#include "Core/IContentManager.h"
#include "Graphics/Texture.h"

#include "Core/FileStream.h"

#include <assert.h>

namespace TikiEngine
{
	struct TerrainVertex
	{
		Single Position[ 3u ];
		Single Normal[ 3u ];
		Single Color[ 4u ];

		static UInt32 DeclarationCount;
		static InputElement Declaration[ 3 ];
	};

	UInt32 TerrainVertex::DeclarationCount = 3u;
	InputElement TerrainVertex::Declaration[ 3 ] =
	{
		InputElement( IST_Position, 0, IEF_Float, 3 ),
		InputElement( IST_Normal, 0, IEF_Float, 3 ),
		InputElement( IST_Color, 0, IEF_Float, 4 )
	};

	namespace Components
	{
		#pragma region  MeshRenderer
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
		#pragma endregion

		#pragma region ParticleRenderer
		#pragma region Class
		ParticleRenderer::ParticleRenderer(Engine* engine, GameObject* gameObject)
			: IParticleRenderer(engine, gameObject), shader(0), texture(0), behavior(0)
		{
			shader = engine->content->LoadShader(L"os_particle");
			shader->AddRef();

			decl = TIKI_NEW VertexDeclaration(engine, shader, ParticleVertex::Declaration, ParticleVertex::DeclarationCount);
			vertexBuffer = TIKI_NEW DynamicBuffer<ParticleVertex, TIKI_VERTEX_BUFFER>(engine);
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
		#pragma region Class
		TerrainRenderer::TerrainRenderer(Engine* engine, GameObject* gameObject)
			: ITerrainRenderer( engine, gameObject ), material( 0 ), useCloddy( false ), m_pVertexBuffer( nullptr ), m_pVertexData( nullptr ), m_vertexCount( 0 )
		{
		}

		TerrainRenderer::~TerrainRenderer()
		{
			SafeRelease(&m_pVertexBuffer);
			SafeRelease(&m_pIndexBuffer);
			SafeRelease(&material);
			SafeRelease(&m_pDeclaration);
			SafeRelease( &m_pHeightTexture );
			SafeRelease( &m_pHeightD3dTexture );

			SafeDelete( &m_pHeightData );
			SafeDelete( &m_pFinalHeightData );
			SafeDelete( &m_pVertexData );
			SafeDelete( &m_pIndexData );
		}
		#pragma endregion

		#pragma region Member - Load
		struct TerrainInitializationData
		{
			UInt32		width;
			UInt32		height;
		};

		void TerrainRenderer::LoadTerrain(string fileName, int scale, int size, float elevation, bool useCloddy )
		{
			this->size = size;
			this->scale = scale;
			this->elevation = elevation;
			this->fileName = fileName;

			this->useCloddy = useCloddy;

			if (useCloddy)
			{
				IO::FileStream stream( StringAtoW( fileName ), IO::FM_Read );

				TerrainInitializationData initData;
				stream.Read( &initData, 0u, sizeof(initData) );

				m_width = initData.width;
				m_height = initData.height;

				m_resWidth = m_width / 4u;
				m_resHeight = m_height / 4u;
			
				m_vertexCount = m_resWidth * m_resHeight;
				m_pVertexData = TIKI_NEW TerrainVertex[ m_vertexCount ];

				const UInt32 pixelCount = m_width * m_height;
				m_pHeightData = TIKI_NEW float[ pixelCount ];
				m_pFinalHeightData = TIKI_NEW float[ pixelCount ];
				
				stream.Read( m_pHeightData, 0u, sizeof(float)* pixelCount );

				stream.Close();

				const float halfWidth = size / -2.0f;
				const float halfHeight = size / -2.0f;
				const float cellWidth = (float)size / m_resWidth;
				const float cellHeight = (float)size / m_resHeight;
				for (int i = 0u; i < m_vertexCount; ++i)
				{
					const int x = i % m_resWidth;
					const int y = i / m_resWidth;

					TerrainVertex& vertex = m_pVertexData[ i ];

					vertex.Position[ 0u ] = halfWidth + x * cellWidth;
					vertex.Position[ 1u ] = 0.0f;
					vertex.Position[ 2u ] = halfHeight + y * cellHeight;

					vertex.Normal[ 0u ] = 0.0f;
					vertex.Normal[ 1u ] = 1.0f;
					vertex.Normal[ 2u ] = 0.0f;

					vertex.Color[ 0u ] = 1.0f;
					vertex.Color[ 1u ] = 0.0f;
					vertex.Color[ 2u ] = 0.0f;
					vertex.Color[ 3u ] = 0.0f;
				}

				m_indexCount = (m_resWidth - 1u) * (m_resHeight - 1u) * 6u;
				m_pIndexData = TIKI_NEW UInt32[ m_indexCount ];

				int i = 0u;
				for ( int y = 0u; y < m_resHeight - 1u; ++y )
				{
					for ( int x = 0u; x < m_resWidth - 1u; ++x )
					{
						m_pIndexData[ i++ ] = ((y + 1) * m_resWidth) + x;
						m_pIndexData[ i++ ] = (y * m_resWidth) + x;
						m_pIndexData[ i++ ] = ((y + 1) * m_resWidth) + (x + 1);
						m_pIndexData[ i++ ] = (y * m_resWidth) + x;
						m_pIndexData[ i++ ] = ((y + 1) * m_resWidth) + (x + 1);
						m_pIndexData[ i++ ] = (y * m_resWidth) + (x + 1);
					}
				}
				//assert( i == m_indexCount );
				m_indexCount = i;

				m_pVertexBuffer = TIKI_NEW StaticBuffer< TIKI_VERTEX_BUFFER >( engine, sizeof(TerrainVertex), m_vertexCount, m_pVertexData );
				m_pIndexBuffer = TIKI_NEW StaticBuffer< TIKI_INDEX_BUFFER >( engine, sizeof(UInt32), m_indexCount, m_pIndexData );

				for (int i = 0u; i < pixelCount; ++i)
				{
					m_pFinalHeightData[ i ] = m_pHeightData[ i ] * elevation;
				} 

				D3D11_TEXTURE2D_DESC texDesc;
				ZeroMemory( &texDesc, sizeof(texDesc) );

				texDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
				texDesc.Width = m_width;
				texDesc.Height = m_height;
				texDesc.Usage = D3D11_USAGE_DEFAULT;
				texDesc.SampleDesc.Count = 1u;
				texDesc.SampleDesc.Quality = 0u;
				texDesc.ArraySize = 1u;
				texDesc.MipLevels = 1u;
				texDesc.Format = DXGI_FORMAT_R32_FLOAT;

				D3D11_SUBRESOURCE_DATA texInitData;
				texInitData.pSysMem = m_pFinalHeightData;
				texInitData.SysMemPitch = sizeof(float)* m_width;
				texInitData.SysMemSlicePitch = 0u; // texInitData.SysMemPitch * m_resHeight;

				DllMain::Device->CreateTexture2D( &texDesc, &texInitData, &m_pHeightD3dTexture );

				m_pHeightTexture = TIKI_NEW Texture( engine, m_pHeightD3dTexture, true, false );
			}
		}
		#pragma endregion

		#pragma region Member
		Material* TerrainRenderer::GetMaterial()
		{
			return material;
		}

		void TerrainRenderer::SetMaterial(Material* mat)
		{
			SafeChangeRef(&this->material, mat);
			
			if ( this->GetReady() )
			{
				Shader* shader = (Shader*)material->GetShader();
				m_pDeclaration = TIKI_NEW VertexDeclaration( engine, shader, TerrainVertex::Declaration, TerrainVertex::DeclarationCount );
			}
		}

		float TerrainRenderer::SampleHeight(const Vector3& position)
		{
			float height = 0.0f;
			if ( useCloddy )
			{
				float s = (float)size;
				float w = (float)m_width;
				float h = (float)m_height;

				Vector3 pos = position + Vector3( s / 2, 0, s / 2 );
				pos = pos * (w / s);
				
				const UInt32 x = UInt32( pos.X );
				const UInt32 y = UInt32( pos.Z );

				height = m_pFinalHeightData[ y * m_width + x ];
			}

			return height;
		}

		bool TerrainRenderer::GetReady()
		{
			return (material != 0);
		}
		#pragma endregion

		#pragma region Member - Draw/Update
		void TerrainRenderer::Draw(const DrawArgs& args)
		{
			if (!this->GetReady() || args.Mode == DM_Shadows) return;
			
			material->UpdateDrawArgs(args, gameObject);
			material->Apply();

			m_pDeclaration->Apply();

			m_pIndexBuffer->Apply();
			m_pVertexBuffer->Apply();
			
			material->GetShader()->SetTexture( "TexHeight", m_pHeightTexture );

			DllMain::Context->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
			DllMain::Context->DrawIndexed( m_indexCount, 0u, 0u );
		}

		void TerrainRenderer::Update(const UpdateArgs& args)
		{
		}
		#pragma endregion
		#pragma endregion
	}
}