#include "TextureManager.h"

#include <libpng\png.h>
#include "Assert.h"

using namespace std;
using namespace Ruin2D;

GLint TextureManager::GLMaxTextureArrayLayers = 0;
GLint TextureManager::GLMaxTextureSize = 0;
GLint TextureManager::GLMaxTextureUnits = 0;

TextureManager::TextureManager()
	: _activeTextures(nullptr), _numTextures(0)
{
	glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &GLMaxTextureUnits);
	glGetIntegerv(GL_MAX_ARRAY_TEXTURE_LAYERS, &GLMaxTextureArrayLayers);
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &GLMaxTextureSize);

	_activeTextures = new TextureInfo[GLMaxTextureUnits];
	for (int i = 0; i < GLMaxTextureUnits; ++i)
	{
		_activeTextures[i].width = 0;
		_activeTextures[i].height = 0;
		_activeTextures[i].handle = 0;
		_activeTextures[i].unit = i;
	}
}

void TextureManager::CreateTexture(unsigned char* data, TextureInfo &info)
{
	glGenTextures(1, &info.handle);
	glBindTexture(GL_TEXTURE_2D, info.handle);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, info.width, info.height);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, info.width, info.height, GL_RGBA, GL_UNSIGNED_BYTE, data);

	glActiveTexture(GL_TEXTURE0 + info.unit);
	glBindTexture(GL_TEXTURE_2D, 0);
}

TextureInfo TextureManager::LoadTexture(const string &filepath)
{
	FILE* fp;
	errno_t error = fopen_s(&fp, filepath.c_str(), "rb");
	Assert_NotNull(fp, ("Failed to open image " + filepath).c_str());

	png_byte header[8];
	fread_s(header, 8, sizeof(png_byte), 8, fp);
	int isPng = png_sig_cmp(header, 0, 8);
	Assert(isPng == 0, "The image is not a png.");

	png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
	Assert_NotNull(png_ptr, "Failed to create the png read struct.");

	auto errorCallback = [&png_ptr]() -> bool
	{
		png_destroy_read_struct(&png_ptr, nullptr, nullptr);
		return false;
	};

	png_infop info_ptr = png_create_info_struct(png_ptr);
	Assert_NotNull(info_ptr, "Failed to create the png info struct.");

	png_infop end_info = png_create_info_struct(png_ptr);
	Assert_NotNull(end_info, "Failed to create the png end info struct.");

	if (setjmp(png_jmpbuf(png_ptr)))
	{
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
		Assert_Fail("An error occured while loading an image.");
	}

	png_init_io(png_ptr, fp);
	png_set_sig_bytes(png_ptr, 8);

	png_read_info(png_ptr, info_ptr);

	int width = png_get_image_width(png_ptr, info_ptr);
	int height = png_get_image_height(png_ptr, info_ptr);
	png_byte color_type = png_get_color_type(png_ptr, info_ptr);
	png_byte bit_depth = png_get_bit_depth(png_ptr, info_ptr);

	int rowBytes = png_get_rowbytes(png_ptr, info_ptr);

	rowBytes += 3 - ((rowBytes - 1) % 4);

	png_byte* image_data;
	image_data = (png_byte*)malloc(rowBytes * height * sizeof(png_byte) + 15);
	Assert_NotNull(image_data, "Failed to allocate memory for image data.");

	png_bytep* row_pointers = (png_bytep*)malloc(height * sizeof(png_bytep));
	Assert_NotNull(row_pointers, "Failed to allocate memory for image rows.");

	for (int i = 0; i < height; i++)
	{
		row_pointers[height - 1 - i] = image_data + i * rowBytes;
	}

	png_read_image(png_ptr, row_pointers);

	TextureInfo* info = &_activeTextures[_numTextures];
	info->width = width;
	info->height = height;
		
	CreateTexture(image_data, *info);

	png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
	free(image_data);
	free(row_pointers);
	fclose(fp);
	
	_numTextures++;

	return *info;
}