#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include <glad/gl.h>


Shader::Shader()
	: id(0)
{
}

Shader::Shader(const std::string& filepath)
	: filepath(filepath), id(0)
{
	ShaderProgramSource source = ParseShader(filepath);
	id = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader()
{
	glDeleteProgram(id);
}


unsigned int Shader::CompileShader(unsigned int Type, const std::string& Source)
{
	unsigned int id = glCreateShader(Type);
	const char* src = Source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int Result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &Result);
	if (Result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);

		std::cout << "Shader compile failed: " <<
			(Type == GL_VERTEX_SHADER ? "Vertex" : "Fragment")
			<< "Shader" << std::endl;
		std::cout << message << std::endl;

		glDeleteShader(id);
		return 0;
	}

	return id;
}

unsigned int Shader::CreateShader(const std::string& VertexShader, const std::string& FragmentShader) {
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, VertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, FragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

ShaderProgramSource Shader::ParseShader(const std::string& Filepath) {
	std::ifstream stream(Filepath);

	enum class ShaderType {
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while (getline(stream, line)) {
		if (line.find("#shader") != std::string::npos) {
			if (line.find("vertex") != std::string::npos) {
				type = ShaderType::VERTEX;
			}

			else if (line.find("fragment") != std::string::npos) {
				type = ShaderType::FRAGMENT;
			}
		}
		else {
			ss[(int)type] << line << "\n";
		}
	}

	return { ss[0].str(), ss[1].str() };
}

Shader::Shader(Shader&& other) noexcept
	: id(other.id), filepath(std::move(other.filepath)), uniformCache(std::move(other.uniformCache))
{
	other.id = 0;
}

Shader& Shader::operator=(Shader&& other) noexcept
{
	if (id) glDeleteProgram(id);
	id = other.id;
	filepath = std::move(other.filepath);
	uniformCache = std::move(other.uniformCache);
	other.id = 0;
	return *this;
}

void Shader::Bind() const
{
	glUseProgram(id);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

void Shader::SetUniform1i(const std::string& Name, int v0)
{
	glUniform1i(GetUniformLocation(Name), v0);
}

void Shader::SetUniform1f(const std::string& Name, float v0)
{
	glUniform1f(GetUniformLocation(Name), v0);
}

void Shader::SetUniform3f(const std::string& Name, glm::vec3 vec)
{
	glUniform3f(GetUniformLocation(Name), vec.x, vec.y, vec.z);
}

void Shader::SetUniform4f(const std::string& Name, float v0, float v1, float v2, float v3)
{
	glUniform4f(GetUniformLocation(Name), v0, v1, v2, v3);
}

void Shader::SetUniform4f(const std::string& Name, glm::vec4 vec)
{
	glUniform4f(GetUniformLocation(Name), vec.x, vec.y, vec.z, vec.w);
}

void Shader::SetUniformMat4f(const std::string& Name, const glm::mat4& Matrix)
{
	glUniformMatrix4fv(GetUniformLocation(Name), 1, GL_FALSE, &Matrix[0][0]);
}

int Shader::GetUniformLocation(const std::string& Name)
{
	if (uniformCache.find(Name) != uniformCache.end())
		return uniformCache[Name];

	int location = glGetUniformLocation(id, Name.c_str());
	if (location == -1)
		std::cout << "Warning: uniform loc wrong" << std::endl;

	uniformCache[Name] = location;
	return location;
}
