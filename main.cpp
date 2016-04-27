#include "mainwindow.h"
#include <QApplication>
#include "JQUIButton.h"
#include <QGraphicsScene>
#include <QGraphicsView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QGraphicsScene *scene = new QGraphicsScene();
    JQUIButton* btn = new JQUIButton();
    btn->setTitle("Hello, zk");
    scene->addItem(btn);
    QGraphicsView *view = new QGraphicsView();
    view->setScene(scene);
    view->show();

    return a.exec();
}
