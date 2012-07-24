
#include "Core/Mesh.h"
#include "Core/Engine.h"

using namespace TikiEngine;

class Box : public Mesh
{
public:
	Box(Engine* engine, Shader* shader);
	~Box();
	
	void Update(const FrameArgs& args);
};