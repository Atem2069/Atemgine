#pragma once

#include "Model.h"
#include "Camera.h"
#include "..\DrawCall.h"
#include "..\Renderer.h"
#include "..\RenderTarget.h"

#include<iostream>
#include<vector>

struct RenderPass
{
	IRenderTarget* renderTarget;
	XMFLOAT4 clearColor;

	ICamera* baseCamera;
	std::vector<IConstantBuffer*> constantBuffers;

	IVertexShader* vertexShader;
	IPixelShader* pixelShader;
};


class IScene
{
public:
	bool loadObject(std::string objPath);
	bool addObject(IModel* obj);
	bool addRenderPass(RenderPass& renderPass);
	void destroy();

	void render();				//render all passes
	void render(int passIndex); //render specific pass so work can be done inbetween
private:
	std::vector<RenderPass> m_renderPasses;
	std::vector<DrawCall> m_builtDrawCalls;
	std::vector<IModel*> m_sceneObjects;
	IConstantBuffer* m_cameraUploadBuffer;
};