#include "Renderer.h"

#include "Buffer/VertexArray.h"
#include "Buffer/IndexBuffer.h"
#include <glad/gl.h>

void Renderer::Clear()
{
	//glClearColor(1, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Draw(const VertexArray& Va, const IndexBuffer& Ib)
{
	Va.Bind();
	Ib.Bind();

	glDrawElements(Va.GetType(), Ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}
