#include "Graphics.h"

#include <algorithm>
#include <vector>
#include <glm\gtc\constants.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include "Log.h"
#include "Utility.h"

using namespace std;
using namespace Ruin2D;

Graphics::Graphics()
{
	auto version = glGetString(GL_VERSION);

	InitializeBuffers();
}

void Graphics::SetClearColor(float r, float g, float b)
{
	glClearColor(r, g, b, 1.0f);
}

void Graphics::StartBatch()
{
	drawBatch.clear();
}

void Graphics::EndBatch()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (drawBatch.size() > 0)
	{
		sort(drawBatch.begin(), drawBatch.end(), DrawInfoCompare());
		Render();
	}

	//RenderText();
}

void Graphics::UpdateCamera(Camera* camera)
{
	camera->UpdateCameraView(cameraLoc);
}

void Graphics::Draw(const Texture &texture, const glm::vec2 &position, double orientation, short layer, const glm::vec2 &scale, const glm::vec2 &origin)
{
	glm::vec2 textureScale = glm::vec2(texture.Width(), texture.Height()) * scale;

	glm::mat4 transform = glm::mat4(1.0f);
	transform = glm::translate(transform, glm::vec3(position.x - origin.x, -position.y + origin.y, 0.0f));
	transform = glm::scale(transform, glm::vec3(textureScale, 1.0f));
	transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
	transform = glm::rotate(transform, (float)orientation, glm::vec3(0.0f, 0.0f, 1.0f));
	transform = glm::translate(transform, glm::vec3(-0.5f, 0.5f, 0.0f));

	DrawInfo info;
	info.key = 0;
	info.zOrder = layer;
	info.texture = texture.Unit();
	info.transform = transform;
	info.uv = glm::mat3(1.0f);

	drawBatch.push_back(info);
}

void Graphics::Draw(const Texture &texture, const glm::vec2 &position, double orientation, short layer, const glm::vec2 &scale)
{
	Draw(texture, position, orientation, layer, scale, glm::vec2(0.0f, 0.0f));
}

void Graphics::Draw(const Texture &texture, const glm::vec2 &position, double orientation, short layer)
{
	Draw(texture, position, orientation, layer, glm::vec2(1.0f, 1.0f), glm::vec2(0.0f, 0.0f));
}

void Graphics::Draw(const Texture &texture, const glm::vec2 &position, double orientation)
{
	Draw(texture, position, orientation, 0, glm::vec2(1.0f, 1.0f), glm::vec2(0.0f, 0.0f));
}

void Graphics::Draw(const Texture &texture, const glm::vec2 &position)
{
	Draw(texture, position, 0.0, 0, glm::vec2(1.0f, 1.0f), glm::vec2(0.0f, 0.0f));
}

void Graphics::DrawTile(const TileSet &tileSet, int tileIndex, const glm::vec2 &position)
{
	glm::vec2 textureScale = glm::vec2(tileSet.TileWidth(), tileSet.TileHeight());

	glm::mat4 transform = glm::mat4(1.0f);
	transform = glm::translate(transform, glm::vec3(position.x, -position.y, 0.0f));
	transform = glm::scale(transform, glm::vec3(textureScale, 1.0f));

	DrawInfo info;
	info.key = 0;
	info.zOrder = 0;
	info.texture = tileSet.Handle();
	info.unit = tileSet.Unit();
	info.transform = transform;
	info.uv = tileSet.GetTileUVMatrix(tileIndex);

	drawBatch.push_back(info);
}

