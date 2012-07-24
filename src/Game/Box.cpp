
#include "Box.h"

#include "Graphics/DefaultVertex.h"

Box::Box(Engine* engine, Shader* shader)
	: Mesh(engine)
{
	this->Init(
		new DefaultVertexDeclaration(
			engine,
			shader
		)
	);

	DefaultVertex vertices[] = {
		{-1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f},
		{ 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f},
		{ 1.0f,  1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f},
		{-1.0f,  1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f},
		{-1.0f, -1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f},
		{ 1.0f, -1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f},
		{ 1.0f,  1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f},
		{-1.0f,  1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f}
	};

	this->data->SetVertexData(vertices, sizeof(vertices));

	UINT indices[] = {
		0, 1, 2,
		0, 2, 3,
		4, 0, 3,
		4, 3, 7,
		1, 5, 6,
		1, 6, 2,
		3, 4, 6,
		3, 6, 7,
		4, 5, 1,
		4, 1, 0,
		5, 4, 7,
		5, 7, 6
	};

	this->data->SetIndexData(indices, sizeof(indices));
}

Box::~Box()
{

}

void Box::Update(const FrameArgs& args)
{
	float mod = (3.14159f * 2);

	this->PRS.Rotation.X = modf(this->PRS.Rotation.X + (float)args.Time.ElapsedTime, &mod);
	this->PRS.Rotation.Y = modf(this->PRS.Rotation.Y + (float)args.Time.ElapsedTime, &mod);
	this->PRS.Rotation.Z = modf(this->PRS.Rotation.Z + (float)args.Time.ElapsedTime, &mod);

	Mesh::Update(args);
}