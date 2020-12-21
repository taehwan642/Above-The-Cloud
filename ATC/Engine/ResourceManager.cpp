#include "DXUT.h"
#include "Resources.h"
#include "StaticMesh.h"
#include "Shader.h"
#include "ResourceManager.h"
USING(Engine)
HRESULT ResourceManager::AddTexture(wstring _filepath, wstring _filename, wstring _tag)
{
	return S_OK;
}

HRESULT ResourceManager::AddMesh(MeshType _meshtype, wstring _filepath, wstring _filename, wstring _tag)
{
	auto& iter = resourcegroup.find(_tag);
	if (iter != resourcegroup.end())
	{
		wstring error = _tag;
		MessageBox(DXUTGetHWND(), error.c_str(), L"중복 스태틱 메시", MB_ICONERROR | MB_OK);
		return E_FAIL;
	}

	if (_meshtype == MeshType::STATIC)
	{
		StaticMesh* staticmesh = new StaticMesh();
		if (FAILED(staticmesh->LoadMesh(_filepath, _filename)))
		{
			wstring error = _filepath + _filename;
			MessageBox(DXUTGetHWND(), error.c_str(), L"스태틱 메시 로드 FAIL", MB_ICONERROR | MB_OK);
			return E_FAIL;
		}
		resourcegroup.emplace(_tag, staticmesh);
	}
	else
	{

	}
	return S_OK;
}

HRESULT ResourceManager::AddShader(wstring _filepath, wstring _tag)
{
	Shader* shader = new Shader();
	if(FAILED(shader->CreateShader(_filepath)))
		return E_FAIL;
	resourcegroup.emplace(_tag, shader);
	return S_OK;
}

Resources* ResourceManager::LoadResource(wstring _tag)
{
	auto& iter = resourcegroup.find(_tag);
	if (iter != resourcegroup.end())
		return resourcegroup[_tag]->Clone();
	return nullptr;
}