void Graphics::DrawTile(const TileSet &tileSet, int tileIndex, const glm::vec2 &position, short layer)
{
	glm::vec2 textureScale = glm::vec2(tileSet.TileWidth(), tileSet.TileHeight());

	glm::mat4 transform = glm::mat4(1.0f);
	transform = glm::translate(transform, glm::vec3(position.x, -position.y, 0.0f));
	transform = glm::scale(transform, glm::vec3(textureScale, 1.0f));

	DrawInfo info;
	info.key = layer > 0 ? (((DrawKey)layer) << 48) | (DrawKey)ceil(position.y + tileSet.TileHeight()) : 0;
	info.zOrder = layer;
	info.texture = tileSet.Handle();
	info.unit = tileSet.Unit();
	info.transform = transform;
	info.uv = tileSet.GetTileUVMatrix(tileIndex);

	drawBatch.push_back(info);
}

void Graphics::Render()
{
	glUseProgram(shader);
	glBindVertexArray(vertexArray);

	glBindBuffer(GL_ARRAY_BUFFER, transformBuffer);
	glBufferData(GL_ARRAY_BUFFER, MaxSprites * sizeof(glm::mat4), nullptr, GL_DYNAMIC_DRAW);
	glm::mat4* transforms = static_cast<glm::mat4*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));

	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, MaxSprites * sizeof(glm::mat3), nullptr, GL_DYNAMIC_DRAW);
	glm::mat3* uvs = static_cast<glm::mat3*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));

	auto spriteItor = drawBatch.begin();
	auto textureBuckets = std::vector<DrawCmd>();
	GLuint currentTexture = spriteItor->texture;
	GLint currentUnit = spriteItor->unit;
	int index = 0, prevIndex = 0, count = 0;

	for (; spriteItor != drawBatch.end(); ++spriteItor)
	{
		if (spriteItor->texture != currentTexture)
		{
			textureBuckets.push_back(DrawCmd(currentTexture, currentUnit, count));
			currentTexture = spriteItor->texture;
			currentUnit = spriteItor->unit;
			count = 0;
		}

		memcpy(transforms + index, glm::value_ptr(spriteItor->transform), sizeof(glm::mat4));
		memcpy(uvs + index, value_ptr(spriteItor->uv), sizeof(glm::mat3));
		++index;
		++count;
	}

	// Push the final texture group.
	textureBuckets.push_back(DrawCmd(currentTexture, currentUnit, count));

	glBindBuffer(GL_ARRAY_BUFFER, transformBuffer);
	glUnmapBuffer(GL_ARRAY_BUFFER);
	transforms = nullptr;

	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glUnmapBuffer(GL_ARRAY_BUFFER);
	uvs = nullptr;

	int baseInstance = 0;
	Assert(textureBuckets.size() < 100, "Exceeded command buffer size.");
	int drawCount = 0;
	for (auto cmd : textureBuckets)
	{
		glUniform1i(textureLoc, cmd.unit);
		glActiveTexture(GL_TEXTURE0 + cmd.unit);
		glBindTexture(GL_TEXTURE_2D, cmd.texture);

		glDrawArraysInstancedBaseInstance(GL_TRIANGLE_FAN, 0, 4, cmd.count, baseInstance);
		baseInstance += cmd.count;
		drawCount++;
	}
}

void Graphics::RenderText()
{
	glUseProgram(textShader);
	glBindVertexArray(textVAO);

	glm::mat4 transform = glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(100.0f, 100.0f, 0.0f)), glm::vec3(1.0f));

	glUniformMatrix4fv(textTransformLoc, 1, GL_FALSE, glm::value_ptr(transform));

	glActiveTexture(GL_TEXTURE1);

	glDrawArrays(GL_TRIANGLES, 0, 4 * 6);
}

