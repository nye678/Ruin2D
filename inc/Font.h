#ifndef __RUIN2D_FONT_H_
#define __RUIN2D_FONT_H_

#include <string>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <GL\gl3w.h>
#include <glm\glm.hpp>

namespace Ruin2D
{
	/* Font Class */
	/* Represents a font resource. Fonts are loaded using freetype and a
	   texture atlas is created and loaded into gpu memory. */
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

	public:
		/* Loads a font from a font file. */
		static Font Load(const std::string &filepath);

		/* Gets the atlas offset for a character. */
		glm::vec2 GetCharacterOffset(char c) const;

		/* Draws a string at a given location on the screen. */
		void DrawString(const std::string &str, const glm::vec2 &position);

	private:
		/* Initializes the freetype library. */
		static void InitializeFreeType();

		/* Creates the font texture atlas that is loaded on the gpu. */
		void ConstructFontTexture(const std::string &filepath);

		/* Generates a glyph using freetype and copies it to the atlas. */
		void GenerateGlyph(char c, unsigned char* &atlas);
	};
}

#endif