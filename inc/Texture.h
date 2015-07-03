#ifndef __RUIN2D_TEXTURE_H_
#define __RUIN2D_TEXTURE_H_

#include <string>
#include <GL\gl3w.h>
#include <libpng\png.h>
#include "TextureManager.h"

namespace Ruin2D
{
	/* Texture Class */
	/* Simple texture class that loads an image into the gpu memory. 
	   Only png files are currently supported. */
	class Texture
	{
	private:
		static TextureManager* Manager;

		std::string _filepath;
		TextureInfo _info;

	public:
		static void SetManager(TextureManager* manager);

		/* Load
		   Loads the texture into the gpu memory. */
		static Texture Load(const std::string &filepath);

		/* Handle
		   Gets the OpenGL handle for the texture. */
		GLuint Handle() const;

		/* Unit
		   Gets the active texture unit this texture is bound to. */
		GLint Unit() const;

		/* Width
		   Gets the width of the texture. */
		int Width() const;

		/* Height
		   Gets the height of the texture. */
		int Height() const;

		/* Filepath
		   Gets the filepath of the loaded texture. */
		const std::string &Filepath() const;
	};
}

#endif