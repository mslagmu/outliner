#include "colorbox.h"
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>

ColorBox::ColorBox(QWidget *parent):QWidget(parent)
{
    setMinimumHeight(20);
    setMinimumWidth(150);
    colors << "black" << "white" << "red" << "blue" << "green" << "yellow";
}


void ColorBox::paintEvent(QPaintEvent *event) {
    QPainter p(this);
    int nbcolors = colors.length();
    int h = height();
    int w = width();
    int l = w / nbcolors;

    for(int i = 0 ; i < nbcolors;i++) {
        int x = l * i;
        p.fillRect(QRect(x+2,0,x+l-2,h),QColor(colors.at(i)));
    }

}

void ColorBox::mousePressEvent(QMouseEvent *event){
    int x = event->x();
    int nbcolors = colors.length();
    int w = width();
    int l = w / nbcolors;
    int index = x / l;
    emit colorSelected(QColor(colors.at(index)));
    QWidget::mouseMoveEvent(event);
}


