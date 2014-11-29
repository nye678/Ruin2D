#ifndef __RUIN2D_GRAPHICS_H_
#define __RUIN2D_GRAPHICS_H_

#include <algorithm>
#include <vector>
#include <memory>
#include <GL3\gl3w.h>
#include <glm\glm.hpp>
#include <glm\gtc\constants.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include "Texture.h"
#include "TileSet.h"
#include "Camera.h"
#include "Font.h"
#include "TextureManager.h"
#include "Log.h"

namespace Ruin2D
{
	class Graphics
	{
		typedef uint64_t DrawKey;

		struct DrawInfo
		{
			DrawKey key;
			int zOrder;
			GLuint texture;
			GLint unit;
			glm::mat4 transform;
			glm::mat3 uv;
		};

		struct DrawCmd
		{
			GLuint texture;
			GLint unit;
			int count;

			DrawCmd(GLuint texture, GLint unit, int count)
				: texture(texture), unit(unit), count(count)
			{}
		};

		struct DrawInfoCompare
		{
			inline bool operator() (const DrawInfo &lhs, const DrawInfo &rhs)
			{
				return lhs.key < rhs.key;
			}
		};

		static const int MaxSprites = 10000;

	private:
		GLuint vertexArray;
		GLuint transformBuffer;
		GLuint uvBuffer;

		GLuint shader;
		GLint transformLoc;
		GLint uvLoc;
		GLint textureLoc;
		GLint layerLoc;
		GLint cameraLoc;

		GLuint textVAO;
		GLuint textBuffer;

		GLuint textShader;
		GLint textPosLoc;
		GLint textUVLoc;
		GLint textTransformLoc;
		GLint textOrthoLoc;
		GLint textFontTexLoc;
		GLint textColorLoc;

		GLuint staticObjectBuffer;
		GLuint dynamicObjectBuffer;

		std::vector<DrawInfo> drawBatch;
		std::vector<DrawInfo> textBatch;
	public:
		void SetClearColor(float r, float g, float b);

		void StartBatch();

		void EndBatch();

		void Draw(const Texture &texture, const glm::vec2 &position, double orientation, short layer, const glm::vec2 &scale, const glm::vec2 &origin);

		void Draw(const Texture &texture, const glm::vec2 &position, double orientation, short layer, const glm::vec2 &scale);

		void Draw(const Texture &texture, const glm::vec2 &position, double orientation, short layer);

		void Draw(const Texture &texture, const glm::vec2 &position, double orientation);

		void Draw(const Texture &texture, const glm::vec2 &position);

		void DrawTile(const TileSet &tileSet, int tileIndex, const glm::vec2 &position);

		void DrawTile(const TileSet &tileSet, int tileIndex, const glm::vec2 &position, short layer);

		void BufferText(const Font &font, const std::string &str);

		void UpdateCamera(Camera* camera);

		Graphics();
		Graphics(const Graphics &) = delete;
		Graphics &operator= (const Graphics &) = delete;
	private:
		void Render();

		void RenderText();

		void InitializeBuffers();

		GLuint CreateBasicShader(const char* vertexCode, const char* fragmentCode);

		GLuint CompileShader(GLenum type, const char* code);

		GLint GetShaderLocation(GLuint program, const char* name);
	};
}

#endif