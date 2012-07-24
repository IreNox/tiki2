#pragma once

#include <D3D11.h>

#include "Core\Element.h"
#include "Graphics\SimpleVertex.h"

using namespace TikiEngine;
using namespace TikiEngine::Elements;

class TeeTriangle : public Element
{
public:
	TeeTriangle(Engine* engine);
	~TeeTriangle();

	void Draw(double gameTime, double elapsedTime);
	void Update(double gameTime, double elapsedTime);

	void Dispose();
private:
	ID3D11DeviceContext* context;

	ID3D11Buffer* vertexBuffer;

	ID3D11PixelShader* shaderPS;
	ID3D11VertexShader* shaderVS;

	ID3D11InputLayout* inputLayout;
};