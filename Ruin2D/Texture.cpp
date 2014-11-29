#include "Texture.h"
#include "Assert.h"

using namespace std;
using namespace Ruin2D;

TextureManager* Texture::Manager = nullptr;

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

void Texture::SetManager(TextureManager* manager)
{
	Manager = manager;
}

Texture Texture::Load(const std::string &filepath)
{
	auto texture = Texture();

	texture._filepath = filepath;

	Assert_NotNull(Manager, "No texture manager has been set for the texture class.");
	texture._info = Manager->LoadTexture(filepath);

	return texture;
}
