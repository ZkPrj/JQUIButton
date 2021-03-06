#include <QCursor>
#include "JQUIButton.h"

#define JQUIBTN_DEFAULT_H 21
#define JQUIBTN_DEFAULT_W 42
#define JQUIBTN_DEFAULT_TITLE "Button"
#define JQUIBTN_DEFAULT_COLOR  (QColor(Qt::red))

JQUIButton::JQUIButton()
{
    QRectF lRect = QRectF(0.0, 0.0, JQUIBTN_DEFAULT_W, JQUIBTN_DEFAULT_H);
    setCursor(Qt::OpenHandCursor);
    init(lRect);
}

JQUIButton::JQUIButton(QRectF iFrame){
    init(iFrame);
}

void JQUIButton::init(QRectF iFrame){
    _frame = iFrame;
    _titleForNormal = JQUIBTN_DEFAULT_TITLE;
    _titleForDown = _titleForNormal;
    _fontColorForNormal = JQUIBTN_DEFAULT_COLOR;
    _fontColorForDown = _fontColorForNormal;
    _status = JQUIButtonStatusNormal;
    _imgForBg = NULL;
    _imgForNormal = NULL;
    _imgForDown = NULL;
    this->delegate = NULL;
}

void JQUIButton::setFrame(QRectF iFrame){
    this->_frame = iFrame;
    this->setPos(_frame.x(), _frame.y());
}

QRectF JQUIButton::getFrame(){
    return this->_frame;
}

void JQUIButton::setTitle(QString iTitle){
    this->_titleForNormal = iTitle;
    this->update();
}

QString JQUIButton::getTitle(){
    return this->_titleForNormal;
}

void JQUIButton::setBgImg(QPixmap *iPixmap){
    this->_imgForBg = iPixmap;
}

QPixmap* JQUIButton::getBgImg(){
    return this->_imgForBg;
}

void JQUIButton::setImgAtStatus(QPixmap *iPixmap, JQUIButtonStatus iStatus){
    if (iStatus == JQUIButtonStatusNormal){
        this->_imgForNormal = iPixmap;
    }else{
        this->_imgForDown = iPixmap;
    }
}

void JQUIButton::setTitleAtStatus(QString iTitle, JQUIButtonStatus iStatus, QFont iFont, QColor iColor){
    if (iStatus == JQUIButtonStatusNormal){
        this->_titleForNormal = iTitle;
        this->_fontForNormal = iFont;
        this->_fontColorForNormal = iColor;
    }else{
        this->_titleForDown = iTitle;
        this->_fontForDown = iFont;
        this->_fontColorForDown = iColor;
    }
    this->update();
}

QRectF JQUIButton::boundingRect() const{
    return QRectF(-1 * _frame.width() / 2, -1 * _frame.height() / 2, _frame.width(), _frame.height());
}

void JQUIButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if  (_imgForBg){
        QPixmap lBgImg = _imgForBg->scaled(_frame.size().toSize(), Qt::KeepAspectRatio);
        painter->drawPixmap(boundingRect().toRect(), lBgImg);
    }

    if (_status == JQUIButtonStatusNormal){
        if (_imgForNormal){
            QPixmap lNormalImg = _imgForNormal->scaled(_frame.size().toSize(), Qt::KeepAspectRatio);
            painter->drawPixmap(boundingRect().toRect(), lNormalImg);
        }else{
            painter->setPen(_fontColorForNormal);
            painter->setFont(_fontForNormal);
            painter->drawText(boundingRect().toRect(), Qt::AlignCenter, _titleForNormal);
        }
    }else{
        if (_imgForDown){
            QPixmap lDownImg = _imgForDown->scaled(_frame.size().toSize(), Qt::KeepAspectRatio);
            painter->drawPixmap(boundingRect().toRect(), lDownImg);
        }else if (_imgForNormal){
            QPixmap lNormalImg = _imgForNormal->scaled(_frame.size().toSize(), Qt::KeepAspectRatio);
            painter->drawPixmap(boundingRect().toRect(), lNormalImg);
        }else if (_titleForDown.count() > 0){
            painter->setPen(_fontColorForDown);
            painter->setFont(_fontForDown);
            painter->drawText(boundingRect().toRect(), Qt::AlignCenter, _titleForNormal);
        }else{
            painter->setPen(_fontColorForNormal);
            painter->setFont(_fontForNormal);
            painter->drawText(boundingRect().toRect(), Qt::AlignCenter, _titleForNormal);
        }
    }
}

void JQUIButton::mousePressEvent(QGraphicsSceneMouseEvent *event){
    setCursor(Qt::ClosedHandCursor);
    _status = JQUIButtonStatusDown;
    if (delegate){
        this->delegate->handlePressDown(this, event);
    }
    update();
}

void JQUIButton::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
   setCursor(Qt::OpenHandCursor);
   _status = JQUIButtonStatusNormal;
   if (delegate){
        this->delegate->handleReleaseUp(this, event);
    }
   update();
}


