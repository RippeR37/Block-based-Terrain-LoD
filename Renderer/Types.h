#ifndef RENDERINGTYPES_H_INCLUDED
#define RENDERINGTYPES_H_INCLUDED

namespace Rendering {

    struct Vertex {
        Vertex() { }
        Vertex(float a, float b, float c, float d) : x(a), y(b), z(c), w(d) { }

        float x, y, z, w;
    };

}

#endif // RENDERINGTYPES_H_INCLUDED
