#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 2) in vec2 texCoord;

out vec2 v_TexCoord; //v_ = varying

uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * position;
	v_TexCoord = texCoord;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;

struct Material {
	vec4 color;
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};
uniform Material u_Material;

void main()
{
	vec4 texColor = texture(u_Material.diffuse, v_TexCoord);
	color = texColor * u_Material.color;
};