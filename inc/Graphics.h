#ifndef __RUIN2D_GRAPHICS_H_
#define __RUIN2D_GRAPHICS_H_

#include <GL\gl3w.h>
#include <glm\glm.hpp>

#include "Texture.h"
#include "TileSet.h"
#include "Camera.h"
#include "Font.h"

namespace Ruin2D
{
	/* Graphics Class */
	/* The graphics class provides functionality for drawing various elements.
	   Draw calls will need to be preceded and succeeded by calls to start and end batch.
	   Each draw call will append draw information to a list which is then sorted so
	   everything will be drawn in the correct order. */
	class Graphics
	{
		// The draw key which will determine the order that things will be drawn.
		typedef uint64_t DrawKey;

		// Provides information about the draw. The key will be used to sort
		// draws and the other information will be subsequently used to batch
		// similar calls into buckets.
		struct DrawInfo
		{
			DrawKey key;
			int zOrder;
			GLuint texture;
			GLint unit;
			glm::mat4 transform;
			glm::mat3 uv;
		};

		// The final result of bucketed draws. Once the draws are sorted all
		// sequential draws of the same texture will be drawn at once.
		struct DrawCmd
		{
			GLuint texture;
			GLint unit;
			int count;

			DrawCmd(GLuint texture, GLint unit, int count)
				: texture(texture), unit(unit), count(count)
			{}
		};

		// Used to compare draw keys and determines how they are sorted.
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
		/* Sets the color that will used to clear the screen with each frame. */
		void SetClearColor(float r, float g, float b);

		/* Starts a new draw batch. Must call this before making draw calls. */
		void StartBatch();

		/* Finishes the batch and renders all the collected draws. */
		void EndBatch();

		/* Draws a single texture */
		void Draw(const Texture &texture, const glm::vec2 &position, double orientation, short layer, const glm::vec2 &scale, const glm::vec2 &origin);

		/* Draws a single texture */
		void Draw(const Texture &texture, const glm::vec2 &position, double orientation, short layer, const glm::vec2 &scale);

		/* Draws a single texture */
		void Draw(const Texture &texture, const glm::vec2 &position, double orientation, short layer);

		/* Draws a single texture */
		void Draw(const Texture &texture, const glm::vec2 &position, double orientation);

		/* Draws a single texture */
		void Draw(const Texture &texture, const glm::vec2 &position);

		/* Draws a tile in a tile map. */
		void DrawTile(const TileSet &tileSet, int tileIndex, const glm::vec2 &position);

		/* Draws a tile in a tile map. */
		void DrawTile(const TileSet &tileSet, int tileIndex, const glm::vec2 &position, short layer);

		/* Draws some text. */
		void BufferText(const Font &font, const std::string &str);

		/* Updates the camera to the video card. */
		void UpdateCamera(Camera* camera);

	private:
		/* Renders all the currently collected draw calls. */
		void Render();

		/* Renders all the text. */
		void RenderText();

		/* Initializes the buffers used on the graphics card. */
		void InitializeBuffers();

		/* Creates shader program with only a vertex and fragment shader. */
		GLuint CreateBasicShader(const char* vertexCode, const char* fragmentCode);

		/* Compiles shader code. */
		GLuint CompileShader(GLenum type, const char* code);

		/* Gets the location of a shader attribute or uniform. */
		GLint GetShaderLocation(GLuint program, const char* name);

	public:
		Graphics();
		Graphics(const Graphics &) = delete;
		Graphics &operator= (const Graphics &) = delete;
	};
}

#endif