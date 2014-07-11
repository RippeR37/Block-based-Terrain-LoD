#ifndef GUITYPES_H_INCLUDED
#define GUITYPES_H_INCLUDED

#include <gl/glew.h>

namespace GUI {

    enum VERTEX_ATTRIB {
        ATTRIB_POS      = 0,    // vec4(x, y, type, state/c_b)
        ATTRIB_TEX      = 1,    // vec4(s, t,  c_r,       c_g)
    };

    enum ELEMENT_TYPE {
        TYPE_TEX        = 0,    // text
        TYPE_BUTTON     = 1,    // button
        TPYE_CHECKBOX   = 2,    // checkbox
        TYPE_TEXTINPUT  = 3,    // input box for text etc.
    };

    enum ELEMENT_STATE {
        STATE_NORMAL    = 0,    // normal, unhoverd etc.
        STATE_EXTRA     = 1,    // extra, hoverd, etc.
    };

    enum STYLE_ALIGNMENT {
        ALIGN_LEFT      = 0,    // align text to left
        ALIGN_RIGHT     = 1,    // align text to right
        ALIGN_CENTER    = 2,    // align text to center
    };

    struct VertexPos {
        VertexPos(GLfloat a, GLfloat b, GLfloat c, GLfloat d) :
            x(a), y(b), type(c), state(d) { }

        GLfloat x, y, type, state;
    };

    struct VertexTex {
        VertexTex(GLfloat pX, GLfloat pY, GLfloat pS, GLfloat pT) :
            x(pX), y(pY), s(pS), t(pT) { }

        GLfloat x, y, s, t;
    };

}

#endif // GUITYPES_H_INCLUDED
