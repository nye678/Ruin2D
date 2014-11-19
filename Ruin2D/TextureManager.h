#ifndef __RUIN2D_TEXTUREMANAGER_H_
#define __RUIN2D_TEXTUREMANAGER_H_

#include <memory>
#include <string>
#include <GL3\gl3w.h>
#include <libpng\png.h>
#include "Singleton.h"
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
		friend class Singleton<TextureManager>;
		
	private:
		static Singleton<TextureManager> Singleton;

		static GLint GLMaxTextureUnits;
		static GLint GLMaxTextureArrayLayers;
		static GLint GLMaxTextureSize;

		TextureInfo* _activeTextures;
		int _numTextures;

	public:
		static std::shared_ptr<TextureManager> Create();

		inline static std::shared_ptr<TextureManager> Get()
		{
			return Singleton.Get();
		}

		TextureInfo LoadTexture(const std::string &filepath);

	private:
		void CreateTexture(unsigned char* data, TextureInfo &info);

		TextureManager();
		TextureManager(const TextureManager &) = delete;
		TextureManager &operator= (const TextureManager &) = delete;
	};
}

#endif