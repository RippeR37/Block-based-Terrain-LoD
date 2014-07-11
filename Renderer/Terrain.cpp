#include "Terrain.h"
#include "Types.h"
#include "../Game.h"

#include <vector>
#include <fstream>
#include <iostream>

namespace Rendering {

    CTerrain::CTerrain() {
        m_heightmap = NULL;

        m_heightmapdensity = 1.0f;  /// distance between each vertex
    }

    CTerrain::~CTerrain() {
        if(m_heightmap != NULL)
            delete[] m_heightmap;
    }

    void CTerrain::Init() {
        /*** Creating VAO, VBO and IBO ***/
        glGenVertexArrays(1, &m_vaoID);
        glGenBuffers(1, &m_vboID);
        glGenBuffers(1, &m_iboID);

        std::cout << "RDR::Terrain | Loading terrain... ";
        //LoadTerrain("assets/levels/test/heightmap_big.raw", 1024, 1024, 5);
        LoadTerrain("assets/levels/test/heightmap_big2.raw", 2*1024, 2*1024, 5);
        std::cout << "done." << std::endl;
    }

    void CTerrain::Render() {
        Update();

        /// Bind VAO
        glBindVertexArray(m_vaoID);

        /// Render elements
        static GLuint UID_COLOR = CGame::Get().Renderer().Shader().GetUniformID("COL");

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        glUniform3f(UID_COLOR, 0.0f, 0.0f, 0.0f);
        glMultiDrawElements(GL_TRIANGLES,
                  (GLsizei*)&m_tile_count[0],
                            GL_UNSIGNED_INT,
            (const GLvoid**)&m_tile_offset[0],
                   (GLsizei)m_tile_count.size());

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        /// Unbind VAO
        glBindVertexArray(0);
    }

    void CTerrain::Update() {
        static int dist;
        static int level;
        static glm::vec2 camPos;

        /// Clear LOD tiles
        m_tile_count.clear();
        m_tile_offset.clear();

        /// Update LOD tiles
        camPos = CGame::Get().Renderer().Camera().getPos2D() * m_heightmapdensity;
        for(int y = 0; y < m_tilesV; ++y) {
            for(int x = 0; x < m_tilesH; ++x) {
                /// Calculate distance between terrain chunk and camera
                dist  = glm::distance(camPos, glm::vec2((x + 0.5f) * m_tileSize, (y + 0.5f) * m_tileSize));

                /// Calculate terrain chunk's level of details using distance
                level = m_LoDlevel - (dist / 80);
                (level < 0)          ? level = 0 : level;
                (level > m_LoDlevel) ? level = m_LoDlevel : level;

                /// Insert terrains chunk to containers
                m_tile_count.push_back(m_LoD[level][y][x].count);
                m_tile_offset.push_back(m_LoD[level][y][x].first);
            }
        }
    }

    void CTerrain::LoadTerrain(std::string filePath, unsigned int width, unsigned int height, int pLoDlevel) {
        /// Variables
        std::vector<Vertex> vertices;
        std::vector<GLuint> indices;
        std::fstream fileStream;

        m_width  = width;
        m_height = height;

        /// Implementation
        glBindVertexArray(m_vaoID);
        glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iboID);

        if(m_heightmap != NULL)
            delete[] m_heightmap;

        m_heightmap = new char[width*height];

        /// Opening file to read
        fileStream.open(filePath.c_str(), std::fstream::in | std::fstream::binary);
        if(fileStream.is_open() == false) {
            std::cerr << "RDR::Terrain | Failed to load terrain heightmap" << std::endl;
            return;
        }

        /// Read data
        fileStream.read(m_heightmap, width*height);
        if(!fileStream) {
            std::cerr << "RDR::Terrain | Failed to read heightmap" << std::endl;
            fileStream.close();
            return;
        }

        /// Close file
        fileStream.close();

        /// Calculate VBO data
        vertices.resize(width*height);
        int p;
        unsigned char v;
        for(unsigned int z = 0; z < height; ++z) {
            for(unsigned int x = 0; x < width; ++x) {
                p = z * height + x;
                v = (unsigned char)m_heightmap[p];
                vertices[p] = Vertex((float)x, (float)(v) / 256.0f, (float)z, m_heightmapdensity);
            }
        }

        /// Calculate IBO data for each LoD
        unsigned int count;
        int distance;
        int p1, p2, p3, p4;                 /// (p1, p2) - start of given quad,
                                            /// (p3, p4) -  end  of given quad

        /// Setting up variables
        m_LoDlevel    = pLoDlevel;
        m_tileSize    = (1 << m_LoDlevel);
        m_distance    = (1 << m_LoDlevel);
        m_distanceMin = 1;
        m_tilesH      = (int)(ceil((double)(width  - m_distanceMin - m_tileSize) / (double)(m_tileSize))) + 1;
        m_tilesV      = (int)(ceil((double)(height - m_distanceMin - m_tileSize) / (double)(m_tileSize))) + 1;
        distance      = m_distance; // temp distance which will be modyfied during LoD database construction

        /// Database construction
        m_LoD.resize(m_LoDlevel + 1);
        for(int L = 0; L <= m_LoDlevel; L += 1) {

            m_LoD[L].resize(m_tilesV);
            for(int V = 0; V < m_tileSize * m_tilesV; V += m_tileSize) {

                m_LoD[L][V/m_tileSize].resize(m_tilesH);
                for(int H = 0; H < m_tileSize * m_tilesH; H += m_tileSize) {

                    count = 0;
                    m_LoD[L][V/m_tileSize][H/m_tileSize].first = (GLvoid*)(indices.size() * sizeof(unsigned int));

                    for(int y = 0; y <= m_tileSize - distance; y += distance) {         /// WARNING (<= instead <)
                        for(int x = 0; x <= m_tileSize - distance; x += distance) {     /// WARNING (<= instead <)

                            p1 = H + x;
                            p2 = V + y;
                            p3 = (H + x + distance >= m_width)  ? m_width - 1  : H + x + distance;
                            p4 = (V + y + distance >= m_height) ? m_height - 1 : V + y + distance;

                            /// Triangle #1
                            indices.push_back(p2 * width + p1);
                            indices.push_back(p4 * width + p1);
                            indices.push_back(p2 * width + p3);

                            /// Triangle #2
                            indices.push_back(p2 * width + p3);
                            indices.push_back(p4 * width + p1);
                            indices.push_back(p4 * width + p3);

                            count += 6;
                        }
                    }

                    m_LoD[L][V/m_tileSize][H/m_tileSize].count = count;
                }
            }
            distance /= 2;
        }

        /// Binding buffers
        glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
        glBufferData(GL_ARRAY_BUFFER, width*height*sizeof(Vertex), &vertices[0], GL_DYNAMIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iboID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_DYNAMIC_DRAW);
        m_indices = indices.size();

        /// Cleaning up
        glBindVertexArray(0);
    }

}