void Graphics::BufferText(const Font &font, const string &text)
{
	if (text.size() < 1) return;

	glBindBuffer(GL_ARRAY_BUFFER, textBuffer);
	glBufferData(GL_ARRAY_BUFFER, MaxSprites * sizeof(glm::vec4), nullptr, GL_DYNAMIC_DRAW);
	glm::vec4* textBuf = static_cast<glm::vec4*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));

	float advance = 0.0f;
	int boffset = 0;

	for (uint32_t i = 0; i < text.size(); ++i)
	{
		//FT_UInt charIndex = FT_Get_Char_Index(mFace, text.text[i]);
		//FT_Load_Glyph(mFace, charIndex, 0);
		//FT_Render_Glyph(mFace->glyph, FT_RENDER_MODE_NORMAL);

		glm::vec2 charOffset = font.GetCharacterOffset(text[i]);
		float yoffset = 32 - charOffset.y;

		glm::mat4 transform = glm::scale(glm::mat4(1.0f), glm::vec3((float)32, (float)32, 1.0f));
		transform = glm::translate(transform, glm::vec3(advance / 32, yoffset / 32, 0.0f));

		float x = (float)(text[i] % 16);
		float y = (float)(int)floor((float)text[i] / 16.0f);

		glm::vec4 v1 = transform * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
		glm::vec4 v2 = transform * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
		glm::vec4 v3 = transform * glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
		glm::vec4 v4 = transform * glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);

		textBuf[boffset + 0] = (glm::vec4(v1.x, v1.y, x / 16.0f, y / 16.0f));
		textBuf[boffset + 1] = (glm::vec4(v3.x, v3.y, x / 16.0f, y / 16.0f + 1.0f / 16.0f));
		textBuf[boffset + 2] = (glm::vec4(v2.x, v2.y, x / 16.0f + 1.0f / 16.0f, y / 16.0f));
		textBuf[boffset + 3] = (glm::vec4(v2.x, v2.y, x / 16.0f + 1.0f / 16.0f, y / 16.0f));
		textBuf[boffset + 4] = (glm::vec4(v3.x, v3.y, x / 16.0f, y / 16.0f + 1.0f / 16.0f));
		textBuf[boffset + 5] = (glm::vec4(v4.x, v4.y, x / 16.0f + 1.0f / 16.0f, y / 16.0f + 1.0f / 16.0f));

		//advance += mFace->glyph->advance.x >> 6;
		advance += charOffset.x;
		boffset += 6;
	}

	glUnmapBuffer(GL_ARRAY_BUFFER);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//textBufferSize = boffset;
}

