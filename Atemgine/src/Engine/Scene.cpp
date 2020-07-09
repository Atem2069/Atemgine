#include "..\..\headers\Engine\Scene.h"

bool IScene::loadObject(std::string objPath)
{
	IModel* temp = new IModel;
	if (!temp->load(objPath))
	{
		delete temp;
		return false;
	}

	m_sceneObjects.push_back(temp);

	return true;
}

bool IScene::addObject(IModel* obj)
{
	m_sceneObjects.push_back(obj);
	return true;
}

bool IScene::addRenderPass(RenderPass& renderPass)
{
	if (!m_cameraUploadBuffer)
	{
		ConstantBufferUploadInfo uploadData = {};
		uploadData.rawData = (void*)&renderPass.baseCamera->getCameraMatrices();
		uploadData.sizeBytes = sizeof(CameraInfo);
		m_cameraUploadBuffer = new IConstantBuffer;
		if (!m_cameraUploadBuffer->initialize(uploadData))
		{
			m_cameraUploadBuffer->destroy();
			delete m_cameraUploadBuffer;
			return false;
		}

		m_cameraUploadBuffer->setBinding(BIND_VS, 0);
	}
	m_renderPasses.push_back(renderPass);

	DrawCall tempDrawCall = {};
	tempDrawCall.drawType = DRAWTYPE_MULTIDRAWINDEXED;
	tempDrawCall.primitiveTopology = TOPOLOGY_TRIANGLELIST;
	tempDrawCall.vertexShader = renderPass.vertexShader;
	tempDrawCall.pixelShader = renderPass.pixelShader;
	tempDrawCall.constantBuffers.insert(tempDrawCall.constantBuffers.end(), renderPass.constantBuffers.begin(), renderPass.constantBuffers.end());;
	tempDrawCall.constantBuffers.push_back(m_cameraUploadBuffer);

	m_builtDrawCalls.push_back(tempDrawCall);

	return true;
}

void IScene::destroy()
{
	for (int i = 0; i < m_sceneObjects.size(); i++)
	{
		m_sceneObjects[i]->destroy();
		delete m_sceneObjects[i];
	}
}

void IScene::render()
{
	IRenderer* rendererInstance = IRenderer::getCurrentInstance();
	if (!rendererInstance)
		return;
	for (int i = 0; i < m_renderPasses.size(); i++)
	{
		RenderPass currentRenderPass = m_renderPasses[i];
		ConstantBufferUploadInfo newCameraInfo = {};
		newCameraInfo.rawData = (void*)&currentRenderPass.baseCamera->getCameraMatrices();
		newCameraInfo.sizeBytes = sizeof(CameraInfo);

		m_cameraUploadBuffer->update(newCameraInfo);


		//now setup rendertarget
		currentRenderPass.renderTarget->setActive();
		currentRenderPass.renderTarget->clear(currentRenderPass.clearColor, 1.0f);

		DrawCall renderPassDrawCall = m_builtDrawCalls[i];

		//loop through models and draw
		for (int j = 0; j < m_sceneObjects.size(); j++)
		{
			DrawCall currentObjDrawCall = renderPassDrawCall;
			m_sceneObjects[j]->writeDrawCall(currentObjDrawCall);
			rendererInstance->draw(currentObjDrawCall);
		}
	}
}

void IScene::render(int passIndex)
{
	assert(passIndex < m_renderPasses.size());
	RenderPass currentRenderPass = m_renderPasses[passIndex];
	DrawCall renderPassDrawCall = m_builtDrawCalls[passIndex];

	ConstantBufferUploadInfo newCameraInfo = {};
	newCameraInfo.rawData = (void*)&currentRenderPass.baseCamera->getCameraMatrices();
	newCameraInfo.sizeBytes = sizeof(CameraInfo);

	m_cameraUploadBuffer->update(newCameraInfo);

	currentRenderPass.renderTarget->setActive();
	currentRenderPass.renderTarget->clear(currentRenderPass.clearColor, 1.0f);

	for (int i = 0; i < m_sceneObjects.size(); i++)
	{
		DrawCall currentObjDrawCall = renderPassDrawCall;
		m_sceneObjects[i]->writeDrawCall(currentObjDrawCall);
		IRenderer::getCurrentInstance()->draw(currentObjDrawCall);
	}
}