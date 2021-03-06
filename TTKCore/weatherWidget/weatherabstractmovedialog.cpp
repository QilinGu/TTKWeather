#include "weatherabstractmovedialog.h"

#include <QMouseEvent>
#include <QBitmap>
#include <QPainter>

WeatherAbstractMoveDialog::WeatherAbstractMoveDialog(QWidget *parent)
    : QDialog(parent)
{
    ///Remove the title bar
    setWindowFlags( Qt::Window | Qt::FramelessWindowHint );
    m_leftButtonPress = false;
}

WeatherAbstractMoveDialog::~WeatherAbstractMoveDialog()
{

}

void WeatherAbstractMoveDialog::drawWindowRoundedRect(QWidget *widget)
{
    QBitmap bmp(widget->size());
    bmp.fill();
    QPainter p(&bmp);
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::black);
    p.drawRoundedRect(bmp.rect(),4,4);
    widget->setMask(bmp);
}

void WeatherAbstractMoveDialog::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
    if( event->button() == Qt::LeftButton )///Press the left key
    {
        m_leftButtonPress = true;
    }
    m_pressAt = event->globalPos();
}

void WeatherAbstractMoveDialog::mouseMoveEvent(QMouseEvent *event)
{
    QWidget::mouseMoveEvent(event);
    if( !m_leftButtonPress )///Not press the left key
    {
        event->ignore();
        return;
    }
    int xpos = event->globalX() - m_pressAt.x();
    int ypos = event->globalY() - m_pressAt.y();
    m_pressAt = event->globalPos();
    move( this->x()+xpos, this->y()+ypos);
}

void WeatherAbstractMoveDialog::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mouseReleaseEvent(event);
    m_pressAt = event->globalPos();
    m_leftButtonPress = false;
}
