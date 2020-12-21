#include "DXUT.h"
#include "Shader.h"
USING(Engine)

Shader::Shader(void)
{
}

Shader::Shader(const Shader& cp) :
	effect(cp.effect),
	errormsg(cp.errormsg)
{
	effect->AddRef();
}

Shader::~Shader(void)
{
}

void Shader::ResetDevice(void)
{
	effect->OnResetDevice();
}

void Shader::LostDevice(void)
{
	effect->OnLostDevice();
}

HRESULT Shader::CreateShader(wstring _filepath)
{
	HRESULT hr = S_OK;
	hr = D3DXCreateEffectFromFile(DEVICE, _filepath.c_str(), NULL, NULL, D3DXSHADER_DEBUG, NULL, &effect, &errormsg);
	if (FAILED(hr))
	{
		MessageBox(DXUTGetHWND(), static_cast<WCHAR*>(errormsg->GetBufferPointer()), L"Shader Create Error", MB_OK);
		hr = E_FAIL;
		return hr;
	}
	else if(errormsg != nullptr)
		MessageBox(DXUTGetHWND(), static_cast<WCHAR*>(errormsg->GetBufferPointer()), L"Shader Warning", MB_OK);

	return hr;
}

HRESULT Shader::SetupTable()
{
	D3DXMATRIX matWorld, matView, matProj;
	DEVICE->GetTransform(D3DTS_WORLD, &matWorld);
	DEVICE->GetTransform(D3DTS_VIEW, &matView);
	DEVICE->GetTransform(D3DTS_PROJECTION, &matProj);

	effect->SetValue((D3DXHANDLE)"g_matWorld", &matWorld, sizeof(D3DXMATRIX));
	effect->SetValue((D3DXHANDLE)"g_matView", &matView, sizeof(D3DXMATRIX));
	effect->SetValue((D3DXHANDLE)"g_matProj", &matProj, sizeof(D3DXMATRIX));
	return S_OK;
}

void Shader::Free(void)
{
	Safe_Release(effect);
}

Resources* Shader::Clone(void)
{
	return new Shader(*this);
}
