#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

uniform mat4 u_MVP;
uniform mat4 u_Model;

out vec2 v_TexCoord; //v_ = varying
out vec3 v_Normal;
out vec3 v_FragPos;

void main()
{
	gl_Position = u_MVP * position;

	v_TexCoord = texCoord;
	//v_Normal = normal;
	v_Normal = mat3(transpose(inverse(u_Model))) * normal;
	v_FragPos = vec3(u_Model * position);
};


#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in vec3 v_Normal;
in vec3 v_FragPos;

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};
uniform Material u_Material;

struct Light {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform Light u_Light;

uniform vec4 u_Color;
uniform vec3 u_LightColor;
uniform vec3 u_View;
uniform sampler2D u_Texture;

void main()
{
	//Texture
	vec4 texColor = texture(u_Texture, v_TexCoord);

	//ambient
	vec3 ambient = u_Material.ambient * u_Light.ambient;

	//calcs
	vec3 norm = normalize(v_Normal);
	vec3 lightDir = normalize(u_Light.position - v_FragPos);

	//diffuse
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = (diff * u_Material.diffuse) * u_Light.diffuse;

	//specular
	vec3 viewDir = normalize(u_View - v_FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.shininess);
	vec3 specular = (u_Material.specular * spec) * u_Light.specular;

	vec3 result = (ambient + diffuse + specular);

	//apply
	color = texColor * u_Color * vec4(result, 1.0);
};