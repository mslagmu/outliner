#ifndef NOTETREEWIDGET_H
#define NOTETREEWIDGET_H

#include <QTreeWidget>
#include "noteitem.h"

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

        noteItem * currentItem() const {
            return dynamic_cast<noteItem*>(QTreeWidget::currentItem());
        };

    signals:
        void focus();


};

#endif // NOTETREEWIDGET_H
