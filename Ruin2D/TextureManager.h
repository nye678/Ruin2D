#ifndef __RUIN2D_TEXTUREMANAGER_H_
#define __RUIN2D_TEXTUREMANAGER_H_

#include <memory>
#include <string>
#include <GL3\gl3w.h>
#include <libpng\png.h>
#include "Assert.h"

namespace Ruin2D
{
	struct TextureInfo
	{
		int width, height;

		GLuint handle;
		GLint unit;
	};

	class TextureManager
	{	
	private:
		static GLint GLMaxTextureUnits;
		static GLint GLMaxTextureArrayLayers;
		static GLint GLMaxTextureSize;

		TextureInfo* _activeTextures;
		int _numTextures;

	public:
		TextureInfo LoadTexture(const std::string &filepath);


		TextureManager();
		TextureManager(const TextureManager &) = delete;
		TextureManager &operator= (const TextureManager &) = delete;
	private:
		void CreateTexture(unsigned char* data, TextureInfo &info);

	};
}

#endif