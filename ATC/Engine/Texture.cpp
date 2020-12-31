#include "DXUT.h"
#include "Texture.h"
USING(Engine)
Texture::Texture(void)
{
}

Texture::Texture(const Texture& cp) :
	textures(cp.textures),
	texturescount(cp.texturescount)
{
	for (int i = 0; i < texturescount; ++i)
		textures[i]->AddRef();

}

Texture::~Texture(void)
{
}

HRESULT Texture::LoadTexture(wstring _filepath, const UINT& _texturecount)
{
	LPDIRECT3DTEXTURE9 texture;
	texturescount = _texturecount;
	if (_texturecount <= 1)
	{
		if(FAILED(D3DXCreateTextureFromFile(DEVICE, _filepath.c_str(), &texture)))
			return E_FAIL;
		textures.emplace_back(texture);
	}
	else
	{
		TCHAR finalfilepath[MAX_PATH] = L"";
		for (size_t i = 0; i < texturescount; ++i)
		{
			wsprintf(finalfilepath, _filepath.c_str(), i);

			if(FAILED(D3DXCreateTextureFromFile(DEVICE, finalfilepath, &texture)))
				return E_FAIL;
			
			textures.emplace_back(texture);
		}
	}
	return S_OK;
}

void Texture::RenderTexture(LPD3DXEFFECT& _effect, const UINT& _index)
{
	_effect->SetTexture((D3DXHANDLE)L"g_BaseTexture", textures[_index]);
}

void Texture::RenderTexture(const UINT& _index)
{
	if (textures.size() < _index)
		return;

	DEVICE->SetTexture(0, textures[_index]);
}

void Texture::Render(const FLOAT& dt)
{
	
}

Resources* Texture::Clone(void)
{
	return new Texture(*this);
}

void Texture::Free(void)
{
	for (int i = 0; i < texturescount; ++i)
		textures[i]->Release();
	textures.clear();
}
