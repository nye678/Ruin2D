#version 430

layout (location = 0) in vec2 position;
layout (location = 1) in int texlayer;
layout (location = 2) in int tile;

layout (binding = 2, std140) uniform TextureInfoBlock
{
	float width;
	float height;
	float tileWidth;
	float tileHeight;
	int rows;
	int columns;
} textureInfo[];

uniform mat4 camera;

const vec4 vertices[4] = vec4[4](
	vec4(0.0, 0.0, 0.0, 1.0),
	vec4(1.0, 0.0, 0.0, 1.0),
	vec4(1.0, -1.0, 0.0, 1.0),
	vec4(0.0, -1.0, 0.0, 1.0));

const vec3 uv_verts[4] = vec3[4](
	vec3(0.0, 0.0, 1.0),
	vec3(1.0, 0.0, 1.0),
	vec3(1.0, -1.0, 1.0),
	vec3(0.0, -1.0, 1.0));

out vec2 uv;

void main()
{
	mat4 transform = mat4(1.0);
	transform[0][0] = textureInfo[texlayer].tileWidth;
	transform[1][1] = -textureInfo[texlayer].tileHeight;
	transform[3].xy = position;

	gl_Position = camera * transform * vertices[gl_VertexID];

	int column = tile % textureInfo[texlayer].columns;
	int row = int(floor(tile / textureInfo[texlayer].columns));

	float tileWidthDelta = textureInfo[texlayer].tileWidth / textureInfo[texlayer].width;
	float tileHeightDelta = textureInfo[texlayer].tileHeight / textureInfo[texlayer].height;

	mat3 uvMatrix = mat3(1.0);
	uvMatrix[0][0] = tileWidthDelta;
	uvMatrix[1][1] = tileHeightDelta;
	uvMatrix[2].xy = vec2(column * tileWidthDelta, -row * tileHeightDelta)

	uv = (uvMat * uv_verts[gl_VertexID]).xy;
}