#pragma once
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

class Shader {
public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    void bind() const;
    void unbind() const;

    // Uniform setters
    void setBool(const std::string& name, bool value);
    void setInt(const std::string& name, int value);
    void setFloat(const std::string& name, float value);
    void setVec3(const std::string& name, const glm::vec3& vec);
    void setMat4(const std::string& name, const glm::mat4& mat);

private:
    unsigned int m_ID;
    std::unordered_map<std::string, int> m_UniformLocationCache;

    std::string loadFile(const std::string& path);
    unsigned int compileShader(unsigned int type, const std::string& source);
    void checkCompileErrors(unsigned int shader, const std::string& type);
    int getUniformLocation(const std::string& name);
};