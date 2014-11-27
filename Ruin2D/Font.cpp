#include "Font.h"

using namespace std;
using namespace glm;
using namespace Ruin2D;

FT_Library Font::FreeType;
FT_Face Font::Face;
bool Font::FreeTypeInitialized = false;

Font Font::Load(const string &filepath)
{
	if (!FreeTypeInitialized)
	{
		InitializeFreeType();
	}

	Font font;
	font.ConstructFontTexture(filepath);

	return font;
}

void Font::InitializeFreeType()
{
	FT_Error error;

	error = FT_Init_FreeType(&FreeType);
	Assert(!error, "Failed to initialize the freetype library.");

	FreeTypeInitialized = true;
}

void Font::ConstructFontTexture(const string &filepath)
{
	FT_Error error;
	error = FT_New_Face(FreeType, filepath.c_str(), 0, &Face);
	Assert(error != (FT_Error)FT_Err_Unknown_File_Format, "FreeType doesn't recognize the supplied error format.");
	Assert(!error, "FreeType failed to load the font!");
	FT_Set_Pixel_Sizes(Face, 0, 32);

	unsigned char* atlas;
	atlas = new unsigned char[AtlasSize * AtlasSize];
	memset(atlas, 0, AtlasSize * AtlasSize);

	for (int i = 32; i < 128; ++i)
		GenerateGlyph((char)i, atlas);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glActiveTexture(GL_TEXTURE10);
	glGenTextures(10, &_fontTexture);
	glBindTexture(GL_TEXTURE_2D, _fontTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, AtlasSize, AtlasSize, 0, GL_RED, GL_UNSIGNED_BYTE, atlas);
	//glTexStorage2D(GL_TEXTURE_2D, GL_R8, 3, AtlasSize, AtlasSize);
	//glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, AtlasSize, AtlasSize, GL_RED, GL_UNSIGNED_BYTE, atlas);

	if (atlas) delete[] atlas;
	atlas = nullptr;
}

void Font::GenerateGlyph(char c, unsigned char* &atlas)
{
	FT_Error error;

	int px = (c % 16) * 32;
	int py = ((int)glm::floor((float)c / (float)16) * 32) * AtlasSize;

	FT_UInt charIndex = FT_Get_Char_Index(Face, c);
	error = FT_Load_Glyph(Face, charIndex, 0);
	Assert(!error, "Don't know.");
	error = FT_Render_Glyph(Face->glyph, FT_RENDER_MODE_NORMAL);
	Assert(!error, "Don't know.");

	_charOffsets[c].x = Face->glyph->advance.x >> 6;
	_charOffsets[c].y = Face->glyph->bitmap_top;

	FT_GlyphSlot slot = Face->glyph;

	int height = abs(slot->bitmap.rows);
	int width = abs(slot->bitmap.width);

	for (int y = 0; py + (y * AtlasSize) < py + (height * AtlasSize); ++y) {
		for (int x = 0; px + x < px + width; ++x) {
			atlas[py + (y * AtlasSize) + px + x] =
				(y >= height || x >= width ?
				0 :
				slot->bitmap.buffer[y * width + x]);
		}
	}
}

vec2 Font::GetCharacterOffset(char c) const
{
	return _charOffsets[c];
}

void Font::DrawString(const string &str, const vec2 &position)
{

}