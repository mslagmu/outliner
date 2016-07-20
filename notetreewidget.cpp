#include "notetreewidget.h"
#include "ui_outlinerviewer.h"
#include <QDebug>
#include<QContextMenuEvent>

noteTreeWidget::noteTreeWidget(QWidget *parent):QTreeWidget(parent)
{

}

noteTreeWidget::~noteTreeWidget()
{

}

void noteTreeWidget::setEnableButton(int enable) {
    ui->actionAddItem->setEnabled(enable);
    ui->actionRemoveItem->setEnabled(enable);
    ui->actionAddChild->setEnabled(enable);
    ui->treeToolBar->setVisible(enable);
}

void noteTreeWidget::focusInEvent(QFocusEvent * e){
    emit focus();
}

void noteTreeWidget::dropEvent(QDropEvent *event){
    QTreeWidgetItem * c =currentItem();
    QTreeWidget::dropEvent(event);
    dynamic_cast<noteItem*>(currentItem())->manageIcon();
    dynamic_cast<noteItem*>(c->parent())->manageIcon();
}

void noteTreeWidget::contextMenuEvent(QContextMenuEvent *event){
    QMenu menu(this);
    menu.addAction(ui->actionAddItem);
    menu.addAction(ui->actionAddChild);
    menu.addSeparator();
    menu.addAction(ui->actionRemoveItem);
    menu.exec(event->globalPos());
}
