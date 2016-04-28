#include "mainwindow.h"
#include <QApplication>
#include "JQUIButton.h"
#include <QGraphicsScene>
#include <QGraphicsView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QGraphicsScene *scene = new QGraphicsScene();
    for (int i = 0; i < 100; ++i){
        JQUIButton* btn = new JQUIButton();
        btn->setFrame(QRectF(i/10*60, i%10*60, 50, 50));
        btn->setTitle("Hello");
        btn->setTitleAtStatus("张凯", JQUIButtonStatusNormal,QFont("宋体",14), QColor(Qt::blue));
        btn->setBgImg(new QPixmap("D:\\My_Project\\Resource\\image\\weixin_normal.png"));
        scene->addItem(btn);
    }

    QGraphicsView *view = new QGraphicsView();
    view->setScene(scene);
    view->show();

    return a.exec();
}
