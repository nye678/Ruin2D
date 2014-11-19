#include "Texture.h"

using namespace std;
using namespace Ruin2D;

GLuint Texture::Handle() const
{
	return _info.handle;
}

GLint Texture::Unit() const
{
	return _info.unit;
}

int Texture::Width() const
{
	return _info.width;
}

int Texture::Height() const
{
	return _info.height;
}

const string &Texture::Filepath() const
{
	return _filepath;
}

Texture Texture::Load(const std::string &filepath)
{
	auto textureManager = TextureManager::Get();
	auto texture = Texture();

	texture._filepath = filepath;
	texture._info = textureManager->LoadTexture(filepath);

	return texture;
}
