#include "notetreewidget.h"
#include "ui_outlinerviewer.h"
#include <QDebug>
#include<QContextMenuEvent>

void manageIcon(QTreeWidgetItem *i) {
    int nb = i->childCount();
    if (nb > 0) {
        i->setIcon(0,QIcon::fromTheme("folder"));
    } else {
        i->setIcon(0,QIcon::fromTheme("text-x-generic"));
    }
}

QDataStream & operator<< (QDataStream & out, QTreeWidgetItem * n){
    out << n->text(0);
    out << n->data(0,htmlRole).toString();
    out << n->childCount();

    for(int i=0; i< n->childCount();i++){
        out <<  (n->child(i));
    }
    return out;
}

QDataStream & operator>>(QDataStream & in, QTreeWidgetItem * n){
    QString a,b;
    int nb;
    in >> a >> b >> nb;
    n->setText(0,a);
    n->setData(0,htmlRole,b);

    for(int i = 0;i<nb;i++) {
        QTreeWidgetItem * current = createNewItem();
        in >> current;
        n->addChild(current);
    }
    manageIcon(n);
    return in;
}





QTreeWidgetItem * createNewItem(){
    QTreeWidgetItem * n = new QTreeWidgetItem();
    n->setText(0,"");
    n->setData(0,htmlRole,"");
    n->setFlags(n->flags() | Qt::ItemIsEditable);
    manageIcon(n);
    return n;
}


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
    manageIcon(c);
    manageIcon(c->parent());
}

void noteTreeWidget::contextMenuEvent(QContextMenuEvent *event){
    QMenu menu(this);
    menu.addAction(ui->actionAddItem);
    menu.addAction(ui->actionAddChild);
    menu.addSeparator();
    menu.addAction(ui->actionRemoveItem);
    menu.exec(event->globalPos());
}
