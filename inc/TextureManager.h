#ifndef __RUIN2D_TEXTUREMANAGER_H_
#define __RUIN2D_TEXTUREMANAGER_H_

#include <string>
#include <GL\gl3w.h>

namespace Ruin2D
{
	// Basic info for a texture.
	struct TextureInfo
	{
		int width, height;

		GLuint handle;
		GLint unit;
	};

	/* TextureManager Class */
	/* Manager class for textures. Each texture is loaded directed into
	   gpu memory. */
	class TextureManager
	{	
	private:
		static GLint GLMaxTextureUnits;
		static GLint GLMaxTextureArrayLayers;
		static GLint GLMaxTextureSize;

		TextureInfo* _activeTextures;
		int _numTextures;

	public:
		/* Loads a texture into gpu memory. */
		TextureInfo LoadTexture(const std::string &filepath);

	private:
		/* Creates a new texture in gpu memory. */
		void CreateTexture(unsigned char* data, TextureInfo &info);

	public:
		TextureManager();
		TextureManager(const TextureManager &) = delete;
		TextureManager &operator= (const TextureManager &) = delete;
	};
}

#endif