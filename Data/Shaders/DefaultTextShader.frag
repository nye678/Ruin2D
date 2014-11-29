#version 430

in vec2 uv;

uniform sampler2D tex;
uniform vec4 color;

out vec4 final_color;

void main()
{
	final_color = vec4(vec3(1.0), texture2D(tex, vec2(uv.x, uv.y)).r) * color;
}