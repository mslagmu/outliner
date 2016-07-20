#ifndef COLORBOX_H
#define COLORBOX_H
#include <QWidget>



class ColorBox : public QWidget
{
    Q_OBJECT

public:
    ColorBox(QWidget * parent=0);


protected:
    void paintEvent(QPaintEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);

signals:
   void colorSelected(QColor color);


private:
    QStringList colors;
};



#endif // COLORBOX_H
