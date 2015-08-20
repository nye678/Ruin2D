#version 430

in vec2 uv;

out vec4 end_color;

uniform sampler2D spriteTex;

void main()
{
	vec4 texColor = texture(spriteTex, uv);
	end_color = texColor;
    //end_color = vec4(1.0);
}