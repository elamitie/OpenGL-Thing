#version 130

in vec2 fragPosition;
in vec4 fragColor;
in vec2 fragUV;

out vec4 color;

uniform float time;
uniform sampler2D tex;

void main()
{
	vec4 texColor = texture(tex, fragUV);
	color = texColor * fragColor;
}