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

	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};
uniform Material u_Material;

struct Light {
	vec3 position;
	vec3 direction;
	float innerCutOff;
	float outerCutOff;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};
uniform Light u_Light;

uniform vec4 u_Color;
uniform vec3 u_LightColor;
uniform vec3 u_View;

void main()
{
	//Texture
	//vec4 texColor = texture(u_Texture, v_TexCoord);

	//ambient
	vec3 ambient = u_Light.ambient * vec3(texture(u_Material.diffuse, v_TexCoord));

	//calcs
	vec3 norm = normalize(v_Normal);
	vec3 lightDir = normalize(u_Light.position - v_FragPos);
	//vec3 lightDir = normalize(-u_Light.direction);

	//Attenuation
	float distance = length(u_Light.position - v_FragPos);
	float attenuation = 1.0 / (u_Light.constant + u_Light.linear * distance +
		u_Light.quadratic * (distance * distance));

	//Spotlight
	float theta = dot(lightDir, normalize(-u_Light.direction));
	float epsilon = u_Light.innerCutOff - u_Light.outerCutOff;
	float intensity = clamp((theta - u_Light.outerCutOff) / epsilon, 0.0, 1.0);

	//diffuse
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * vec3(texture(u_Material.diffuse, v_TexCoord)) * u_Light.diffuse;

	//specular
	vec3 viewDir = normalize(u_View - v_FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.shininess);
	vec3 specular = u_Light.specular * spec * vec3(texture(u_Material.specular, v_TexCoord));

	diffuse *= intensity;
	specular *= intensity;

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	vec3 result = (ambient + diffuse + specular);

	//apply
	color = u_Color * vec4(result, 1.0);
};