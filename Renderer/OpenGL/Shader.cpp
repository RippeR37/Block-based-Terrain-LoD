#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include "../../Common/File.h"
#include "Shader.h"

namespace OpenGL {

    CShader::CShader() {
        m_programID = 0;
    }

    CShader::~CShader() {
        if(m_programID != 0)
            glDeleteProgram(m_programID);
    }

    void CShader::LoadShader(std::string vsPath, std::string fsPath) {
        /*** Variables ***/
        GLuint vsID;
        GLuint fsID;
        GLchar const *vsCodePtr;
        GLchar const *fsCodePtr;

        std::string vsCode;
        std::string fsCode;

        /*** Creating Shader objects ***/
        vsID = glCreateShader(GL_VERTEX_SHADER);
        fsID = glCreateShader(GL_FRAGMENT_SHADER);

        vsCode = Common::CFile::ReadTextFile(vsPath);
        fsCode = Common::CFile::ReadTextFile(fsPath);

        if(vsCode == "" || fsCode == "") {
            std::cerr << "OGL::Shader | Could not load shader files!" << std::endl;
            exit(1);
        }

        vsCodePtr = vsCode.c_str();
        fsCodePtr = fsCode.c_str();

        glShaderSource(vsID, 1, &vsCodePtr, NULL);
        glShaderSource(fsID, 1, &fsCodePtr, NULL);

        glCompileShader(vsID);
        glCompileShader(fsID);

        if(!VerifyShaderCompilation(vsID, "VS") || !VerifyShaderCompilation(fsID, "FS"))
            exit(1);

        /*** Creating Program object ***/
        m_programID = glCreateProgram();
        glAttachShader(m_programID, vsID);
        glAttachShader(m_programID, fsID);
        glLinkProgram(m_programID);

        if(!VerifyProgramLinking(m_programID, "PROG"))
            exit(1);

        glDeleteShader(vsID);
        glDeleteShader(fsID);

        /*** Uniform auto-detection & mapping ***/
        MapShaderUniforms(m_programID, vsCode);
        MapShaderUniforms(m_programID, fsCode);
    }

    GLuint CShader::GetUniformID(std::string uniformName) {
        std::map<std::string, GLuint>::iterator it = m_uniforms.find(uniformName);
        if(it != m_uniforms.end())
            return it->second;
        else
            return 0;
    }

    bool CShader::VerifyShaderCompilation(GLuint shaderID, std::string name) {
        std::vector<char> shaderErrorMsg;
        GLint result;
        GLint infoLen;

        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLen);

        shaderErrorMsg.resize(infoLen);
        glGetShaderInfoLog(shaderID, infoLen, NULL, &shaderErrorMsg[0]);

        if(result != GL_TRUE)
            std::cerr << name << ": " << &shaderErrorMsg[0] << std::endl;

        return (result == GL_TRUE);
    }

    bool CShader::VerifyProgramLinking(GLuint programID, std::string name) {
        std::vector<char> programErrorMsg;
        GLint result;
        GLint infoLen;

        glGetProgramiv(programID, GL_LINK_STATUS, &result);
        glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLen);

        programErrorMsg.resize(infoLen);
        glGetProgramInfoLog(programID, infoLen, NULL, &programErrorMsg[0]);

        if(result != GL_TRUE)
            std::cerr << name << ": " << &programErrorMsg[0] << std::cerr;

        return (result == GL_TRUE);
    }

    void CShader::MapShaderUniforms(GLuint programID, std::string& shaderCode) {
        /*** Variables ***/
        std::stringstream stream;
        std::string uniform;

        /*** Detecting and mapping ***/
        stream.str(shaderCode);
        while(stream.good()) {
            stream >> uniform;
            if(uniform == "uniform") {
                stream >> uniform; // reading type of uniform
                stream >> uniform; // reading name of uniform

                /// Deleting semicolon at the end
                if(uniform[uniform.size()-1] == ';')
                    uniform.erase(uniform.size() - 1);

                /// Insertin uniform location to database
                m_uniforms[uniform] = glGetUniformLocation(programID, uniform.c_str());
                //std::cout << "m_uniforms[" << uniform << "] = " << m_uniforms[uniform] << std::endl;
            }
        }
    }

}
