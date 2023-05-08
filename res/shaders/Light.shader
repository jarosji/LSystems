#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

uniform mat4 u_MVP;
uniform mat4 u_Model;

//v_ = varying
out vec2 v_TexCoord; 
out vec3 v_Normal;
out vec3 v_FragPos;

void main()
{
	gl_Position = u_MVP * position;

	v_TexCoord = texCoord;
	v_Normal = mat3(transpose(inverse(u_Model))) * normal;
	v_FragPos = vec3(u_Model * position);
};


//Thanks learnopengl.com <3

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in vec3 v_Normal;
in vec3 v_FragPos;

struct Material {

	sampler2D diffuse;
	vec4 diffuseColor;

	sampler2D specular;
	float shininess;
};
uniform Material u_Material;

struct DirLight {
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform DirLight u_DirLight;


struct PointLight {
	vec3 position;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
#define NR_POINT_LIGHTS 3  
uniform PointLight u_PointLights[NR_POINT_LIGHTS];

struct SpotLight {
	vec3 position;
	vec3 direction;
	float cutOff;
	float outerCutOff;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform SpotLight u_SpotLight;

uniform vec3 u_View;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir) {
	vec3 lightDir = normalize(-light.direction);
	// diffuse shading
	float diff = max(dot(normal, lightDir), 0.0);
	// specular shading
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.shininess);
	// combine results
	vec3 ambient = light.ambient * vec3(texture(u_Material.diffuse, v_TexCoord));
	vec3 diffuse = light.diffuse * diff * vec3(texture(u_Material.diffuse, v_TexCoord));
	vec3 specular = light.specular * spec * vec3(texture(u_Material.specular, v_TexCoord));

	return (ambient + diffuse + specular);
};

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fragPos);
	// diffuse shading
	float diff = max(dot(normal, lightDir), 0.0);
	// specular shading
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.shininess);
	// attenuation
	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance +
		light.quadratic * (distance * distance));
	// combine results
	vec3 ambient = light.ambient * vec3(texture(u_Material.diffuse, v_TexCoord));
	vec3 diffuse = light.diffuse * diff * vec3(texture(u_Material.diffuse, v_TexCoord));
	vec3 specular = light.specular * spec * vec3(texture(u_Material.specular, v_TexCoord));
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;
	return (ambient + diffuse + specular);
};

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fragPos);
	// diffuse shading
	float diff = max(dot(normal, lightDir), 0.0);
	// specular shading
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.shininess);
	// attenuation
	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
	// spotlight intensity
	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
	// combine results
	vec3 ambient = light.ambient * vec3(texture(u_Material.diffuse, v_TexCoord));
	vec3 diffuse = light.diffuse * diff * vec3(texture(u_Material.diffuse, v_TexCoord));
	vec3 specular = light.specular * spec * vec3(texture(u_Material.specular, v_TexCoord));
	ambient *= attenuation * intensity;
	diffuse *= attenuation * intensity;
	specular *= attenuation * intensity;
	return (ambient + diffuse + specular);
};

void main()
{
	// properties
	vec3 norm = normalize(v_Normal);
	vec3 viewDir = normalize(u_View - v_FragPos);

	// == =====================================================
	// Our lighting is set up in 3 phases: directional, point lights and an optional flashlight
	// For each phase, a calculate function is defined that calculates the corresponding color
	// per lamp. In the main() function we take all the calculated colors and sum them up for
	// this fragment's final color.
	// == =====================================================
	// 
	// phase 1: directional lighting
	vec3 result = CalcDirLight(u_DirLight, norm, viewDir);

	// phase 2: point lights
	for (int i = 0; i < NR_POINT_LIGHTS; i++)
		result += CalcPointLight(u_PointLights[i], norm, v_FragPos, viewDir);

	// phase 3: spot light
	result += CalcSpotLight(u_SpotLight, norm, v_FragPos, viewDir);

	color = vec4(result, 1.0) * u_Material.diffuseColor;
};