void Graphics::InitializeBuffers()
{
	glViewport(0, 0, 1024, 768);

	char* vertShaderCode = nullptr;
	char* fragShaderCode = nullptr;
	size_t read = 0;
	read = LoadTextFile("D:\\Projects\\Ruin2D\\Data\\Shaders\\DefaultTileShader.vert", vertShaderCode);
	Assert(read != 0, "Failed to read the vert shader file");
	read = LoadTextFile("D:\\Projects\\Ruin2D\\Data\\Shaders\\DefaultTileShader.frag", fragShaderCode);
	Assert(read != 0, "Failed to read the frag shader file");

	shader = CreateBasicShader(vertShaderCode, fragShaderCode);
	glUseProgram(shader);

	delete[] vertShaderCode;
	delete[] fragShaderCode;

	transformLoc = GetShaderLocation(shader, "transform");
	uvLoc = GetShaderLocation(shader, "uvMat");
	textureLoc = GetShaderLocation(shader, "spriteTex");
	cameraLoc = GetShaderLocation(shader, "camera");
	layerLoc = GetShaderLocation(shader, "layer");

	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	glGenBuffers(1, &transformBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, transformBuffer);
	glBufferData(GL_ARRAY_BUFFER, MaxSprites * sizeof(glm::mat4), nullptr, GL_DYNAMIC_DRAW);

	for (int i = 0; i < 4; i++)
	{
		glEnableVertexAttribArray(transformLoc + i);
		glVertexAttribPointer(transformLoc + i, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 16, (const GLvoid*)(sizeof(GLfloat) * i * 4));
		glVertexAttribDivisor(transformLoc + i, 1);
	}

	glGenBuffers(1, &uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, MaxSprites * sizeof(glm::mat3), nullptr, GL_DYNAMIC_DRAW);

	for (int i = 0; i < 3; i++)
	{
		glEnableVertexAttribArray(uvLoc + i);
		glVertexAttribPointer(uvLoc + i, 3, GL_FLOAT, GL_FALSE, sizeof(glm::mat3), (const GLvoid*)(sizeof(GLfloat) * i * 3));
		glVertexAttribDivisor(uvLoc + i, 1);
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	char* textVertShaderCode = nullptr;
	char* textFragShaderCode = nullptr;
	read = LoadTextFile("D:\\Projects\\Ruin2D\\Data\\Shaders\\DefaultTextShader.vert", textVertShaderCode);
	Assert(read != 0, "Failed to read the text vert shader file");
	read = LoadTextFile("D:\\Projects\\Ruin2D\\Data\\Shaders\\DefaultTextShader.frag", textFragShaderCode);
	Assert(read != 0, "Failed to read the text frag shader file");

	textShader = CreateBasicShader(textVertShaderCode, textFragShaderCode);

	delete[] textVertShaderCode;
	delete[] textFragShaderCode;

	glUseProgram(textShader);

	textPosLoc = GetShaderLocation(textShader, "pos");
	textUVLoc = GetShaderLocation(textShader, "vert_uv");
	textTransformLoc = GetShaderLocation(textShader, "transform");
	textOrthoLoc = GetShaderLocation(textShader, "ortho");
	textFontTexLoc = GetShaderLocation(textShader, "tex");
	textColorLoc = GetShaderLocation(textShader, "color");

	glGenVertexArrays(1, &textVAO);
	glBindVertexArray(textVAO);

	glGenBuffers(1, &textBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, textBuffer);
	glBufferData(GL_ARRAY_BUFFER, MaxSprites * sizeof(glm::vec4), nullptr, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(textPosLoc);
	glEnableVertexAttribArray(textUVLoc);
	glVertexAttribPointer(textPosLoc, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), nullptr);
	glVertexAttribPointer(textUVLoc, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)(sizeof(GL_FLOAT) * 2));

	glm::vec4 textColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	glUniform4fv(textColorLoc, 1, value_ptr(textColor));

	glm::mat4 orthoMat = glm::ortho(0.0f, -1.0f, 1.0f, 0.0f, 0.01f, 1000.0f);
	orthoMat *= glm::lookAt(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	orthoMat = glm::scale(orthoMat, glm::vec3(1.0f / 1024.0f, 1.0f / 768.0f, 1.0f));

	glUniformMatrix4fv(textOrthoLoc, 1, GL_FALSE, value_ptr(orthoMat));

	glUniform1i(textFontTexLoc, 1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

GLuint Graphics::CreateBasicShader(const char* vertexCode, const char* fragmentCode)
{
	GLuint program, vertShader, fragShader;
	vertShader = CompileShader(GL_VERTEX_SHADER, vertexCode);
	fragShader = CompileShader(GL_FRAGMENT_SHADER, fragmentCode);

	program = glCreateProgram();
	glAttachShader(program, vertShader);
	glAttachShader(program, fragShader);
	glLinkProgram(program);

	glDeleteShader(vertShader);
	glDeleteShader(fragShader);
	
	return program;
}

GLuint Graphics::CompileShader(GLenum type, const char* code)
{
	GLuint handle = glCreateShader(type);
	glShaderSource(handle, 1, &code, nullptr);
	glCompileShader(handle);

	GLint status;
	glGetShaderiv(handle, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &infoLogLength);

		char* errors = new char[infoLogLength + 1];
		memset(errors, '\0', infoLogLength + 1);

		glGetShaderInfoLog(handle, infoLogLength, nullptr, errors);

		string errorString = string(errors);
		delete errors;

		Assert_Fail(errorString.c_str());
	}

	return handle;
}

GLint Graphics::GetShaderLocation(GLuint program, const char* name)
{
	GLint loc = -1;
	loc = glGetUniformLocation(program, name);

	if (loc == -1)
	{
		loc = glGetAttribLocation(program, name);
	}

	return loc;
}