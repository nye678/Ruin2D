#include "Graphics.h"

using namespace std;
using namespace glm;
using namespace Ruin2D;

const char* vertShaderCode = R"glsl(
#version 430

layout (location = 5) in mat4 transform;
layout (location = 10) in mat3 uvMat;

uniform mat4 camera;

out vec2 uv;

void main()
{
	const vec4 vertices[4] = vec4[4](vec4(0.0, 0.0, 0.0, 1.0),
									 vec4(1.0, 0.0, 0.0, 1.0),
									 vec4(1.0, -1.0, 0.0, 1.0),
									 vec4(0.0, -1.0, 0.0, 1.0));

	gl_Position = camera * transform * vertices[gl_VertexID];

	const vec3 uv_verts[4] = vec3[4](vec3(0.0, 0.0, 1.0),
									 vec3(1.0, 0.0, 1.0),
									 vec3(1.0, -1.0, 1.0),
									 vec3(0.0, -1.0, 1.0));

	uv = (uvMat * uv_verts[gl_VertexID]).xy;
}
)glsl";

const char* fragShaderCode = R"glsl(
#version 430

in vec2 uv;

out vec4 end_color;

uniform sampler2D spriteTex;

void main()
{
	vec4 texColor = texture(spriteTex, uv);
	end_color = texColor;
}
)glsl";

const char* textVertShaderCode = R"glsl(
#version 430

layout (location = 0) in vec2 pos;
layout (location = 1) in vec2 vert_uv;

uniform mat4 transform;
uniform mat4 ortho;

out vec2 uv;

void main()
{
	gl_Position = ortho * transform * vec4(pos, 0.0, 1.0);
	uv = vert_uv;
}
)glsl";

const char* textFragShaderCode = R"glsl(
#version 430

in vec2 uv;

uniform sampler2D tex;
uniform vec4 color;

out vec4 final_color;

void main()
{
	final_color = vec4(vec3(1.0), texture2D(tex, vec2(uv.x, uv.y)).r) * color;
}
)glsl";

const char* tileVertShaderCode = R"glsl(
#version 430

layout (location = 0) in vec2 position;
layout (location = 1) in vec3 tex_coords;

uniform mat4 transform;
uniform mat4 camera;

out VS_OUT
{
	vec3 tex_coords;
} vs_out;

void main()
{
	gl_Position = camera * transform * vec4(position, 0.0, 1.0);
	vs_out.tex_coords = tex_coords;
}
)glsl";

const char* textFragBerhhShaderCode = R"glsl(
#version 430

in VS_OUT
{
	vec3 tex_coords;
} vs_in;

uniform sampler2DArray tex;

out vec4 color;

void main()
{
	color = texture(tex, vec3(vs_in.tex_coords));
}
)glsl";

Graphics::Graphics()
{
	auto version = glGetString(GL_VERSION);

	InitializeBuffers();
	Camera::Create();
	TextureManager::Create();
}

