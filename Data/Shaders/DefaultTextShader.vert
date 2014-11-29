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