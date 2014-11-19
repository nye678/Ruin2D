#ifndef __RUIN2D_FONT_H_
#define __RUIN2D_FONT_H_

#include <string>
#include <freetype\ft2build.h>
#include FT_FREETYPE_H

#include <GL3\gl3w.h>
#include <glm\glm.hpp>
#include "Assert.h"

namespace Ruin2D
{
	class Font
	{
	private:
		static const int AtlasSize = 512;
		static const int FontSize = 32;

		static FT_Library FreeType;
		static FT_Face Face;
		static bool FreeTypeInitialized;

		GLuint _fontTexture;
		glm::vec2 _charOffsets[128];

		static void InitializeFreeType();
		void ConstructFontTexture(const std::string &filepath);
		void GenerateGlyph(char c, unsigned char* &atlas);
	public:
		static Font Load(const std::string &filepath);

		glm::vec2 GetCharacterOffset(char c) const;

		void DrawString(const std::string &str, const glm::vec2 &position);
	};
}

#endif