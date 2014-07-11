#include "VAO.h"

namespace OpenGL {

    CVAO::CVAO() {
        m_dataType = GL_TRIANGLES;
    }

    CVAO::~CVAO() {
        Dispose();
    }

    void CVAO::Init() {
        glGenVertexArrays(1, &m_vaoID);
        glBindVertexArray(m_vaoID);

        glEnableVertexAttribArray(VAO_ATTR_VERTICES);
        glEnableVertexAttribArray(VAO_ATTR_NORMALS);
        glEnableVertexAttribArray(VAO_ATTR_TEXCOORDS);

        glGenBuffers(1, &m_vboID);
    }

    void CVAO::Begin() {
        Bind();
    }

    void CVAO::End() {
        glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
        glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(Vertex), &m_vertexData[0], GL_STATIC_DRAW);

        glVertexAttribPointer(VAO_ATTR_VERTICES,    3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, pos));
        glVertexAttribPointer(VAO_ATTR_NORMALS,     3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, nor));
        glVertexAttribPointer(VAO_ATTR_TEXCOORDS,   2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, tex));

        Unbind();
    }

    void CVAO::Draw() {
        Bind();

        glDrawArrays(m_dataType, 0, m_vertexData.size());

        Unbind();
    }

    void CVAO::Dispose() {
        Bind();

        glDisableVertexAttribArray(VAO_ATTR_VERTICES);
        glDisableVertexAttribArray(VAO_ATTR_NORMALS);
        glDisableVertexAttribArray(VAO_ATTR_TEXCOORDS);

        glDeleteBuffers(1, &m_vboID);
        glDeleteVertexArrays(1, &m_vaoID);
    }


    void CVAO::Bind() {
        glBindVertexArray(m_vaoID);
    }

    void CVAO::Unbind() {
        glBindVertexArray(0);
    }


    void CVAO::AddVertex(Vertex vertex) {
        m_vertexData.push_back(vertex);
    }

    //void CVAO::LoadFromOBJ(std::string filePath) {
    //
    //}

}
