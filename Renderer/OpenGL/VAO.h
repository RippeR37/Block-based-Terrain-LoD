#ifndef VAO_H_INCLUDED
#define VAO_H_INCLUDED

#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace OpenGL {

    enum VAO_ATTR {
        VAO_ATTR_VERTICES   = 0,
        VAO_ATTR_NORMALS    = 1,
        VAO_ATTR_TEXCOORDS  = 2,
    };

    enum OBJ_FACE_FORMAT {
        OBJ_VNT = 0,
        OBJ_VT  = 1,
    };

    struct Vertex {
        Vertex(float x, float y, float z, float nx, float ny, float nz, float u, float v)
                : pos(glm::vec3(x,y,z)), nor(glm::vec3(nx,ny,nz)), tex(glm::vec2(u,v)) { }

        glm::vec3 pos;
        glm::vec3 nor;
        glm::vec2 tex;
    };

  //template <typename T>
    class CVAO {
        public:
            CVAO();
            ~CVAO();

            void Init();
            void Begin();
            void End();
            void Draw();
            void Dispose();

            void Bind();
            void Unbind();

            void AddVertex(Vertex vertex);
          //void LoadFromOBJ(std::string filePath);

        private:
            GLuint      m_vaoID;
            GLuint      m_vboID;
          //GLuint      m_iboID;
            GLuint      m_dataType;

            std::vector<Vertex>     m_vertexData;
    };

}

#endif // VAO_H_INCLUDED
