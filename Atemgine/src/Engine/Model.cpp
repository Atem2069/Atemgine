#include "..\..\headers\Engine\Model.h"

bool IModel::load(std::string path)
{
	return false;
}

void IModel::destroy()
{
	vertexBuffer->destroy();
	indexBuffer->destroy();
}

void IModel::writeDrawCall(DrawCall& drawCall)
{

}