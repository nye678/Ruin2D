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

	/* const vec4 vertices[4] = vec4[4](vec4(0.0, 0.0, 0.0, 1.0),
									 vec4(16.0, 0.0, 0.0, 1.0),
									 vec4(16.0, -16.0, 0.0, 1.0),
									 vec4(0.0, -16.0, 0.0, 1.0)); */

	gl_Position = camera * transform * vertices[gl_VertexID];

	const vec3 uv_verts[4] = vec3[4](vec3(0.0, 0.0, 1.0),
									 vec3(1.0, 0.0, 1.0),
									 vec3(1.0, -1.0, 1.0),
									 vec3(0.0, -1.0, 1.0));

	uv = (uvMat * uv_verts[gl_VertexID]).xy;
}