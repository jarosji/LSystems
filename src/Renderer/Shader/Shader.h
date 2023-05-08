#pragma once

#include <unordered_map>
#include <string>
#include <iostream>

#include <glm/glm.hpp>

struct ShaderProgramSource {
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader {

public:
	Shader();
	Shader(const std::string& Filepath);
	~Shader();

	// non copyable
	Shader(const Shader&) = delete;
	Shader& operator=(const Shader&) = delete; 

	// move constructor
	Shader(Shader&& other) noexcept;
	Shader& operator=(Shader&& other) noexcept;

	void Bind() const;
	void Unbind() const;

	const unsigned int GetProgram() const { return id; }

	void SetUniform1i(const std::string& Name, int v0);
	void SetUniform1f(const std::string& Name, float v0);
	void SetUniform3f(const std::string& Name, glm::vec3 vec);
	void SetUniform4f(const std::string& Name, float v0, float v1, float v2, float v3);
	void SetUniform4f(const std::string& Name, glm::vec4 vec);
	void SetUniformMat4f(const std::string& Name, const glm::mat4& Matrix);

private:
	unsigned int id;
	std::string filepath;
	std::unordered_map<std::string, int> uniformCache;

	unsigned int CreateShader(const std::string& VertexShader, const std::string& FragmentShader);
	ShaderProgramSource ParseShader(const std::string& Filepath);
	unsigned int CompileShader(unsigned int Type, const std::string& Source);

	int GetUniformLocation(const std::string& Name);
};