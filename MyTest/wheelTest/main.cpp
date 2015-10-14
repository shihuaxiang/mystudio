#include "mainwindow.h"
#include <QApplication>
#include "graphics_view_zoom.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    //MainWindow w;
    //w.show();

    QGraphicsScene scene;
    scene.addText("GraphicsView rotated clockwise");

    QGraphicsView view(&scene);
    //view.rotate(90); // the text is rendered with a 90 degree clockwise rotation
    view.resize(400,400);

    Graphics_view_zoom* z = new Graphics_view_zoom(&view);
    z->set_modifiers(Qt::NoModifier);

    view.show();

    return a.exec();
}
