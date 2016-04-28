#ifndef JQUIBUTTON_H
#define JQUIBUTTON_H
/**
  定义类似ios中uikit中的uibutton
  Function:
  1. 当前状态（正常状态和按下状态）
  2. 不同状态下需要显示的图片
  3. 能显示背景图片
  4. 不同状态下需要显示的文字
  5. 文字颜色、文字字体、文字大小
  6. 能够通过代理模式相应鼠标点击事件
  7. 设置按钮大小和位置
**/

#include <QGraphicsItem>
#include <QPixmap>
#include <QString>
#include <QRectF>
#include <QFont>
#include <QColor>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>

typedef enum{
    JQUIButtonStatusNormal = 0,
    JQUIButtonStatusDown
}JQUIButtonStatus;

class JQUIButton;

class JQUIButtonDelegate : public QObject{
public :
    virtual void handlePressDown(JQUIButton* iSender, QGraphicsSceneMouseEvent* iEvent) = 0;
    virtual void handleReleaseUp(JQUIButton* iSender, QGraphicsSceneMouseEvent* iEvent) = 0;
};

class JQUIButton : public QGraphicsItem
{
public:
    JQUIButton();
    JQUIButton(QRectF iFrame);

    void setFrame(QRectF iFrame);
    QRectF getFrame();
    void setTitle(QString iTitle);
    QString getTitle();
    void setBgImg(QPixmap* iPixmap);
    QPixmap* getBgImg();
    void setImgAtStatus(QPixmap* iPixmap, JQUIButtonStatus iStatus);
    void setTitleAtStatus(QString iTitle, JQUIButtonStatus iStatus, QFont iFont, QColor iColor);
    virtual QRectF	boundingRect() const;
    virtual void	paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
public:
    JQUIButtonDelegate* delegate;
private:
    QPixmap* _imgForDown;
    QPixmap* _imgForNormal;
    QPixmap* _imgForBg;
    QString  _titleForNormal;
    QString  _titleForDown;
    QRectF   _frame;
    QFont    _fontForNormal;
    QFont    _fontForDown;
    QColor   _fontColorForNormal;
    QColor   _fontColorForDown;
    JQUIButtonStatus _status;
private:
    void init(QRectF iFrame);
};

#endif // JQUIBUTTON_H
