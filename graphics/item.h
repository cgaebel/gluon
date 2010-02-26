#ifndef Item_H
#define Item_H
#include "transform.h"
#include "mesh.h"
#include "glpainter.h"
#include "texture.h"
#include "gluon_graphics_export.h"

namespace GluonGraphics
{
    class Engine;
    class GLUON_GRAPHICS_EXPORT Item : public Transform
    {

    public:
        Item(Mesh * mesh= 0, QObject* parent=0);
        Item(QSizeF size){init();}
        virtual void paintGL();
        void setColor(const QColor& col){m_color=col;}
        QColor color(){return m_color;}

    protected:
        void init();

    private:
        Mesh * m_mesh;
        GLPainter * m_painter;
        Texture * m_texture;
        QColor m_color;
    };

}
#endif // Item_H