shared_ptr<Graphics> Graphics::Create()
{
	Log::Info("Creating singleton instance for Graphics.");
	return Singleton.Create();
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

void Graphics::Draw(const Texture &texture, const glm::vec2 &position, double orientation, short layer, const glm::vec2 &scale, const glm::vec2 &origin)
{
	vec2 textureScale = vec2(texture.Width(), texture.Height()) * scale;

	mat4 transform = mat4(1.0f);
	transform = translate(transform, vec3(position.x - origin.x, -position.y + origin.y, 0.0f));
	transform = glm::scale(transform, vec3(textureScale, 1.0f));
	transform = translate(transform, vec3(0.5f, -0.5f, 0.0f));
	transform = rotate(transform, (float)orientation, vec3(0.0f, 0.0f, 1.0f));
	transform = translate(transform, vec3(-0.5f, 0.5f, 0.0f));

	DrawInfo info;
	info.key = layer;
	info.texture = texture.Unit();
	info.transform = transform;
	info.uv = mat3(1.0f);

	drawBatch.push_back(info);
}

void Graphics::Draw(const Texture &texture, const vec2 &position, double orientation, short layer, const vec2 &scale)
{
	Draw(texture, position, orientation, layer, scale, vec2(0.0f, 0.0f));
}

void Graphics::Draw(const Texture &texture, const vec2 &position, double orientation, short layer)
{
	Draw(texture, position, orientation, layer, vec2(1.0f, 1.0f), vec2(0.0f, 0.0f));
}

void Graphics::Draw(const Texture &texture, const vec2 &position, double orientation)
{
	Draw(texture, position, orientation, 0, vec2(1.0f, 1.0f), vec2(0.0f, 0.0f));
}

void Graphics::Draw(const Texture &texture, const vec2 &position)
{
	Draw(texture, position, 0.0, 0, vec2(1.0f, 1.0f), vec2(0.0f, 0.0f));
}

void Graphics::DrawTile(const TileSet &tileSet, int tileIndex, const vec2 &position)
{
	vec2 textureScale = vec2(tileSet.TileWidth(), tileSet.TileHeight());

	mat4 transform = mat4(1.0f);
	transform = translate(transform, vec3(position.x, -position.y, 0.0f));
	transform = glm::scale(transform, vec3(textureScale, 1.0f));

	DrawInfo info;
	info.key = 0;
	info.texture = tileSet.Handle();
	info.unit = tileSet.Unit();
	info.transform = transform;
	info.uv = tileSet.GetTileUVMatrix(tileIndex);

	drawBatch.push_back(info);
}

void Graphics::DrawTile(const TileSet &tileSet, int tileIndex, const vec2 &position, short layer)
{
	vec2 textureScale = vec2(tileSet.TileWidth(), tileSet.TileHeight());

	mat4 transform = mat4(1.0f);
	transform = translate(transform, vec3(position.x, -position.y, 0.0f));
	transform = glm::scale(transform, vec3(textureScale, 1.0f));

	DrawInfo info;
	info.key = layer;
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
	glBufferData(GL_ARRAY_BUFFER, MaxSprites * sizeof(mat4), nullptr, GL_DYNAMIC_DRAW);
	mat4* transforms = static_cast<mat4*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));

	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, MaxSprites * sizeof(mat3), nullptr, GL_DYNAMIC_DRAW);
	mat3* uvs = static_cast<mat3*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));

	auto spriteItor = drawBatch.begin();
	auto textureBuckets = std::vector<std::tuple<GLuint, GLint, int>>();
	GLuint currentTexture = spriteItor->texture;
	GLint currentUnit = spriteItor->unit;
	int index = 0, prevIndex = 0, count = 0;

	for (; spriteItor != drawBatch.end(); ++spriteItor)
	{
		if (spriteItor->texture != currentTexture)
		{
			textureBuckets.push_back(tuple<GLuint, GLint, int>(currentTexture, currentUnit, count));
			currentTexture = spriteItor->texture;
			currentUnit = spriteItor->unit;
			count = 0;
		}

		memcpy(transforms + index, value_ptr(spriteItor->transform), sizeof(mat4));
		memcpy(uvs + index, value_ptr(spriteItor->uv), sizeof(mat3));
		++index;
		++count;
	}

	// Push the final texture group.
	textureBuckets.push_back(tuple<GLuint, GLint, int>(currentTexture, currentUnit, count));

	glBindBuffer(GL_ARRAY_BUFFER, transformBuffer);
	glUnmapBuffer(GL_ARRAY_BUFFER);
	transforms = nullptr;

	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glUnmapBuffer(GL_ARRAY_BUFFER);
	uvs = nullptr;

	Camera::Get()->UpdateCameraView(cameraLoc);

	int baseInstance = 0;
	Assert_True(textureBuckets.size() < 100, "Exceeded command buffer size.");
	int drawCount = 0;
	for (auto pair : textureBuckets)
	{
		GLuint texture = std::get<0>(pair);
		GLint unit = std::get<1>(pair);
		int count = std::get<2>(pair);

		glUniform1i(textureLoc, unit);
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_2D, texture);

		glDrawArraysInstancedBaseInstance(GL_TRIANGLE_FAN, 0, 4, count, baseInstance);
		baseInstance += count;
		drawCount++;
	}
}

void Graphics::RenderText()
{
	glUseProgram(textShader);
	glBindVertexArray(textVAO);

	mat4 transform = scale(translate(mat4(1.0f), vec3(100.0f, 100.0f, 0.0f)), vec3(1.0f));
	glUniformMatrix4fv(textTransformLoc, 1, GL_FALSE, value_ptr(transform));

	glActiveTexture(GL_TEXTURE1);

	glDrawArrays(GL_TRIANGLES, 0, 4 * 6);
}

