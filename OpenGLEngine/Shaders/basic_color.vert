#version 130

in vec2 vertexPos;
in vec4 vertexColor;
in vec2 vertexUV;

out vec2 fragPosition;
out vec4 fragColor;
out vec2 fragUV;

void main()
{
	gl_Position.xy = vertexPos;
	gl_Position.z = 0.0;
	gl_Position.w = 1.0;
	
	fragPosition = vertexPos;
	fragColor = vertexColor;
	fragUV = vec2(vertexUV.x, 1.0 - vertexUV.y);
}