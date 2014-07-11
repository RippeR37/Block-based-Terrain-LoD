#ifndef SHADER_H_INCLUDED
#define SHADER_H_INCLUDED

#include "../../Common/File.h"

#include <map>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


namespace OpenGL {

    class CShader {
        public:
            CShader();
            ~CShader();

            void LoadShader(std::string vsPath, std::string fsPath);

            GLuint GetUniformID(std::string uniformName);
            GLuint GetID()          { return m_programID; }

        private:
            /*** Methods ***/
            static bool VerifyShaderCompilation(GLuint shaderID, std::string name);
            static bool VerifyProgramLinking(GLuint programID, std::string name);
            void MapShaderUniforms(GLuint programID, std::string& shaderCode);

            /*** Variables ***/
            GLuint                          m_programID;
            std::map<std::string, GLuint>   m_uniforms;
    };

}

#endif // SHADER_H_INCLUDED