void Graphics::BufferText(const Font &font, const string &text)
{
	if (text.size() < 1) return;

	glBindBuffer(GL_ARRAY_BUFFER, textBuffer);
	glBufferData(GL_ARRAY_BUFFER, MaxSprites * sizeof(vec4), nullptr, GL_DYNAMIC_DRAW);
	vec4* textBuf = static_cast<vec4*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));

	float advance = 0.0f;
	int boffset = 0;

	for (uint i = 0; i < text.size(); ++i)
	{
		//FT_UInt charIndex = FT_Get_Char_Index(mFace, text.text[i]);
		//FT_Load_Glyph(mFace, charIndex, 0);
		//FT_Render_Glyph(mFace->glyph, FT_RENDER_MODE_NORMAL);

		vec2 charOffset = font.GetCharacterOffset(text[i]);
		float yoffset = 32 - charOffset.y;

		mat4 transform = scale(mat4(1.0f), vec3((float)32, (float)32, 1.0f));
		transform = translate(transform, vec3(advance / 32, yoffset / 32, 0.0f));

		float x = (float)(text[i] % 16);
		float y = (float)(int)floor((float)text[i] / 16.0f);

		vec4 v1 = transform * vec4(0.0f, 0.0f, 0.0f, 1.0f);
		vec4 v2 = transform * vec4(1.0f, 0.0f, 0.0f, 1.0f);
		vec4 v3 = transform * vec4(0.0f, 1.0f, 0.0f, 1.0f);
		vec4 v4 = transform * vec4(1.0f, 1.0f, 0.0f, 1.0f);

		textBuf[boffset + 0] = (vec4(v1.x, v1.y, x / 16.0f, y / 16.0f));
		textBuf[boffset + 1] = (vec4(v3.x, v3.y, x / 16.0f, y / 16.0f + 1.0f / 16.0f));
		textBuf[boffset + 2] = (vec4(v2.x, v2.y, x / 16.0f + 1.0f / 16.0f, y / 16.0f));
		textBuf[boffset + 3] = (vec4(v2.x, v2.y, x / 16.0f + 1.0f / 16.0f, y / 16.0f));
		textBuf[boffset + 4] = (vec4(v3.x, v3.y, x / 16.0f, y / 16.0f + 1.0f / 16.0f));
		textBuf[boffset + 5] = (vec4(v4.x, v4.y, x / 16.0f + 1.0f / 16.0f, y / 16.0f + 1.0f / 16.0f));

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

	shader = CreateBasicShader(vertShaderCode, fragShaderCode);
	glUseProgram(shader);

	transformLoc = GetShaderLocation(shader, "transform");
	uvLoc = GetShaderLocation(shader, "uvMat");
	textureLoc = GetShaderLocation(shader, "spriteTex");
	cameraLoc = GetShaderLocation(shader, "camera");
	layerLoc = GetShaderLocation(shader, "layer");

	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	glGenBuffers(1, &transformBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, transformBuffer);
	glBufferData(GL_ARRAY_BUFFER, MaxSprites * sizeof(mat4), nullptr, GL_DYNAMIC_DRAW);

	for (int i = 0; i < 4; i++)
	{
		glEnableVertexAttribArray(transformLoc + i);
		glVertexAttribPointer(transformLoc + i, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 16, (const GLvoid*)(sizeof(GLfloat) * i * 4));
		glVertexAttribDivisor(transformLoc + i, 1);
	}

	glGenBuffers(1, &uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, MaxSprites * sizeof(mat3), nullptr, GL_DYNAMIC_DRAW);

	for (int i = 0; i < 3; i++)
	{
		glEnableVertexAttribArray(uvLoc + i);
		glVertexAttribPointer(uvLoc + i, 3, GL_FLOAT, GL_FALSE, sizeof(mat3), (const GLvoid*)(sizeof(GLfloat) * i * 3));
		glVertexAttribDivisor(uvLoc + i, 1);
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	textShader = CreateBasicShader(textVertShaderCode, textFragShaderCode);

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
	glBufferData(GL_ARRAY_BUFFER, MaxSprites * sizeof(vec4), nullptr, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(textPosLoc);
	glEnableVertexAttribArray(textUVLoc);
	glVertexAttribPointer(textPosLoc, 2, GL_FLOAT, GL_FALSE, sizeof(vec4), nullptr);
	glVertexAttribPointer(textUVLoc, 2, GL_FLOAT, GL_FALSE, sizeof(vec4), (void*)(sizeof(GL_FLOAT) * 2));

	vec4 textColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	glUniform4fv(textColorLoc, 1, value_ptr(textColor));

	mat4 orthoMat = glm::ortho(0.0f, -1.0f, 1.0f, 0.0f, 0.01f, 1000.0f);
	orthoMat *= lookAt(vec3(0.0f, 0.0f, -1.0f), vec3(0.0f), vec3(0.0f, 1.0f, 0.0f));
	orthoMat = scale(orthoMat, vec3(1.0f / 1024.0f, 1.0f / 768.0f, 1.0f));
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

		Assert_Fail(errorString);
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