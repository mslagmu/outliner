#ifndef NOTETREEWIDGET_H
#define NOTETREEWIDGET_H

#include <QTreeWidget>
//#include "noteitem.h"

namespace Ui {
class OutLinerViewer;
}


class noteTreeWidget : public QTreeWidget
{
    Q_OBJECT
    public:
        explicit noteTreeWidget(QWidget *parent=0);
        ~noteTreeWidget();
        Ui::OutLinerViewer *ui;
        virtual void focusInEvent(QFocusEvent * e);
        void setEnableButton(int enable);
        void dropEvent(QDropEvent *event);
        void contextMenuEvent(QContextMenuEvent *event);

    signals:
        void focus();


};

void manageIcon(QTreeWidgetItem * i);
QTreeWidgetItem * createNewItem();

QDataStream & operator>>(QDataStream & in, QTreeWidgetItem * n);
QDataStream & operator<< (QDataStream & out, QTreeWidgetItem * n);

#define htmlRole 20

#endif // NOTETREEWIDGET_H
