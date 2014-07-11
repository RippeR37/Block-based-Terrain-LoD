#ifndef TERRAIN_H_INCLUDED
#define TERRAIN_H_INCLUDED

#include <string>
#include <vector>
#include <gl/glew.h>

namespace Rendering {

    struct LoDTile {
        LoDTile() : first((GLvoid*)0), count(0) { }
        LoDTile(GLvoid* f, unsigned int c) : first(f), count(c) { }

        GLvoid* first;
        unsigned int count;
    };

    class CTerrain {
        public:
            CTerrain();
            ~CTerrain();

            void Init();
            void Render();
            void Update();
            void LoadTerrain(std::string filePath, unsigned int width, unsigned int height, int LODlevel);

            char& Heightmap() { return *m_heightmap; }

        private:
            int m_indices;
            int m_width;
            int m_height;
            int m_tileSize;
            int m_distance;
            int m_LoDlevel;
            int m_distanceMin;
            int m_tilesH;
            int m_tilesV;

            float       m_heightmapdensity;
            char*       m_heightmap;

            GLuint      m_vaoID;
            GLuint      m_vboID;
            GLuint      m_iboID;

            std::vector<unsigned int>   m_tile_count;
            std::vector<GLvoid*>        m_tile_offset;

            std::vector< std::vector< std::vector<LoDTile> > >  m_LoD;
    };

}

#endif // TERRAIN_H_INCLUDED
