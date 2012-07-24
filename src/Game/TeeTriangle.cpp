
#include "TeeTriangle.h"

#include "Core\Engine.h"

using namespace TikiEngine::Vertices;

const char* codeVS = 
    "void VS( in float4 posIn : POSITION, out float4 posOut : SV_Position )\n"
    "{\n"
    "    posOut = posIn;\n"
    "}\n";

const char* codePS = 
    "void PS( out float4 colorOut : SV_Target )\n"
    "{\n"
    "    colorOut = float4( 1.0f, 1.0f, 0.0f, 1.0f );\n"
    "}\n";

TeeTriangle::TeeTriangle(Engine* engine)
	: Element(engine)
{
    SimpleVertex vertices[] =
    {
        0.0f, 0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,
        -0.5f, -0.5f, 0.5f,
    };

    D3D11_INPUT_ELEMENT_DESC elements[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };

	//engine->graphics->CompileShaderVS(
	//	codeVS,
	//	elements,
	//	_countof(elements),
	//	&shaderVS,
	//	&inputLayout
	//);
	//shaderPS = engine->graphics->CompileShaderPS(codePS);

	//vertexBuffer = engine->graphics->CreateVertexBuffer(&vertices, sizeof(vertices));

    UINT offset = 0;
    UINT stride = sizeof(SimpleVertex);
	context = engine->graphics->GetDeviceContext();

	context->IASetInputLayout(inputLayout);
    context->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
    context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	context->VSSetShader(shaderVS, NULL, 0 );
	context->PSSetShader(shaderPS, NULL, 0 );
}

TeeTriangle::~TeeTriangle()
{
}

void TeeTriangle::Draw(double gameTime, double elapsedTime)
{
	context->Draw(3, 0);
}

void TeeTriangle::Update(double gameTime, double elapsedTime)
{

}

void TeeTriangle::Dispose()
{
	vertexBuffer->Release();
	vertexBuffer = NULL;

	shaderVS->Release();
	shaderVS = NULL;

	shaderPS->Release();
	shaderPS = NULL;
}